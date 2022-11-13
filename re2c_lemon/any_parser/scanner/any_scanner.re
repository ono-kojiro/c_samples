#include "config.h"

#include <assert.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <inttypes.h>

#define SIZE (64 * 1024)

/* export YYMAXFILL */
/*!header:re2c:on*/

/*!max:re2c*/

/*!header:re2c:off*/

/*!max:re2c*/

#include "scanner.h"
#include "any_scanner.h"

#if USE_PARSER
#include "parser.h"
#endif

#define PRINT_TOKEN(x) { \
	fprintf(stderr, "(%s:", x); \
	fprintf(stderr, "%.*s", (int)(s->cur - s->tok), s->tok); \
	fprintf(stderr, ")"); \
}

/*!re2c re2c:define:YYCTYPE = "unsigned char"; */

int AnyScanner_Scan(SCANNER *s)
{
    unsigned long u;

	/* from submatch/http_rfc7230.re */

#if 0
	fprintf(stderr, "SCANNER : Scanner_Scan() start\n");
#endif

/*!re2c
    end = "\x00";
    eol = ([\r\n]|[\n]);
    ws  = [ \t\v]+;

    O   = [0-7];         // oct
    D   = [0-9];         // digit
    NZ  = [1-9];         // non-zero
    L   = [a-zA-Z_];     // letter
    A   = [a-zA-Z_0-9];  // alphabet
    H   = [a-fA-F0-9];   // hex
    HP  = "0" [xX];      // hex prefix
    E   = [Ee][+-]?D+;
    P   = [Pp][+-]?D+;
    FS  = ("f"|"F"|"l"|"L");     // float suffix
    IS  = ((("u"|"U")("l"|"L"|"ll"|"LL")?)|(("l"|"L"|"ll"|"LL")("u"|"U")?));
    CP  = ("u"|"U"|"L");
	SP  = ("u8"|"u"|"U"|"L");

    DBS = "\\\\"; // double backslash
	ES  = "\\"  ( [\'"?abfnrtv] | [0-7]{1,3} );
	BS  = "\x5C";  // backspace 0d92

    wd  = (A)+;
    dec = (D|NZ)+;

	any = [^];
*/


    for (;;) {
std:
		s->tok = s->cur;
#if 0
		fprintf(stderr, "%s:%d:%s: ",
			__FILE__ , __LINE__ , __FUNCTION__ );
		fprintf(stderr, "for loop\n");
#endif
        /*!re2c
            re2c:yyfill:enable = 1;
            re2c:define:YYCURSOR = s->cur;
            re2c:define:YYMARKER = s->mar;
            re2c:define:YYLIMIT = s->lim;
            re2c:define:YYFILL = "if (!fill(s, @@)) return EOF;";
            re2c:define:YYFILL:naked = 1;
		*/


		/*!re2c
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
				fprintf(stderr, "(EOL)\n");
				continue;
			}

			end {
				fprintf(stderr, "(EOF)\n");
				RET(EOF);
			}

			SP? "\"" ([^"])* "\"" {
				PRINT_TOKEN("STRING_LITERAL");
				return(STRING_LITERAL);
			}

			BS {
				PRINT_TOKEN("BACKSLASH");
				RET(BACKSLASH);
			}

			CP? "'" ([^'])+ "'" {
				PRINT_TOKEN("I_CONSTANT");
				RET(I_CONSTANT);
			}
			
			(HP) (H)+ (IS)? {
				PRINT_TOKEN("I_CONSTANT");
				RET(I_CONSTANT);
			}

			NZ D* IS? {
				PRINT_TOKEN("I_CONSTANT");
				RET(I_CONSTANT);
			}

			"0" D* IS? {
				PRINT_TOKEN("I_CONSTANT");
				RET(I_CONSTANT);
			}

			D* "." D+ E? FS? {
				PRINT_TOKEN("F_CONSTANT");
				RET(F_CONSTANT);
			}

			dec {
				PRINT_TOKEN("DEC");
				RET(DEC);
			}
			
			wd {
				PRINT_TOKEN("WD");
				RET(WD);
			}

			ws {
				fprintf(stderr, "%.*s",
					(int)(s->cur - s->tok), s->tok);
				continue;
			}
			
			any {
				PRINT_TOKEN("ANY");
				RET(ANY);
			}
			
			* {
				fprintf(stderr, "(UNKNOWN:%X)", s->tok[0]);
				RET(-1);
			}
		*/

comment_c :
		/*!re2c

			"*/" {
				goto std;
			}

			end {
				fprintf(stderr, "\nERROR : unterminated comment\n");
				exit(1);
			}

			* {
				goto comment_c;
			}

		*/

comment_perl :
		/*!re2c
			eol {
				fprintf(stderr, "(EOL)\n");
				goto std;
			}

			end {
				fprintf(stderr, "\nERROR : unterminated comment\n");
				exit(1);
			}

			* {
				goto comment_perl;
			}

		*/

comment_cxx :
		/*!re2c
			eol {
				fprintf(stderr, "(EOL)\n");
				goto std;
			}

			end {
				fprintf(stderr, "\nERROR : unterminated comment\n");
				exit(1);
			}

			* {
				goto comment_cxx;
			}

		*/
	}
}

