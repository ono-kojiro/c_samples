#!/bin/sh

cd tests

echo "1..2"

rm -f ./hello

touch Makefile.am
make
if [ $? -eq 0 ]; then
  echo "ok"
else
  echo "not ok"
fi

./hello
if [ $? -eq 0 ]; then
  echo "ok"
else
  echo "not ok"
fi

