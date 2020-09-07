#include <check.h>
#include "renderer/canvas.h"

START_TEST(test_alloc_canvas)
{
    Canvas canvas = alloc_canvas(100, 100);
    ck_assert_ptr_ne(canvas.pixels, NULL);
    ck_assert_int_eq(canvas.width, 100);
    ck_assert_int_eq(canvas.height, 100);
    free_canvas(&canvas);
    ck_assert_ptr_eq(canvas.pixels, NULL);
    ck_assert_int_eq(canvas.width, 0);
    ck_assert_int_eq(canvas.height, 0);
}
END_TEST

START_TEST(test_clear_canvas)
{
    Canvas canvas = alloc_canvas(100, 100);
    Colour colour = {50, 10, 30};
    clear_canvas(&canvas, colour);
    for (size_t row = 0; row < canvas.height; row++)
        for (size_t col = 0; col < canvas.width; col++)
        {
            Colour read_colour = get_pixel(canvas, row, col);
            ck_assert(colour.red == read_colour.red);
            ck_assert(colour.green == read_colour.green);
            ck_assert(colour.blue == read_colour.blue);
        }
    free_canvas(&canvas);
}
END_TEST

START_TEST(test_get_set_pixel)
{
    Canvas canvas = alloc_canvas(100, 100);
    Colour clear_colour = {(char) 255, (char) 255, (char) 255};
    clear_canvas(&canvas, clear_colour);
    Colour draw_colour = {(char) 255, (char) 255, (char) 255};
    set_pixel(&canvas, draw_colour, 25, 44);
    Colour read_colour = get_pixel(canvas, 25, 44);
    ck_assert(draw_colour.red == read_colour.red);
    ck_assert(draw_colour.green == read_colour.green);
    ck_assert(draw_colour.blue == read_colour.blue);
    free_canvas(&canvas);
}
END_TEST

Suite * make_canvas_suite()
{
    Suite * suite = suite_create("Canvas Test Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_alloc_canvas);
    tcase_add_test(test_case, test_clear_canvas);
    tcase_add_test(test_case, test_get_set_pixel);
    suite_add_tcase(suite, test_case);

    return suite;
}