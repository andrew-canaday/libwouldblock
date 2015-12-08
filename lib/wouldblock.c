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
static long accept_min;
static long recv_min;
static long send_min;


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

/* Used to parse environment args. */
static long wb_get_arg_range(const char* val_name)
{
    long r_val = 100;
    char* arg_val = getenv(val_name);
    if( arg_val ) {
        r_val = atoi(arg_val);
        r_val = WB_MAX(0,WB_MIN(r_val,100));
    };
    return r_val;
};

/* Library initialization.
 * TODO: use .init linker mechanism if __attribute__((constructor)) is not
 * avaiable!
 */
static void __attribute__((constructor)) wb_init()
{
#if HAVE_SRANDDEV
    srandomdev();
#else
    srandom(time(NULL));
#endif /* HAVE_SRANDDEV */

    accept_min = wb_get_arg_range("WB_PROB_ACCEPT");
    recv_min = wb_get_arg_range("WB_PROB_SEND");
    send_min = wb_get_arg_range("WB_PROB_RECV");
    return;
};

#if HAVE_ACCEPT
/* accept (2) override: invoke the real system accept WB_PROB_ACCEPT percent
 * of the time. Else, return EAGAIN.
 */
int
accept(
    int socket,
    struct sockaddr* restrict address,
    socklen_t* restrict address_len)
{
    static size_t counter = 0;
    static ssize_t (*std_accept)(
        int, struct sockaddr* restrict, socklen_t* restrict);

    long p_accept = random() % 100;
    if( !std_accept ) {
        std_accept = dlsym(RTLD_NEXT, "accept");
    };

    if( p_accept < accept_min ) {
        return std_accept(socket, address, address_len);
    }
    else {
        /* TODO: Check for EAGAIN/EWOULDBLOCK availability/equality @ config */
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
