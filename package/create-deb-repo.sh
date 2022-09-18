#!/bin/sh

top_dir="$( cd "$( dirname "$0" )" >/dev/null 2>&1 && pwd )"


usage()
{
  cat - << EOS
usage : $0 [OPTIONS] CMD
EOS

}

init()
{
  mkdir -p $localrepo/dists/jammy/main/binary-amd64
  cd $localrepo

  echo "generate aptftp.conf ..."
  cat - << EOS > aptftp.conf
APT::FTPArchive::Release {
  Origin "My Origin";
  Label "My Local Deb Repository";
  Suite "jammy";
  Codename "jammy";
  Architectures "amd64";
  Components "main";
  Description "My Local Deb Repository";
};
EOS

  echo "generate aptgenerate.conf"

  cat - << EOS > aptgenerate.conf
Dir::ArchiveDir ".";
Dir::CacheDir ".";
Default::Packages::Extensions ".deb";
Default::Packages::Compress ". gzip bzip2";
Default::Sources::Compress ". gzip bzip2";
Default::Contents::Compress "gzip bzip2";

BinDirectory "dists/jammy/main/binary-amd64" {
  Packages "dists/jammy/main/binary-amd64/Packages";
  Contents "dists/jammy/Contents-amd64";
  SrcPackages "dists/jammy/main/source/Sources";
};

Tree "dists/jammy" {
  Sections "main"; # contrib non-free";
  Architectures "amd64";
};
EOS


  rm -f packages-*.db
  cd $top_dir
}

package()
{
  cd $localrepo
  apt-ftparchive generate -c=aptftp.conf aptgenerate.conf
  cd $top_dir
}

release()
{
  cd $localrepo
  apt-ftparchive release \
	-c=aptftp.conf \
	dists/jammy > dists/jammy/Release
  cd $top_dir
}

list()
{
  echo "generate ./mydebrepo.list"

  cat - << EOS > mydebrepo.list
deb [arch=amd64 trusted=yes] file:$localrepo jammy main 
EOS

  echo "Please copy ./mydebrepo.list to /etc/apt/sources.list.d/"
}

clean()
{
  cd $localrepo
  rm -f aptftp.conf aptgenerate.conf
  cd $top_dir
}

if [ "$#" -eq 0 ]; then
  usage
  exit 1
fi

args=""

while [ "$#" -ne 0 ]; do
  case $1 in
    -h | --help )
      usage
      exit 1
      ;;
    -v | --version )
      usage
      exit 1
      ;;
    -r | --root )
      shift
      localrepo=$1
      ;;
    * )
      if [ "$cmd" = "" ]; then
        cmd=$1
      else
        args="$args $1"
      fi
      ;;
  esac

  shift
done

if [ "$cmd" = "" ]; then
  echo "ERROR : no command"
  exit 1
fi

#if [ "$localrepo" = "" ]; then
#  localrepo="/home/share/mydebrepo"
#fi

$cmd $args

