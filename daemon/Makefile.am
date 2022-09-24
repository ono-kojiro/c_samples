ACLOCAL_AMFLAGS = -I config

SUBDIRS = src \
	client

start :
	$(MAKE) -C src start

stop :
	$(MAKE) -C src stop

package :
	$(MAKE) install DESTDIR=`pwd`/$(PACKAGE)-$(VERSION)
	DESTDIR=`pwd`/$(PACKAGE)-$(VERSION) sh mkdebpkg.sh package
