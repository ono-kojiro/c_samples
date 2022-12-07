lib_LTLIBRARIES = libscanner.la

RE2C = $(top_builddir)/tools/re2c/re2c

BUILT_SOURCES = scanner.c

libscanner_la_SOURCES = \
    scanner.c \
    input.c \
    input.h

libscanner_la_CFLAGS = \
	-I$(top_builddir)/parser

-include scanner.dep

.re.c :
	$(RE2C) -o $@ --depfile scanner.dep $<

