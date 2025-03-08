bin_PROGRAMS = myserver

myserver_SOURCES = \
	server.c

myserver_LDFLAGS = 
myserver_LDADD = -levent

test :
	nc localhost 1234

start :
	$(top_builddir)/myserver -p 1234

debug :
	$(top_builddir)/myserver -p 1234 -F

stop :
	-pkill myserver

