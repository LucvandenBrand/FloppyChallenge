#include <check.h>
#include <emulator/system.h>
#include <emulator/emulator.h>

START_TEST(test_op_code_set_index_reg)
{
    BinaryBlob empty_rom = malloc_binary_blob(0);
    System system = init_system(&empty_rom);
    free_binary_blob(&empty_rom);

    ck_assert_int_eq(system.program_counter, 0x200);
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

Suite * make_emulator_suite()
{
    Suite *suite = suite_create("Emulator Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_step_timers);
    suite_add_tcase(suite, test_case);

    TCase * op_code_test_case = tcase_create("Op Code Test Cases");
    tcase_add_test(op_code_test_case, test_op_code_set_index_reg);
    suite_add_tcase(suite, op_code_test_case);

    return suite;
}