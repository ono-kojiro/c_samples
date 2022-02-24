bin_PROGRAMS = mysharedapp

mysharedapp_SOURCES = \
	mysharedapp.c

mysharedapp_CFLAGS = \
    -I$(top_srcdir)/libmysharedlib

mysharedapp_LDFLAGS = \
    -L$(top_builddir)/libmysharedlib

mysharedapp_LDADD = \
	$(top_builddir)/libmysharedlib/libmysharedlib.la \
    -lm

check :
	./mysharedapp

