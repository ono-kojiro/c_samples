#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([mygramar], [0.0.1], [ono.kojiro@gmail.com])
AC_CONFIG_MACRO_DIR([config])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_SRCDIR([lexer/c99.l])
AC_CONFIG_HEADERS([config/config.h])

AM_INIT_AUTOMAKE([foreign subdir-objects])

LT_INIT

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_C_O

AC_PROG_YACC
AC_PROG_LEX

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 parser/Makefile
                 lexer/Makefile
                 tests/Makefile])
AC_OUTPUT
