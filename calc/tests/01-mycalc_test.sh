#!/bin/sh

oldpwd=$(pwd)

top_dir="$( cd "$( dirname "$0" )" >/dev/null 2>&1 && pwd )"
cd $top_dir

basename=$(basename $0 .sh)
MYCALC=../mycalc/mycalc

ret=0

echo 1..5
res=$(echo "1+2" | $MYCALC)
if [ "$res" = "3" ]; then
  echo "ok - 1+2=$res"
else
  echo "not ok - 1+2=$res"
  ret=$(expr $ret + 1)
fi

res=$(echo "3+4" | $MYCALC)
if [ "$res" = "7" ]; then
  echo "ok - 3+4=$res"
else
  echo "not ok - 3+4=$res"
  ret=$(expr $ret + 1)
fi

res=$(echo "5+6*7" | $MYCALC)
if [ "$res" = "47" ]; then
  echo "ok - 5+6*7=$res"
else
  echo "not ok - 5+6*7=$res"
  ret=$(expr $ret + 1)
fi

res=$(echo "(5+6)*7" | $MYCALC)
if [ "$res" = "77" ]; then
  echo "ok - (5+6)*7=$res"
else
  echo "not ok - (5+6)*7=$res"
fi

res=$(echo "2^4" | $MYCALC)
if [ "$res" = "16" ]; then
  echo "ok - 2^4=$res"
else
  echo "not ok - 2^4=$res"
fi

cd $oldpwd

exit $ret

