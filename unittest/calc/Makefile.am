bin_PROGRAMS = calc

calc_SOURCES = main.c

calc_CFLAGS = \
    -DNDEBUG=1 \
	-I$(top_builddir)/scanner \
	-I$(top_builddir)/parser

calc_LDFLAGS =

calc_LDADD = \
	$(top_builddir)/scanner/libscanner.la \
	$(top_builddir)/parser/libparser.la \
	-lm

