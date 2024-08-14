#include "v4l2m2mops.h"

static int vidioc_g_fmt(struct vim2m_ctx *ctx, struct v4l2_format *f)
{
	return 0;
}

// Function definitions
int v4l2m2m_open(struct file *file)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2m2m_open called\n");
#endif
	// Implementation goes here
	return 0;
}

int v4l2m2m_release(struct file *file)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2m2m_release called\n");
#endif
	// Implementation goes here
	return 0;
}

// Ioctl function definitions
int v4l2_ioctl_querycap(struct file *file, void *fh,
			struct v4l2_capability *cap)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2_ioctl_querycap called\n");
#endif
	strscpy(cap->driver, VMName, sizeof(cap->driver));
	strscpy(cap->card, VMName, sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info), "platform:%s", VMName);
	return 0;
}

int v4l2_ioctl_enum_fmt_vid_cap(struct file *file, void *fh,
				struct v4l2_fmtdesc *f)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2_ioctl_enum_fmt_vid_cap called\n");
#endif
	// return vidioc_g_fmt(file2ctx(file), f);
	return 0;
}

int v4l2_ioctl_enum_fmt_vid_out(struct file *file, void *fh,
				struct v4l2_fmtdesc *f)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2_ioctl_enum_fmt_vid_out called\n");
#endif
	// return vidioc_g_fmt(file2ctx(file), f);
	return 0;
}

int v4l2_ioctl_g_fmt_vid_cap(struct file *file, void *fh, struct v4l2_format *f)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2_ioctl_g_fmt_vid_cap called\n");
#endif
	// Implementation goes here
	return 0;
}

int v4l2_ioctl_g_fmt_vid_out(struct file *file, void *fh, struct v4l2_format *f)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2_ioctl_g_fmt_vid_out called\n");
#endif
	// Implementation goes here
	return 0;
}

int v4l2_ioctl_s_fmt_vid_cap(struct file *file, void *fh, struct v4l2_format *f)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2_ioctl_s_fmt_vid_cap called\n");
#endif
	// Implementation goes here
	return 0;
}

int v4l2_ioctl_s_fmt_vid_out(struct file *file, void *fh, struct v4l2_format *f)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2_ioctl_s_fmt_vid_out called\n");
#endif
	// Implementation goes here
	return 0;
}

int v4l2_ioctl_try_fmt_vid_cap(struct file *file, void *fh,
			       struct v4l2_format *f)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2_ioctl_try_fmt_vid_cap called\n");
#endif
	// Implementation goes here
	return 0;
}

int v4l2_ioctl_try_fmt_vid_out(struct file *file, void *fh,
			       struct v4l2_format *f)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2_ioctl_try_fmt_vid_out called\n");
#endif
	// Implementation goes here
	return 0;
}

int v4l2_ioctl_reqbufs(struct file *file, void *fh,
		       struct v4l2_requestbuffers *b)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2_ioctl_reqbufs called\n");
#endif
	// Implementation goes here
	return 0;
}

int v4l2_ioctl_querybuf(struct file *file, void *fh, struct v4l2_buffer *b)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2_ioctl_querybuf called\n");
#endif
	// Implementation goes here
	return 0;
}

int v4l2_ioctl_qbuf(struct file *file, void *fh, struct v4l2_buffer *b)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2_ioctl_qbuf called\n");
#endif
	// Implementation goes here
	return 0;
}

int v4l2_ioctl_dqbuf(struct file *file, void *fh, struct v4l2_buffer *b)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2_ioctl_dqbuf called\n");
#endif
	// Implementation goes here
	return 0;
}

int v4l2_ioctl_streamon(struct file *file, void *fh, enum v4l2_buf_type i)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2_ioctl_streamon called\n");
#endif
	// Implementation goes here
	return 0;
}

int v4l2_ioctl_streamoff(struct file *file, void *fh, enum v4l2_buf_type i)
{
#if LOGLEVEL <= 1
	printk(KERN_INFO "Function v4l2_ioctl_streamoff called\n");
#endif
	// Implementation goes here
	return 0;
}