lib_LTLIBRARIES = libscanner.la

EXTRA_DIST = scanner.re scanner.h

BUILT_SOURCES = scanner.c

libscanner_la_SOURCES = scanner.c

libscanner_la_CFLAGS = \
	-I$(top_builddir)/parser

.re.c :
	re2c -o $@ $<


