ACLOCAL_AMFLAGS = -I config

bin_PROGRAMS = timer

timer_SOURCES = \
	main.c

timer_CFLAGS = \
	@libevent_CFLAGS@

timer_LDADD = \
	@libevent_LIBS@

test :
	./timer output.bin

debug :
	./timer -d output.bin


