bin_PROGRAMS = mycalc

mycalc_SOURCES = mycalc.c

mycalc_CFLAGS = \
	-I$(top_builddir)/libscanner \
	-I$(top_builddir)/libparser

mycalc_LDFLAGS =

mycalc_LDADD = \
	$(top_builddir)/libscanner/libscanner.la \
	$(top_builddir)/libparser/libparser.la

