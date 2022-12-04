lib_LTLIBRARIES = libparser.la

LEMON = $(top_builddir)/tools/lemon
MAKEHEADERS = $(top_builddir)/tools/makeheaders

LEMPAR = $(top_srcdir)/tools/lempar.c

BUILT_SOURCES = parser.c parser.h

CLEANFILES = parser.c parser.h

libparser_la_SOURCES = parser.c userdata.c str.c

parser.h : parser.c token.h
	{ \
	echo '#ifndef PARSER_H'; \
	echo ''; \
	echo '#define PARSER_H'; \
	echo '#include "token.h"'; \
	echo '#include "userdata.h"'; \
	$(MAKEHEADERS) -h $<; \
	echo ''; \
	echo '#endif /* #define PARSER_H */'; \
	} > $@

parser.c : parser.y
	$(LEMON) T=$(LEMPAR) -s -m $< && { if test $$? -ne 0; then rm -f $@; exit 1; fi }

