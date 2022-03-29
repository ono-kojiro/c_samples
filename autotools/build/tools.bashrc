path_add() {
  if [ -d "$1" ]; then
    echo ":$PATH:" | grep ":$1:" > /dev/null 2>&1
	if [ $? -ne 0 ]; then
      PATH="$1:$PATH"
	fi
  fi
}

add_ld_library_path() {
  if [ -d "$1" ]; then
    echo ":$LD_LIBRARY_PATH:" | grep ":$1:" > /dev/null 2>&1
	if [ $? -ne 0 ]; then
      LD_LIBRARY_PATH="$1:$LD_LIBRARY_PATH"
	fi
  fi
}

TOOLS=~/tmp/autotools-1.0.0

path_add $TOOLS/usr/bin
export PATH

add_ld_library_path $TOOLS/usr/lib
export LD_LIBRARY_PATH


export AUTOCONF=`which autoconf`
export ACLOCAL=`which aclocal`
#export ACLOCAL="$ACLOCAL --automake-acdir=$TOOLS/usr/share/automake-1.16"
export ACLOCAL="$ACLOCAL --automake-acdir=$TOOLS/usr/share/aclocal-1.16"
export ACLOCAL="$ACLOCAL --system-acdir=$TOOLS/usr/share/aclocal"
export ACLOCAL="$ACLOCAL -I $TOOLS/usr/share/autoconf"

export AUTOHEADER=`which autoheader`
export AUTOM4TE=`which autom4te`
export AUTOMAKE=`which automake`
export AUTOPOINT=`which autopoint`
export LIBTOOLIZE=`which libtoolize`
export M4=`which m4`
export AUTORECONF=`which autoreconf`

export AUTOMAKE="$AUTOMAKE --libdir=$TOOLS/usr/share/automake-1.16"

# change autom4te perllibdir
export autom4te_perllibdir=$TOOLS/usr/share/autoconf

export PERL5LIB=$TOOLS/usr/share/autoconf
export PERL5LIB=$PERL5LIB:$TOOLS/usr/share/automake-1.16
export AUTOMAKE_UNINSTALLED=1

export ACLOCAL_AUTOMAKE_DIR=$TOOLS/usr/share/aclocal-1.16
export trailer_m4=`pwd`/dummy.m4

export AC_MACRODIR=$TOOLS/usr/share/autoconf

cwd=`pwd`

cp -f $TOOLS/usr/share/autoconf/autom4te.cfg .
sed -i -e "s|'/usr/share/autoconf'|'$TOOLS/usr/share/autoconf'|" autom4te.cfg
export AUTOM4TE_CFG=$cwd/autom4te.cfg
#export AUTOM4TE_CFG=$TOOLS/usr/share/autoconf


# for libtool
export _lt_pkgdatadir=$TOOLS/usr/share/libtool

# for autoconf
touch dummy.m4




