%include {
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <sqlite3.h>

#include "token.h"

#include "userdata.h"

#include "str.h"

/* #include "parser.h" */


void token_destructor(Token *t)
{
   //fprintf(stderr, "In token_destructor t.value= %d\n", t.value);
   //fprintf(stderr, "In token_destructor t.n= %d\n", t.n);
}

} /* %include */
  

%name MyParser
//%token_prefix TOKEN_

%token_type {Token*}
%default_type {Token*}
%token_destructor { token_destructor($$); }

//%extra_argument { USERDATA *userdata }
%extra_context { USERDATA *userdata }

%parse_accept
{
	fprintf(stderr, "parsing complete!\n\n\n"); 
}

%parse_failure
{
	fprintf(stderr, "parsing failed!\n\n\n");
}
   
%syntax_error {  
  fprintf(stderr, "Syntax error!\n");
  exit(1);
}   

%start_symbol input

/*  This is to terminate with a new line */
input ::= lines .

lines ::= EOL .
lines ::= line EOL .
lines ::= lines line EOL .

line ::= wd .
line ::= dec .
line ::= any .
line ::= i_constant .
line ::= f_constant .
line ::= dbs .
line ::= backslash .
line ::= string_literal .

line ::= line wd .
line ::= line dec .
line ::= line any .
line ::= line i_constant .
line ::= line f_constant .
line ::= line dbs .
line ::= line backslash .
line ::= line string_literal .

dec       ::= DEC .
wd        ::= WD .
any       ::= ANY .
i_constant ::= I_CONSTANT .
f_constant ::= F_CONSTANT .
backslash ::= BACKSLASH .
dbs ::= DBS .
string_literal ::= STRING_LITERAL .

