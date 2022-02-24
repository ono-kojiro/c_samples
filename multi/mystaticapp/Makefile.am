bin_PROGRAMS = mystaticapp

mystaticapp_SOURCES = \
	mystaticapp.c

mystaticapp_CFLAGS = \
    -I$(top_srcdir)/libmystaticlib

mystaticapp_LDFLAGS = \
    -L$(top_builddir)/libmystaticlib

mystaticapp_LDADD = \
	-lmystaticlib \
    -lm

check :
	./mystaticapp

