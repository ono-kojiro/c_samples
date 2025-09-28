SRCS = main.c exampleapp.c exampleappwin.c resources.c
OBJS = $(SRCS:.c=.o)
PROG = example

PKGCONFIG != which pkg-config

CFLAGS != $(PKGCONFIG) --cflags gtk4

LIBS   != $(PKGCONFIG) --libs   gtk4

GLIB_COMPILE_RESOURCES != $(PKGCONFIG) --variable=glib_compile_resources gio-2.0


all : res obj prog

res : resources.c

resources.c: exampleapp.gresource.xml window.ui
	$(GLIB_COMPILE_RESOURCES) exampleapp.gresource.xml --target=$@ --sourcedir=. --generate-source

debug :
	@echo cflags is $(CFLAGS)
	@echo libs is $(LIBS)

	@echo hoge is $(HOGE)

obj : $(OBJS)

%.o : %.c
	cc $(CFLAGS) -c -o $@ $<


prog : $(PROG)

$(PROG) : $(OBJS)
	cc -o $@ $(OBJS) $(LIBS)

test :
	./$(PROG)

clean :
	rm -f $(OBJS) $(PROG)

