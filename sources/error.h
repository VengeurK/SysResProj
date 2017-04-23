#ifndef ERROR_H
#define ERROR_H
typedef enum {
    E2BIG,	//Argument list too long
    EACCES,	//Permission denied
    EAGAIN,	//Resource temporarily unavailable; try again
    EBADF,	//Bad file descriptor
    EBUSY,	//Resource unavailable
    ECHILD,	//No child process
    EDEADLK,	//Resource deadlock would occur
    EDOM,	//Domain error for math functions, etc.
    EEXIST,	//File exists
    EFAULT,	//Bad address
    EFBIG,	//File too large
    EINTR,	//Function interrupted by signal
    EINVAL,	//Invalid argument
    EIO,	//Hardware I/O error
    EISDIR,	//Is a directory
    EMFILE,	//Too many open files by the process
    EMLINK,	//Too many links
    ENAMETOOLONG,	//Filename too long
    ENFILE,	//Too many open files in the system
    ENODEV,	//No such device
    ENOENT,	//No such file or directory
    ENOEXEC,	//Not an executable file
    ENOLCK,	//No locks available
    ENOMEM,	//Not enough memory
    ENOSPC,	//No space left on device
    ENOSYS,	//Function not supported
    ENOTDIR,	//Not a directory
    ENOTEMPTY,	//Directory not empty
    ENOTTY,	//Inappropriate I/O control operation
    ENXIO,	//No such device or address
    EPERM,	//Operation not permitted
    EPIPE,	//Broken pipe
    ERANGE,	//Result too large
    EROFS,	//Read-only file system
    ESPIPE,	//Invalid seek e.g. on a pipe
    ESRCH,	//No such process
    EXDEV,	//Invalid link
    EWOULDBLOCK,	//Operation would block
    EINPROGRESS,	//Operation now in progress
    EALREADY,	//Operation already in progress
    ENOTSOCK,	//Socket operation on non-socket
    EDESTADDRREQ,	//Destination address required
    EMSGSIZE,	//Message too long
    EPROTOTYPE,	//Protocol wrong type for socket
    ENOPROTOOPT,	//Protocol not available
    EPROTONOSUPPORT,	//Protocol not supported
    ESOCKTNOSUPPORT,	//Socket type not supported
    EOPNOTSUPP,	//Operation not supported on socket
    EPFNOSUPPORT,	//Protocol family not supported
    EAFNOSUPPORT,	//Address family not supported by protocol family
    EADDRINUSE,	//Address already in use
    EADDRNOTAVAIL,	//Can't assign requested address
    ENETDOWN,	//Network is down
    ENETUNREACH,	//Network is unreachable
    ENETRESET,	//Network dropped connection on reset
    ECONNABORTED,	//Software caused connection abort
    ECONNRESET,	//Connection reset by peer
    ENOBUFS,	//No buffer space available
    EISCONN,	//Socket is already connected
    ENOTCONN,	//Socket is not connected
    ESHUTDOWN,	//Can't send after socket shutdown
    ETOOMANYREFS,	//Too many references: can't splice
    ETIMEDOUT,	//Connection timed out
    ECONNREFUSED,	//Connection refused
    EHOSTDOWN,	//Host is down
    EHOSTUNREACH,	//No route to host
    ELOOP,	//Too many levels of symbolic links
    EOVERFLOW,	//File size or position not representable
    EUNKNOWNERR,	//Unknown error
} error_t;
#endif /* ERROR_H */

