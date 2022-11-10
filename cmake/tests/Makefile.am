TESTS = check_hoge check_test2

check_PROGRAMS = $(TESTS)

check_hoge_SOURCES = \
	./src/check_hoge.c

check_hoge_CFLAGS = \
	-I$(top_srcdir)/libhoge/inc \
	@CHECK_CFLAGS@

check_hoge_LDFLAGS = 

check_hoge_LDADD = \
	$(top_builddir)/libhoge/libhoge.la \
	$(top_builddir)/libfoo/libfoo.la \
	@CHECK_LIBS@

check_test2_SOURCES = \
	./src/check_test2.c

check_test2_CFLAGS = \
	@CHECK_CFLAGS@

check_test2_LDFLAGS =

check_test2_LDADD = \
	@CHECK_LIBS@

