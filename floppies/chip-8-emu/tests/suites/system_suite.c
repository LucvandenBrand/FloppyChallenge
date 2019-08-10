#include <check.h>
#include <emulator/system.h>
#include <io/file_system.h>
#include <limits.h>

START_TEST(test_init_system)
{
    char rom_file_path[PATH_MAX];
    get_full_path("TETRIS", rom_file_path);
    int num_bytes = get_file_size(rom_file_path);
    BinaryBlob rom = malloc_binary_blob(num_bytes);
    read_binary_file(rom_file_path, &rom);
    System system = init_system(&rom);
    free_binary_blob(&rom);

    ck_assert(system.is_running == true);
    ck_assert(system.video_changed == true);
    ck_assert(system.audio_triggered == false);
    ck_assert_int_eq(system.index_register, 0);
    ck_assert_int_eq(system.program_counter, ADDRESS_ROM);
    ck_assert_int_eq(system.stack_pointer, 0);
    ck_assert_int_eq(system.delay_timer, 0);
    ck_assert_int_eq(system.sound_timer, 0);

    for (int index = ADDRESS_ROM; index < rom.num_bytes; ++index)
        ck_assert_int_eq(system.main_memory[index], rom.data[index-ADDRESS_ROM]);

    for (int index = 0; index < VIDEO_MEMORY_SIZE; ++index)
        ck_assert_int_eq(system.video_memory[index], 0);

    for (int index = 0; index < NUM_V_REGISTERS; ++index)
        ck_assert_int_eq(system.v_registers[index], 0);

    for (int index = 0; index < STACK_SIZE; ++index)
        ck_assert_int_eq(system.stack[index], 0);

    for (int index = 0; index < NUM_KEYS; ++index)
        ck_assert_int_eq(system.key_states[index], 0);
}
END_TEST

Suite * make_system_suite()
{
    Suite *suite = suite_create("System Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_init_system);
    suite_add_tcase(suite, test_case);

    return suite;
}