#include <check.h>
#include "renderer/movemap.h"

START_TEST(test_alloc_empty_move_map)
{
    MoveMap map = alloc_empty_move_map();
    for (size_t index = 0; index < 3; index++)
        ck_assert_ptr_ne(map.directions[index].symbols, NULL);
    ck_assert(map.rotation_angle == 0);
    map.rotation_angle = 60;
    free_move_map(&map);
    for (size_t index = 0; index < 3; index++)
        ck_assert_ptr_eq(map.directions[index].symbols, NULL);
    ck_assert(map.rotation_angle == 0);
}
END_TEST

START_TEST(test_set_symbol_direction)
{
    MoveMap map = alloc_empty_move_map();
    set_symbol_direction('Q', MOVE, &map);
    set_symbol_direction('A', MOVE, &map);
    ck_assert(map.directions[MOVE].symbols[0] == 'Q');
    ck_assert(map.directions[MOVE].symbols[1] == 'A');
    free_move_map(&map);
}
END_TEST

START_TEST(test_get_symbol_direction)
{
    MoveMap map = alloc_empty_move_map();
    set_symbol_direction('Q', MOVE, &map);
    set_symbol_direction('A', MOVE, &map);
    set_symbol_direction('B', ROTATE_RIGHT, &map);
    ck_assert(get_symbol_direction('Q', map) == MOVE);
    ck_assert(get_symbol_direction('A', map) == MOVE);
    ck_assert(get_symbol_direction('B', map) == ROTATE_RIGHT);
    ck_assert(get_symbol_direction('X', map) == NONE);
    free_move_map(&map);
}
END_TEST

Suite * make_move_map_suite()
{
    Suite * suite = suite_create("MoveMap Test Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_alloc_empty_move_map);
    tcase_add_test(test_case, test_set_symbol_direction);
    tcase_add_test(test_case, test_get_symbol_direction);

    suite_add_tcase(suite, test_case);

    return suite;
}