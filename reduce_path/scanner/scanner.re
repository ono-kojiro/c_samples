#include <stdio.h>

#include "scanner.h"

int scan(SCANNER *s)
{
    const char *cursor = s->cursor;
    const char *marker;
    const char *ctxmarker;

    if(s->cursor >= s->limit){
        return 0;
    }

    s->token = s->cursor;

#   define YYCTYPE        char
#   define YYPEEK()       *cursor
#   define YYSKIP()       ++cursor
#   define YYMARKER       marker
#   define YYBACKUP()     marker = cursor
#   define YYBACKUPCTX()  ctxmarker = cursor
#   define YYRESTORE()    cursor = marker
#   define YYRESTORECTX() cursor = ctxmarker
#   define YYLESSTHAN(n)  s->limit - cursor < n
#   define YYFILL(n)      {}

#   define YYCURSOR       cursor
#   define YYLIMIT        s->limit

#   define RET(n)         { s->cursor = cursor; return n; }

loop :
    /*!re2c
        dir = [^/]+;
        slash = "/";

        dir slash ".." slash {
            s->token = cursor;
            goto loop;
        }

        slash "." slash {
            s->token = cursor - 1;
            goto loop;     
        }

        dir {
            //printf("%.*s", (int)(s->cursor - marker), s->cursor);
            RET(TOKEN_WORD);
        }
        slash {
            //printf("/");
            RET(TOKEN_SLASH);
        }
        "\x00" {
            RET(TOKEN_END);
        }

    */
}

