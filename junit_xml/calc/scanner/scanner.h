#ifndef _SCANNER_H_
#define _SCANNER_H_

#define TOKEN_ADD 1
#define TOKEN_SUB 2
#define TOKEN_MUL 3
#define TOKEN_DIV 4
#define TOKEN_INT 5
#define EOI 319

typedef unsigned int uint;
typedef unsigned char uchar;

#define	BSIZE	8192

#define	YYCTYPE		uchar
#define	YYCURSOR	cursor
#define	YYLIMIT		s->lim
#define	YYMARKER	s->ptr
#define	YYFILL(n)	{cursor = fill(s, cursor);}

#define	RET(i)	{s->cur = cursor; return i;}

typedef union {
	int int_value;
} YYSTYPE;

typedef struct Scanner {
    int			fd;
    uchar		*bot, *tok, *ptr, *cur, *pos, *lim, *top, *eof;
    uint		line;
} Scanner;

uchar *fill(Scanner *s, uchar *cursor);
int scan(Scanner *s, YYSTYPE *yylval);

#endif /* #ifndef _SCANNER_H_ */

