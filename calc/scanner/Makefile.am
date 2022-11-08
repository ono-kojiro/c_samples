lib_LTLIBRARIES = libscanner.la

DIST_SOURCES = scanner.re

BUILT_SOURCES = scanner.c

libscanner_la_SOURCES = scanner.c

libscanner_la_CFLAGS = \
	-I$(top_builddir)/parser

.re.c :
	re2c -o $@ $<


