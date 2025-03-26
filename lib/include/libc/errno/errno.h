#ifndef ERRNO_H
#define ERRNO_H

extern int errno;

#define EPERM 1       // Operation not permitted
#define ENOENT 2      // No such file or directory
#define ESRCH 3       // No such process
#define EINTR 4       // Interrupted system call
#define EIO 5         // Input/output error
#define ENXIO 6       // No such device or address
#define E2BIG 7       // Argument list too long
#define ENOEXEC 8     // Exec format error
#define EBADF 9       // Bad file descriptor
#define ENOMEM 12     // Out of memory

#endif // ERRNO_H
