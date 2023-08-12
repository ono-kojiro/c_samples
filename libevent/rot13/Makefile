SRCS = main.c
OBJS = $(SRCS:.c=.o)

PROG = rot13

all : obj prog

obj : $(OBJS)

prog : $(PROG)


%.o : %.c
	gcc -c -o $@ $<

$(PROG) : $(OBJS)
	gcc -o $@ $(OBJS)

clean :
	rm -f $(OBJS) $(PROG)

test :
	./$(PROG) -o output.log

