#!/bin/sh

top_dir="$( cd "$( dirname "$0" )" >/dev/null 2>&1 && pwd )"
cd $top_dir

PROG=$(basename $0)
VERSION="1.0"

#build_dir=_abuild
build_dir=_cbuild

address=localhost

usage()
{
	echo "$PROG <target>"
}

version()
{
	:
}

prepare()
{
	sudo apt -y install cmake pkg-config libssl-dev
}

config()
{
	mkdir -p $build_dir
	if [ "x$build_dir" = "x_abuild" ]; then
		autoreconf -vi
		cd $build_dir && sh ../configure
	elif [ "x$build_dir" = "x_cbuild" ]; then
		cd $build_dir && cmake \
			-G "Unix Makefiles" \
			-DCMAKE_TOOLCHAIN_FILE=../arm-toolchain.cmake \
			..
	else
		echo invalid build_dir name, $build_dir
		exit 1
	fi
}

build()
{
	cd $build_dir && make VERBOSE=1
}

clean()
{
	cd $build_dir && make clean
}

mclean()
{
	rm -rf $build_dir
}

server()
{
	./$build_dir/server/server -h localhost -p 55555
}

client()
{
	./$build_dir/client/client -h localhost -p 55555
}

receiver()
{
	./$build_dir/receiver/receiver -h 127.0.0.1 -p 22222 -m 239.255.0.1
}

sender()
{
	./$build_dir/sender/sender -h 127.0.0.1 -p 22222 -m 239.255.0.1
}

install()
{
  cd $build_dir && make install DESTDIR=${top_dir}/dest
}


for target in "$@" ; do
	LANG=C type $target | grep function > /dev/null 2>&1
	res=$?	
	if [ "x$res" = "x0" ] ; then
		$target
	else
		echo $target is not a shell function
		exit 1
	fi
done

