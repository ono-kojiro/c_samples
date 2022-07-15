#!/bin/sh

set -e

top_dir="$(cd "$(dirname "$0")" > /dev/null 2>&1 && pwd)"

#buildtool="cmake"
buildtool="amake"


usage()
{
  echo "usage : $0 [options] target1 target2 ..."
}

configure()
{
  top_dir=$(pwd)

  case $buildtool in
    amake )
      autoreconf -vi
      ;;
    * )
      ;;
  esac

  rm -rf $builddir
  mkdir -p $builddir
  cd $builddir

  case $buildtool in
    amake )
      sh ../configure "$@"
      ;;
    cmake )
      cmake "$@" .. 
      ;;
    * )
      ;;
  esac

  cd $top_dir
}

config()
{
  configure "$@"
}

build()
{
  echo "build"

  top_dir=$(pwd)

  cd $builddir

  case $buildtool in
    amake )
      make
      ;;
    cmake )
      cmake --build .
      ;;
    * )
      ;;
  esac

  cd $top_dir
}

clean()
{
  top_dir=$(pwd)

  cd $builddir

  case $buildtool in
    amake )
      make clean
      ;;
    cmake )
      make clean
      ;;
    * )
      ;;
  esac

  cd $top_dir
}


check()
{
  make check
}

install()
{
  top_dir=$(pwd)

  cd $builddir

  case $buildtool in
    amake )
      make install "$@"
      ;;
    cmake )
      make install "$@"
      ;;
    * )
      ;;
  esac

  cd $top_dir
}

all()
{
  build "$@"
}

output=""
logfile=""

args=""
target=""

while [ "$#" -ne 0 ] ; do
  case "$1" in
    -h | --help)
      usage
      exit 1
      ;;
    -o | --output)
      shift
      output=$1
      ;;
    -l | --logfile)
      shift
      logfile=$1
      ;;
    -b | --buildtool)
      shift
      buildtool=$1
      ;;
    *)
      if [ -z "$target" ]; then
        target=$1
      else
        args="$args $1"
      fi
      ;;
  esac

  shift
done

builddir="_build-$buildtool"

if [ -z "$target" ]; then
  all $args
else
  num=`LANG=C type $target | grep 'function' | wc -l`
  if [ "$num" -ne 0 ]; then
    $target $args
  else
    echo "ERROR : $target is not a shell function"
    exit 1
  fi
fi

