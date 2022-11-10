lib_LTLIBRARIES = libhoge.la

dist_data_DATA = CMakeLists.txt

libhoge_la_SOURCES = \
	./src/hoge.c \
	./inc/hoge.h

include_HEADERS = \
	./inc/hoge.h

libhoge_la_CFLAGS = \
	-I./inc \
	-I$(top_srcdir)/libfoo/inc

libhoge_la_LDFLAGS = \
	-no-undefined \
	-avoid-version

