bin_PROGRAMS = mydaemond

mydaemond_SOURCES = \
	mydaemon.c

mydaemond_DATA = mydaemon.service
mydaemonddir = /lib/systemd/system

dist_pkgdata_DATA = mydaemon.service
#noinst_pkgdata_DATA = mydaemon.service

start :
	./mydaemond

stop :
	pkill mydaemond

