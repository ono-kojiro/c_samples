lib_LTLIBRARIES = libfoo.la

dist_data_DATA = CMakeLists.txt

libfoo_la_SOURCES = \
	./src/foo.c \
	./inc/foo.h

include_HEADERS = \
	./inc/foo.h

libfoo_la_CFLAGS = \
	-I./inc

libfoo_la_LDFLAGS = \
	-no-undefined \
	-avoid-version

