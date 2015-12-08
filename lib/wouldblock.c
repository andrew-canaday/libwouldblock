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
#include <time.h>
#include <errno.h>
#include <dlfcn.h>

#include "wb_config.h"

/*--------------------------------
 *           Macros:
 *--------------------------------*/
#define WB_MAX(x,y) (x > y ? x : y)
#define WB_MIN(x,y) (x < y ? x : y)

/*--------------------------------
 *          Globals:
 *--------------------------------*/
static int accept_min = 0;
static int recv_min = 0;
static int send_min = 0;


/*--------------------------------
 *          Public API:
 *--------------------------------*/
const char*
wouldblock_version_str(void)
{
    return VERSION;
};


/*---------------------------------
 *        Private Functions:
 *---------------------------------*/
static void __attribute__((constructor)) wb_init()
{
#if HAVE_SRANDDEV
    sranddev();
#else
    srand(time(NULL));
#endif /* HAVE_SRANDDEV */

    char* accept_arg = getenv("WB_ACCEPT_PROB");
    if( accept_arg ) {
        int accept_val = atoi(accept_arg);
        accept_min = WB_MAX(0,WB_MIN(accept_val,100));
    };
    return;
};

#if HAVE_ACCEPT
int
accept(
    int socket,
    struct sockaddr* restrict address,
    socklen_t* restrict address_len)
{
    static size_t counter = 0;
    static ssize_t (*std_accept)(
        int, struct sockaddr* restrict, socklen_t* restrict);

    int p_accept = rand() % 100;
    if( !std_accept ) {
        std_accept = dlsym(RTLD_NEXT, "accept");
    };

    if( p_accept < accept_min ) {
        return std_accept(socket, address, address_len);
    }
    else {
        errno = EAGAIN;
        return -1;
    };
};
#endif /* HAVE_ACCEPT */

#if 0
#if HAVE_RECV
ssize_t
recv(int socket, void* buffer, size_t length, int flags)
{
    return 0;
};
#endif /* HAVE_RECV */

#if HAVE_SEND
ssize_t
send(int socket, const void* buffer, size_t length, int flags)
{
    return 0;
};
#endif /* HAVE_SEND */
#endif /* 0 */


/* EOF */
