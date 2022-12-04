#!/usr/bin/env sh

echo "1..1"
example=../example/example
$example input.json
if [ $? -eq 0 ]; then
  echo "ok - input.json"
else
  echo "not ok - input.json"
fi



