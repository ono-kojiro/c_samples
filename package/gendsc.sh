#!/bin/sh

name="simple"
version="0.0.1"

tarfile="${name}_${version}.tar.gz"
dscfile="${name}_${version}.dsc"

sha256sum=`sha256sum $tarfile | awk '{ print $1 }'`
md5sum=`md5sum $tarfile | awk '{ print $1 }'`
size=`ls -l $tarfile | awk '{ print $5 }'`

username=`git config user.name`
email=`git config user.email`

cat - << EOS > $dscfile
Format: 3.0 (native)
Source: $name
Binary: $name
Architecture: any
Version: $version
Maintainer: $username <$email>
Uploaders: $username <$email>
Homepage: http://example.com/
Standards-Version: 4.6.0
Testsuite: autopkgtest
Package-List:
 $name
EOS

{
  echo "Checksums-Sha256:"
  echo " $sha256sum $size $tarfile"
  echo "Files:"
  echo " $md5sum $size $tarfile"
} >> $dscfile

