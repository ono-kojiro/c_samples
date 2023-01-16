lib_LTLIBRARIES = libparser.la

LEMON = $(top_builddir)/tools/lemon
MAKEHEADERS = $(top_builddir)/tools/makeheaders

EXTRA_DIST = parser.y userdata.h token.h

BUILT_SOURCES = parser.c parser.h

libparser_la_SOURCES = parser.c userdata.c

libparser_la_CFLAGS = -DNDEBUG=1

parser.h : parser.c token.h $(MAKEHEADERS)
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

parser.c : parser.y $(LEMON)
	$(LEMON) T=$(top_builddir)/tools/lempar.c -m -q $<

clean-local :
	rm -f parser.c parser.h

