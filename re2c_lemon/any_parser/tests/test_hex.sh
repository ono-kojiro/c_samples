#!/usr/bin/env sh

example=../example/example

$example -o $0.got hex.txt

diff -urp $0.got $0.exp

