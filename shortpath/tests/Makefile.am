TESTS = 01-basic.t check_shortpath

EXECUTABLE=$(top_builddir)/shortpath/shortpath

check_SCRIPTS = 01-basic.t

check_PROGRAMS = check_shortpath

check_shortpath_SOURCES = \
    check_shortpath.c

check_shortpath_CFLAGS = \
    -I$(top_srcdir)/shortpath \
    @CHECK_CFLAGS@

check_shortpath_LDADD = \
    $(top_builddir)/shortpath/libshortpath.a \
    @CHECK_LIBS@

test : check

.PHONY : test


