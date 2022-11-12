bin_PROGRAMS = example

example_SOURCES = \
	main.c

example_CFLAGS = \
	-I$(top_srcdir)/parser \
	-I$(top_srcdir)/lexer \
	-I$(top_builddir)/parser

example_LDFLAGS =

example_LDADD = \
	$(top_builddir)/parser/libparser.la \
	$(top_builddir)/lexer/liblexer.la


