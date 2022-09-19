ACLOCAL_AMFLAGS = -I config

SUBDIRS = src tests

EXTRA_DIST = myscript.spec

rpm :
	$(MAKE) dist
	rm -rf ./rpmbuild
	mkdir -p ./rpmbuild
	rpmbuild -bb myscript.spec \
		--define "_topdir $(abs_top_srcdir)/rpmbuild" \
        --define "_sourcedir $(abs_top_srcdir)" \
		--target=x86_64-linux-gnu

