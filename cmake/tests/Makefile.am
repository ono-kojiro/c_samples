TESTS = check_hello check_test2

check_PROGRAMS = $(TESTS)

check_hello_SOURCES = \
	./src/check_hello.c

check_hello_CFLAGS = \
	-I$(top_srcdir)/libhello/src \
	@CHECK_CFLAGS@

check_hello_LDFLAGS = 

check_hello_LDADD = \
	$(top_builddir)/libhello/libhello.la \
	@CHECK_LIBS@

check_test2_SOURCES = \
	./src/check_test2.c

check_test2_CFLAGS = \
	@CHECK_CFLAGS@

check_test2_LDFLAGS =

check_test2_LDADD = \
	@CHECK_LIBS@

