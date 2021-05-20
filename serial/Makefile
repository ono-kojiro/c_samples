SRCS = serial.c
OBJS = $(SRCS:.c=.o)
PROG = serial

all : obj prog

prog : $(PROG)

$(PROG) : $(OBJS)
	$(CC) -o $@ $(OBJS) -levent

obj : $(OBJS)

%.o : %.c
	$(CC) -c -o $@ $<

clean :
	rm -f $(OBJS) $(PROG)

test3 :
	./$(PROG) -p /dev/pts/3

test5 :
	./$(PROG) -p /dev/pts/5

setup :
	sudo apt -y install socat

start :
	socat -d -d \
		pty,raw,echo=0,b115200 \
		pty,raw,echo=0,b115200 \
		&

stop :
	pkill socat

