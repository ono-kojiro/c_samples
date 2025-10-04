bin_PROGRAMS = client

client_SOURCES = \
  recv_handler.c \
  client.c \
  common.c

client_CFLAGS = \
	@CFLAGS@ \
	@LIBEVENT_CFLAGS@

client_LDADD = \
  @LIBS@ \
  @LIBEVENT_LIBS@

test :
	./client --host localhost --port 1234



