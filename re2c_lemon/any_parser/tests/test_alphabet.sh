#!/usr/bin/env sh

basename=$(basename $0 .sh)
testcase=`echo $basename | sed 's/test_//'`

example=../example/example

$example -o ${basename}.got ${testcase}.txt

diff -urp ${basename}.got ${basename}.exp

