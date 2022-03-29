TOOLS=/opt/autotools

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

PATH=$TOOLS/usr/bin:$PATH
export PATH

#add_ld_library_path $TOOLS/usr/lib
LD_LIBRARY_PATH=$TOOLS/usr/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH

export ACLOCAL="$TOOLS/usr/bin/aclocal"
export ACLOCAL="$ACLOCAL --automake-acdir=$TOOLS/usr/share/aclocal-1.16"
export ACLOCAL="$ACLOCAL --system-acdir=$TOOLS/usr/share/aclocal"
export ACLOCAL="$ACLOCAL -I $TOOLS/usr/share/autoconf"

export AUTOHEADER=$TOOLS/usr/bin/autoheader

export AUTOMAKE=$TOOLS/usr/bin/automake
export AUTOMAKE="$AUTOMAKE --libdir=$TOOLS/usr/share/automake-1.16"

export AUTOPOINT=$TOOLS/usr/bin/autopoint
export LIBTOOLIZE=$TOOLS/usr/bin/libtoolize
export M4=$TOOLS/usr/bin/m4
export AUTORECONF=$TOOLS/usr/bin/autoreconf

export AUTOSCAN="$TOOLS/usr/bin/autoscan -B $TOOLS/usr/share/autoconf"

# for autoconf
autom4te_cfg="$TOOLS/usr/share/autoconf/autom4te.cfg"
if [ -e "$autom4te_cfg" ]; then
  sed -i -e "s|'/usr/share/autoconf'|'$TOOLS/usr/share/autoconf'|" \
    $autom4te_cfg
  export AUTOM4TE_CFG=$autom4te_cfg
fi

export AUTOM4TE=$TOOLS/usr/bin/autom4te

export PERL5LIB=$TOOLS/usr/share/autoconf
export PERL5LIB=$PERL5LIB:$TOOLS/usr/share/automake-1.16

export ACLOCAL_AUTOMAKE_DIR=$TOOLS/usr/share/aclocal-1.16

export trailer_m4=$TOOLS/usr/share/autoconf/autoconf/trailer.m4

export AUTOCONF=$TOOLS/usr/bin/autoconf

export AUTOHEADER=$TOOLS/usr/bin/autoheader
export _lt_pkgdatadir=$TOOLS/usr/share/libtool
export aclocaldir=$TOOLS/usr/share/libtool

