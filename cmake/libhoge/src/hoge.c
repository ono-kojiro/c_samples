#include <stdio.h>
#include "hoge.h"
#include "foo.h"

int hoge()
{
  printf("This is hoge().\n");
  printf("Call foo() in hoge().\n");
  foo();
  return 0;
}

