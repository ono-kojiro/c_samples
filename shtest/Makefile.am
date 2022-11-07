ACLOCAL_AMFLAGS = -I config

SUBDIRS = src tests

EXTRA_DIST = shtest.spec

rpm :
	$(MAKE) dist
	rm -rf ./rpmbuild
	mkdir -p ./rpmbuild
	rpmbuild -bb shtest.spec \
		--define "_topdir $(abs_top_srcdir)/rpmbuild" \
        --define "_sourcedir $(abs_top_srcdir)" \
		--target=x86_64-linux-gnu

debian :
	sh mkpackage.sh ctrl \
		-o $(PACKAGE_NAME)_$(PACKAGE_VERSION).debian.tar.xz \
		-p $(PACKAGE_NAME) -v $(PACKAGE_VERSION)

dsc :
	$(MAKE) dist
	mv -f \
		$(PACKAGE_NAME)-$(PACKAGE_VERSION).tar.gz \
		$(PACKAGE_NAME)_$(PACKAGE_VERSION).orig.tar.gz
	
	sh mkpackage.sh dsc \
		-p $(PACKAGE_NAME) -v $(PACKAGE_VERSION) \
		-o $(PACKAGE_NAME)_$(PACKAGE_VERSION).dsc \
		$(PACKAGE_NAME)_$(PACKAGE_VERSION).orig.tar.gz \
		$(PACKAGE_NAME)_$(PACKAGE_VERSION).debian.tar.xz

deb :
	$(MAKE) debian dsc
	rm -rf $(PACKAGE_NAME)-$(PACKAGE_VERSION)
	dpkg-source -x $(PACKAGE_NAME)_$(PACKAGE_VERSION).dsc
	cd $(PACKAGE_NAME)-$(PACKAGE_VERSION) && \
		dpkg-buildpackage -rfakeroot -b -us -uc
	rm -rf $(PACKAGE_NAME)-$(PACKAGE_VERSION)

.PHONY : \
	rpm dsc debian deb

