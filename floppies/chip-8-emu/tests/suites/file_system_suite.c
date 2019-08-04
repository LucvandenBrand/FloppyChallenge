#include <check.h>
#include <file_system.h>

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

Suite * make_file_system_suite()
{
    Suite *suite = suite_create("FileSystem Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_get_file_size);
    tcase_add_test(test_case, test_get_missing_file_size);
    suite_add_tcase(suite, test_case);

    return suite;
}