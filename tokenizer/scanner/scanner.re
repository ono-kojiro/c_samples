#include "config.h"

#include <assert.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <inttypes.h>

#include "input.h"
#include "scanner.h"

#if USE_PARSER
#include "parser.h"
#endif

#define PRINT_TOKEN(x) { \
	fprintf(s->out, "(%s:", x); \
	fprintf(s->out, "%.*s", (int)(s->cur - s->tok), s->tok); \
	fprintf(s->out, ")"); \
}

int Scanner_Scan(INPUT *s)
{
    unsigned long u;

/*!re2c
    end = "\x00";
    eol = ([\r\n]|[\n]);
    
    ws    = [ \t\v]+;
    DIGIT = [0-9];         // digit
    DIGIT1TO9 = [1-9];         // non-zero
    DIGITS = DIGIT+;
    INT = DIGIT | DIGIT1TO9 DIGITS | "-" DIGITS | "-" DIGIT1TO9 DIGITS;
    FRAC = [.] DIGITS;
    E   = [Ee][+-]?;
    EXP = E DIGITS;
    
    HEX_DIGIT   = [a-fA-F0-9];   // hex digit
    NUMBER = INT | INT FRAC | INT EXP | INT FRAC EXP;
    UNESCAPEDCHAR = [ -!#-\[\]--~];
    ESCAPEDCHAR = "\\" [\\bfnrt/];

    UNICODECHAR = "\\u" HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT;
    CHAR = UNESCAPEDCHAR | ESCAPEDCHAR | UNICODECHAR;
    CHARS = CHAR+;
    DBL_QUOTE = [\"];

	ANY = [^];
*/

    for (;;) {
std:
		s->tok = s->cur;
        /*!re2c
            re2c:eof = 0;
            re2c:api:style = free-form;
            re2c:yyfill:enable = 1;
            re2c:define:YYCTYPE = char;
            re2c:define:YYCURSOR = s->cur;
            re2c:define:YYMARKER = s->mar;
            re2c:define:YYLIMIT = s->lim;
            re2c:define:YYFILL = "fill(s) == 0";
			
            $ {
				fprintf(s->out, "(EOF)\n");
				RET(EOF);
            }

			"/*" {
				goto comment_c;
			}
			
			"#" {
				goto comment_perl;
			}
			
			"//" {
				goto comment_cxx;
			}

			eol {
				fprintf(s->out, "(EOL)\n");
				continue;
                //RET(TOKEN_EOL);
			}

			end {
				fprintf(s->out, "(EOF)\n");
				RET(EOF);
			}
			
			DBL_QUOTE ANY* DBL_QUOTE {
                RET(TOKEN_STRING);
            }

            NUMBER {
                RET(TOKEN_NUMBER);
            }

            "true" {
                RET(TOKEN_TRUE);
            }

            "false" {
                RET(TOKEN_FALSE);
            }

            "null" {
                RET(TOKEN_NULL);
            }

            "{" {
                RET(TOKEN_O_BEGIN);
            }

            "}" {
                RET(TOKEN_O_END);
            }

            "[" {
                RET(TOKEN_A_BEGIN);
            }

            "]" {
                RET(TOKEN_A_END);
            }

            "," {
                RET(TOKEN_COMMA);
            }

            ":" {
                RET(TOKEN_COLON);
            }

            ws+ {
                continue;
            }

            //DBL_QUOTE {
            //    RET(TOKEN_DBL_QUOTE);
            //}
            
            * {
				fprintf(stderr, "(UNKNOWN:%X)", s->tok[0]);
				RET(-1);
			}
            

		*/

        /*!include:re2c "comment_c.re" */

        /*!include:re2c "comment_perl.re" */

        /*!include:re2c "comment_cxx.re" */
	}
}

