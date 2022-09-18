ACLOCAL_AMFLAGS = -I config

EXTRA_DIST = debian

bin_PROGRAMS = simple

simple_SOURCES = simple.c

SUBDIRS = tests

DEB_REPO_ROOT = /home/share/mydebrepo

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

debrepo :
	sh create-deb-repo.sh init -r $(DEB_REPO_ROOT)
	cp $(PACKAGE_NAME)_$(PACKAGE_VERSION)_amd64.deb \
	 $(DEB_REPO_ROOT)/dists/jammy/main/binary-amd64
	sh create-deb-repo.sh package -r $(DEB_REPO_ROOT)
	sh create-deb-repo.sh release -r $(DEB_REPO_ROOT)
	sh create-deb-repo.sh list    -r $(DEB_REPO_ROOT)

