bin_PROGRAMS = example

example_SOURCES = example.c

example_CFLAGS = \
	-I$(top_builddir)/scanner \
	-I$(top_builddir)/parser

example_LDFLAGS = \
	$(SQLITE3_CFLAGS)

example_LDADD = \
	$(top_builddir)/scanner/libscanner.la \
	$(top_builddir)/parser/libparser.la \
	$(SQLITE3_LIBS)

