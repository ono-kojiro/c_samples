ACLOCAL_AMFLAGS = -I config

EXTRA_DIST = debian

bin_PROGRAMS = simple

simple_SOURCES = simple.c

SUBDIRS = tests

dpkg :
	sh mkpackage.sh ctrl --package $(PACKAGE_NAME) --version $(PACKAGE_VERSION)
	$(MAKE) dist
	cp -f $(PACKAGE_NAME)-$(PACKAGE_VERSION).tar.gz \
		$(PACKAGE_NAME)_$(PACKAGE_VERSION).tar.gz
	sh mkpackage.sh dsc  --package $(PACKAGE_NAME) --version $(PACKAGE_VERSION)
	
	rm -rf $(PACKAGE_NAME)-$(PACKAGE_VERSION)
	dpkg-source -x $(PACKAGE_NAME)_$(PACKAGE_VERSION).dsc
	cd $(PACKAGE_NAME)-$(PACKAGE_VERSION) && \
		dpkg-buildpackage -rfakeroot -b -us -uc

    

