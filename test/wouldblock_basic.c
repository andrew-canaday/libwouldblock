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
#include <stdio.h>
#include <assert.h>
#include "wouldblock.h"

int main( int argc, char** argv )
{
    const char* lib_version = wouldblock_version_str();
    assert(lib_version != NULL);
    printf( "libwouldblock: %s\n", lib_version );
    return 0;
};

/* EOF */
