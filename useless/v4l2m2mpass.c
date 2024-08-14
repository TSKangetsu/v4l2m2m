#include "v4l2m2mops.h"

MODULE_LICENSE("GPL");

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
	if (err)
		goto v4l2_free;
	//============================================//
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
v4l2_free:
	kfree(v4l2m2mdev);
	video_device_release(vdev);
	return err;
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
