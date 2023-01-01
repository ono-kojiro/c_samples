lib_LTLIBRARIES = libparser.la

LEMON = lemon
LEMPAR = /usr/share/lemon/lempar.c
MAKEHEADERS = makeheaders

EXTRA_DIST = parser.y userdata.h token.h

BUILT_SOURCES = parser.c parser.h

libparser_la_SOURCES = parser.c userdata.c

parser.h : parser.c token.h
	echo '#ifdef __cplusplus' > $@
	echo 'extern "C" {' >> $@
	echo '#endif' >> $@
	echo '' >> $@
	echo '#include "token.h"' >> $@
	echo '#include "userdata.h"' >> $@
	$(MAKEHEADERS) -h $< >> $@
	echo '#ifdef __cplusplus' >> $@
	echo '}' >> $@
	echo '#endif' >> $@

parser.c : parser.y
	$(LEMON) T=$(LEMPAR) -m -q $<


