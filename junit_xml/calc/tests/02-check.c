#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "parser.h"
#include "scanner.h"

#include <check.h>

START_TEST(test_check)
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
    ck_assert_ptr_ne(parser, NULL);

	userdata = Userdata_Create();
    ck_assert_ptr_ne(userdata, NULL);

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

    ck_assert_int_eq(userdata->result, 3);

    if(parser){
	    MyParserFree(parser, free);
    }

	if(userdata){
        Userdata_Delete(userdata);
    }
}
END_TEST

Suite *create_suite()
{
    Suite *s;
    TCase *tc;

    s = suite_create("calc");
    tc = tcase_create("Core");

    tcase_add_test(tc, test_check);
    suite_add_tcase(s, tc);

    return s;
}


int main(int argc, char **argv)
{
    int number_failed = 0;
    Suite *s;
    SRunner *sr;

    char filepath[PATH_MAX];

    s = create_suite();
    sr = srunner_create(s);

    srunner_set_xml(sr, "02-check-check.xml");
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

