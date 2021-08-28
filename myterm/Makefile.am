PORT = /dev/pts/4

bin_PROGRAMS = myterm

BUILT_SOURCES = scanner.c

myterm_SOURCES = \
	main.c \
	scanner.c \
	userdata.c \
	baudrate.c

myterm_CFLAGS = \
	@LIBEVENT_CFLAGS@

myterm_LDADD = \
	@LIBEVENT_LIBS@

.re.c :
	re2c --debug-output -o $@ $<

test :
	./myterm -p $(PORT) -b 115200

debug :
	gdb ./myterm core
