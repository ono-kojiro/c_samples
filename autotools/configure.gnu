#!/bin/sh

AUTOMAKE=`which automake`
ACLOCAL=`which aclocal`

AUTOMAKE="$AUTOMAKE" \
  ACLOCAL="$ACLOCAL" \
  sh configure --prefix=/usr

