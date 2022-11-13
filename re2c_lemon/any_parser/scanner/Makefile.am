lib_LTLIBRARIES = libscanner.la

BUILT_SOURCES = any_scanner.c

libscanner_la_SOURCES = any_scanner.c

libscanner_la_CFLAGS = \
	-I$(top_builddir)/parser

.re.c :
	re2c -o $@ --type-header ${*}_type.h $<

