#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "scanner.h"

uchar *fill(Scanner *s, uchar *cursor){
	//fprintf(stderr, "fill is called\n");
    if(!s->eof){
	uint cnt = s->tok - s->bot;
	if(cnt){
	    memcpy(s->bot, s->tok, s->lim - s->tok);
	    s->tok = s->bot;
	    s->ptr -= cnt;
	    cursor -= cnt;
	    s->pos -= cnt;
	    s->lim -= cnt;
	}
	if((s->top - s->lim) < BSIZE){
	    uchar *buf = (uchar*) malloc(((s->lim - s->bot) + BSIZE)*sizeof(uchar));
	    memcpy(buf, s->tok, s->lim - s->tok);
	    s->tok = buf;
	    s->ptr = &buf[s->ptr - s->bot];
	    cursor = &buf[cursor - s->bot];
	    s->pos = &buf[s->pos - s->bot];
	    s->lim = &buf[s->lim - s->bot];
	    s->top = &s->lim[BSIZE];
	    free(s->bot);
	    s->bot = buf;
	}
	if((cnt = read(s->fd, (char*) s->lim, BSIZE)) != BSIZE){
	    s->eof = &s->lim[cnt]; *(s->eof)++ = '\n';
	}
	s->lim += cnt;
    }
    return cursor;
}

int scan(Scanner *s, YYSTYPE *yylval)
{
	uchar *cursor = s->cur;
	//fprintf(stderr, "\nscan is called\n");
std:
	s->tok = cursor;

/*!re2c
	INTEGER = [1-9][0-9]*;
	ANY = [^];
*/

/*!re2c
	INTEGER {
		//fprintf(stderr, " INTEGER");
		RET(TOKEN_NUM);
	}
	
	"^" {
		RET(TOKEN_POWER);
	}

	"(" {
		RET(TOKEN_LRB);
	}
	
	")" {
		RET(TOKEN_RRB);
	}

	"+"	{
		//fprintf(stderr, " ADD");
		RET(TOKEN_PLUS);
	}
	"-" 			{ RET(TOKEN_MINUS); }
	"*"				{ RET(TOKEN_TIMES); }
	"/"				{ RET(TOKEN_DIVIDE); }
	
	[ \t\v\f]+ {
		//fprintf(stderr, " WHITESPACE");
		goto std;
	}

	"\r\n" | "\n"
	{
		//fprintf(stderr, "\nNEWLINE\n");
		if(cursor == s->eof){
			RET(EOF);
		}
		s->line++;
		//s->pos = cursor; 
		RET(TOKEN_NEWLINE);

		/* goto std; */
	}
	
	ANY {
		fprintf(stderr, "unexpected character: %c\n", *s->tok);
		goto std;
	}

*/
}

