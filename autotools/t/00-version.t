#!/bin/sh

echo "1..3"

check_version()
{
  pkgname=$1
  expected=$2

  got=`$pkgname --version | grep -e "^$pkgname" | gawk '{ print $4 }'`

  if [ "$got" = "$expected" ]; then
    echo "ok - version of $pkgname is $got"
  else
    echo "not ok - version of $pkgname is $got, not expected $expected"
  fi
}

# m4 (GNU M4) 1.4.19
check_version "m4" "1.4.19"

#autoconf (GNU Autoconf) 2.71
check_version "autoconf" "2.71"

# automake (GNU automake) 1.16.3
check_version "automake" "1.16.3"


