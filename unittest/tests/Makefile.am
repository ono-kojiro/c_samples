EXTRA_DIST = 01-run.sh

TESTS = \
  01-run.sh \
  02-check_simple \
  03-check_xml \
  04-gtest_simple \
  05-cunit_simple

check_SCRIPTS = 01-run.sh

bin_PROGRAMS = \
  02-check_simple \
  03-check_xml \
  04-gtest_simple \
  05-cunit_simple
    
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

04_gtest_simple_SOURCES = 04-gtest_simple.cpp
04_gtest_simple_CPPFLAGS = \
    $(COMMON_CFLAGS) \
    -I/usr/src/googletest/googletest/include
04_gtest_simple_LDFLAGS = -L$(top_builddir)/tools/gtest/lib
04_gtest_simple_LDADD  = \
    $(COMMON_LDADD) \
    -lgtest -lgtest_main

05_cunit_simple_SOURCES = 05-cunit_simple.c
05_cunit_simple_CFLAGS  = $(COMMON_CFLAGS) @CUNIT_CFLAGS@
05_cunit_simple_LDADD   = $(COMMON_LDADD)   @CUNIT_LIBS@ -lm

check : 03-plus.xml

03-plus.xml : 03-plus-check.xml XML_for_JUnit.xsl
	python3 xml2junit.py -o $@ --xsl XML_for_JUnit.xsl $<

XML_for_JUnit.xsl :
	curl -O -L https://raw.githubusercontent.com/libcheck/check/master/contrib/XML_for_JUnit.xsl


.PHONY : xsl


