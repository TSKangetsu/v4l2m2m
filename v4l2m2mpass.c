#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/videodev2.h>
#include <linux/vmalloc.h>
#include <media/v4l2-device.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-core.h>
#include <media/videobuf2-vmalloc.h>

#include <linux/platform_device.h>

MODULE_LICENSE("GPL");

#define EXAMPLE_WIDTH 640
#define EXAMPLE_HEIGHT 480
#define EXAMPLE_PIXEL_FORMAT V4L2_PIX_FMT_YUYV
#define LOGLEVEL 1

#define VMName "v4l2passer"

struct v4l2_m2m_device {
	struct v4l2_device v4l2_dev;
	struct video_device *vdev;
	struct mutex lock;
	struct vb2_queue vb2_queue;
	struct list_head buffer_list;
	spinlock_t slock;
	int streaming;
};

struct v4l2_m2m_buffer {
	struct vb2_v4l2_buffer vb;
	struct list_head list;
};

static const struct v4l2_file_operations v4l2_ops = {

};

static void v4l2m2m_dev_release(struct device *dev)
{
}

static struct platform_device v4l2m2mp = { .name = VMName,
					   .dev.release = v4l2m2m_dev_release };

static int v4l2m2m_probe(struct platform_device *pdev)
{
#ifdef LOGLEVEL <= 1
	printk("[V4L2M2M] check module probe");
#endif
	int err;
	struct video_device *vdev = video_device_alloc();
	if (vdev == NULL)
		return -ENOMEM;
	//
	struct v4l2_m2m_device *v4l2m2mdev =
		kzalloc(sizeof(struct v4l2_m2m_device), GFP_KERNEL);
	//
	err = v4l2_device_register(&pdev->dev, &v4l2m2mdev->v4l2_dev);
	if (err)
		goto error_free;
	// Set dev info
	strcpy("V4L2M2MPasser", vdev->name);
	v4l2m2mdev->vdev = vdev;
	vdev->vfl_dir = VFL_DIR_M2M;
	// vdev->fops = NULL;
	// vdev->ioctl_ops = NULL;
	// vdev->lock = NULL;
	// vdev->queue = NULL;
	// vdev->prio = VIDIOC_G_PRIORITY | VIDIOC_S_PRIORITY;
	// vdev->dev_parent = NULL;
	vdev->device_caps = V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING,

	err = video_register_device(vdev, VFL_TYPE_VIDEO, 5);
	if (err) {
		kfree(v4l2m2mdev);
		video_device_release(vdev); 
		return err;
	}

	video_set_drvdata(vdev, v4l2m2mdev);
	platform_set_drvdata(pdev, v4l2m2mdev);

#ifdef LOGLEVEL <= 1
	printk("[V4L2M2M] check module inited");
#endif
	return 0;

error_free:
	kfree(v4l2m2mdev);
	return -EINVAL;
}

int v4l2m2m_remove(struct platform_device *pdev)
{
	struct v4l2_m2m_device *dev = platform_get_drvdata(pdev);
	video_unregister_device(dev->vdev);
	return 0;
}

static struct platform_driver v4l2m2m_pdrv = {
	.probe		= v4l2m2m_probe,
	.remove		= v4l2m2m_remove,
	.driver		= {
		.name	= VMName,
	},
};

int v4l2m2m_init_module(void)
{
	int ret;

	ret = platform_device_register(&v4l2m2mp);
	if (ret)
		return ret;

	ret = platform_driver_register(&v4l2m2m_pdrv);
	if (ret)
		platform_device_unregister(&v4l2m2mp);

	return ret;
	return 0;
}

void v4l2m2m_cleanup_module(void)
{
	platform_driver_unregister(&v4l2m2m_pdrv);
	platform_device_unregister(&v4l2m2mp);
}

module_init(v4l2m2m_init_module);
module_exit(v4l2m2m_cleanup_module);

MODULE_LICENSE("GPL");
