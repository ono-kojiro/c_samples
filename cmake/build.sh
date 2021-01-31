#!/bin/sh

builddir=_cmake_make
buildcmd=make

cmake=cmake

_usage()
{
	echo "usage : $0 [options] target1 target2 ..."
	exit 0
}

_config()
{
	echo config
	mkdir -p $builddir
	cd $builddir && \
		$cmake -G "Unix Makefiles" \
			-DCMAKE_INSTALL_PREFIX=/usr \
			-DCMAKE_INSTALL_LIBDIR=/usr/lib64 \
			-DCMAKE_BUILD_TYPE=Release \
			..
}

_build()
{
	echo build
	cd $builddir && $buildcmd
}

_test()
{
	cd $builddir && $buildcmd test

}

_splint()
{
	cd $builddir && $buildcmd splint
}


_install()
{
	cd $builddir && $buildcmd install DESTDIR=~/tmp/cmake_sample

}

_dist()
{
	cd $builddir && $buildcmd package_source
}


_clean()
{
	echo clean
	cd $builddir && $buildcmd clean
}

_maintainer_clean()
{
	echo maintainer-clean
	rm -rf $builddir
}


logfile=""

while getopts hvl: option
do
	case "$option" in
		h)
			_usage;;
		v)
			verbose=1;;
		l)
			logfile=$OPTARG;;
		*)
			echo unknown option "$option";;
	esac
done

shift $(($OPTIND-1))

if [ "x$logfile" != "x" ]; then
	echo logfile is $logfile
fi

for target in "$@" ; do
	echo target is "$target"
	if [ "x$target" = "xconfig" ]; then
		_config
	elif [ "x$target" = "xbuild" ]; then
		_build
	elif [ "x$target" = "xtest" ]; then
		_test
	elif [ "x$target" = "xinstall" ]; then
		_install
	elif [ "x$target" = "xdist" ]; then
		_dist
	elif [ "x$target" = "xclean" ]; then
		_clean
	elif [ "x$target" = "xsplint" ]; then
		_splint
	elif [ "x$target" = "xmaintainer-clean" ]; then
		_maintainer_clean
	elif [ "x$target" = "xmclean" ]; then
		_maintainer_clean
	else
		echo unknown target, "$target"
	fi
done

