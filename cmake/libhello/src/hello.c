#include <stdio.h>
#include "hello.h"

int hello()
{
	int i;
	printf("Hello World\n");
#ifdef LIBHELLO_MACRO
	printf("LIBHELLO_MACRO is defined.\n");
#else
	printf("LIBHELLO_MACRO is defined.\n");
#endif
	return 0;
}

