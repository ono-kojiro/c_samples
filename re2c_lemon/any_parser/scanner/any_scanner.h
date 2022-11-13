#ifndef ANYSCANNER_H
#define ANYSCANNER_H

#include <stdio.h>
#include "scanner.h"

#if 0
#if USE_PARSER
#else
enum {
	DEC = 1,
	WD,
	WS,
	EOL,
	HOST,
	MACHINE,
	LOGIN,
	PASSWORD,
	METHOD,
	FIELD_NAME,
	TCHAR,
	ANY
};
#endif
#endif

int AnyScanner_Scan(SCANNER *s);

#endif /* #ifndef SCANNER_H */


