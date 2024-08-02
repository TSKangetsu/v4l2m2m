#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/videodev2.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <media/v4l2-device.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-core.h>
#include <media/videobuf2-vmalloc.h>

MODULE_LICENSE("GPL");

#define EXAMPLE_WIDTH 640
#define EXAMPLE_HEIGHT 480
#define EXAMPLE_PIXEL_FORMAT V4L2_PIX_FMT_YUYV

struct v4l2_m2m_device
{
    struct v4l2_device v4l2_dev;
    struct video_device vdev;
    struct mutex lock;
    struct vb2_queue vb2_queue;
    struct list_head buffer_list;
    spinlock_t slock;
    int streaming;
};

struct v4l2_m2m_buffer
{
    struct vb2_v4l2_buffer vb;
    struct list_head list;
};

int v4l2m2m_init_module(void)
{
    return 0;
}

void v4l2m2m_cleanup_module(void)
{
}

module_init(v4l2m2m_init_module);
module_exit(v4l2m2m_cleanup_module);

MODULE_LICENSE("GPL");
