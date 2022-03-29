#!/bin/sh

echo "1..1"

cd tests
$AUTOSCAN

if [ $? -eq 0 ]; then
  echo "ok"
else
  echo "not ok"
fi


