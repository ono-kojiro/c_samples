lib_LTLIBRARIES = libparser.la

LEMON = $(top_builddir)/tools/lemon
MAKEHEADERS = $(top_builddir)/tools/makeheaders

EXTRA_DIST = parser.y userdata.h token.h

BUILT_SOURCES = parser.c parser.h

libparser_la_SOURCES = parser.c userdata.c

parser.h : parser.c token.h $(MAKEHEADERS)
	echo '#include "macro.h"' > parser.h
	echo '#include "token.h"' >> parser.h
	echo '#include "userdata.h"' >> parser.h
	$(MAKEHEADERS) -h parser.c >> parser.h

parser.c : parser.y $(LEMON)
	$(LEMON) T=$(top_builddir)/tools/lempar.c -m -q parser.y


