#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "scanner.h"

//#include <check.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

void test_times(void)
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
    //ck_assert_ptr_ne(parser, NULL);
    CU_ASSERT(parser != NULL);

	userdata = Userdata_Create();
    //ck_assert_ptr_ne(userdata, NULL);
    CU_ASSERT(userdata != NULL);

	MyParserInit(parser);

#ifndef NDEBUG
	MyParserTrace(stderr, prompt);
#endif

    /* 2 x 3 */
    token.value = 2;
    MyParser(parser, TOKEN_NUM, token, userdata);
   
    token.value = 0;
    MyParser(parser, TOKEN_TIMES, token, userdata);

    token.value = 3;
    MyParser(parser, TOKEN_NUM, token, userdata);
   
    token.value = 0;
    MyParser(parser, TOKEN_NEWLINE, token, userdata);
    
    token.value = 0;
    MyParser(parser, 0, token, userdata);

    //ck_assert_int_eq(userdata->result, 3);
    CU_ASSERT(userdata->result == 6);

    if(parser){
	    MyParserFree(parser, free);
    }

	if(userdata){
        Userdata_Delete(userdata);
    }
}

int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

int main(int argc, char **argv)
{
    int ret = 0;
    void *p = NULL;

    CU_pSuite pSuite = NULL;
    ret = CU_initialize_registry();
    if(ret != CUE_SUCCESS){
        return CU_get_error();
    }

    pSuite = CU_add_suite("Suite_1", init_suite, clean_suite);
    if(NULL == pSuite){
        CU_cleanup_registry();
        return CU_get_error();
    }

    p = CU_add_test(pSuite, "test of times", test_times);
    if(NULL == p){
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_set_output_filename("03-cunit");

    CU_basic_set_mode(CU_BRM_VERBOSE);
    //CU_basic_run_tests();
    CU_automated_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

