#!/bin/sh

echo "1..2"

cd tests

rm -f ./hello

touch configure.ac
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

