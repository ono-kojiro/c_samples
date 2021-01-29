lib_LTLIBRARIES = libhello.la

libhello_la_SOURCES = \
	./src/hello.h \
	./src/hello.c

libhello_la_CFLAGS = \
	-Wall \
	$(AM_CFLAGS)

libhello_la_LDFLAGS = \
	-no-undefined \
	-avoid-version \
	-rpath $(libdir)



