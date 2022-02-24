ACLOCAL_AMFLAGS = -I config

SUBDIRS = \
    libmystaticlib \
    mystaticapp \
    libmysharedlib \
    mysharedapp

package :
	VERSION=0.0.1 \
	HOME=$(PWD) \
	QA_SKIP_BUILD_ROOT=1 \
    rpmbuild -bb \
    --nodeps \
    --target=aarch64-poky-linux \
    --define="_build x86_64-linux-gnu" \
    --define="_topdir $(PWD)/rpmbuild" \
    --define="_lib lib" \
    --define="_libdir %{_prefix}/lib" \
    --define="version $(VERSION)" \
    --define="dist .poky" \
    multi.spec

