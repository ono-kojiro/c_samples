#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "scanner.h"

#include <check.h>

START_TEST(test_init)
{
    Scanner in;
	YYSTYPE yylval;

	/* Parser */
	void *parser = NULL;

	/* Userdata */
	USERDATA *userdata = NULL;

	parser = (void *)MyParserAlloc(malloc);
    ck_assert_ptr_ne(parser, NULL);

	userdata = Userdata_Create();
    ck_assert_ptr_ne(userdata, NULL);

	MyParserInit(parser);

#if 0
	MyParserTrace(stderr, "PARSER : ");
#endif

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

    tcase_add_test(tc, test_init);
    suite_add_tcase(s, tc);

    return s;
}


int main(int argc, char **argv)
{
    int number_failed = 0;
    Suite *s;
    SRunner *sr;

    s = create_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

