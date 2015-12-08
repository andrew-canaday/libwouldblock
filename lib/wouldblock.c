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

/*--------------------------------
 *           Macros:
 *--------------------------------*/
#define LWB_MAX(x,y) (x > y ? x : y)
#define LWB_MIN(x,y) (x < y ? x : y)

/*--------------------------------
 *          Globals:
 *--------------------------------*/
static long accept_min;
static long recv_min;
static long send_min;

static ssize_t
(*std_accept)(int, struct sockaddr* restrict, socklen_t* restrict) = NULL;

static ssize_t
(*std_recv)(int socket, void* buffer, size_t length, int flags) = NULL;

static ssize_t
(*std_send)(int socket, const void* buffer, size_t length, int flags) = NULL;


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
        r_val = LWB_MAX(0,LWB_MIN(r_val,100));
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

    accept_min = wb_get_arg_range("LWB_PROB_ACCEPT");
    recv_min = wb_get_arg_range("LWB_PROB_SEND");
    send_min = wb_get_arg_range("LWB_PROB_RECV");
    
    /* Initialize the real accept function pointer: */
    if( !std_accept ) {
        std_accept = dlsym(RTLD_NEXT, "accept");
    };

    /* Initialize the real recv function pointer: */
    if( !std_recv ) {
        std_recv = dlsym(RTLD_NEXT, "recv");
    };

    /* Initialize the real send function pointer: */
    if( !std_send ) {
        std_send = dlsym(RTLD_NEXT, "send");
    };
    return;
};

#if HAVE_ACCEPT
/* accept (2) override: invoke the real system accept LWB_PROB_ACCEPT percent
 * of the time. Else, return EAGAIN.
 */
int
accept(
    int socket,
    struct sockaddr* restrict address,
    socklen_t* restrict address_len)
{
    static size_t counter = 0;
    long p_accept = random() % 100;

    /* Block, artificially: */
    if( p_accept < accept_min ) {
        return std_accept(socket, address, address_len);
    }
    /* Just execute standard accept: */
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
