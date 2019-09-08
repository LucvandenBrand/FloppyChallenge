#include <check.h>
#include <emulator/system.h>
#include <emulator/emulator.h>

System create_empty_system()
{
    BinaryBlob empty_rom = malloc_binary_blob(0);
    System system = init_system(&empty_rom);
    free_binary_blob(&empty_rom);
    return system;
}

START_TEST(test_clear_display) // 00E0
{
    System system = create_empty_system();
    memset(system.video_memory, 10, sizeof(system.video_memory));
    for (int index = 0; index < VIDEO_MEMORY_SIZE; index++)
        ck_assert_int_eq(system.video_memory[index], 10);
    process_op_code(&system, 0x00E0);
    for (int index = 0; index < VIDEO_MEMORY_SIZE; index++)
        ck_assert_int_eq(system.video_memory[index], 0);

    ck_assert_int_eq(system.video_changed, true);
    ck_assert_int_eq(system.program_counter, 0x202);
}
END_TEST

START_TEST(test_return_from_subroutine) // 00EE
{
    System system = create_empty_system();
    system.stack[0] = 0x300;
    system.stack_pointer = 1;
    process_op_code(&system, 0x00EE);
    ck_assert_int_eq(system.program_counter, 0x300);
    ck_assert_int_eq(system.stack_pointer,0);
}
END_TEST

START_TEST(test_jump_to_location) // 1NNN
{
    System system = create_empty_system();
    process_op_code(&system, 0x1434);
    ck_assert_int_eq(system.stack_pointer, 0x434);
}
END_TEST

START_TEST(test_call_subroutine) // 2NNN
{
    System system = create_empty_system();
    process_op_code(&system, 0x2345);
    ck_assert_int_eq(system.stack_pointer, 1);
    ck_assert_int_eq(system.stack[0], 0x200);
    ck_assert_int_eq(system.program_counter, 0x345);
}
END_TEST

START_TEST(test_skip_if_register_equal) // 3XKK
{
    System system = create_empty_system();
    process_op_code(&system, 0x3011);
    ck_assert_int_eq(system.program_counter, 0x202);
    system.v_registers[0] = 0x11;
    process_op_code(&system, 0x3011);
    ck_assert_int_eq(system.program_counter, 0x206);

    process_op_code(&system, 0x3133);
    ck_assert_int_eq(system.program_counter, 0x208);
    system.v_registers[0] = 0x33;
    process_op_code(&system, 0x3133);
    ck_assert_int_eq(system.program_counter, 0x212);
}
END_TEST

START_TEST(test_skip_if_register_not_equal) // 4XKK
{
    System system = create_empty_system();
    process_op_code(&system, 0x4011);
    ck_assert_int_eq(system.program_counter, 0x204);
    system.v_registers[0] = 0x11;
    process_op_code(&system, 0x4011);
    ck_assert_int_eq(system.program_counter, 0x206);

    process_op_code(&system, 0x4133);
    ck_assert_int_eq(system.program_counter, 0x210);
    system.v_registers[0] = 0x33;
    process_op_code(&system, 0x4133);
    ck_assert_int_eq(system.program_counter, 0x212);
}
END_TEST

START_TEST(test_skip_if_registers_equal) // 5XY0
{
    System system = create_empty_system();
    system.v_registers[1] = 0x11;
    system.v_registers[3] = 0x33;
    process_op_code(&system, 0x5130);
    ck_assert_int_eq(system.program_counter, 0x202);
    system.v_registers[3] = 0x11;
    process_op_code(&system, 0x5130);
    ck_assert_int_eq(system.program_counter, 0x206);
}
END_TEST

START_TEST(test_set_register_to_value) // 6XKK
{
    System system = create_empty_system();
    ck_assert_int_eq(system.v_registers[1], 0);
    process_op_code(&system, 0x6112);
    ck_assert_int_eq(system.v_registers[1], 0x12);
    ck_assert_int_eq(system.program_counter, 0x202);
}
END_TEST

START_TEST(test_add_value_to_register) // 7XKK
{
    System system = create_empty_system();
    system.v_registers[1] = 0x11;
    process_op_code(&system, 0x7112);
    ck_assert_int_eq(system.v_registers[1], 0x23);
    ck_assert_int_eq(system.program_counter, 0x202);
}
END_TEST

START_TEST(test_op_code_set_index_reg) // ANNN
{
    System system = create_empty_system();
    process_op_code(&system, 0xA123);
    ck_assert_int_eq(system.index_register, 0x0123);
    ck_assert_int_eq(system.program_counter, 0x202);
}
END_TEST

START_TEST(test_step_timers)
{
    BinaryBlob empty_rom = malloc_binary_blob(0);
    System system = init_system(&empty_rom);
    free_binary_blob(&empty_rom);
    system.delay_timer = 2;
    system.sound_timer = 2;
    step_timers(&system);
    ck_assert_int_eq(system.delay_timer, 1);
    ck_assert_int_eq(system.sound_timer, 1);
    ck_assert(system.audio_triggered == false);
    step_timers(&system);
    ck_assert_int_eq(system.delay_timer, 0);
    ck_assert_int_eq(system.sound_timer, 0);
    ck_assert(system.audio_triggered == true);
    step_timers(&system);
    ck_assert_int_eq(system.delay_timer, 0);
    ck_assert_int_eq(system.sound_timer, 0);
    ck_assert(system.audio_triggered == true);
}
END_TEST

START_TEST(test_copy_system_video_memory)
{
    BinaryBlob empty_rom = malloc_binary_blob(0);
    System system = init_system(&empty_rom);
    free_binary_blob(&empty_rom);
    system.video_memory[0] = 10;
    system.video_memory[VIDEO_HEIGHT * VIDEO_WIDTH - 1] = 42;

    RenderContext context = create_render_context("Test", VIDEO_WIDTH * 2, VIDEO_HEIGHT * 2);
    FrameBuffer frame_buffer = create_frame_buffer(context, VIDEO_WIDTH * 2, VIDEO_HEIGHT * 2);
    copy_system_video_memory(system, frame_buffer);
    ck_assert_int_eq(frame_buffer.pixels[0], 10);
    unsigned int last_pixel_index = (VIDEO_HEIGHT - 1) * frame_buffer.frame_width + VIDEO_WIDTH - 1;
    ck_assert_int_eq(frame_buffer.pixels[last_pixel_index], 42);
    free_frame_buffer(&frame_buffer);
    free_render_context(&context);
}
END_TEST

Suite * make_emulator_suite()
{
    Suite *suite = suite_create("Emulator Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_step_timers);
    tcase_add_test(test_case, test_copy_system_video_memory);
    suite_add_tcase(suite, test_case);

    TCase * op_code_test_case = tcase_create("Op Code Test Cases");
    tcase_add_test(op_code_test_case, test_clear_display);
    tcase_add_test(op_code_test_case, test_return_from_subroutine);
    tcase_add_test(op_code_test_case, test_jump_to_location);
    tcase_add_test(op_code_test_case, test_call_subroutine);
    tcase_add_test(op_code_test_case, test_skip_if_register_equal);
    tcase_add_test(op_code_test_case, test_skip_if_register_not_equal);
    tcase_add_test(op_code_test_case, test_skip_if_registers_equal);
    tcase_add_test(op_code_test_case, test_op_code_set_index_reg);
    suite_add_tcase(suite, op_code_test_case);

    return suite;
}