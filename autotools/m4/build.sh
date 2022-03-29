#!/bin/sh

top_dir="$( cd "$( dirname "$0" )" >/dev/null 2>&1 && pwd )"
cd $top_dir

. ../autotools.bashrc

build_dir=.

pkgname="m4"
pkgver="1.4.19"
url=http://ftp.jaist.ac.jp/pub/GNU/$pkgname/$pkgname-$pkgver.tar.xz

#install_dir=$TOOLS

archive=`basename $url`

sources="$top_dir/sources"
work="$top_dir/work"
build_dir="$work/build"

help()
{
  echo "usage : $0 <target>"
  echo "  targets :"
  echo "    fetch, extract, config, build, install"
  echo "    clean, mclean"
}

all()
{
  fetch
  extract
  #patch
  configure
  build
  install
  check
}

fetch()
{
  if [ ! -e "$sources/$archive" ]; then
    wget $url
    mv -f $archive $sources/
  else
    echo "skip fetch"
  fi
}

extract()
{
  if [ ! -d "$work/$pkgname-$pkgver" ]; then
    mkdir -p $work
    tar -C $work/ -xf $sources/$archive
  else
    echo "skip extract"
  fi
}

patch()
{
  cd "$work/$pkgname-$pkgver"
  find $top_dir/patches -type f -name "*.patch" -print -exec patch -p1 -i {} \;
  cd $top_dir
}

configure()
{
  rm    -rf $build_dir
  mkdir -p  $build_dir
  cd "$build_dir"
  pwd
  sh $work/$pkgname-$pkgver/configure \
    --prefix=$TOOLS/usr
  cd $top_dir
}

config()
{
  configure
}


build()
{
  num_cpu=`LANG=C lscpu 2>&1 | grep -e '^CPU(s)' | gawk '{ print $2 }'`
  cd "$build_dir"
  make -j $num_cpu
  cd $top_dir
}

install()
{
  cd "$build_dir"
  #make install DESTDIR=$install_dir
  make install
  cd $top_dir
}

check()
{
  . ../autotools.bashrc
  which m4
  if [ $? -eq 0 ]; then
    echo "ok"
  else
    echo "not ok"
  fi
}

clean()
{
  cd $pkgname-$pkgver
  make clean
  cd $top_dir
}

mclean()
{
  rm -rf $pkgname-$pkgver
}

mclean()
{
  rm -rf $pkgname-$pkgver
}

if [ $# -eq 0 ]; then
  all
fi

for target in "$@" ; do
  LANG=C type $target | grep function > /dev/null 2>&1
  if [ $? -eq 0 ]; then
    $target
  else
    echo "$target is not a shell function"
	exit $res
  fi
done

