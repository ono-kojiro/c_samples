lib_LTLIBRARIES = libscanner.la

BUILT_SOURCES = any_scanner.c simple.c

libscanner_la_SOURCES = \
    any_scanner.c \
    input.c \
    simple.c

libscanner_la_CFLAGS = \
	-I$(top_builddir)/parser

.re.c :
	re2c -o $@ $<

