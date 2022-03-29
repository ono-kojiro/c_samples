#!/bin/sh

export AUTOCONF=`which autoconf`
export ACLOCAL=`which aclocal`
export AUTOHEADER=`which autoheader`
export AUTOM4TE=`which autom4te`
export AUTOMAKE=`which automake`
export LIBTOOLIZE=`which libtoolize`
export M4=`which m4`
export AUTORECONF=`which autoreconf`

export AUTOMAKE="$AUTOMAKE --libdir=/home/kojiro/tmp/autotools/usr/share/automake-1.16"

# change autom4te perllibdir
export autom4te_perllibdir=/home/kojiro/tmp/autotools/usr/share/autoconf

export PERL5LIB=/home/kojiro/tmp/autotools/usr/share/autoconf
export PERL5LIB=$PERL5LIB:/home/kojiro/tmp/autotools/usr/share/automake-1.16
export AUTOMAKE_UNINSTALLED=1

export ACLOCAL_AUTOMAKE_DIR=/home/kojiro/tmp/autotools/usr/share/aclocal-1.16
#export trailer_m4=/home/kojiro/tmp/autotools/usr/share/autoconf/autoconf/trailer.m4
export trailer_m4=`pwd`/dummy.m4


$AUTORECONF -vi

sh configure

