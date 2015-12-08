## Run autoconf on this file to produce configure.in
##=============================================================================
##
## libwouldblock: configure.ac:
##
##=============================================================================

#=======
# Init:
#=======
AC_INIT( [libwouldblock], [0.0.0], [andrew.canaday@nytimes.com] )

AC_CONFIG_AUX_DIR([.])
AM_INIT_AUTOMAKE( [-Wall foreign] )

# Make sure we have a C compiler:
AC_PROG_CC
AC_PROG_CXX

# For static linking:
AM_PROG_AR

# To silence weird warnings:
AC_CONFIG_MACRO_DIR([m4])

# Make sure we have libtool:
AC_PROG_LIBTOOL()

# LIBRARY INTERFACE Version:
AC_SUBST([WOULDBLOCK_LIB_VERSION],[0:0:0])

# Metadata:
AC_SUBST([PACKAGE_URL],["https://github.com/andrew-canaday/libwouldblock"])
AC_SUBST([PACKAGE_LICENSE],["Apache 2.0"])
AC_SUBST([PACKAGE_VENDOR],["Andrew Canaday"])
AC_SUBST([PACKAGE_COPYRIGHT],["copyright 2015 Andrew Canaday"])
AC_SUBST([PACKAGE_DESCRIPTION],["C Library for Non-blocking IO Testing"])
AC_SUBST([PACKAGE_SUMMARY],["C Library for Non-blocking IO Testing"])


#=========
# Output:
#=========
AC_CONFIG_HEADERS( [config.h] )
AC_CONFIG_FILES(
  Makefile
  lib/Makefile
  include/Makefile
  test/Makefile
  libwouldblock.pc
)
AC_OUTPUT

## EOF
