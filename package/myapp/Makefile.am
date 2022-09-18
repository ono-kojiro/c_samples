ACLOCAL_AMFLAGS = -I config

SUBDIRS = src

EXTRA_DIST = \
	debian \
	myapp.spec

rpm :
	$(MAKE) dist
	rm -rf ./rpmbuild
	mkdir -p ./rpmbuild
	rpmbuild -bb $(PACKAGE_NAME).spec \
		--define "_topdir $(abs_top_srcdir)/rpmbuild" \
        --define "_sourcedir $(abs_top_srcdir)" \
		--target=x86_64-linux-gnu

dpkg :
	sh ../mkpackage.sh ctrl --package $(PACKAGE_NAME) --version $(PACKAGE_VERSION)
	$(MAKE) dist
	cp -f $(PACKAGE_NAME)-$(PACKAGE_VERSION).tar.gz \
		$(PACKAGE_NAME)_$(PACKAGE_VERSION).tar.gz
	sh ../mkpackage.sh dsc  --package $(PACKAGE_NAME) --version $(PACKAGE_VERSION)
	
	rm -rf ./debbuild
	echo "extract source ..."
	dpkg-source -x $(PACKAGE_NAME)_$(PACKAGE_VERSION).dsc ./debbuild
	echo "build package ..."
	cd debbuild && \
		dpkg-buildpackage -rfakeroot -b -us -uc


