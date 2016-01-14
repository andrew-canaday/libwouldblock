## Run autoconf on this file to produce configure.in
##=============================================================================
##
## libwouldblock: configure.ac:
##
##=============================================================================
#==============================================================================
# The Apache 2.0 License
# 
# Copyright (c) 2015 The New York Times Company
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#==============================================================================

#-----------------------------
#           Init:
#-----------------------------
AC_INIT(
    [libwouldblock], [0.0.1],
    [andrew.canaday@nytimes.com],[libwouldblock],
    [https://github.com/andrew-canaday/libwouldblock])
AC_CONFIG_AUX_DIR([./build-aux])
AC_CONFIG_MACRO_DIR([m4])

#-----------------------------
#         Metadata:
#-----------------------------
AC_DEFINE([PACKAGE_LICENSE],["Apache 2.0"],[Package License])
AC_SUBST([PACKAGE_VENDOR],["Andrew Canaday"])
AC_COPYRIGHT([© Copyright 2015-2016 The New York Times Company])
AC_SUBST([PACKAGE_COPYRIGHT],
    ["© Copyright 2015-2016 The New York Times Company"],
    [Copyright Info])
AC_SUBST([PACKAGE_DESCRIPTION],
    ["C library for testing non-blocking IO"])
AC_SUBST([PACKAGE_SUMMARY],["C library for testing non-blocking IO"])
AC_SUBST([WOULDBLOCK_LIB_VERSION],[0:0:0])

# HACK: get the version components (note: we get awk early here)
AC_PROG_AWK
AC_SUBST([PACKAGE_MAJOR],[`echo $PACKAGE_VERSION | awk -F. '{print $1}'`])
AC_SUBST([PACKAGE_MINOR],[`echo $PACKAGE_VERSION | awk -F. '{print $2}'`])
AC_SUBST([PACKAGE_PATCH],[`echo $PACKAGE_VERSION | awk -F. '{print $3}'`])


#-----------------------------
#         Programs:
#-----------------------------
AM_INIT_AUTOMAKE([-Wall foreign])
AC_PROG_CC
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_INIT
PKG_PROG_PKG_CONFIG([0.24])


#-----------------------------
#         Libraries:
#-----------------------------
AX_LIB_SOCKET_NSL


#-----------------------------
#           Headers:
#-----------------------------
AC_HEADER_ASSERT
AC_HEADER_STDC
AC_CHECK_HEADERS([sys/socket.h])
AC_CHECK_HEADERS([netinet/in.h])
AC_CHECK_HEADERS([stddef.h])
AC_CHECK_HEADERS([sys/time.h])
AC_CHECK_HEADERS([dlfcn.h])


#-----------------------------
#           Types:
#-----------------------------
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T


#-----------------------------
#        Declarations:
#-----------------------------
AC_CHECK_DECLS([RTLD_NEXT],[],
        [AC_MSG_ERROR([libwould build requires "$as_decl_name" definition])],
        [#include <dlfcn.h>])

#-----------------------------
#       Function Checks:
#-----------------------------
AC_FUNC_MALLOC
AC_CHECK_FUNCS([accept])
AC_CHECK_FUNCS([send])
AC_CHECK_FUNCS([recv])
AC_CHECK_FUNCS([dlsym])
AC_CHECK_FUNCS([rand])
AC_CHECK_FUNCS([srand])
AC_CHECK_FUNCS([sranddev])
AC_CHECK_FUNCS([random])
AC_CHECK_FUNCS([srandom])
AC_CHECK_FUNCS([srandomdev])
AC_CHECK_FUNCS([getenv])
AC_CHECK_FUNCS([strtol])


#-----------------------------
#      Compiler Features:
#-----------------------------
AX_GCC_FUNC_ATTRIBUTE([constructor])
AC_C_RESTRICT
AC_C_INLINE

#-----------------------------
#    Configuration Options:
#-----------------------------
m4_ifdef([PKG_INSTALLDIR],[PKG_INSTALLDIR],[
    AC_SUBST([pkgconfigdir],[$libdir/pkgconfig])
])

#--- Maintainer Debug: ---
# Check for maintainer-debug:
AC_ARG_ENABLE([maintainer-debug],
    AS_HELP_STRING(
        [--enable-maintainer-debug],
        [VERY verbose logging for maintainer-debug development]))

# If set, extend CFLAGS with ALL KINDS OF VERBOSE INFORMATION:
AS_IF([test "x$enable_maintainer_debug" = "xyes"], [
    AC_MSG_NOTICE([COMPILING WITH MAINTAINER DEBUG CFLAGS])
    CFLAGS="${CFLAGS} \
        -O0 -g -std=c99 -pedantic -Wall -Werror \
        -Wno-error=nonnull -Wundef"
    ])
AM_CONDITIONAL([MAINTAINER_DEBUG],[test "x$enable_maintainer_debug" = "xyes"])


#-----------------------------
#          Output:
#-----------------------------
AC_CONFIG_HEADERS( [wb_config.h] )
AC_CONFIG_FILES(
    [
    Makefile
    libwouldblock-$PACKAGE_MAJOR.pc:libwouldblock.pc.in
    lib/Makefile
    bin/Makefile
    bin/wouldblock.sh
    ],[
    chmod u+x bin/wouldblock.sh
    ]
)
AC_OUTPUT
AS_BOX([libwouldblock configuration complete])

## EOF

