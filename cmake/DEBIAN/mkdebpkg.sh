#!/bin/sh

BASENAME=cmake_sample
VERSION=1.0.4
ARCHIVE=$BASENAME-$VERSION.tar.gz
	
DESTDIR=~/tmp/$BASENAME-$VERSION
OUTPUTDIR=.

_extract()
{
	if [ ! -e $BASENAME-$VERSION ]; then
		tar xzvf $ARCHIVE;
	fi
}

_configure()
{
	cd $BASENAME-$VERSION
	#make config
	sh build.sh config
	cd ..
}

_build()
{
	cd $BASENAME-$VERSION
	#make
	sh build.sh build
	cd ..
}

_install()
{
	cd $BASENAME-$VERSION
	#make install DESTDIR=$DESTDIR
	sh build.sh install
	cd ..
}

_make_package()
{
	cd $BASENAME-$VERSION
	mkdir -p $DESTDIR/DEBIAN
	cp ./DEBIAN/control $DESTDIR/DEBIAN
	fakeroot dpkg-deb --build $DESTDIR $OUTPUTDIR
	cd ..
}

_extract

_configure

_build

_install

_make_package

