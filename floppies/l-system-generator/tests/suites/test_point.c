#include <check.h>
#include <math.h>
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

START_TEST(test_normalize_point_list)
{
    PointList list = alloc_empty_point_list();
    Point point_ll = {-10, -20};
    add_point_to_list(point_ll, &list);
    Point point_lr = {20, -21};
    add_point_to_list(point_lr, &list);
    Point point_ul = {-11, 30};
    add_point_to_list(point_ul, &list);
    Point point_ur = {10, 30};
    add_point_to_list(point_ur, &list);
    normalize_point_list(&list);
    for (size_t index = 0; index < list.length; index++)
    {
        Point point = list.points[index];
        ck_assert(point.x >= 0.0f);
        ck_assert(point.x <= 1.0f);
        ck_assert(point.y >= 0.0f);
        ck_assert(point.y <= 1.0f);
    }
}
END_TEST

START_TEST(test_get_list_bounds)
{
    PointList list = alloc_empty_point_list();
    Point low_point = {-10, 3};
    add_point_to_list(low_point, &list);
    Point mid_point = {5, 2};
    add_point_to_list(mid_point, &list);
    Point high_point = {23, 6};
    add_point_to_list(high_point, &list);
    Point min, max;
    get_list_bounds(list, &min, &max);
    ck_assert(min.x == low_point.x);
    ck_assert(min.y == mid_point.y);
    ck_assert(max.x == high_point.x);
    ck_assert(max.y == high_point.y);
    free_point_list(&list);
}
END_TEST

START_TEST(test_point_length)
{
    Point point = {2, 4};
    float ref_length = sqrtf(2*2 + 4*4);
    float length = point_length(point);
    ck_assert(length == ref_length);
}
END_TEST

START_TEST(test_divide_point)
{
    Point point = {4, 7};
    point = divide_point(point, 2);
    ck_assert(point.x == 2.0f);
    ck_assert(point.y == 3.5f);
}
END_TEST

START_TEST(test_subtract_points)
{
    Point point = {4, 7};
    Point subtractor = {1, 8};
    point = subtract_points(point, subtractor);
    ck_assert(point.x == 3.0f);
    ck_assert(point.y == -1.0f);
}
END_TEST

Suite * make_point_suite()
{
    Suite * suite = suite_create("Point Test Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_alloc_point_list);
    tcase_add_test(test_case, test_add_point_to_list);
    tcase_add_test(test_case, test_normalize_point_list);
    tcase_add_test(test_case, test_get_list_bounds);
    tcase_add_test(test_case, test_point_length);
    tcase_add_test(test_case, test_divide_point);
    tcase_add_test(test_case, test_subtract_points);

    suite_add_tcase(suite, test_case);

    return suite;
}