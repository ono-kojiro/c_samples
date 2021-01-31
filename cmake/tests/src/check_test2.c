#include <stdio.h>
#include <stdlib.h>
#include <check.h>

START_TEST(test_testcase1)
{
	ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_testcase2)
{
	ck_assert_msg(1 == 1, "ck_assert_msg test");
}
END_TEST

Suite * create_suite(void)
{
	Suite *s;
	TCase *tc_core;
	TCase *tc_limits;

	s = suite_create("Hello");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_testcase1);
	suite_add_tcase(s, tc_core);

	tc_limits = tcase_create("Limits");
	tcase_add_test(tc_limits, test_testcase2);

	suite_add_tcase(s, tc_limits);

	return s;
}

int main(int argc, char **argv)
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = create_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
	return 0;
}

