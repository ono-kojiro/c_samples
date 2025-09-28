SRCS = main.c
OBJS = $(SRCS:.c=.o)
PROG = example


CFLAGS != pkg-config --cflags gtk+-2.0

LIBS   != pkg-config --libs   gtk+-2.0

all : obj prog

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

clean :
	rm -rf $(OBJS) $(PROG)

