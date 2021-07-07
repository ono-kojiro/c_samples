bin_PROGRAMS = mycalc

mycalc_SOURCES = mycalc.c

mycalc_CFLAGS = \
	-I$(top_builddir)/scanner \
	-I$(top_builddir)/parser

mycalc_LDFLAGS =

mycalc_LDADD = \
	$(top_builddir)/scanner/libscanner.la \
	$(top_builddir)/parser/libparser.la

