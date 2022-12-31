#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])
AC_CONFIG_SRCDIR([calc.c])
AC_CONFIG_HEADERS([config/config.h])

AM_INIT_AUTOMAKE([foreign subdir-objects])

# Checks for programs.
AC_PROG_CC

AC_CONFIG_SUBDIRS([gtest])

# Checks for libraries.
# FIXME: Replace 'main' with a function in '-lgtest':
#AC_CHECK_LIB([gtest], [main])
# FIXME: Replace 'main' with a function in '-lgtest_main':
#AC_CHECK_LIB([gtest_main], [main])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 gtest/Makefile])
AC_OUTPUT

