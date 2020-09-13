#include <check.h>
#include "renderer/turtle.h"
#include "math/point.h"

LSystem alloc_test_line_system()
{
    SymbolList symbol_list = alloc_empty_symbol_list();
    add_symbol_to_list('A', &symbol_list);
    add_symbol_to_list('B', &symbol_list);
    add_symbol_to_list('+', &symbol_list);
    add_symbol_to_list('-', &symbol_list);
    add_symbol_to_list('B', &symbol_list);

    RuleList rule_list = alloc_empty_rule_list();
    LSystem system = {symbol_list, rule_list};
    return system;
}

START_TEST(test_build_polyline_from_system)
{
    LSystem system = alloc_test_line_system();
    PointList polyline = alloc_empty_point_list();

    build_polyline_from_system(&polyline, system);
    ck_assert_int_eq(polyline.length, 4);
    ck_assert(polyline.points[0].x == 0);
    ck_assert(polyline.points[0].y == 0);
    ck_assert(polyline.points[1].x == 0);
    ck_assert(polyline.points[1].y == 1);
    ck_assert(polyline.points[2].x == 0);
    ck_assert(polyline.points[2].y == 2);
    ck_assert(polyline.points[3].x == 0);
    ck_assert(polyline.points[3].y == 3);

    free_point_list(&polyline);
    free_system(&system);
}
END_TEST

Suite * make_turtle_suite()
{
    Suite * suite = suite_create("Turtle Test Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_build_polyline_from_system);

    suite_add_tcase(suite, test_case);

    return suite;
}