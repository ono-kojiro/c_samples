#!/bin/sh

cd tests

echo "1..1"

autoreconf -vi
if [ $? -eq 0 ]; then
  echo "ok"
else
  echo "not ok"
fi

