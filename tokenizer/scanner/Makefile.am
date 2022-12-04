lib_LTLIBRARIES = libscanner.la

BUILT_SOURCES = scanner.c

libscanner_la_SOURCES = \
    scanner.c \
    input.c \
    input.h

libscanner_la_CFLAGS = \
	-I$(top_builddir)/parser

-include scanner.dep

.re.c :
	re2c -o $@ --depfile scanner.dep $<

