TESTS = \
  05-cunit_simple

bin_PROGRAMS = \
  05-cunit_simple

COMMON_CFLAGS = \
    -I$(top_builddir)/parser \
    -I$(top_builddir)/scanner

COMMON_LDADD = \
    $(top_builddir)/parser/libparser.la \
    $(top_builddir)/scanner/libscanner.la
    
05_cunit_simple_SOURCES = 05-cunit_simple.c
05_cunit_simple_CFLAGS  = $(COMMON_CFLAGS) @CUNIT_CFLAGS@
05_cunit_simple_LDADD   = $(COMMON_LDADD)   @CUNIT_LIBS@ -lm

