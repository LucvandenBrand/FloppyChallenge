#include <check.h>
#include <game/item.h>
#include <stdlib.h>

START_TEST(test_init_item)
{
    Item item = init_item("Toy", "A toy.");
    ck_assert_str_eq(item.name, "Toy");
    ck_assert_str_eq(item.description, "A toy.");
}
END_TEST

START_TEST(test_free_item)
    {
        char * item_name = malloc(4 * sizeof(char));
        strcpy(item_name, "Toy\0");
        char * item_description = malloc(7 * sizeof(char));
        strcpy(item_description, "A toy.\0");
        Item item = init_item(item_name, item_description);
        ck_assert_str_eq(item.name, "Toy");
        ck_assert_str_eq(item.description, "A toy.");
        free_item(&item);
        ck_assert_ptr_eq(item.name, NULL);
        ck_assert_ptr_eq(item.description, NULL);
    }
END_TEST

Suite * makeItemSuite()
{
    Suite *suite = suite_create("Item Test Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_init_item);
    tcase_add_test(test_case, test_free_item);
    suite_add_tcase(suite, test_case);

    return suite;
}