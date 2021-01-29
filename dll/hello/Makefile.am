bin_PROGRAMS = hello

hello_DEPENDENCIES = \
	$(top_builddir)/libhello/libhello.la

hello_SOURCES = \
	./src/main.c

hello_CFLAGS = \
	-Wall \
	-I$(top_srcdir)/libhello/src

hello_LDFLAGS =

hello_LDADD = \
	$(top_builddir)/libhello/libhello.la

test :
	./hello

