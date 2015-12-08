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

#include <stdarg.h>
#include <stdio.h>
#include "config.h"
#include "wouldblock.h"

const char* wouldblock_version_str(void)
{
    return VERSION;
};

/* EOF */
