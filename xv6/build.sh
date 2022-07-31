#!/bin/sh

top_dir="$( cd "$( dirname "$0" )" >/dev/null 2>&1 && pwd )"
cd $top_dir

builddir="${top_dir}/_build"

usage()
{
  echo "usage : $0 [options] target1 target2 ..."
  echo ""
  echo "  target"
  echo "    config"
  echo "    build"
  echo "    clean"
  exit 0
}

help()
{
  usage
}

prepare()
{
  sudo apt -y install libgcc-12-dev-i386-cross
}

config()
{
  mkdir -p ${builddir}
  cd ${builddir}
  pwd
  cmake ..
  cd ${top_dir}
}

build()
{
  mkdir -p ${builddir}
  cd ${builddir}
  make -C ${builddir}
  cd ${top_dir}
}

fetch()
{
  if [ ! -d "src" ]; then
    git clone https://github.com/pandax381/xv6-net.git src
  else
    git -C src pull
  fi
}

default_target()
{
  arg=$1
  shift
  
  mkdir -p ${builddir}
  cd ${builddir}
  make -C ${builddir} $arg
  cd ${top_dir}
}

mclean()
{
  rm -rf ${builddir}
}

all()
{
  build
}


opts=""
args=""

while [ $# -ne 0 ]; do
  case "$1" in
    -c )
      shift
      opts="$opts -c $1"
      ;;
    -v )
      opts="$opts -v"
      ;;
	*)
      args="$args $1"
	  ;;
  esac

  shift

done


if [ -z "$args" ]; then
  all
  exit
fi

for arg in $args ; do
	LANG=C type $arg | grep 'function' > /dev/null 2>&1
	if [ $? -eq 0 ]; then
		$arg
	else
	    default_target $arg
	fi
done

