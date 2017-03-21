/*
 * Minimal wrappers to allow compiling kni on older kernels.
 */

#include <linux/version.h>

#ifndef RHEL_RELEASE_VERSION
#define RHEL_RELEASE_VERSION(a, b) (((a) << 8) + (b))
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 39) && \
	(!(defined(RHEL_RELEASE_CODE) && \
	   RHEL_RELEASE_CODE >= RHEL_RELEASE_VERSION(6, 4)))

#define kstrtoul strict_strtoul

#endif /* < 2.6.39 */

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35)

#define sk_sleep(s) (s)->sk_sleep

#endif /* < 2.6.35 */

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,19,0)
#define HAVE_IOV_ITER_MSGHDR
#endif

#if ( LINUX_VERSION_CODE < KERNEL_VERSION(4,1,0) )
#define HAVE_KIOCB_MSG_PARAM
#endif /* < 4.1.0 */

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0)
#define HAVE_TRANS_START_HELPER
#endif

/*
 * KNI uses NET_NAME_UNKNOWN macro to select correct version of alloc_netdev()
 * For old kernels just backported the commit that enables the macro
 * (685343fc3ba6) but still uses old API, it is required to undefine macro to
 * select correct version of API, this is safe since KNI doesn't use the value.
 * This fix is specific to RedHat/CentOS kernels.
 */
#if (defined(RHEL_RELEASE_CODE) && \
	(RHEL_RELEASE_CODE >= RHEL_RELEASE_VERSION(6, 8)) && \
	(LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 34)))
#undef NET_NAME_UNKNOWN
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 11, 0)
#define HAVE_SIGNAL_FUNCTIONS_OWN_HEADER
#endif
