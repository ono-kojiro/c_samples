#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([hello], [0.0.1], [ono.kojiro@gmail.com])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])
AC_CONFIG_SRCDIR([libhello/src/hello.h])
AC_CONFIG_HEADERS([config/config.h])

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([foreign subdir-objects])

LT_INIT([win32-dll])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
#AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

AC_ENABLE_SHARED
AC_DISABLE_STATIC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lhello':
#AC_CHECK_LIB([hello], [main])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 hello/Makefile
                 libhello/Makefile])
AC_OUTPUT
