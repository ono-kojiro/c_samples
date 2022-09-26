#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([myapp], [0.0.1], [ono.kojiro@gmail.com])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])
AC_CONFIG_SRCDIR([src/myapp.c])
AC_CONFIG_HEADERS([config/config.h])

AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE([foreign subdir-objects])

LT_INIT

# Checks for programs.
AC_PROG_CC

AC_ARG_WITH(mylib_include,
  [  --with-mylib-include=DIR  mylib include directory ],
  [
    withval=`realpath $withval 2>/dev/null`
    CFLAGS="$CFLAGS -I$withval"
    AC_DEFINE([HAVE_MYLIB], [1], [mylib-include])
  ],
  [
  ]
)

AC_ARG_WITH(mylib_lib,
  [  --with-mylib-lib=DIR  mylib library directory ],
  [
    withval=`realpath $withval 2>/dev/null`
    LDFLAGS="$LDFLAGS -L$withval"
    mylib_lib_path="$withval"
    AC_DEFINE([HAVE_MYLIB], [1], [mylib-lib])
  ],
  [
  ]
)

AC_ARG_WITH(mylib,
  [  --with-mylib=DIR  mylib install directory ],
  [
    withval=`realpath $withval 2>/dev/null`
    if test -z "$with_mylib_lib" && test -z "$with_mylib_include" ; then
      CFLAGS="$CFLAGS -I$withval/include"
      LDFLAGS="$LDFLAGS -L$withval/lib"
      mylib_lib_path="$withval/lib"
      AC_DEFINE([HAVE_MYLIB], [1], [mylib])
    else
      AC_MSG_FAILURE([Do not use --with-mylib and --with-mylib-include/--with-mylib-lib options simultaneously.])
    fi
  ],
  [
  ]
)

AC_ARG_WITH(mylib_build,
  [  --with-mylib-build=DIR   mylib build directory],
  [
    withval=`realpath $withval 2>/dev/null`
    if test -z "$mylib_lib_path" && test -z "$with_mylib_include" ; then
      CFLAGS="$CFLAGS -I$withval"
      LDFLAGS="$LDFLAGS -L$withval -L$withval/.libs"
      mylib_lib_path="$withval"
      AC_DEFINE([HAVE_MYLIB], [1], [mylib-build])
    else
      AC_MSG_WARN([mylib_lib_path is $mylib_lib_path])
      AC_MSG_WARN([with_mylib_include is $with_mylib_include])
      AC_MSG_FAILURE([Do not use --with-mylib-build and other --with-mylib options simultaneously.])
    fi
  ]
)

# Checks for libraries.
AC_CHECK_LIB(mylib, mylib,
    [LIBS="$mylib_lib_path/libmylib.la $LIBS"]
)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT
