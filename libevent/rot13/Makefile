SRCS = main.c
OBJS = $(SRCS:.c=.o)

LDADD = -levent

PROG = rot13

all : obj prog

obj : $(OBJS)

prog : $(PROG)


%.o : %.c
	gcc -c -o $@ $<

$(PROG) : $(OBJS)
	gcc -o $@ $(OBJS) $(LDADD)

clean :
	rm -f $(OBJS) $(PROG)

test :
	./$(PROG) -o output.log

