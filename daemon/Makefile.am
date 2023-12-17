ACLOCAL_AMFLAGS = -I config

SUBDIRS = src \
	client

prepare :
	sudo apt -y install libevent-dev

start :
	$(MAKE) -C tests start

debug :
	$(MAKE) -C tests debug

stop :
	$(MAKE) -C tests stop

test :
	$(MAKE) -C tests test

package :
	$(MAKE) install DESTDIR=`pwd`/$(PACKAGE)-$(VERSION)
	DESTDIR=`pwd`/$(PACKAGE)-$(VERSION) sh mkdebpkg.sh package

