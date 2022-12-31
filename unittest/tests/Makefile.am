EXTRA_DIST = 01-run.sh

TESTS = 01-run.sh 02-init 03-plus 04-minus 05-times

check_SCRIPTS = 01-run.sh

bin_PROGRAMS = 02-init 03-plus 04-minus 05-times
    
COMMON_CFLAGS = \
    -I$(top_builddir)/parser \
    -I$(top_builddir)/scanner

COMMON_LDADD = \
    $(top_builddir)/parser/libparser.la \
    $(top_builddir)/scanner/libscanner.la

02_init_SOURCES = 02-init.c
02_init_CFLAGS = $(COMMON_CFLAGS) @CHECK_CFLAGS@
02_init_LDADD = $(COMMON_LDADD)   @CHECK_LIBS@

03_plus_SOURCES = 03-plus.c
03_plus_CFLAGS = $(COMMON_CFLAGS) @CHECK_CFLAGS@
03_plus_LDADD = $(COMMON_LDADD)   @CHECK_LIBS@

04_minus_SOURCES = 04-minus.cpp
04_minus_CPPFLAGS = \
    $(COMMON_CFLAGS) \
    -I/usr/src/googletest/googletest/include
04_minus_LDFLAGS = -L$(top_builddir)/gtest/lib
04_minus_LDADD  = \
    $(COMMON_LDADD) \
    -lgtest -lgtest_main

05_times_SOURCES = 05-times.c
05_times_CFLAGS = $(COMMON_CFLAGS) @CUNIT_CFLAGS@
05_times_LDADD = $(COMMON_LDADD)   @CUNIT_LIBS@ -lm

check : 03-plus.xml

03-plus.xml : 03-plus-check.xml XML_for_JUnit.xsl
	python3 xml2junit.py -o $@ --xsl XML_for_JUnit.xsl $<

XML_for_JUnit.xsl :
	curl -O -L https://raw.githubusercontent.com/libcheck/check/master/contrib/XML_for_JUnit.xsl


.PHONY : xsl


