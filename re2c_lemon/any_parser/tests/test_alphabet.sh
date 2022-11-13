#!/usr/bin/env sh

example=../example/example

$example -o $0.got alphabet.txt

diff -urp $0.got $0.exp

