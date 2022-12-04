#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include "input.h"

#define RET(x) { \
	return (x); \
}

#if USE_PARSER
#else
enum {
	TOKEN_COMMA = 1,
	TOKEN_NUMBER,
	TOKEN_COLON,
	TOKEN_A_BEGIN,
	TOKEN_A_END,
	TOKEN_O_BEGIN,
	TOKEN_O_END,
	TOKEN_STRING,
    TOKEN_NULL,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_DBL_QUOTE,
	TOKEN_ANY
};
#endif

int Scanner_Scan(INPUT *s);

#endif /* #ifndef SCANNER_H */


