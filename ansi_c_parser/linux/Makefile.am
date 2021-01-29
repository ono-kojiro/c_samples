noinst_PROGRAMS = c99

LEXER = flex
PARSER = bison

AM_YFLAGS = -d

c99_SOURCES = \
	../src/parser.y \
	../src/lexer.l \
	../src/main.c

BUILT_SOURCES = \
	../src/lexer.c \
	../src/parser.h \
	../src/parser.c

c99_CFLAGS = \
	-Wall -DYYDEBUG=1

c99_LDFLAGS =

c99_LDADD =

../src/parser.c : ../src/parser.y
	$(PARSER) $(AM_YFLAGS) -o $@ $<

test :
	./c99 < test.c




