#include <check.h>
#include <game/door_list.h>
#include <stdlib.h>

START_TEST(test_init_door_list)
{
    DoorList list = init_door_list();
    ck_assert_int_eq(list.num_doors, 0);
    ck_assert_int_eq(list.list_size, 4);
    ck_assert_ptr_ne(list.doors, NULL);
    free_door_list(&list);
}
END_TEST

START_TEST(test_free_door_list)
{
    DoorList list = init_door_list();
    free_door_list(&list);
    ck_assert_int_eq(list.num_doors, 0);
    ck_assert_int_eq(list.list_size, 0);
    ck_assert_ptr_eq(list.doors, NULL);
}
END_TEST

START_TEST(test_add_door)
{
    DoorList list = init_door_list();
    char * door_name = malloc(7 * sizeof(char));
    strcpy(door_name, "A door\0");
    Door door = init_door(door_name, NORTH, 1, 2, false);
    add_door(&list, door);
    ck_assert_int_eq(list.num_doors, 1);
    free_door_list(&list);
}
END_TEST

START_TEST(test_has_door_with_name)
{
    DoorList list = init_door_list();
    ck_assert(!has_door_with_name(list, "A door"));
    char * door_name = malloc(7 * sizeof(char));
    strcpy(door_name, "A door\0");
    Door door = init_door(door_name, NORTH, 1, 2, false);
    add_door(&list, door);
    ck_assert(has_door_with_name(list, "a door\0"));
    free_door_list(&list);
}
END_TEST

START_TEST(test_has_door_with_direction)
{
    DoorList list = init_door_list();
    ck_assert(!has_door_with_direction(list, EAST));
    char * door_name = malloc(7 * sizeof(char));
    strcpy(door_name, "A door\0");
    Door door = init_door(door_name, EAST, 1, 2, false);
    add_door(&list, door);
    ck_assert(has_door_with_direction(list, EAST));
    free_door_list(&list);
}
END_TEST

START_TEST(test_get_door_id_with_direction)
{
    DoorList list = init_door_list();
    ck_assert_int_eq(get_door_id_with_direction(list, EAST), ID_EMPTY);
    char * door_name = malloc(7 * sizeof(char));
    strcpy(door_name, "A door\0");
    Door door = init_door(door_name, EAST, 1, 2, false);
    add_door(&list, door);
    ck_assert_int_eq(get_door_id_with_direction(list, EAST), 0);
    free_door_list(&list);
}
END_TEST

START_TEST(test_get_door_id_with_name)
{
    DoorList list = init_door_list();
    ck_assert_int_eq(get_door_id_with_name(list, "A door"), ID_EMPTY);
    char * door_name = malloc(7 * sizeof(char));
    strcpy(door_name, "A door\0");
    Door door = init_door(door_name, EAST, 1, 2, false);
    add_door(&list, door);
    ck_assert_int_eq(get_door_id_with_name(list, "a door\0"), 0);
    free_door_list(&list);
}
END_TEST

Suite * makeDoorListSuite()
{
    Suite *suite = suite_create("Door List Test Suite");

    TCase * test_case = tcase_create("Door List");
    tcase_add_test(test_case, test_init_door_list);
    tcase_add_test(test_case, test_free_door_list);
    tcase_add_test(test_case, test_add_door);
    tcase_add_test(test_case, test_has_door_with_name);
    tcase_add_test(test_case, test_has_door_with_direction);
    tcase_add_test(test_case, test_get_door_id_with_name);
    tcase_add_test(test_case, test_get_door_id_with_direction);
    suite_add_tcase(suite, test_case);

    return suite;
}