#!/usr/bin/env sh

example=../example/example

$example digits.txt > $0.got

diff -urp $0.exp $0.got

