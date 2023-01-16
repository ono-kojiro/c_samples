/* Copyright (GPL) 2004 mchirico@users.sourceforge.net or mchirico@comcast.net
  Simple lemon parser  example.

  
    $ ./lemon example2.y                          

  

*/

%include {   
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "token.h"

#include "userdata.h"

/* #include "parser.h" */


void token_destructor(Token t)
{
#ifndef NDEBUG
    fprintf(stderr, "\n");
    fprintf(stderr, "DEBUG : %s(%d)\n", __FILE__, __LINE__ );
    fprintf(stderr, "In token_destructor t.value= %d\n", t.value);
    fprintf(stderr, "In token_destructor t.n= %d\n", t.n);
    fprintf(stderr, "\n");
#endif
}

}  

%name MyParser
%token_prefix TOKEN_

%token_type {Token}
%default_type {Token}
%token_destructor { token_destructor($$); }

%extra_argument { USERDATA *userdata }

%type expr {Token}
%type NUM {Token}

%left PLUS MINUS.
%left TIMES DIVIDE MOD .
%right EXP .
 
%parse_accept
{
#ifndef NDEBUG
    fprintf(stderr, "\n");
    fprintf(stderr, "parsing complete!\n\n\n");
#endif
    userdata->accept = 1;
}

%parse_failure
{
    fprintf(stderr, "\n");
    fprintf(stderr, "parsing failed!\n\n\n");
    userdata->failure = 1;
}
   
%syntax_error
{
    fprintf(stderr, "\n");
    fprintf(stderr, "Syntax error!\n");
    userdata->error = 1;
}   

%start_symbol main

/*  This is to terminate with a new line */
main ::= in.
in ::= .
in ::= in state NEWLINE.

state ::= expr(A).
{ 
#ifndef NDEBUG
    fprintf(stderr, "Result.n = %d\n", A.n);
    fprintf(stderr, "Result.value = %d\n", A.value);
#endif
    userdata->result = A.value;
}  

expr(A) ::= expr(B) MINUS  expr(C).
{
  A.value = B.value - C.value; 
  A.n = B.n+1  + C.n+1;
}  

expr(A) ::= expr(B) PLUS  expr(C).
{
  A.value = B.value + C.value; 
  A.n = B.n+1  + C.n+1;
}  

expr(A) ::= expr(B) TIMES  expr(C).
{
  A.value = B.value * C.value;
  A.n = B.n+1  + C.n+1;
}  

expr(A) ::= expr(B) EXP expr(C).
{
  A.value = pow(B.value, C.value);
  A.n = B.n+1  + C.n+1;
}
 
expr(A) ::= expr(B) DIVIDE expr(C).
{ 
   if(C.value != 0){
     A.value = B.value / C.value;
     A.n = B.n+1 + C.n+1;
   }else{
     fprintf(stderr, "divide by zero\n");
   }
}  /* end of DIVIDE */

expr(A) ::= NUM(B).
{
  A.value = B.value; A.n = B.n+1;
#ifndef NDEBUG
  fprintf(stderr, "\n");
  fprintf(stderr, "DEBUG : expr ::= NUM\n");
  fprintf(stderr, "DEBUG : input value is %d\n", B.value);
  fprintf(stderr, "\n");
#endif

}

/*
  LRB : Left Round Bracket, '('
  RRB : Right Round Bracket, ')'
*/
expr(A) ::= LRB expr(B) RRB .
{
  A.value = B.value;
}

expr(A) ::= expr(B) MOD expr(C) .
{
  A.value = B.value % C.value;
}


