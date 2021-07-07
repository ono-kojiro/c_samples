GPERFS = baudrate.gperf

GENCODES = $(GPERFS:.gperf=.c)

SRCS = serial.c $(GENCODES)
OBJS = $(SRCS:.c=.o)
PROG = serial

BAUDRATE = 115200

all : gen obj prog

gen : $(GENCODES)

prog : $(PROG)

$(PROG) : $(OBJS)
	$(CC) -o $@ $(OBJS) -levent

baudrate.c : baudrate.gperf
	gperf --no-strlen --output-file=$@ $<

obj : $(OBJS)

%.o : %.c
	$(CC) -c -o $@ $<

clean :
	rm -f $(OBJS) $(PROG)

test3 :
	./$(PROG) -p /dev/pts/3 -b $(BAUDRATE)

test5 :
	./$(PROG) -p /dev/pts/5 -b $(BAUDRATE)

setup :
	sudo apt -y install socat

start :
	socat -d -d \
		pty,raw,echo=0,b115200 \
		pty,raw,echo=0,b115200 \
		&

stop :
	pkill socat

