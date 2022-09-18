ACLOCAL_AMFLAGS = -I config

SUBDIRS = \
  src \
  tests

EXTRA_DIST = libmylib.spec

#dist_pkgdata_DATA = LICENSE

rpm:
	$(MAKE) dist
	rm -rf ./rpmbuild
	mkdir -p ./rpmbuild/SOURCES/
	rpmbuild --bb libmylib.spec \
		--define "_topdir $(abs_top_srcdir)/rpmbuild" \
		--define "_sourcedir $(abs_top_srcdir)" \
		--target x86_64-linux-gnu

