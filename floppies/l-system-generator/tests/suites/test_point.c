#include <check.h>
#include "math/point.h"

START_TEST(test_alloc_point_list)
{
    PointList list = alloc_empty_point_list();
    ck_assert_ptr_ne(list.points, NULL);
    ck_assert_int_eq(list.length, 0);
    ck_assert_int_eq(list.space, 2);
    free_point_list(&list);
    ck_assert_ptr_eq(list.points, NULL);
    ck_assert_int_eq(list.length, 0);
    ck_assert_int_eq(list.space, 0);
}
END_TEST

START_TEST(test_add_point_to_list)
{
    PointList list = alloc_empty_point_list();

    Point point = {1.0f, 0.4f};
    add_point_to_list(point, &list);
    ck_assert_int_eq(list.length, 1);
    ck_assert_int_eq(list.space, 2);
    ck_assert(list.points[0].x == 1.0f);
    ck_assert(list.points[0].y == 0.4f);

    Point next_point = { 0.3f, 0.2f};
    add_point_to_list(next_point, &list);
    ck_assert_int_eq(list.length, 2);
    ck_assert_int_eq(list.space, 4);
    ck_assert(list.points[1].x == 0.3f);
    ck_assert(list.points[1].y == 0.2f);

    free_point_list(&list);
}
END_TEST

Suite * make_point_suite()
{
    Suite * suite = suite_create("Point Test Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_alloc_point_list);
    tcase_add_test(test_case, test_add_point_to_list);
    suite_add_tcase(suite, test_case);

    return suite;
}