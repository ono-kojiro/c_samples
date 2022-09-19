#!/bin/sh

top_dir="$( cd "$( dirname "$0" )" >/dev/null 2>&1 && pwd )"
cd $top_dir

pkgname=multilib
version=0.0.1

target=aarch64-poky-linux

usage()
{
  echo "usage : $0 [options] target1 target2 ..."
}

build()
{
  HOME=$top_dir \
  QA_SKIP_BUILD_ROOT=1 \
    rpmbuild -bb \
    --nodeps \
    --target=aarch64-poky-linux \
    --define="_build x86_64-linux-gnu" \
    --define="_topdir $top_dir/rpmbuild" \
    --define="_lib lib" \
    --define="_libdir %{_prefix}/lib" \
    --define="version $version" \
    --define="dist .poky" \
    ${pkgname}.spec
}

all()
{
  build
}

args=""
logfile=""

while [ $# -ne 0 ]; do
  case $1 in
    -h | --help)
      shift
      ;;
    -v | --version)
      shift
      ;;
    *)
      args="$args $1"
      ;;
  esac
  shift
done

if [ -z "$args" ]; then
  all
fi


for arg in $args ; do
  LANG=C type $arg | grep 'function' > /dev/null 2>&1
  if [ $? -eq 0 ]; then
    $arg
  else
    echo "ERROR: $arg is not a function."
    exit 1
  fi
done

