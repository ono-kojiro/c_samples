bin_PROGRAMS = example

example_SOURCES = example.c

example_CFLAGS = \
	-I$(top_builddir)/scanner

if USE_PARSER
example_CFLAGS += \
	-I$(top_builddir)/parser
endif

example_LDFLAGS = \
	$(SQLITE3_CFLAGS)

example_LDADD = \
	$(top_builddir)/scanner/libscanner.la


if USE_PARSER
example_LDADD += \
	$(top_builddir)/parser/libparser.la
endif

example_LDADD += \
	$(SQLITE3_LIBS)


