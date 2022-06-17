#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])
AC_CONFIG_SRCDIR([mythread/main.c])
AC_CONFIG_HEADERS([config/config.h])

AM_INIT_AUTOMAKE([foreign subdir-objects])
LT_INIT

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace 'main' with a function in '-lmythread':
#AC_CHECK_LIB([mythread], [main])
# FIXME: Replace 'main' with a function in '-lpthread':
AC_CHECK_LIB([pthread], [main])

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 libmythread/Makefile
                 mythread/Makefile])
AC_OUTPUT
