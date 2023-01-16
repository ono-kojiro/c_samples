bin_PROGRAMS = \
  02-check_simple \
  03-check_xml
    
COMMON_CFLAGS = \
    -I$(top_builddir)/parser \
    -I$(top_builddir)/scanner

COMMON_LDADD = \
    $(top_builddir)/parser/libparser.la \
    $(top_builddir)/scanner/libscanner.la

02_check_simple_SOURCES = 02-check_simple.c
02_check_simple_CFLAGS  = $(COMMON_CFLAGS) @CHECK_CFLAGS@
02_check_simple_LDADD   = $(COMMON_LDADD)   @CHECK_LIBS@

03_check_xml_SOURCES = 03-check_xml.c
03_check_xml_CFLAGS  = $(COMMON_CFLAGS) @CHECK_CFLAGS@
03_check_xml_LDADD   = $(COMMON_LDADD)   @CHECK_LIBS@

check :
	./02-check_simple
	./03-check_xml


