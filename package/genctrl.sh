#!/usr/bin/env sh

pkgname="simple"
version="0.0.1"
username=`git config user.name`
email=`git config user.email`

mkdir -p debian

ctrlfile="debian/control"
echo generate $ctrlfile ...

cat - << EOS > $ctrlfile
Source: simple
Section: utils
Maintainer: $username <$email>
Build-Depends: make

Package: $pkgname
Architecture: amd64
Version: $version
Depends: libc6
Description: $pkgname

EOS

compatfile="debian/compat"
echo generate $compatfile ...
cat - << EOS > $compatfile
10
EOS


formatfile="debian/source/format"
echo generate $formatfile ...
mkdir -p "debian/source"
cat - << EOS > $formatfile
3.0 (native)
EOS

changelog="./debian/changelog"
echo copy $changelog ...
cp -f ChangeLog $changelog

rules="debian/rules"
echo generate $rules ...
cat - << 'EOS' > $rules
#!/usr/bin/make -f

# Aim for the top, adapt if anything should break on the buildds.
DEB_BUILD_MAINT_OPTIONS=	hardening=+all
export DEB_BUILD_MAINT_OPTIONS

GARCH:=	$(shell dpkg-architecture -qDEB_HOST_GNU_TYPE)

%:
	dh '$@'

override_dh_auto_configure:
	dh_auto_configure

execute_after_dh_auto_test:
	make check

override_dh_makeshlibs:
	dh_makeshlibs -- -c4
EOS


