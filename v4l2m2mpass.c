#include "v4l2m2mops.h"

MODULE_LICENSE("GPL");

#define VMName "v4l2passer"

struct v4l2_m2m_device {
	struct v4l2_device v4l2_dev;
	struct video_device vdev;
	struct mutex lock;
	struct vb2_queue vb2_queue;
	struct list_head buffer_list;
	spinlock_t slock;
	int streaming;
	atomic_t num_inst;
	struct mutex dev_mutex;
};

static const struct v4l2_ioctl_ops v4l2m2m_ioctl_ops = {
	.vidioc_querycap = v4l2_ioctl_querycap,
	.vidioc_enum_fmt_vid_cap = v4l2_ioctl_enum_fmt_vid_cap,
	.vidioc_enum_fmt_vid_out = v4l2_ioctl_enum_fmt_vid_out,
	.vidioc_g_fmt_vid_cap = v4l2_ioctl_g_fmt_vid_cap,
	.vidioc_g_fmt_vid_out = v4l2_ioctl_g_fmt_vid_out,
	.vidioc_s_fmt_vid_cap = v4l2_ioctl_s_fmt_vid_cap,
	.vidioc_s_fmt_vid_out = v4l2_ioctl_s_fmt_vid_out,
	.vidioc_try_fmt_vid_cap = v4l2_ioctl_try_fmt_vid_cap,
	.vidioc_try_fmt_vid_out = v4l2_ioctl_try_fmt_vid_out,
	.vidioc_reqbufs = v4l2_ioctl_reqbufs,
	.vidioc_querybuf = v4l2_ioctl_querybuf,
	.vidioc_qbuf = v4l2_ioctl_qbuf,
	.vidioc_dqbuf = v4l2_ioctl_dqbuf,
	.vidioc_streamon = v4l2_ioctl_streamon,
	.vidioc_streamoff = v4l2_ioctl_streamoff,
};

static const struct v4l2_file_operations v4l2m2m_fops = {
	.owner = THIS_MODULE,
	.open = v4l2m2m_open,
	.release = v4l2m2m_release,
	// .mmap = v4l2_m2m_fop_mmap,
	.unlocked_ioctl = video_ioctl2,
	// .poll = v4l2_m2m_fop_poll,
};

static void v4l2m2m_device_release(struct video_device *vdev)
{
	struct v4l2_m2m_device *dev =
		container_of(vdev, struct v4l2_m2m_device, vdev);

	v4l2_device_unregister(&dev->v4l2_dev);
	kfree(dev);
}

static const struct video_device v4l2m2m_videodev = {
	.name = VMName,
	.vfl_dir = VFL_DIR_M2M,
	.fops = &v4l2m2m_fops,
	.ioctl_ops = &v4l2m2m_ioctl_ops,
	.minor = -1,
	.release = v4l2m2m_device_release,
	.device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_M2M,
};

static void v4l2m2m_dev_release(struct device *dev)
{
}

static struct platform_device v4l2m2mp = { .name = VMName,
					   .dev.release = v4l2m2m_dev_release };

static int v4l2m2m_probe(struct platform_device *pdev)
{
#if LOGLEVEL <= 1
	printk("[V4L2M2M] check module probe 1");
#endif
	//============================================//
	int err;
	struct video_device *vdev;
	//============================================//
	struct v4l2_m2m_device *v4l2m2mdev =
		kzalloc(sizeof(struct v4l2_m2m_device), GFP_KERNEL);
	if (!v4l2m2mdev)
		return -ENOMEM;

	err = v4l2_device_register(&pdev->dev, &v4l2m2mdev->v4l2_dev);
	if (err)
		goto error_free;
	//============================================//
	atomic_set(&v4l2m2mdev->num_inst, 0);
	mutex_init(&v4l2m2mdev->dev_mutex);
	v4l2m2mdev->vdev = v4l2m2m_videodev;
	vdev = &v4l2m2mdev->vdev;
	vdev->lock = &v4l2m2mdev->dev_mutex;
	vdev->v4l2_dev = &v4l2m2mdev->v4l2_dev;
	err = video_register_device(&v4l2m2mdev->vdev, VFL_TYPE_VIDEO, -1);
	if (err) {
		kfree(v4l2m2mdev);
		video_device_release(vdev);
		return err;
	}
	//============================================//
	printk("check here");
	video_set_drvdata(vdev, v4l2m2mdev);
	platform_set_drvdata(pdev, v4l2m2mdev);
	//============================================//
#if LOGLEVEL <= 1
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
	video_unregister_device(&dev->vdev);
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
