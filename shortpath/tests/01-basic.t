#!/bin/sh

echo "1..1"

EXECUTABLE=../shortpath/shortpath

got=`$EXECUTABLE "/aaa/bbb/ccc/../ddd/eee"`
exp="/aaa/bbb/ddd/eee"

if [ "$got" = "$exp" ]; then
    echo "ok"
else
    echo "not ok"
fi

