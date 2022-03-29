#!/bin/sh

. ../autotools.bashrc

rm -rf autom4te.cache
rm -rf config

ACLOCAL=`which aclocal`

mkdir -p config

ACLOCAL="$ACLOCAL --automake-acdir=$HOME/tmp/autotools/usr/share/aclocal-1.16"

$ACLOCAL

autoheader

rm -f dummy.m4
touch dummy.m4

#export AUTOM4TE='/home/kojiro/tmp/autotools/usr/bin/autom4te'
AUTOM4TE=`which autom4te`
#export trailer_m4='/home/kojiro/tmp/autotools/usr/share/autoconf/autoconf/trailer.m4'
export trailer_m4=`pwd`/dummy.m4

libtoolize

autom4te_perllibdir=$HOME/tmp/autotools/usr/share/autoconf

autoconf -i \
	-I $HOME/tmp/autotools/usr/share/autoconf/autoconf \
	-I $HOME/tmp/autotools/usr/share/autoconf/Autom4te

ACLOCAL="$ACLOCAL" \
automake \
	--foreign \
	--add-missing \
	--force-missing \
	--copy \
	--libdir="$HOME/tmp/autotools/usr/share/automake-1.16"

