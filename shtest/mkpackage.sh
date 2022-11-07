#!/usr/bin/env sh

set -e
top_dir="$( cd "$( dirname "$0" )" >/dev/null 2>&1 && pwd )"

logfile=""

pkgname=""
version=""

usage()
{
  cat - << EOS
usage : $0 [OPTIONS] TARGET1 [TARGET2]...
EOS
}

control()
{
  username=`git config user.name`
  email=`git config user.email`

  if [ -z "$outdir" ]; then
    outdir="debian"
  fi
  mkdir -p $outdir

  ctrlfile="$outdir/control"
  echo generate $ctrlfile ...

  cat - << EOS > $ctrlfile
Source: $pkgname
Section: utils
Maintainer: $username <$email>
Build-Depends: make

Package: $pkgname
Architecture: all
Depends: bash
Description: $pkgname
EOS

  compatfile="$outdir/compat"
  echo generate $compatfile ...
  echo "10" > $compatfile

  formatfile="$outdir/source/format"
  echo generate $formatfile ...
  mkdir -p "$outdir/source"
  #echo "3.0 (native)" > $formatfile
  echo "3.0 (quilt)" > $formatfile

  changelog="$outdir/changelog"
  echo copy $changelog ...
  cp -f ChangeLog $changelog

  rules="$outdir/rules"
  echo generate $rules ...
  cat - << 'EOS' > $rules
#!/usr/bin/make -f

# Aim for the top, adapt if anything should break on the buildds.
DEB_BUILD_MAINT_OPTIONS=	hardening=+all
export DEB_BUILD_MAINT_OPTIONS

GARCH:=	$(shell dpkg-architecture -qDEB_HOST_GNU_TYPE)

%:
	dh '$@'

override_dh_auto_configure:
	dh_auto_configure

execute_after_dh_auto_test:
	make check

override_dh_makeshlibs:
	dh_makeshlibs -- -c4
EOS

}

ctrl()
{
  control
}

dsc()
{
  origfile="${pkgname}_${version}.orig.tar.gz"
  debianfile="${pkgname}_${version}.debian.tar.xz"

  dscfile="${pkgname}_${version}.dsc"
  
  username=`git config user.name`
  email=`git config user.email`

  cat - << EOS > $dscfile
Format: 3.0 (quilt)
Source: $pkgname
Binary: $pkgname
Architecture: any
Version: $version
Maintainer: $username <$email>
Uploaders: $username <$email>
Homepage: http://example.com/
Standards-Version: 4.6.0
Testsuite: autopkgtest
Package-List:
 $pkgname
EOS

  {
    echo "Checksums-Sha256:"
    for archive in $origfile $debianfile; do
      sha256sum=`sha256sum $archive | awk '{ print $1 }'`
      size=`ls -l $archive | awk '{ print $5 }'`

      echo " $sha256sum $size $archive"
    done

  } >> $dscfile

  {  
    echo "Files:"
    for archive in $origfile $debianfile; do
      md5sum=`md5sum $archive | awk '{ print $1 }'`
      size=`ls -l $archive | awk '{ print $5 }'`
      echo " $md5sum $size $archive"
    done

  } >> $dscfile

}

if [ "$#" -eq 0 ]; then
  usage
  exit 1
fi

cmd="$1"
shift

case $cmd in
  -* )
    echo "invalid command, $cmd"
    exit 2
    ;;
  * )
    ;;
esac

echo cmd is $cmd

set +e
LANG=C type "$cmd" | grep 'function'
if [ "$?" -ne 0 ]; then
  echo "no such function in $0, $cmd"
  exit 1
fi

set -e

while [ "$#" -ne 0 ]; do
  case "$1" in
    -h | --help )
      ;;
    -l | --log )
      shift
      logfile=$1
      ;;
    -v | --version )
      shift
      version=$1
      ;;
    -p | --package )
      shift
      pkgname=$1
      ;;
    -o | --outdir )
      shift
      outdir=$1
      ;;
    * )
      ;;
  esac

  shift
done

ret=0

if [ -z "$pkgname" ]; then
  echo "ERROR : no package option"
  ret=$(expr $ret + 1)
fi

if [ -z "$version" ]; then
  echo "ERROR : no version option"
  ret=$(expr $ret + 1)
fi

if [ "$ret" -ne 0 ]; then
  exit $ret
fi


$cmd

