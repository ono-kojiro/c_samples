PORT = /dev/pts/4

bin_PROGRAMS = myterm

BUILT_SOURCES = scanner.c

myterm_SOURCES = \
	main.c \
	scanner.c \
	userdata.c

myterm_CFLAGS = \
	-I$(top_srcdir)/common \
	@libevent_CFLAGS@

myterm_LDADD = \
	$(top_srcdir)/common/libcommon.la \
	@libevent_LIBS@

.re.c :
	re2c --debug-output -o $@ $<

test :
	./myterm -p $(PORT) -b 115200

debug :
	gdb ./myterm core
