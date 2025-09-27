/* Copyright (GPL) 2004 mchirico@users.sourceforge.net or mchirico@comcast.net
  Simple lemon parser  example.

  
    $ ./lemon example2.y                          

  

*/

%include {   
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "macro.h"
#include "token.h"
#include "userdata.h"

/* #include "parser.h" */


  void token_destructor(Token t)
    {
      fprintf(stderr, "In token_destructor t.value= %d\n", t.value);
      fprintf(stderr, "In token_destructor t.n= %d\n", t.n);
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
	fprintf(stderr, "parsing complete!\n\n\n"); 
}

%parse_failure
{
	fprintf(stderr, "parsing failed!\n\n\n");
}

   
%syntax_error {  
  fprintf(stderr, "Syntax error!\n");
}   

%start_symbol main

/*  This is to terminate with a new line */
main ::= in.
in ::= .
in ::= in state NEWLINE.



state ::= expr(A).   { 
                        fprintf(stderr, "Result.n = %d\n", A.n);
                        printf("%d\n", A.value);
                         }  



expr(A) ::= expr(B) MINUS  expr(C).   { A.value = B.value - C.value; 
                                       A.n = B.n+1  + C.n+1;
                                      }  

expr(A) ::= expr(B) PLUS  expr(C).   { A.value = B.value + C.value; 
                                       A.n = B.n+1  + C.n+1;
                                      }  

expr(A) ::= expr(B) TIMES  expr(C).   { A.value = B.value * C.value;
                                        A.n = B.n+1  + C.n+1;

                                         }  

expr(A) ::= expr(B) EXP expr(C).
{
  A.value = pow(B.value, C.value);
  A.n = B.n+1  + C.n+1;
}
 
expr(A) ::= expr(B) DIVIDE expr(C).  { 

         if(C.value != 0){
           A.value = B.value / C.value;
           A.n = B.n+1 + C.n+1;
          }else{
           fprintf(stderr, "divide by zero\n");
           }
}  /* end of DIVIDE */
expr(A) ::= NUM(B). { A.value = B.value; A.n = B.n+1; }

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


