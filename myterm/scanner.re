#include <stdio.h>

#include "scanner.h"

#define RET(i) { s->cur = cursor; return i; }

int yydebug(int state, char current)
{
	fprintf(stderr, "(%d, %d)\n", state, current);
	return 0;
}

int dump_scanner(SCANNER *s)
{
	int len;
	fprintf(stderr, "# cur : %ld, ", s->cur - s->top);
	fprintf(stderr, "tok : %ld, ", s->tok - s->top);
	fprintf(stderr, "ptr : %ld, ", s->ptr - s->top);
	fprintf(stderr, "lim : %ld", s->lim - s->top);
	fprintf(stderr, "\n");
	return 0;
}

int lex(SCANNER *s)
{
    const char *marker;
    const char *ctxmarker;

	char *cursor = s->cur;
std:
	s->tok = cursor;

	/*!re2c
		re2c:yyfill:enable = 1;
	*/
#   define YYCTYPE        unsigned char
#   define YYPEEK()       *cursor
#   define YYSKIP()       ++cursor
#   define YYBACKUP()     marker = cursor
#   define YYBACKUPCTX()  ctxmarker = cursor
#   define YYRESTORE()    cursor = marker
#   define YYRESTORECTX() cursor = ctxmarker
#   define YYLESSTHAN(n)  limit - cursor < n
#   define YYFILL(n) { return -1; }
#	define YYLIMIT		s->lim
#	define YYCURSOR		cursor
#	define YYMARKER		s->ptr
    /*!re2c
		FF = "\xFF";
		FD = "\xFD";
		LF = "\x0A";
    */

	/*!re2c
		FF FD {
			RET(TOKEN_FF_FD);
		}

		FF [^\xFD] . {
			RET(TOKEN_FF_ANY_ANY);
		}

		LF {
			RET(TOKEN_LF);
		}

		. {
			RET(TOKEN_ANY);
		}
	*/
}

