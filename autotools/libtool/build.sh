#!/bin/sh

top_dir="$( cd "$( dirname "$0" )" >/dev/null 2>&1 && pwd )"
cd $top_dir

. ../autotools.bashrc

build_dir=.

pkgname="libtool"
pkgver="2.4.7"
url=http://ftp.jaist.ac.jp/pub/GNU/$pkgname/$pkgname-$pkgver.tar.xz

install_dir=$TOOLS

archive=`basename $url`

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
  configure
  build
  install
}

fetch()
{
  if [ ! -e $archive ]; then
    wget $url
  else
    echo "skip fetch"
  fi
}

extract()
{
  if [ ! -d $pkgname-$pkgver ]; then
    tar xf $archive
  else
    echo "skip extract"
  fi
}

config()
{
  configure
}

configure()
{
  cd $pkgname-$pkgver
  sh configure --prefix=/usr
  cd $top_dir
}

build()
{
  num_cpu=`LANG=C lscpu 2>&1 | grep -e '^CPU(s)' | gawk '{ print $2 }'`
  cd $pkgname-$pkgver
  make -j $num_cpu
  cd $top_dir
}

install()
{
  cd $pkgname-$pkgver
  make install DESTDIR=$install_dir
  libtool --finish $install_dir/usr/lib
  #ln -s $install_dir/usr/share/aclocal $install_dir/usr/share/libtool/m4
  cd $top_dir
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

