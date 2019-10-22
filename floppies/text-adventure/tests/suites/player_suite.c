#include <check.h>
#include <game/player.h>
#include <stdlib.h>

START_TEST(test_init_player)
{
    Player player = init_player();
    ck_assert_int_eq(player.num_items, 0);
    ck_assert_int_eq(player.max_items, 4);
    ck_assert_ptr_ne(player.items, NULL);
    free_player(&player);
}
END_TEST

START_TEST(test_free_player)
{
    Player player = init_player();
    free_player(&player);
    ck_assert_int_eq(player.num_items, 0);
    ck_assert_int_eq(player.max_items, 0);
    ck_assert_ptr_eq(player.items, NULL);
}
END_TEST

START_TEST(test_add_item_to_player)
{
    Player player = init_player();
    for (int i=0; i<10; i++)
    {
        add_item_to_player(&player, i);
        ck_assert_int_eq(player.num_items, i+1);
        ck_assert_int_eq(player.items[i], i);
    }
    ck_assert_int_eq(player.max_items, 16);
    free_player(&player);
}
END_TEST

START_TEST(test_remove_item_from_player)
{
    Player player = init_player();
    for (int i=0; i<10; i++)
        add_item_to_player(&player, i);
    remove_item_from_player(&player, 42);
    ck_assert_int_eq(player.num_items, 10);
    for (int i=0; i<10; i++)
    {
        remove_item_from_player(&player, i);
        ck_assert_int_eq(player.num_items, 9-i);
    }
    ck_assert_int_eq(player.max_items, 16);
    remove_item_from_player(&player, 42);
    ck_assert_int_eq(player.num_items, 0);
    free_player(&player);
}
END_TEST

Suite * makePlayerSuite()
{
    Suite *suite = suite_create("Player Test Suite");

    TCase * test_case = tcase_create("Player");
    tcase_add_test(test_case, test_init_player);
    tcase_add_test(test_case, test_free_player);
    tcase_add_test(test_case, test_add_item_to_player);
    tcase_add_test(test_case, test_remove_item_from_player);
    suite_add_tcase(suite, test_case);

    return suite;
}