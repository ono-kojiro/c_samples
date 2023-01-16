#include <stdlib.h>

#include <gtest/gtest.h>

#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

#include "parser.h"
#include "scanner.h"

TEST(minusTest, simple)
{
    Scanner in;
	YYSTYPE yylval;

	/* Parser */
	void *parser = NULL;
	char prompt[] = "PARSER : ";

	/* Userdata */
	USERDATA *userdata = NULL;
    Token token;

	parser = (void *)MyParserAlloc(malloc);
    EXPECT_FALSE(parser == NULL);

	userdata = Userdata_Create();
    EXPECT_FALSE(userdata == NULL);

	MyParserInit(parser);

#ifndef NDEBUG
	MyParserTrace(stderr, prompt);
#endif

    /* 1 + 2 */
    token.value = 1;
    MyParser(parser, TOKEN_NUM, token, userdata);
   
    token.value = 0;
    MyParser(parser, TOKEN_PLUS, token, userdata);

    token.value = 2;
    MyParser(parser, TOKEN_NUM, token, userdata);
   
    token.value = 0;
    MyParser(parser, TOKEN_NEWLINE, token, userdata);
    
    token.value = 0;
    MyParser(parser, 0, token, userdata);

    EXPECT_TRUE(userdata->result == 3);

    if(parser){
	    MyParserFree(parser, free);
    }

	if(userdata){
        Userdata_Delete(userdata);
    }
}

