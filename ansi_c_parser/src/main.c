#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>

#include "parser.h"

int main(int argc, char **argv)
{
	extern int yydebug;
	yydebug = 1;
	printf("Hello World\n");
	yyparse();
	//yylex();
	return 0;
}

