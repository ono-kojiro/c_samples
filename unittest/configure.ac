#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([calc], [0.0.1], [ono.kojiro@gmail.com])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])
AC_CONFIG_SRCDIR([calc/main.c])
AC_CONFIG_HEADERS([config/config.h])

AM_INIT_AUTOMAKE([foreign subdir-objects])

LT_INIT

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
LT_INIT

AC_CONFIG_SUBDIRS([tools/gtest])
AC_CONFIG_SUBDIRS([ctest])

# Checks for libraries.
PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])
PKG_CHECK_MODULES([CUNIT], [cunit >= 2.1])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile
				 tools/Makefile
                 scanner/Makefile
				 parser/Makefile
                 calc/Makefile
                 cunit/Makefile
                 tests/Makefile
                 ctest/Makefile])
AC_OUTPUT
