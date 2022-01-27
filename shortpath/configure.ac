#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([shortpath], [0.0.1], [ono.kojiro@gmail.com])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])
AC_CONFIG_SRCDIR([shortpath/main.c])
AC_CONFIG_HEADERS([config/config.h])

AM_INIT_AUTOMAKE([foreign subdir-objects])

LT_INIT

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.
PKG_CHECK_MODULES([CHECK],
  [check >= 0.9.4],
  [
      #AC_MSG_NOTICE([found check])
	  found_check=1
  ],
  [
      #AC_MSG_NOTICE([NOT found check])
	  found_check=0
  ]
)

AC_ARG_ENABLE([check],
  [AC_HELP_STRING([--enable-check], [ use libcheck for unit test])],
  [
    case "${enableval}" in
	  yes)
        #AC_MSG_NOTICE([check is enabled])
	    enable_check=1
	    ;;
      no)
        #AC_MSG_NOTICE([check is disabled])
	    enable_check=0
	    ;;
    esac
  ],
  [
    enable_check=1
  ]
)

if test "$found_check" = "1" -a "$enable_check" = "1" ; then
  #AC_MSG_NOTICE([libcheck is enabled])
  AC_DEFINE([HAVE_LIBCHECK], [1], [Define if you want to use libcheck])
  use_check=1
else
  #AC_MSG_NOTICE([libcheck is disabled])
  use_check=0
fi

AM_CONDITIONAL([HAVE_LIBCHECK], [ test "$use_check" = "1" ])


# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile
                 shortpath/Makefile])
AC_CONFIG_FILES([tests/Makefile])

AC_OUTPUT
