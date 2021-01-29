#!/bin/sh

mkdir -p config

aclocal -I config
autoheader
automake -a
autoconf

