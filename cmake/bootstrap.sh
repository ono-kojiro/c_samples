#!/bin/sh

mkdir -p config

aclocal -I config
libtoolize --copy
autoheader
automake -a
autoconf

