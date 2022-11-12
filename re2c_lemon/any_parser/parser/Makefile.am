lib_LTLIBRARIES = libparser.la

LEMON = lemon
MAKEHEADERS = makeheaders

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
	$(LEMON) T=/usr/share/lemon/lempar.c -m -q $< || { rm -f $@; exit 1; }

