ACLOCAL_AMFLAGS = -I config

SUBDIRS = \
	tools \
	parser \
	scanner \
	calc \
    tests \
    ctest

ctest :
	$(MAKE) -C ctest check

.PHONY : \
	ctest

