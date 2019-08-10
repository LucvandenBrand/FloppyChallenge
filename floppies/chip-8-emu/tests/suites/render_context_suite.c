#include <check.h>
#include <rendering/render_context.h>
#include <emulator/system.h>

START_TEST(test_create_free_context)
{
    RenderContext render_context = create_render_context("CHIP-8-emu", VIDEO_WIDTH, VIDEO_HEIGHT);
    ck_assert_ptr_ne(render_context.window, NULL);
    ck_assert_ptr_ne(render_context.renderer, NULL);
    ck_assert_int_eq(render_context.screen_width, VIDEO_WIDTH);
    ck_assert_int_eq(render_context.screen_height, VIDEO_HEIGHT);
    ck_assert_str_eq(render_context.title, "CHIP-8-emu");
    free_render_context(&render_context);
}
END_TEST

Suite * make_render_context_suite()
{
    Suite *suite = suite_create("Render Context Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_create_free_context);
    suite_add_tcase(suite, test_case);

    return suite;
}