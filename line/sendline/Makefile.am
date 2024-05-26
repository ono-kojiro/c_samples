bin_PROGRAMS = sendline

sendline_SOURCES = sendline.c

sendline_CFLAGS = ${LIBEVENT_CFLAGS}

sendline_LDFLAGS = -levent -L/usr/local/lib

test :
	./sendline -h localhost -p 9999

