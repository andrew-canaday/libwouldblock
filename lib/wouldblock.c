/*=============================================================================
 * libwouldblock: C Library for Non-blocking IO Testing
 *
 * The Apache 2.0 License
 * 
 * Copyright (c) 2015 Andrew Canaday
 * 
 * <INSERT LICENSE>
 *
 *===========================================================================*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>

#include <errno.h>
#include <stdarg.h>

#include "wb_config.h"

const char*
wouldblock_version_str(void)
{
    return VERSION;
};

#if HAVE_RECV
ssize_t
recv(int socket, void *buffer, size_t length, int flags)
{
    return 0;
};
#endif /* HAVE_RECV */

#if HAVE_SEND
ssize_t
send(int socket, const void *buffer, size_t length, int flags)
{
    return 0;
};
#endif /* HAVE_SEND */

#if HAVE_ACCEPT
int
accept(
    int socket,
    struct sockaddr *restrict address,
    socklen_t *restrict address_len)
{
    return 0;
};
#endif /* HAVE_ACCEPT */

/* EOF */
