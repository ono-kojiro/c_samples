bin_PROGRAMS = sendline

sendline_SOURCES = sendline.c

sendline_CFLAGS = ${LIBEVENT_CFLAGS}

sendline_LDFLAGS = -L/usr/local/lib
sendline_LDADD   = -levent

test :
	./sendline -h localhost -p 9999

