#include <check.h>
#include <memory/safe_memory.h>
#include <stdlib.h>

START_TEST(test_safe_malloc)
{
    int * memory = safe_malloc(12);
    ck_assert_ptr_ne(memory, NULL);
    free(memory);
}
END_TEST

START_TEST(test_safe_empty_malloc)
{
    int * memory = safe_malloc(0);
    ck_assert_ptr_eq(memory, NULL);
}
END_TEST

START_TEST(test_safe_realloc)
{
    int * memory = safe_malloc(12);
    int * new_memory = safe_realloc(memory, 4);
    ck_assert_ptr_ne(new_memory, NULL);
    free(new_memory);
}
END_TEST

START_TEST(test_safe_empty_realloc)
{
    int * memory = safe_malloc(12);
    int * new_memory = safe_realloc(memory, 0);
    ck_assert_ptr_eq(new_memory, NULL);
}
END_TEST

Suite * makeMemorySuite()
{
    Suite *suite = suite_create("Memory Test Suite");

    TCase * test_case = tcase_create("Memory");
    tcase_add_test(test_case, test_safe_malloc);
    tcase_add_test(test_case, test_safe_empty_malloc);
    tcase_add_test(test_case, test_safe_realloc);
    tcase_add_test(test_case, test_safe_empty_realloc);
    suite_add_tcase(suite, test_case);

    return suite;
}