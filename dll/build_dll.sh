#!/bin/sh

autoreconf -vi

LDFLAGS="" \
sh configure \
	--host=x86_64-w64-mingw32 \
	--prefix=/mingw64 \
	--disable-static \
	--enable-shared

make

