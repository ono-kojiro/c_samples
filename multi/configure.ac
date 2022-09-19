#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([multilib], [0.0.1], [ono.kojiro@gmail.com])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])
AC_CONFIG_SRCDIR([libmystaticlib/mystaticlib.h])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([foreign subdir-objects])

LT_INIT

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lmystaticlib':
#AC_CHECK_LIB([mystaticlib], [main])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 libmystaticlib/Makefile
                 mystaticapp/Makefile])
AC_CONFIG_FILES([libmysharedlib/Makefile])
AC_CONFIG_FILES([mysharedapp/Makefile])

#AC_CONFIG_SUBDIRS([daemon])
AC_OUTPUT
