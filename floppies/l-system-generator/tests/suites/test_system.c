#include <check.h>
#include "system.h"

START_TEST(test_alloc_system)
{
    LSystem system = alloc_empty_system();
    ck_assert_int_eq(system.axiom.length, 0);
    ck_assert_int_eq(system.axiom.space, 2);
    ck_assert_int_eq(system.rules.length, 0);
    ck_assert_int_eq(system.rules.space, 2);
    free_system(&system);
}
END_TEST

Suite * make_system_suite()
{
    Suite * suite = suite_create("System Test Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_alloc_system);
    suite_add_tcase(suite, test_case);

    return suite;
}