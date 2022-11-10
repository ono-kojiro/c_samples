bin_PROGRAMS = hello

dist_data_DATA = CMakeLists.txt

hello_SOURCES = \
	./src/main.c

hello_CFLAGS = \
	-I$(top_srcdir)/libhoge/inc \
	-I$(top_srcdir)/libfoo/inc

hello_LDFLAGS = 

hello_LDADD = \
	$(top_builddir)/libhoge/libhoge.la \
	$(top_builddir)/libfoo/libfoo.la

