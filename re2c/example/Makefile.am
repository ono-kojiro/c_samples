bin_PROGRAMS = example

example_SOURCES = example.c

example_CFLAGS = \
	-I$(top_builddir)/scanner \
	-I$(top_builddir)/parser

example_LDFLAGS =

example_LDADD = \
	$(top_builddir)/parser/libparser.la \
	$(top_builddir)/scanner/libscanner.la

TESTS = 01-simple.sh 02-simple_tap.sh

