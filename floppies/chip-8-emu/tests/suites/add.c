#include <check.h>
#include <add.h>

START_TEST(testAdd)
{
    int result = add(1, 2);
    ck_assert_int_eq(result, 3);
}
END_TEST

Suite * makeAddSuite()
{
    Suite *suite = suite_create("Add Test Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, testAdd);
    suite_add_tcase(suite, test_case);

    return suite;
}