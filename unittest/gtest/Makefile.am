bin_PROGRAMS = \
  04-gtest_simple
    
COMMON_CFLAGS = \
    -I$(top_builddir)/parser \
    -I$(top_builddir)/scanner

COMMON_LDADD = \
    $(top_builddir)/parser/libparser.la \
    $(top_builddir)/scanner/libscanner.la

04_gtest_simple_SOURCES = 04-gtest_simple.cpp
04_gtest_simple_CPPFLAGS = \
    $(COMMON_CFLAGS) \
    -I/usr/src/googletest/googletest/include
04_gtest_simple_LDFLAGS = -L$(top_builddir)/tools/gtest/lib
04_gtest_simple_LDADD  = \
    $(COMMON_LDADD) \
    -lgtest -lgtest_main

check :
	./04-gtest_simple

