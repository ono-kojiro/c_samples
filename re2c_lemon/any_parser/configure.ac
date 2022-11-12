#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])
AC_CONFIG_SRCDIR([example/example.c])
AC_CONFIG_HEADERS([config/config.h])
AC_REQUIRE_AUX_FILE([tap-driver.sh])

AM_INIT_AUTOMAKE([foreign subdir-objects])

LT_INIT

# Checks for programs.
AC_PROG_CC
#AC_PROG_LIBTOOL

# Checks for libraries.
PKG_CHECK_MODULES([SQLITE3], [sqlite3 >= 3.37.2])

# Checks for libraries.
PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])

AC_ARG_ENABLE([parser],
	[
		AS_HELP_STRING(
			[--enable-parser],
			[parser feature (default is yes)]
		)
	],
	[
		case "${enableval}" in
			yes )
				enable_parser=yes
				;;
			no )
				enable_parser=no
				;;
		esac
	],
	[
		enable_parser="yes"
	]
)

AS_IF([test "x$enable_parser" = "xyes"],
	[AC_DEFINE([USE_PARSER], [1], [parser support])],
	[AC_DEFINE([USE_PARSER], [0], [parser support])]
)

AC_ARG_ENABLE([debug],
	[
		AS_HELP_STRING(
			[--enable-debug],
			[enable debug (default is yes)]
		)
	],
	[
		case "${enableval}" in
			yes )
				enable_debug=yes
				;;
			no )
				enable_debug=no
				;;
		esac
	],
	[
		enable_debug="yes"
	]
)

AS_IF([test "x$enable_debug" = "xyes"],
	[AC_DEFINE([DEBUG], [1], [enable debug])],
	[AC_DEFINE([DEBUG], [0], [enable debug])]
)

AC_ARG_ENABLE([debug-parser],
	[ AS_HELP_STRING(
			[--enable-debug-parser],
			[enable debug in parser (default is no)])
	],
	[ enable_debug_parser="${enableval}" ],
	[ enable_debug_parser="no" ]
)

AS_IF([test "x$enable_debug_parser" = "xyes"],
	[AC_DEFINE([DEBUG_PARSER], [1], [enable debug parser])],
	[AC_DEFINE([DEBUG_PARSER], [0], [enable debug parser])]
)


# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile
                 tools/Makefile
                 parser/Makefile
                 scanner/Makefile
                 example/Makefile
                 tests/Makefile])
AC_OUTPUT

echo ""
echo "enable_parser : $enable_parser"
echo "enable_debug  : $enable_debug"
echo "enable_debug_parser  : $enable_debug_parser"

