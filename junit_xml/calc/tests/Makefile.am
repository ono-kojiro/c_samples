EXTRA_DIST = 01-shell.sh

TESTS = 01-shell.sh 02-check 03-cunit

check_SCRIPTS = 01-shell.sh

bin_PROGRAMS = 02-check 03-cunit
    
COMMON_CFLAGS = \
    -I$(top_builddir)/parser \
    -I$(top_builddir)/scanner

COMMON_LDADD = \
    $(top_builddir)/parser/libparser.la \
    $(top_builddir)/scanner/libscanner.la

02_check_SOURCES = 02-check.c
02_check_CFLAGS  = $(COMMON_CFLAGS) @CHECK_CFLAGS@
02_check_LDADD   = $(COMMON_LDADD)   @CHECK_LIBS@

03_cunit_SOURCES = 03-cunit.c
03_cunit_CFLAGS = $(COMMON_CFLAGS) @CUNIT_CFLAGS@
03_cunit_LDADD = $(COMMON_LDADD)   @CUNIT_LIBS@ -lm

check : 02-check.xml 03-cunit.xml

02-check.xml : 02-check-check.xml XML_for_JUnit.xsl
	python3 xml2junit.py -o $@ --xsl XML_for_JUnit.xsl $<

03-cunit.xml : 03-cunit-Results.xml cunit-to-junit.xsl
	python3 xml2junit.py -o $@ --xsl cunit-to-junit.xsl $<

xsl : XML_for_JUnit.xsl cunit-to-junit.xsl

XML_for_JUnit.xsl :
	curl -O -L https://raw.githubusercontent.com/libcheck/check/master/contrib/XML_for_JUnit.xsl

cunit-to-junit.xsl :
	curl -O -L https://raw.githubusercontent.com/shawnliang/cunit-to-junit/master/cunit-to-junit.xsl

.PHONY : xsl

