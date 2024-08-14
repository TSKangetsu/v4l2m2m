#ifndef _V4L2M2MOPS_H
#define _V4L2M2MOPS_H

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/videodev2.h>
#include <linux/vmalloc.h>
#include <linux/platform_device.h>
#include <media/v4l2-mem2mem.h>
#include <media/v4l2-device.h>
#include <media/v4l2-ioctl.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-event.h>
#include <media/videobuf2-vmalloc.h>
#define LOGLEVEL 1
#define VMName "v4l2passer"

int v4l2m2m_open(struct file *file);
int v4l2m2m_release(struct file *file);

int v4l2_ioctl_querycap(struct file *file, void *fh,
			struct v4l2_capability *cap);
int v4l2_ioctl_enum_fmt_vid_cap(struct file *file, void *fh,
				struct v4l2_fmtdesc *f);
int v4l2_ioctl_enum_fmt_vid_out(struct file *file, void *fh,
				struct v4l2_fmtdesc *f);
int v4l2_ioctl_g_fmt_vid_cap(struct file *file, void *fh,
			     struct v4l2_format *f);
int v4l2_ioctl_g_fmt_vid_out(struct file *file, void *fh,
			     struct v4l2_format *f);
int v4l2_ioctl_s_fmt_vid_cap(struct file *file, void *fh,
			     struct v4l2_format *f);
int v4l2_ioctl_s_fmt_vid_out(struct file *file, void *fh,
			     struct v4l2_format *f);
int v4l2_ioctl_try_fmt_vid_cap(struct file *file, void *fh,
			       struct v4l2_format *f);
int v4l2_ioctl_try_fmt_vid_out(struct file *file, void *fh,
			       struct v4l2_format *f);
int v4l2_ioctl_reqbufs(struct file *file, void *fh,
		       struct v4l2_requestbuffers *b);
int v4l2_ioctl_querybuf(struct file *file, void *fh, struct v4l2_buffer *b);
int v4l2_ioctl_qbuf(struct file *file, void *fh, struct v4l2_buffer *b);
int v4l2_ioctl_dqbuf(struct file *file, void *fh, struct v4l2_buffer *b);
int v4l2_ioctl_streamon(struct file *file, void *fh, enum v4l2_buf_type i);
int v4l2_ioctl_streamoff(struct file *file, void *fh, enum v4l2_buf_type i);

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

static const struct v4l2_file_operations v4l2m2m_fops = {
	.owner = THIS_MODULE,
	.open = v4l2m2m_open,
	.release = v4l2m2m_release,
	.mmap = v4l2_m2m_fop_mmap,
	.unlocked_ioctl = video_ioctl2,
	.poll = v4l2_m2m_fop_poll,
};

static void v4l2m2m_device_release(struct video_device *vdev)
{
	struct v4l2_m2m_device *dev =
		container_of(vdev, struct v4l2_m2m_device, vdev);

	v4l2_device_unregister(&dev->v4l2_dev);
	kfree(dev);
}

static void v4l2m2m_dev_release(struct device *dev)
{
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

static struct platform_device v4l2m2mp = {
	.name = VMName,
	.dev.release = v4l2m2m_dev_release,
};

#endif