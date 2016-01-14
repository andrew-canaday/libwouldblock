/*=============================================================================
 * libwouldblock: C Library for Non-blocking IO Testing
 *
 * The Apache 2.0 License
 * 
 * Copyright (c) 2015 The New York Times Company
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *===========================================================================*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <dlfcn.h>

#include "wb_config.h"

/*---------------------------------------------------------------------------*
 * TODO:
 * 1. Use .init linker mechanism where __attribute__((constructor) is
 *    not available.
 * 2. Check for EAGAIN/EWOULDBLOCK equivalency/availability at config time.
 *---------------------------------------------------------------------------*/

/*--------------------------------*
 *             Macros:
 *--------------------------------*/
#define WB_PROB_MAX 100
#define WB_MAX(x,y) (x > y ? x : y)
#define WB_MIN(x,y) (x < y ? x : y)


/*--------------------------------*
 *             Types:
 *--------------------------------*/
typedef ssize_t
(*accept_fn_t)(int, struct sockaddr* restrict, socklen_t* restrict);

typedef ssize_t
(*recv_fn_t)(int socket, void* buffer, size_t length, int flags);

typedef ssize_t
(*send_fn_t)(int socket, const void* buffer, size_t length, int flags);


/*--------------------------------
 *            Global:
 *--------------------------------*/
static long accept_min;
static long recv_min;
static long send_min;
static accept_fn_t std_accept;
static recv_fn_t std_recv;
static send_fn_t std_send;


/*---------------------------------------------------------------------------*
 *
 *                               Public API:
 *
 *---------------------------------------------------------------------------*/
const char*
wouldblock_version_str(void)
{
    return VERSION;
}


/*---------------------------------------------------------------------------*
 *
 *                                Utility:
 *
 *---------------------------------------------------------------------------*/
/* Used to parse environment args. */
static long wb_get_arg_range(const char* val_name)
{
    long r_val = WB_PROB_MAX;
    char* arg_val = getenv(val_name);
    if( arg_val ) {
#if HAVE_STRTOL
        char* endptr;
        r_val = strtol(arg_val, &endptr, 10);
        if(endptr == arg_val) {
            return WB_PROB_MAX;
        };
#else
        r_val = atoi(arg_val);
#endif /* HAVE_STRTOL */
        r_val = WB_MAX(0,WB_MIN(r_val,WB_PROB_MAX));
    };
    return r_val;
}


/*--------------------------------*
 * Library initialization:
 *--------------------------------*/
static void __attribute__((constructor)) wb_init()
{
    wb_srandom(time(NULL));
    accept_min = wb_get_arg_range("WB_PROB_ACCEPT");
    recv_min = wb_get_arg_range("WB_PROB_SEND");
    send_min = wb_get_arg_range("WB_PROB_RECV");
    
    /* Initialize the real accept function pointer: */
    if( !std_accept ) {
        std_accept = (accept_fn_t)dlsym(RTLD_NEXT, "accept");
    };

    /* Initialize the real recv function pointer: */
    if( !std_recv ) {
        std_recv = (recv_fn_t)dlsym(RTLD_NEXT, "recv");
    };

    /* Initialize the real send function pointer: */
    if( !std_send ) {
        std_send = (send_fn_t)dlsym(RTLD_NEXT, "send");
    };
    return;
}


/*---------------------------------------------------------------------------*
 *
 *                       Network Function Overrides:
 *
 *---------------------------------------------------------------------------*/
#if HAVE_ACCEPT
/* accept (2) override: invoke the real accept syscall WB_PROB_ACCEPT percent
 * of the time. Else, return EAGAIN.
 */
int
accept(
    int socket,
    struct sockaddr* restrict address,
    socklen_t* restrict address_len)
{
    long p_accept = wb_random() % WB_PROB_MAX;

    /* Block, artificially: */
    if( p_accept < accept_min ) {
        return std_accept(socket, address, address_len);
    }
    /* Just execute standard accept: */
    else {
        errno = EAGAIN;
        return -1;
    };
}
#endif /* HAVE_ACCEPT */


#if HAVE_RECV
/* recv (2) override: invoke the real recv syscall WB_PROB_RECV percent
 * of the time. Else, return EAGAIN.
 */
ssize_t
recv(int socket, void* buffer, size_t length, int flags)
{
    long p_recv = wb_random() % WB_PROB_MAX;

    /* Block, artificially: */
    if( p_recv < recv_min ) {
        return std_recv(socket, buffer, length, flags);
    }
    /* Just execute standard recv: */
    else {
        errno = EAGAIN;
        return -1;
    };
    return 0;
}
#endif /* HAVE_RECV */


#if HAVE_SEND
/* send (2) override: invoke the real send syscall WB_PROB_SEND percent
 * of the time. Else, return EAGAIN.
 */
ssize_t
send(int socket, const void* buffer, size_t length, int flags)
{
    long p_send = wb_random() % WB_PROB_MAX;

    /* Block, artificially: */
    if( p_send < send_min ) {
        return std_send(socket, buffer, length, flags);
    }
    /* Just execute standard send: */
    else {
        errno = EAGAIN;
        return -1;
    };
    return 0;
}
#endif /* HAVE_SEND */

/* EOF */
