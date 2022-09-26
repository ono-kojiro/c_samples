#include "config.h"

#include <stdio.h>
#include <stdlib.h>

#if HAVE_MYLIB
#include "mylib.h"
#endif

int main(int argc, char **argv)
{
	printf("This is myapp.\n");
	printf("add stdlib.h\n");

#if HAVE_MYLIB
	mylib();
#else
	printf("mylib() is NOT called.\n");
#endif

	return 0;
}

