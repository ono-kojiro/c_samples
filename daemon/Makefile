SRCS = daemon.c
OBJS = $(SRCS:.c=.o)

PROG = mydaemon

all : obj prog

obj : $(OBJS)

prog : $(PROG)

$(PROG) : $(OBJS)
	gcc -o $@ $(OBJS)

%.o : %.c
	gcc -c -o $@ $<

start :
	./$(PROG)

stop :
	@pid=`pgrep $(PROG)`; \
	if [ "x$$pid" != "x" ]; then \
		echo "kill $(PROG)"; \
		kill $$pid; \
	else \
		echo no $(PROG) running; \
	fi

status :
	ps -ef | grep $(PROG)

