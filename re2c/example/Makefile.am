bin_PROGRAMS = example

example_SOURCES = example.c

example_CFLAGS = \
	-I$(top_builddir)/scanner \
	-I$(top_builddir)/parser

example_LDFLAGS =

example_LDADD = \
	$(top_builddir)/scanner/libscanner.la

TESTS = 01-simple.sh

