SRCS = serial.c baudrate.c
OBJS = $(SRCS:.c=.o)
PROG = serial

BAUDRATE = 115200

all : obj prog

prog : $(PROG)

$(PROG) : $(OBJS)
	$(CC) -o $@ $(OBJS) -levent

obj : $(OBJS)

%.o : %.c
	$(CC) -c -o $@ $<

clean :
	rm -f $(OBJS) $(PROG)

server :
	./$(PROG) -p /dev/pts/3 -b $(BAUDRATE) -e

client :
	./$(PROG) -p /dev/pts/4 -b $(BAUDRATE)

setup :
	sudo apt -y install socat

start :
	socat -d -d \
		pty,raw,echo=0,b115200 \
		pty,raw,echo=0,b115200 \
		&

stop :
	pkill socat

