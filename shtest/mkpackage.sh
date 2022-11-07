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
  workdir="debian"

  rm -rf $workdir

  username=`git config user.name`
  email=`git config user.email`

  if [ -z "$output" ]; then
    echo "ERROR : no output option"
    exit 1
  fi

  mkdir -p $workdir

  ctrlfile="$workdir/control"
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

  compatfile="$workdir/compat"
  echo generate $compatfile ...
  echo "10" > $compatfile

  formatfile="$workdir/source/format"
  echo generate $formatfile ...
  mkdir -p "$workdir/source"
  #echo "3.0 (native)" > $formatfile
  echo "3.0 (quilt)" > $formatfile

  changelog="$workdir/changelog"
  echo copy $changelog ...
  cp -f ChangeLog $changelog

  rules="$workdir/rules"
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

  case $output in
    *.tar.xz )
      tar cJvf $output debian/
      ;;
    *.tar.bz2 )
      tar cjvf $output debian/
      ;;
    *.tar.gz )
      tar czvf $output debian/
      ;;
    * )
      echo "ERROR : invalid extension, $output"
      exit 1
      ;;
  esac

  rm -rf debian/
}

ctrl()
{
  control
}

dsc()
{
  archives="$@"
  #origfile="${pkgname}_${version}.orig.tar.gz"
  #debianfile="${pkgname}_${version}.debian.tar.xz"

  if [ -z "$archives" ]; then
    echo "ERROR : no archives"
    exit 1
  fi
  
  username=`git config user.name`
  email=`git config user.email`

  if [ -z "$output" ]; then
    echo "ERROR : no output option"
    exit 1
  fi

  dscfile="$output"

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
    #for archive in $origfile $debianfile; do
    for archive in $archives; do
      sha256sum=`sha256sum $archive | awk '{ print $1 }'`
      size=`ls -l $archive | awk '{ print $5 }'`

      echo " $sha256sum $size $archive"
    done

  } >> $dscfile

  {  
    echo "Files:"
    #for archive in $origfile $debianfile; do
    for archive in $archives; do
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

set +e
LANG=C type "$cmd" | grep 'function' > /dev/null 2>&1
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
    -o | --output )
      shift
      output=$1
      ;;
    * )
      break
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


$cmd "$@"

