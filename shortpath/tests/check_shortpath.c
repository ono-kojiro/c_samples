#include <stdio.h>
#include <stdlib.h>

#include <check.h>

#include "shortpath.h"

START_TEST(test_shortpath)
{
    char input[]     = "/aaa/bbb/../ccc/ddd";
    const char exp[] = "/aaa/ccc/ddd";

    shortpath(input);
    ck_assert_str_eq(input, exp);
}
END_TEST

START_TEST(test_shortpath_dot)
{
    char input[]     = "/aaa/bbb/./ccc/ddd";
    const char exp[] = "/aaa/bbb/ccc/ddd";

    shortpath(input);
    ck_assert_str_eq(input, exp);
}
END_TEST

START_TEST(test_shortpath_tilda)
{
    char input[]     = "~/aaa/bbb/ccc/ddd";
    const char exp[] = "~/aaa/bbb/ccc/ddd";

    shortpath(input);
    ck_assert_str_eq(input, exp);
}
END_TEST

START_TEST(test_shortpath_comb)
{
    char input[]     = "~/aaa/bbb/../ccc/../ddd";
    const char exp[] = "~/aaa/ddd";

    shortpath(input);
    ck_assert_str_eq(input, exp);
}
END_TEST


Suite *shortpath_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ShortPath");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_shortpath);
    tcase_add_test(tc_core, test_shortpath_dot);
    tcase_add_test(tc_core, test_shortpath_tilda);
    tcase_add_test(tc_core, test_shortpath_comb);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(int argc, char **argv)
{
    int not_ok = 0;

    Suite *s;
    SRunner *sr;

    s = shortpath_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    not_ok = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (not_ok == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

