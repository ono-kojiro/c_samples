#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([chktoken], [0.0.1], [ono.kojiro@gmail.com])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])
AC_CONFIG_SRCDIR([example/example.c])
AC_CONFIG_HEADERS([config/config.h])
AC_REQUIRE_AUX_FILE([tap-driver.sh])

AM_INIT_AUTOMAKE([foreign subdir-objects])
LT_INIT

AC_CONFIG_SUBDIRS([tools/re2c])

# Checks for programs.
AC_PROG_CC
#AC_PROG_LIBTOOL

# Checks for libraries.
PKG_CHECK_MODULES([SQLITE3], [sqlite3 >= 3.22.0])

# Checks for libraries.
#PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])

#######################
###   Parser
#######################
AC_ARG_ENABLE([parser],
	[ AS_HELP_STRING(
			[--enable-parser],
			[enable parser (default is yes)])
	],
	[ enable_parser="${enableval}" ],
	[ enable_parser="yes" ]
)

# define USE_PARSER variable in config.h
AS_IF([test "x$enable_parser" = "xyes"],
	[
      AC_DEFINE([USE_PARSER], [1], [use parser])
    ],
    [
      AC_DEFINE([USE_PARSER], [0], [use parser])
    ]
)

# define USE_PARSER variable in Makefile
AM_CONDITIONAL([USE_PARSER], [ test $enable_parser = "yes" ])

#######################
###   DEBUG
#######################
AC_ARG_ENABLE([debug],
	[ AS_HELP_STRING(
			[--enable-debug],
			[enable debug (default is yes)])
	],
	[ enable_debug="${enableval}" ],
	[ enable_debug="yes" ]
)

AS_IF([test "x$enable_debug" = "xyes"],
	[AC_DEFINE([DEBUG], [1], [enable debug])],
	[AC_DEFINE([DEBUG], [0], [enable debug])]
)
AC_SUBST([DEBUG])


AC_ARG_ENABLE([debug-parser],
	[ AS_HELP_STRING(
			[--enable-debug-parser],
			[enable debug in parser (default is yes)])
	],
	[ enable_debug_parser="${enableval}" ],
	[ enable_debug_parser="yes" ]
)

AS_IF([test "x$enable_debug_parser" = "xyes"],
	[AC_DEFINE([DEBUG_PARSER], [1], [enable debug parser])],
	[AC_DEFINE([DEBUG_PARSER], [0], [enable debug parser])]
)
AC_SUBST([DEBUG_PARSER])

######################
### Debug Scanner
######################
AC_ARG_ENABLE([debug-scanner],
	[ AS_HELP_STRING(
			[--enable-debug-scanner],
			[enable debug in scanner (default is yes)])
	],
	[ enable_debug_scanner="${enableval}" ],
	[ enable_debug_scanner="yes" ]
)

AS_IF([test "x$enable_debug_scanner" = "xyes"],
	[AC_DEFINE([DEBUG_SCANNER], [1], [enable debug scanner])],
	[AC_DEFINE([DEBUG_SCANNER], [0], [enable debug scanner])]
)

AC_SUBST([DEBUG_SCANNER])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])
AC_CHECK_HEADERS([inttypes.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([memset])
AC_CHECK_FUNCS([memmove])
AC_CHECK_FUNCS([strdup])
AC_CHECK_FUNCS([strndup])

if test -n "$enable_parser" -a "x$enable_parser" = "xyes" ; then
  AC_CONFIG_FILES([
                  tools/Makefile
                  parser/Makefile])
fi


AC_CONFIG_FILES([Makefile
                 scanner/Makefile
                 example/Makefile
                 tests/Makefile])

AC_OUTPUT

echo ""
echo "enable_parser : $enable_parser"
echo "enable_debug  : $enable_debug"
echo "enable_debug_parser   : $enable_debug_parser"
echo "enable_debug_scanner  : $enable_debug_scanner"

