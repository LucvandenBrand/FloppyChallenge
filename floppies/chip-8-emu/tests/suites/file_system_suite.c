#include <check.h>
#include <io/file_system.h>

START_TEST(test_get_file_size)
{
    int num_bytes = get_file_size("TETRIS");
    ck_assert_int_eq(num_bytes, 494);
    num_bytes = get_file_size("SYZYGY");
    ck_assert_int_eq(num_bytes, 946);
    num_bytes = get_file_size("./INVADERS");
    ck_assert_int_eq(num_bytes, 1283);
}
END_TEST

START_TEST(test_get_missing_file_size)
{
    int num_bytes = get_file_size("foo");
    ck_assert_int_eq(num_bytes, -1);
}
END_TEST

START_TEST(test_read_binary_file)
{
    int num_bytes = get_file_size("TETRIS");
    BinaryBlob rom = malloc_binary_blob(num_bytes);
    read_binary_file("TETRIS", &rom);
    ck_assert_int_eq(rom.num_bytes, num_bytes);
    ck_assert_int_eq(rom.data[0], 0xA2);
    ck_assert_int_eq(rom.data[1], 0xB4);
    ck_assert_int_eq(rom.data[num_bytes-2], 0x37);
    ck_assert_int_eq(rom.data[num_bytes-1], 0x23);
}
END_TEST

START_TEST(test_file_path_exist)
{
    int present_file = file_path_exists("TETRIS");
    ck_assert_int_eq(present_file, 1);
    int non_present_file = file_path_exists("NO_TETRIS");
    ck_assert_int_eq(non_present_file, 0);
}
END_TEST

Suite * make_file_system_suite()
{
    Suite *suite = suite_create("FileSystem Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_get_file_size);
    tcase_add_test(test_case, test_get_missing_file_size);
    tcase_add_test(test_case, test_read_binary_file);
    tcase_add_test(test_case, test_file_path_exist);
    suite_add_tcase(suite, test_case);

    return suite;
}