#ifndef SCANNER_H
#define SCANNER_H

enum {
	TOKEN_FF_FD,
	TOKEN_FF_ANY_ANY,
	TOKEN_LF,
	TOKEN_ANY
};

typedef struct _SCANNER {
	char *top;
	char *cur;
	char *lim;
	char *tok;
	char *ptr;
} SCANNER;

int lex(SCANNER *s);
int dump_scanner(SCANNER *s);

#ifdef YYDEBUG
#undef YYDEBUG
#define YYDEBUG(state, current)  yydebug(state, current)
#else
#define YYDEBUG(state, current)
#endif /* #ifdef YYDEBUG */

#endif /* #ifndef SCANNER_H */

