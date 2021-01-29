ACLOCAL_AMFLAGS = -I config

SUBDIRS = \
	libhello \
	hello

copy :
	mkdir -p test
	cp -f libhello/linux/.libs/libhello.dll test/
	cp -f hello/linux/.libs/hello.exe test/

test :
	$(MAKE) -C hello test

