#include <check.h>
#include <emulator/system.h>
#include <emulator/emulator.h>
#include <emulator/font.h>

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
    ck_assert_int_eq(system.program_counter, 0x302);
    ck_assert_int_eq(system.stack_pointer,0);
}
END_TEST

START_TEST(test_jump_to_location) // 1NNN
{
    System system = create_empty_system();
    process_op_code(&system, 0x1434);
    ck_assert_int_eq(system.program_counter, 0x434);
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
    system.v_registers[1] = 0x33;
    process_op_code(&system, 0x3133);
    ck_assert_int_eq(system.program_counter, 0x20C);
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
    ck_assert_int_eq(system.program_counter, 0x20A);
    system.v_registers[0] = 0x33;
    process_op_code(&system, 0x4133);
    ck_assert_int_eq(system.program_counter, 0x20E);
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

START_TEST(test_load_register_in_register) // 8XY0
{
    System system = create_empty_system();
    system.v_registers[2] = 0x33;
    process_op_code(&system, 0x8120);
    ck_assert_int_eq(system.v_registers[1], 0x33);
    ck_assert_int_eq(system.program_counter, 0x202);
}
END_TEST

START_TEST(test_bitwise_or_registers) // 8XY1
{
    System system = create_empty_system();
    system.v_registers[0] = 0x01;
    system.v_registers[1] = 0x10;
    process_op_code(&system, 0x8011);
    ck_assert_int_eq(system.v_registers[0], 0x11);
    ck_assert_int_eq(system.program_counter, 0x202);
}
END_TEST

START_TEST(test_bitwise_and_registers) // 8XY2
{
    System system = create_empty_system();
    system.v_registers[0] = 0x01;
    system.v_registers[1] = 0x10;
    process_op_code(&system, 0x8012);
    ck_assert_int_eq(system.v_registers[0], 0x00);
    ck_assert_int_eq(system.program_counter, 0x202);
}
END_TEST

START_TEST(test_bitwise_xor_registers) // 8XY3
{
    System system = create_empty_system();
    system.v_registers[0] = 0x11;
    system.v_registers[1] = 0x10;
    process_op_code(&system, 0x8013);
    ck_assert_int_eq(system.v_registers[0], 0x01);
    ck_assert_int_eq(system.program_counter, 0x202);
}
END_TEST

START_TEST(test_add_registers) // 8XY4
{
    System system = create_empty_system();
    system.v_registers[0] = 0x01;
    system.v_registers[1] = 0x0F;
    process_op_code(&system, 0x8014);
    ck_assert_int_eq(system.v_registers[0], 0x10);
    ck_assert_int_eq(system.program_counter, 0x202);
    ck_assert_int_eq(system.v_registers[NUM_V_REGISTERS-1], 0x00);

    system.v_registers[1] = 0xFF;
    process_op_code(&system, 0x8014);
    ck_assert_int_eq(system.v_registers[0], 0x0F);
    ck_assert_int_eq(system.program_counter, 0x204);
    ck_assert_int_eq(system.v_registers[NUM_V_REGISTERS-1], 0x01);
}
END_TEST

START_TEST(test_subtract_registers) // 8XY5
{
    System system = create_empty_system();
    system.v_registers[0] = 0x10;
    system.v_registers[1] = 0x0F;
    process_op_code(&system, 0x8015);
    ck_assert_int_eq(system.v_registers[0], 0x01);
    ck_assert_int_eq(system.program_counter, 0x202);
    ck_assert_int_eq(system.v_registers[NUM_V_REGISTERS-1], 0x01);

    process_op_code(&system, 0x8015);
    ck_assert_int_eq(system.v_registers[0], 0xF2);
    ck_assert_int_eq(system.program_counter, 0x204);
    ck_assert_int_eq(system.v_registers[NUM_V_REGISTERS-1], 0x00);
}
END_TEST

START_TEST(test_shift_register_right) // 8XY6
{
    System system = create_empty_system();
    system.v_registers[1] = 0x10;
    process_op_code(&system, 0x8106);
    ck_assert_int_eq(system.v_registers[1], 0x08);
    ck_assert_int_eq(system.program_counter, 0x202);
    ck_assert_int_eq(system.v_registers[NUM_V_REGISTERS-1], 0x00);

    system.v_registers[1] = 0x01;
    process_op_code(&system, 0x8106);
    ck_assert_int_eq(system.v_registers[0], 0x00);
    ck_assert_int_eq(system.program_counter, 0x204);
    ck_assert_int_eq(system.v_registers[NUM_V_REGISTERS-1], 0x01);
}
END_TEST

START_TEST(test_subtract_registers_reverse) // 8XY7
{
    System system = create_empty_system();
    system.v_registers[0] = 0x0F;
    system.v_registers[1] = 0x10;
    process_op_code(&system, 0x8017);
    ck_assert_int_eq(system.v_registers[0], 0x01);
    ck_assert_int_eq(system.program_counter, 0x202);
    ck_assert_int_eq(system.v_registers[NUM_V_REGISTERS-1], 0x01);

    system.v_registers[0] = 0x11;
    process_op_code(&system, 0x8017);
    ck_assert_int_eq(system.v_registers[0], 0x01);
    ck_assert_int_eq(system.program_counter, 0x204);
    ck_assert_int_eq(system.v_registers[NUM_V_REGISTERS-1], 0x00);
}
END_TEST

START_TEST(test_shift_register_left) // 8XYE
{
    System system = create_empty_system();
    system.v_registers[1] = 0x04;
    process_op_code(&system, 0x810E);
    ck_assert_int_eq(system.v_registers[1], 0x08);
    ck_assert_int_eq(system.program_counter, 0x202);
    ck_assert_int_eq(system.v_registers[NUM_V_REGISTERS-1], 0x00);

    system.v_registers[1] = 0xF0;
    process_op_code(&system, 0x810E);
    ck_assert_int_eq(system.v_registers[1], 0xE0);
    ck_assert_int_eq(system.program_counter, 0x204);
    ck_assert_int_eq(system.v_registers[NUM_V_REGISTERS-1], 0x01);
}
END_TEST

START_TEST(test_skip_if_registers_not_equal) // 9xy0
{
    System system = create_empty_system();
    system.v_registers[1] = 0x11;
    system.v_registers[3] = 0x33;
    process_op_code(&system, 0x9130);
    ck_assert_int_eq(system.program_counter, 0x204);
    system.v_registers[3] = 0x11;
    process_op_code(&system, 0x9130);
    ck_assert_int_eq(system.program_counter, 0x206);
}
END_TEST

START_TEST(test_set_index_reg) // ANNN
{
    System system = create_empty_system();
    process_op_code(&system, 0xA123);
    ck_assert_int_eq(system.index_register, 0x0123);
    ck_assert_int_eq(system.program_counter, 0x202);
}
END_TEST

START_TEST(test_jump_to_location_plus_register) // BNNN
{
    System system = create_empty_system();
    system.v_registers[0] = 0x29;
    process_op_code(&system, 0xB300);
    ck_assert_int_eq(system.program_counter, 0x300 + 0x29);
}
END_TEST

START_TEST(test_random_masked) // CXKK
{
    System system = create_empty_system();
    process_op_code(&system, 0xC30F);
    ck_assert_int_eq(system.v_registers[3] & 0xF0, 0x00);
    ck_assert_int_eq(system.program_counter, 0x202);
    process_op_code(&system, 0xC3F0);
    ck_assert_int_eq(system.v_registers[3] & 0x0F, 0x00);
    ck_assert_int_eq(system.program_counter, 0x204);
}
END_TEST

START_TEST(test_draw_sprite) // DXYN
{
    System system = create_empty_system();
    uint8_t sprite[5] = {0xF0, 0x90, 0x90, 0x90, 0xF0};
    memcpy(&system.main_memory[30], sprite, sizeof(sprite));
    system.v_registers[0] = 6;
    system.v_registers[1] = 5;
    system.index_register = 30;

    process_op_code(&system, 0xD015);
    for (unsigned int byte_num = 0; byte_num < 5; byte_num++)
    {
        uint8_t byte = sprite[byte_num];
        for (unsigned int bit_num = 0; bit_num < 8; bit_num++)
        {
            unsigned int video_index = (5 + byte_num) * VIDEO_WIDTH + 6 + bit_num;
            if ((byte & (0x80 >> bit_num)) == 0)
                ck_assert_int_eq(system.video_memory[video_index], 0);
            else
                ck_assert_int_eq(system.video_memory[video_index], 1);
        }
    }
}
END_TEST

START_TEST(test_skip_if_key_pressed) // EX9E
{
    System system = create_empty_system();
    system.v_registers[3] = 0x0A;
    process_op_code(&system, 0xE39E);
    ck_assert_int_eq(system.program_counter, 0x202);
    system.key_states[0xA] = 0x01;
    process_op_code(&system, 0xE39E);
    ck_assert_int_eq(system.program_counter, 0x206);
}
END_TEST

START_TEST(test_skip_if_key_not_pressed) // EXA1
{
    System system = create_empty_system();
    system.v_registers[3] = 0x0A;
    process_op_code(&system, 0xE3A1);
    ck_assert_int_eq(system.program_counter, 0x204);
    system.key_states[0xA] = 0x01;
    process_op_code(&system, 0xE3A1);
    ck_assert_int_eq(system.program_counter, 0x206);
}
END_TEST

START_TEST(test_get_delay_timer_value) // FX07
{
    System system = create_empty_system();
    system.delay_timer = 0x42;
    process_op_code(&system, 0xF407);
    ck_assert_int_eq(system.delay_timer, system.v_registers[4]);
    ck_assert_int_eq(system.program_counter, 0x202);
}
END_TEST

START_TEST(test_wait_for_key_press) // FX0A
{
    System system = create_empty_system();
    process_op_code(&system, 0xF50A);
    ck_assert_int_eq(system.program_counter, 0x200);
    system.key_states[5] = 0x01;
    process_op_code(&system, 0xF50A);
    ck_assert_int_eq(system.program_counter, 0x202);
}
END_TEST

START_TEST(test_set_delay_timer) // FX15
{
    System system = create_empty_system();
    system.v_registers[3] = 0x31;
    process_op_code(&system, 0xF315);
    ck_assert_int_eq(system.delay_timer, system.v_registers[3]);
    ck_assert_int_eq(system.program_counter, 0x202);
}
END_TEST

START_TEST(test_set_sound_timer) // FX18
{
    System system = create_empty_system();
    system.v_registers[3] = 0x31;
    process_op_code(&system, 0xF318);
    ck_assert_int_eq(system.sound_timer, system.v_registers[3]);
    ck_assert_int_eq(system.program_counter, 0x202);
}
END_TEST

START_TEST(test_add_to_index) // FX1E
{
    System system = create_empty_system();
    system.index_register = 0x05;
    system.v_registers[7] = 0xF1;
    process_op_code(&system, 0xF71E);
    ck_assert_int_eq(system.index_register, 0x05 + 0xF1);
    ck_assert_int_eq(system.program_counter, 0x202);
}
END_TEST

START_TEST(test_set_index_to_digit_sprite) // FX29
{
    System system = create_empty_system();
    for (uint8_t digit = 0; digit < 10; digit++)
    {
        system.v_registers[0] = digit;
        process_op_code(&system, 0xF029);
        ck_assert_int_eq(system.index_register,  0x05 * digit);
        ck_assert_int_eq(system.program_counter, 0x202 + 0x002 * digit);
    }
}
END_TEST

START_TEST(test_store_bcd_representation) // FX33
{
    System system = create_empty_system();
    system.index_register = 0x0300;
    system.v_registers[1] = 145;
    process_op_code(&system, 0xF133);
    ck_assert_int_eq(system.main_memory[0x0300], 1);
    ck_assert_int_eq(system.main_memory[0x0301], 4);
    ck_assert_int_eq(system.main_memory[0x0302], 5);
    ck_assert_int_eq(system.program_counter, 0x202);
}
END_TEST

START_TEST(test_store_registers) // FX55
{
    System system = create_empty_system();
    system.index_register = 0x300;
    for (int index = 0; index <= 5; index++)
        system.v_registers[index] = index;
    for (int index = 6; index < NUM_V_REGISTERS; index++)
        system.v_registers[index] = 0;

    process_op_code(&system, 0xF555);
    for (int index = 0; index <= 5; index++)
        ck_assert_int_eq(system.main_memory[0x300 + index], index);
    for (int index = 6; index < NUM_V_REGISTERS; index++)
        ck_assert_int_eq(system.main_memory[0x300 + index], 0);

    ck_assert_int_eq(system.program_counter, 0x202);
}
END_TEST

START_TEST(test_load_registers) // FX65
{
    System system = create_empty_system();
    system.index_register = 0x300;
    for (int index = 0; index <= 5; index++)
        system.main_memory[0x300 + index] = index;
    for (int index = 6; index < NUM_V_REGISTERS; index++)
        system.main_memory[0x300 + index] = 0;

    process_op_code(&system, 0xF565);
    for (int index = 0; index <= 5; index++)
        ck_assert_int_eq(system.v_registers[index], index);
    for (int index = 6; index < NUM_V_REGISTERS; index++)
        ck_assert_int_eq(system.v_registers[index], 0);

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
    ck_assert(system.audio_triggered == false);
}
END_TEST

Suite * make_emulator_suite()
{
    Suite *suite = suite_create("Emulator Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_step_timers);
    suite_add_tcase(suite, test_case);

    TCase * op_code_test_case = tcase_create("Op Code Test Cases");
    tcase_add_test(op_code_test_case, test_clear_display);
    tcase_add_test(op_code_test_case, test_return_from_subroutine);
    tcase_add_test(op_code_test_case, test_jump_to_location);
    tcase_add_test(op_code_test_case, test_call_subroutine);
    tcase_add_test(op_code_test_case, test_skip_if_register_equal);
    tcase_add_test(op_code_test_case, test_skip_if_register_not_equal);
    tcase_add_test(op_code_test_case, test_skip_if_registers_equal);
    tcase_add_test(op_code_test_case, test_set_register_to_value);
    tcase_add_test(op_code_test_case, test_add_value_to_register);
    tcase_add_test(op_code_test_case, test_load_register_in_register);
    tcase_add_test(op_code_test_case, test_bitwise_or_registers);
    tcase_add_test(op_code_test_case, test_bitwise_and_registers);
    tcase_add_test(op_code_test_case, test_bitwise_xor_registers);
    tcase_add_test(op_code_test_case, test_add_registers);
    tcase_add_test(op_code_test_case, test_subtract_registers);
    tcase_add_test(op_code_test_case, test_shift_register_right);
    tcase_add_test(op_code_test_case, test_subtract_registers_reverse);
    tcase_add_test(op_code_test_case, test_shift_register_left);
    tcase_add_test(op_code_test_case, test_skip_if_register_not_equal);
    tcase_add_test(op_code_test_case, test_set_index_reg);
    tcase_add_test(op_code_test_case, test_jump_to_location_plus_register);
    tcase_add_test(op_code_test_case, test_random_masked);
    tcase_add_test(op_code_test_case, test_draw_sprite);
    tcase_add_test(op_code_test_case, test_skip_if_key_pressed);
    tcase_add_test(op_code_test_case, test_skip_if_key_not_pressed);
    tcase_add_test(op_code_test_case, test_get_delay_timer_value);
    tcase_add_test(op_code_test_case, test_wait_for_key_press);
    tcase_add_test(op_code_test_case, test_set_delay_timer);
    tcase_add_test(op_code_test_case, test_set_sound_timer);
    tcase_add_test(op_code_test_case, test_add_to_index);
    tcase_add_test(op_code_test_case, test_set_index_to_digit_sprite);
    tcase_add_test(op_code_test_case, test_store_bcd_representation);
    tcase_add_test(op_code_test_case, test_store_registers);
    tcase_add_test(op_code_test_case, test_load_registers);
    suite_add_tcase(suite, op_code_test_case);

    return suite;
}