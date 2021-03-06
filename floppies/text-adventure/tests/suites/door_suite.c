#include <check.h>
#include <game/door.h>
#include <stdlib.h>

START_TEST(test_init_door)
{
    char * item_name = malloc(7 * sizeof(char));
    strcpy(item_name, "A door\0");
    Door door = init_door(item_name, EAST, 1, 2, true);
    ck_assert_str_eq(door.name, "A door");
    ck_assert_int_eq(door.direction, EAST);
    ck_assert_int_eq(door.roomId, 1);
    ck_assert_int_eq(door.keyId, 2);
    ck_assert(door.is_locked);
    free_door(&door);
}
END_TEST

START_TEST(test_free_door)
{
    char * item_name = malloc(7 * sizeof(char));
    strcpy(item_name, "A door\0");
    Door door = init_door(item_name, NORTH, 1, 2, true);
    free_door(&door);
    ck_assert_ptr_eq(door.name, NULL);
    ck_assert_int_eq(door.direction, NORTH);
    ck_assert_int_eq(door.roomId, ID_EMPTY);
    ck_assert_int_eq(door.keyId, ID_EMPTY);
    ck_assert(!door.is_locked);
}
END_TEST

START_TEST(test_exit_door)
{
    char * item_name = malloc(7 * sizeof(char));
    strcpy(item_name, "A door\0");
    Door door = init_door(item_name, NORTH, ROOM_ID_EXIT, 2, false);
    ck_assert(is_exit_door(door));
    door.roomId = ID_EMPTY;
    ck_assert(!is_exit_door(door));
    free_door(&door);
}
END_TEST

START_TEST(test_is_door_locked)
{
    char * item_name = malloc(7 * sizeof(char));
    strcpy(item_name, "A door\0");
    Door door = init_door(item_name, NORTH, 1, 2, true);
    ck_assert(is_door_locked(door));
    free_door(&door);
}
END_TEST

START_TEST(test_is_door_unlocked)
{
    char * item_name = malloc(7 * sizeof(char));
    strcpy(item_name, "A door\0");
    Door door = init_door(item_name, NORTH, 1, 2, false);
    ck_assert(!is_door_locked(door));
    free_door(&door);
}
END_TEST

START_TEST(test_try_lock_door)
{
    char * item_name = malloc(7 * sizeof(char));
    strcpy(item_name, "A door\0");
    Door door = init_door(item_name, NORTH, 1, 2, false);
    ck_assert(!try_lock_door(&door, 1));
    ck_assert(!door.is_locked);
    ck_assert(try_lock_door(&door, 2));
    ck_assert(door.is_locked);
    free_door(&door);
}
END_TEST

START_TEST(test_try_unlock_door)
{
    char * item_name = malloc(7 * sizeof(char));
    strcpy(item_name, "A door\0");
    Door door = init_door(item_name, NORTH, 1, 2, true);
    ck_assert(!try_unlock_door(&door, 1));
    ck_assert(door.is_locked);
    ck_assert(try_unlock_door(&door, 2));
    ck_assert(!door.is_locked);
    free_door(&door);
}
END_TEST

Suite * makeDoorSuite()
{
    Suite *suite = suite_create("Door Test Suite");

    TCase * test_case = tcase_create("Door");
    tcase_add_test(test_case, test_init_door);
    tcase_add_test(test_case, test_free_door);
    tcase_add_test(test_case, test_exit_door);
    tcase_add_test(test_case, test_is_door_locked);
    tcase_add_test(test_case, test_is_door_unlocked);
    tcase_add_test(test_case, test_try_lock_door);
    tcase_add_test(test_case, test_try_unlock_door);
    suite_add_tcase(suite, test_case);

    return suite;
}