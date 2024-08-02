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

int v4l2m2m_open(struct file *file);
int v4l2m2m_release(struct file *file);

int v4l2_ioctl_querycap(struct file *file, void *fh, struct v4l2_capability *cap);
int v4l2_ioctl_enum_fmt_vid_cap(struct file *file, void *fh, struct v4l2_fmtdesc *f);
int v4l2_ioctl_enum_fmt_vid_out(struct file *file, void *fh, struct v4l2_fmtdesc *f);
int v4l2_ioctl_g_fmt_vid_cap(struct file *file, void *fh, struct v4l2_format *f);
int v4l2_ioctl_g_fmt_vid_out(struct file *file, void *fh, struct v4l2_format *f);
int v4l2_ioctl_s_fmt_vid_cap(struct file *file, void *fh, struct v4l2_format *f);
int v4l2_ioctl_s_fmt_vid_out(struct file *file, void *fh, struct v4l2_format *f);
int v4l2_ioctl_try_fmt_vid_cap(struct file *file, void *fh, struct v4l2_format *f);
int v4l2_ioctl_try_fmt_vid_out(struct file *file, void *fh, struct v4l2_format *f);
int v4l2_ioctl_reqbufs(struct file *file, void *fh, struct v4l2_requestbuffers *b);
int v4l2_ioctl_querybuf(struct file *file, void *fh, struct v4l2_buffer *b);
int v4l2_ioctl_qbuf(struct file *file, void *fh, struct v4l2_buffer *b);
int v4l2_ioctl_dqbuf(struct file *file, void *fh, struct v4l2_buffer *b);
int v4l2_ioctl_streamon(struct file *file, void *fh, enum v4l2_buf_type i);
int v4l2_ioctl_streamoff(struct file *file, void *fh, enum v4l2_buf_type i);

#endif