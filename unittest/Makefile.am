ACLOCAL_AMFLAGS = -I config

SUBDIRS = \
	tools \
	parser \
	scanner \
	calc \
    check \
    gtest \
    cunit \
    tests \
    ctest

ctest :
	$(MAKE) -C ctest check

.PHONY : \
	ctest

