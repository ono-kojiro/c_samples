ACLOCAL_AMFLAGS = -I config

EXTRA_DIST = debian

bin_PROGRAMS = simple

simple_SOURCES = simple.c

SUBDIRS = tests

dpkg :
	sh genctrl.sh
	$(MAKE) dist
	cp -f simple-0.0.1.tar.gz simple_0.0.1.tar.gz
	sh gendsc.sh
	rm -rf simple-0.0.1
	dpkg-source -x simple_0.0.1.dsc
	cd simple-0.0.1 && dpkg-buildpackage -rfakeroot -b -us -uc

    

