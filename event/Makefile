SRCS = ev2.c
OBJS = $(SRCS:.c=.o)
PROG = ev2

all : obj prog

obj : $(OBJS)

prog : $(PROG)

$(PROG) : $(OBJS)
	gcc -o $@ $(OBJS) -levent_core

%.o : %.c
	gcc -c -o $@ $<

clean :
	rm -f $(OBJS) $(PROG)

test :
	./$(PROG)

.PHONY : \
	all clean test \
		obj prog

