lib_LTLIBRARIES = liblexer.la

LEXER = flex

liblexer_la_SOURCES = \
	lexer.l

BUILT_SOURCES = \
	lexer.c

liblexer_la_CFLAGS = \
	-I$(top_builddir)/parser \
	-Wall -DYYDEBUG=1

