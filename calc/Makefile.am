ACLOCAL_AMFLAGS = -I config

SUBDIRS = \
	tools \
	parser \
	scanner \
	mycalc \
	tests

debian :
	sh mkpackage.sh ctrl \
		-o $(PACKAGE_NAME)_$(PACKAGE_VERSION).debian.tar.xz \
		-p $(PACKAGE_NAME) -v $(PACKAGE_VERSION)

dsc :
	$(MAKE) dist-xz distdir=$(PACKAGE_NAME)_$(PACKAGE_VERSION).orig
	sh mkpackage.sh dsc \
		-p $(PACKAGE_NAME) -v $(PACKAGE_VERSION) \
		-o $(PACKAGE_NAME)_$(PACKAGE_VERSION).dsc \
		$(PACKAGE_NAME)_$(PACKAGE_VERSION).orig.tar.xz \
		$(PACKAGE_NAME)_$(PACKAGE_VERSION).debian.tar.xz

deb :
	$(MAKE) debian dsc
	rm -rf $(PACKAGE_NAME)-$(PACKAGE_VERSION)
	dpkg-source -x $(PACKAGE_NAME)_$(PACKAGE_VERSION).dsc
	cd $(PACKAGE_NAME)-$(PACKAGE_VERSION) && \
		dpkg-buildpackage -rfakeroot -b -us -uc
	rm -rf $(PACKAGE_NAME)-$(PACKAGE_VERSION)

.PHONY : \
	debian dsc deb

