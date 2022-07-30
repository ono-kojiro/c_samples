#!/bin/sh

top_dir="$( cd "$( dirname "$0" )" >/dev/null 2>&1 && pwd )"
cd ${top_dir}

builddir="${top_dir}/_build"
buildcmd="make"

cmake="cmake"

usage()
{
	echo "usage : $0 [options] target1 target2 ..."
	exit 0
}

config()
{
  echo config
  mkdir -p $builddir
  cd $builddir && \
    $cmake -G "Unix Makefiles" \
      -DCMAKE_TOOLCHAIN_FILE=./toolchain.cmake \
      -DCMAKE_INSTALL_PREFIX=/usr \
      -DCMAKE_INSTALL_LIBDIR=/usr/lib64 \
      -DCMAKE_BUILD_TYPE=Release \
      $d_options \
      ..
}

build()
{
	echo build
	cd $builddir && $buildcmd
}

test()
{
  cd $builddir && $buildcmd test
}

check()
{
  test
}

splint()
{
  cd $builddir && $buildcmd splint
}


install()
{
  cd $builddir && $buildcmd install DESTDIR=$HOME/tmp/cmake_sample
}

dist()
{
  cd $builddir && $buildcmd package_source
}


clean()
{
  echo clean
  cd $builddir && $buildcmd clean
}

mclean()
{
  echo mclean
  rm -rf $builddir
}

all()
{
  config
  build
}

logfile=""

args=""

d_options=""

while [ $# -ne 0 ]; do
  case $1 in
    -h)
      _usage
      ;;
    -v)
      verbose=1
      ;;
    -l)
      logfile=$1
      ;;
    -D*)
      d_options="$d_options $1"
      ;;
    *)
      args="$args $1"
      ;;
  esac

  shift
done

if [ ! -z "$logfile" ]; then
  echo logfile is $logfile
fi

if [ -z "$args" ]; then
  all
fi

for target in $args; do
  LANG=C type $target | grep 'function' > /dev/null 2>&1
  if [ $? -eq 0 ]; then
    $target
  else
    make $target
  fi
done

