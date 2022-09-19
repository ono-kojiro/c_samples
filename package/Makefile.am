ACLOCAL_AMFLAGS = -I config

SUBDIRS = libmylib myapp myscript


DEB_REPO_ROOT = /home/share/mydebrepo
RPM_REPO_ROOT = /home/share/myrpmrepo


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

rpm :
	rm -rf $(top_srcdir)/rpmbuild
	mkdir -p $(top_srcdir)/rpmbuild/SOURCES/
	cp -f $(PACKAGE_NAME)-$(PACKAGE_VERSION).tar.gz $(top_srcdir)/rpmbuild/SOURCES/
	rpmbuild --bb akubi.spec \
		--define "_topdir $(abs_top_srcdir)/rpmbuild" \
		--target x86_64-linux-gnu

rpmrepo :
	mkdir -p $(RPM_REPO_ROOT)/Packages
	cp -f rpmbuild/RPMS/x86_64/$(PACKAGE_NAME)-$(PACKAGE_VERSION)-1.x86_64.rpm \
		$(RPM_REPO_ROOT)/Packages
	createrepo_c --update $(RPM_REPO_ROOT)

rpminstall :
	fakechroot fakeroot /usr/bin/dnf -y --releasever=22.04 \
		--installroot=$(HOME)/.local install $(PACKAGE_NAME)

rpmuninstall :
	fakechroot fakeroot /usr/bin/dnf dnf -y --releasever=22.04 \
		--installroot=$(HOME)/.local remove $(PACKAGE_NAME)

