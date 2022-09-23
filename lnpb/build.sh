#!/bin/sh

set -e

top_dir="$( cd "$( dirname "$0" )" >/dev/null 2>&1 && pwd )"
cd $top_dir

realname="debbuild"
pkgname="${realname}"
version="0.0.1"

sourcedir=$top_dir/work/sources
builddir=$top_dir/work/build
destdir=$top_dir/work/dest/${pkgname}-${version}

outputdir=$top_dir
  
src_urls="
http://www.ncad.co.jp/~mtaneda/lnpb/Chapter_01.tar.gz
http://www.ncad.co.jp/~mtaneda/lnpb/Chapter_03.tar.gz
http://www.ncad.co.jp/~mtaneda/lnpb/Chapter_04.tar.gz
http://www.ncad.co.jp/~mtaneda/lnpb/Chapter_05.tar.gz
http://www.ncad.co.jp/~mtaneda/lnpb/Chapter_06.tar.gz
http://www.ncad.co.jp/~mtaneda/lnpb/Chapter_08.tar.gz
http://www.ncad.co.jp/~mtaneda/lnpb/Chapter_09.tar.gz
http://www.ncad.co.jp/~mtaneda/lnpb/Chapter_10.tar.gz
http://www.ncad.co.jp/~mtaneda/lnpb/Chapter_11.tar.gz
http://www.ncad.co.jp/~mtaneda/lnpb/Chapter_12.tar.gz
"


all()
{
  fetch
  configure
  compile
}

fetch()
{
  archivedir="work/archives"
  srcdir="work/sources"
  builddir="work/build"

  mkdir -p $archivedir
  for url in $src_urls; do
    filename=$(basename $url)
    #echo filename is $filename
    if [ ! -e "$archivedir/$filename" ]; then
      wget -O $archivedir/$filename $url
    else
      echo skip fetching $filename
    fi
  done

  mkdir -p $srcdir
  for url in $src_urls; do
    basename=$(basename $url .tar.gz)
    filename=$(basename $url)
    echo basename is $basename
    if [ ! -d "$srcdir/$basename" ]; then
      tar -C $srcdir -xzvf $top_dir/$archivedir/$filename
    else
      echo skip extracting $filename
    fi
  done
}

configure()
{
  # cd ${builddir}/${pkgname}-${version}
  cd ${top_dir}
  mkdir -p ${builddir}
  cd ${builddir}
  cmake \
    -DCMAKE_INSTALL_PREFIX=/usr \
    ${top_dir} 

  cd ${top_dir}
}

config()
{
  configure
}

compile()
{
  #cd ${builddir}/${pkgname}-${version}
  cd ${builddir}
  make clean
  make VERBOSE=1
  cd ${top_dir}
}

build()
{
  compile
}

install()
{
  cd ${builddir}/${pkgname}-${version}
  cd build
  rm -rf ${destdir}

  PYTHON3_PACKAGES_PATH=/usr/lib/python3.6/dist-packages \
  make install DESTDIR=${destdir}

  cd ${top_dir}

  custom_install
}

custom_install()
{
  :
}

package()
{
  mkdir -p $destdir/DEBIAN

  username=`git config user.name`
  email=`git config user.email`

cat << EOS > $destdir/DEBIAN/control
Package: $pkgname
Maintainer: $username <$email>
Architecture: amd64
Version: $version
Description: $pkgname
EOS
	fakeroot dpkg-deb --build $destdir $outputdir
}

sysinstall()
{
  sudo apt -y install ./${pkgname}_${version}_amd64.deb
}


clean()
{
  rm -rf ${builddir}
  rm -rf ${destdir}
}

test()
{
  cd ${builddir} && make test
  cd ${top_dir}
}



if [ "$#" = 0 ]; then
  all
fi

for target in "$@"; do
	num=`LANG=C type $target | grep 'function' | wc -l`
	if [ $num -ne 0 ]; then
		$target
	else
		echo invalid target, "$target"
	fi
done

