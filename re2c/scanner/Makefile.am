lib_LTLIBRARIES = libscanner.la

BUILT_SOURCES = scanner.c

libscanner_la_SOURCES = scanner.c

libscanner_la_CFLAGS = \
	-I$(top_builddir)/parser

scanner.c : scanner.re
	re2c -o $@ $<


