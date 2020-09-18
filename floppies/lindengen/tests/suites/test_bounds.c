#include <check.h>
#include "math/bounds.h"

START_TEST(test_clamp)
{
    float clamp_value = clamp(2, 0, 1);
    ck_assert(clamp_value == 1);
    clamp_value = clamp(-2, 0, 1);
    ck_assert(clamp_value == 0);
}
END_TEST

START_TEST(test_snap_to_value)
{
    float snap_value = snap_to_value(1.1f, 1, 0.15f);
    ck_assert(snap_value == 1);
    snap_value = snap_to_value(-1.1f, -1, 0.15f);
    ck_assert(snap_value == -1);
}
END_TEST

Suite * make_bounds_suite()
{
    Suite * suite = suite_create("Bounds Test Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_clamp);
    tcase_add_test(test_case, test_snap_to_value);

    suite_add_tcase(suite, test_case);

    return suite;
}