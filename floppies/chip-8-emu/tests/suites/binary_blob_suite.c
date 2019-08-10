#include <check.h>
#include <io/file_system.h>

START_TEST(test_malloc_free_blob)
{
    BinaryBlob blob = malloc_binary_blob(1240);
    ck_assert_int_eq(blob.num_bytes, 1240);
    ck_assert_ptr_ne(blob.data, NULL);
    free_binary_blob(&blob);
}
END_TEST

START_TEST(test_malloc_invalid_blob)
    {
        BinaryBlob blob = malloc_binary_blob(-1);
        ck_assert_int_eq(blob.num_bytes, -1);
        ck_assert_ptr_eq(blob.data, NULL);
    }
END_TEST

Suite * make_binary_blob_suite()
{
    Suite *suite = suite_create("BinaryBlob Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_malloc_free_blob);
    tcase_add_test(test_case, test_malloc_invalid_blob);
    suite_add_tcase(suite, test_case);

    return suite;
}