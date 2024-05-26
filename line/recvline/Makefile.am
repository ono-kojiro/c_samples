bin_PROGRAMS = recvline

recvline_SOURCES = recvline.c

recvline_CFLAGS = ${LIBEVENT_CFLAGS}

recvline_LDFLAGS = -levent -L/usr/local/lib

test :
	./recvline -h localhost -p 9999

