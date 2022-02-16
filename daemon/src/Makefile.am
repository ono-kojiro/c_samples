bin_PROGRAMS = mydaemon

mydaemon_SOURCES = \
	mydaemon.c

mydaemon_DATA = mydaemon.service
mydaemondir = $(sysconfdir)/systemd/system

dist_pkgdata_DATA = mydaemon.service

start :
	./mydaemon

stop :
	pkill mydaemon

