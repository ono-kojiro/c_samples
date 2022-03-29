TOOLS=~/tmp/autotools-1.0.1

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

path_add $TOOLS/usr/bin
export PATH

add_ld_library_path $TOOLS/usr/lib
export LD_LIBRARY_PATH

# for autoconf
cp -f $TOOLS/usr/share/autoconf/autom4te.cfg .
sed -i -e "s|'/usr/share/autoconf'|'$TOOLS/usr/share/autoconf'|" autom4te.cfg
export AUTOM4TE=$TOOLS/usr/bin/autom4te
export AUTOM4TE_CFG=$cwd/autom4te.cfg

export PERL5LIB=$TOOLS/usr/share/autoconf
export PERL5LIB=$PERL5LIB:$TOOLS/usr/share/automake-1.16

cwd=`pwd`
cp -f $TOOLS/usr/share/autoconf/autom4te.cfg .
sed -i -e "s|'/usr/share/autoconf'|'$TOOLS/usr/share/autoconf'|" autom4te.cfg
export AUTOM4TE_CFG=$cwd/autom4te.cfg

export ACLOCAL_AUTOMAKE_DIR=$TOOLS/usr/share/aclocal-1.16
export trailer_m4=`pwd`/dummy.m4

