#ifndef _SCANNER_H_
#define _SCANNER_H_

#define TOKEN_END   0
#define TOKEN_SLASH 1
#define TOKEN_WORD  2

typedef struct SCANNER {
    const char *token;
    const char *cursor;
    const char *limit;
} SCANNER;

int scan(SCANNER *scanner);

#endif /* #ifndef _SCANNER_H_ */

