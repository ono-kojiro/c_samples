ACLOCAL_AMFLAGS = -I config

SUBDIRS = src

package :
	$(MAKE) install DESTDIR=`pwd`/$(PACKAGE)-$(VERSION)
	DESTDIR=`pwd`/$(PACKAGE)-$(VERSION) sh mkdebpkg.sh package
