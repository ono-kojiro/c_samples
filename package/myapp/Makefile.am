ACLOCAL_AMFLAGS = -I config

SUBDIRS = src

EXTRA_DIST = myapp.spec

rpm :
	$(MAKE) dist
	rm -rf ./rpmbuild
	mkdir -p ./rpmbuild
	rpmbuild -bb myapp.spec \
		--define "_topdir $(abs_top_srcdir)/rpmbuild" \
        --define "_sourcedir $(abs_top_srcdir)" \
		--target=x86_64-linux-gnu

