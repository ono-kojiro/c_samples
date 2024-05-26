bin_PROGRAMS = recvline

recvline_SOURCES = recvline.c

recvline_CFLAGS = ${LIBEVENT_CFLAGS}

recvline_LDFLAGS = -L/usr/local/lib
recvline_LDADD   = -levent

test :
	./recvline -h localhost -p 9999

