#!/bin/sh

tarfile="simple_0.0.1.tar.gz"
dscfile="simple_0.0.1.dsc"

sha256sum=`sha256sum $tarfile | awk '{ print $1 }'`
md5sum=`md5sum $tarfile | awk '{ print $1 }'`
size=`ls -l $tarfile | awk '{ print $5 }'`

cat - << 'EOS' > $dscfile
Format: 3.0 (native)
Source: simple
Binary: simple
Architecture: any
Version: 0.0.1
Maintainer: Kojiro ONO <ono.kojiro@gmail.com>
Uploaders: Kojiro ONO <ono.kojiro@gmail.com>
Homepage: http://example.com/
Standards-Version: 4.6.0
Testsuite: autopkgtest
Package-List:
 simple
EOS

{
  echo "Checksums-Sha256:"
  echo " $sha256sum $size $tarfile"
  echo "Files:"
  echo " $md5sum $size $tarfile"
} >> $dscfile

