lib_LTLIBRARIES = libparser.la

PARSER = bison
	
AM_YFLAGS = -d

BUILT_SOURCES = \
	parser.h \
	parser.c

libparser_la_SOURCES = parser.y

libparser_la_CFLAGS = \
	-Wall -DYYDEBUG=1

parser.c : parser.y
	$(PARSER) $(AM_YFLAGS) -o $@ $<

