SRCS = main.c
OBJS = $(SRCS:.c=.o)

PROG = hello

all : obj prog

obj : $(OBJS)

prog : $(PROG)


%.o : %.c
	gcc -c -o $@ $<

$(PROG) : $(OBJS)
	gcc -o $@ $(OBJS) -lpthread

clean :
	rm -f $(OBJS) $(PROG)

test :
	./$(PROG) -o output.log

