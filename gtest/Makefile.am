ACLOCAL_AMFLAGS = -I config

SUBDIRS = gtest .

bin_PROGRAMS = test_calc

test_calc_SOURCES = \
    calc.c \
    calc.h \
    test_calc.c

test_calc_CFLAGS = \
    -I${HOME}/.local/include

test_calc_LDFLAGS = \
    -L${HOME}/.local/lib \
    -L${top_builddir}/googletest/lib

test_calc_LDADD = -lgtest -lgtest_main

TESTS = test_calc

