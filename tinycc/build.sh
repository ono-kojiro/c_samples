#!/bin/sh

set -e

top_dir="$( cd "$( dirname "$0" )" >/dev/null 2>&1 && pwd )"
cd $top_dir

realname="tinycc"
pkgname="${realname}"
version="0.9.27"

url="https://bellard.org/tcc/"
git_url="https://repo.or.cz/tinycc.git"

src_urls=""
src_urls="$src_urls $git_url"

. ./common.sh

all()
{
  fetch
  extract
  configure
  compile
  install
  custom_install
  package
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

