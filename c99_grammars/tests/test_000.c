#include <stdio.h>
#include "c99.h"

int main(int argc, char **argv)
{
	extern int yydebug;
	yydebug = 1;
	printf("Hello World\n");
	yyparse();
	//yylex();
	return 0;
}


