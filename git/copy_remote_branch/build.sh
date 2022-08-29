#!/bin/sh

set -e

top_dir="$( cd "$( dirname "$0" )" >/dev/null 2>&1 && pwd )"
cd $top_dir

#repos="test_git1 test_git2"
#repos="hoge foo bar"
repos="aaa bbb ccc"

help()
{
  echo "usage : $0 [options] target1 target2 ..."
}

init()
{
  echo init

  for repo in $repos; do
    rm -rf $HOME/git/${repo}.git
    git init --bare --shared $HOME/git/${repo}.git 
  done
}

clone()
{
  for repo in $repos; do
    rm -rf ./${repo}
    git clone file://$HOME/git/${repo}.git ${repo}
  done
}

commit()
{
  for repo in $repos; do
    cd $repo

    cfile="main.c"

    cat - << EOS > $cfile
#include <stdio.h>

int main(int argc, char **argv)
{
  printf("Hello World ${repo}\n");
}
EOS

    cat - << 'EOS' > Makefile
SRCS = main.c
OBJS = $(SRCS:.c=.o)

PROG = hello

all : obj prog

prog : $(PROG)

obj : $(OBJS)

$(PROG) : $(OBJS)
	gcc -o $@ $(OBJS)

%.o : %.c
	gcc -c -o $@ $<

test :
	./$(PROG)

clean :
	rm -f $(OBJS) $(PROG)
EOS

    git add main.c Makefile
    git commit -m "commit main.c and Makefile in ${repo}"
    git push origin main 

    cd ${top_dir}
  done
}

add_branch()
{
  for repo in $repos; do
    cd $repo
    branch="branch_${repo}"
    git checkout -b $branch

    echo "branch_${repo}" > branch_${repo}.txt
    git add branch_${repo}.txt
    git commit -m "branch_${repo}"
    git push origin ${branch}
   
    git checkout main 
    cd ${top_dir}
  done
}

add_remote()
{
  for repo in $repos; do
    cd $repo
    for target in $repos; do
      if [ "$repo" != "$target" ]; then
        git remote add remote_$target file://$HOME/git/${target}.git
      fi
    done
    
    cd ${top_dir}
  done
}

orphan()
{
  for repo in $repos; do
    cd $repo
    branch="orphan_${repo}"

    git checkout --orphan $branch
    git rm -rf .
    echo $repo > orphan_${repo}.txt
    git add orphan_${repo}.txt
    git commit -m "add orphan_${repo}.txt"
    git push origin ${branch}
    git checkout main
    cd ${top_dir}
  done
}

copy_remote_branch()
{
  # copy remote branch
  # https://stackoverflow.com/questions/11356460/how-to-cleanly-get-copy-a-remote-git-branch-to-local-repository

  for repo in $repos; do
    cd $repo
    git fetch --all

    case $repo in
      aaa )
        remote="remote_bbb"
        branch="branch_bbb"
        ;;
      bbb )
        remote="remote_ccc"
        branch="branch_ccc"
        ;;
      ccc )
        remote="remote_aaa"
        branch="branch_aaa"
        ;;
      * )
        ;;
    esac

    git checkout -b $branch $remote/$branch
    git push origin $branch
    cd ${top_dir}
  done

}

all()
{
  init
  clone
  commit
  add_branch
  add_remote
  orphan

  copy_remote_branch
}

clean()
{
  for repo in $repos; do
    rm -rf $HOME/git/${repo}.git
    rm -rf ./${repo}
  done
}

args=""

while [ $# -ne 0 ]; do
  case $1 in
    -h )
      usage
      exit 1
      ;;
    -v )
      verbose=1
      ;;
    * )
      args="$args $1"
      ;;
  esac
  
  shift
done

if [ -z "$args" ]; then
  all
fi

for arg in $args; do
  num=`LANG=C type $arg | grep 'function' | wc -l`
  if [ $num -eq 1 ]; then
    $arg
  else
    echo "ERROR : $arg is not shell function"
    exit 1
  fi
done

