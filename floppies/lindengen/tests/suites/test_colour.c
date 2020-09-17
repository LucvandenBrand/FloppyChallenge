#include <check.h>
#include "renderer/colour.h"

START_TEST(test_create_colour)
{
    Colour created_colour = create_colour(0.5f, 0.6f, 1.0f);
    ck_assert(created_colour.red == 127);
    ck_assert(created_colour.green == 153);
    ck_assert(created_colour.blue == 255);
}
END_TEST

START_TEST(test_create_colour_greyscale)
{
    Colour created_colour = create_colour_greyscale(0.5f);
    ck_assert(created_colour.red == 127);
    ck_assert(created_colour.green == 127);
    ck_assert(created_colour.blue == 127);
}
END_TEST

Suite * make_colour_suite()
{
    Suite * suite = suite_create("Colour Test Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_create_colour);
    tcase_add_test(test_case, test_create_colour_greyscale);
    suite_add_tcase(suite, test_case);

    return suite;
}