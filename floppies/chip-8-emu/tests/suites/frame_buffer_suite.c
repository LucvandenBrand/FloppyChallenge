#include <check.h>
#include <rendering/render_context.h>
#include <rendering/frame_buffer.h>
#include <emulator/system.h>

START_TEST(test_create_free_frame_buffer)
{
    RenderContext render_context = create_render_context("CHIP-8-emu", VIDEO_WIDTH, VIDEO_HEIGHT);
    FrameBuffer frame_buffer = create_frame_buffer(render_context, VIDEO_WIDTH, VIDEO_HEIGHT);
    ck_assert_ptr_ne(frame_buffer.sdl_texture, NULL);
    ck_assert_ptr_ne(frame_buffer.pixels, NULL);
    ck_assert_int_eq(frame_buffer.frame_width, VIDEO_WIDTH);
    ck_assert_int_eq(frame_buffer.frame_height, VIDEO_HEIGHT);
    free_frame_buffer(&frame_buffer);
    free_render_context(&render_context);
}
END_TEST

Suite * make_frame_buffer_suite()
{
    Suite *suite = suite_create("Frame Buffer Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_create_free_frame_buffer);
    suite_add_tcase(suite, test_case);

    return suite;
}