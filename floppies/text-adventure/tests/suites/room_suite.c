#include <check.h>
#include <game/room.h>
#include <stdlib.h>

Door create_test_door()
{
    char * item_name = malloc(7 * sizeof(char));
    strcpy(item_name, "A door\0");
    return init_door(item_name, NORTH, 1, 2, false);
}

Room create_test_room()
{
    char * room_description = malloc(8 * sizeof(char));
    strcpy(room_description, "A room.\0");
    return init_room(room_description);
}

START_TEST(test_init_room)
{
    Room room = create_test_room();
    for (Direction dir=0; dir < NUM_DIRECTIONS; dir++)
        ck_assert(!room_has_door_in_direction(room, dir));
    ck_assert_str_eq(room.description, "A room.");
    ck_assert_ptr_ne(room.item_id_list.ids, NULL);
    ck_assert_int_eq(room.item_id_list.num_ids, 0);
    ck_assert_ptr_ne(room.entity_id_list.ids, NULL);
    ck_assert_int_eq(room.entity_id_list.num_ids, 0);
    free_room(&room);
}
END_TEST

START_TEST(test_free_room)
{
    Room room = create_test_room();
    free_room(&room);
    for (Direction dir=0; dir < NUM_DIRECTIONS; dir++)
        ck_assert(!room_has_door_in_direction(room, dir));
    ck_assert_ptr_eq(room.description, NULL);
    ck_assert_ptr_eq(room.item_id_list.ids, NULL);
    ck_assert_int_eq(room.item_id_list.num_ids, 0);
    ck_assert_int_eq(room.item_id_list.list_size, 0);
    ck_assert_ptr_eq(room.entity_id_list.ids, NULL);
    ck_assert_int_eq(room.entity_id_list.num_ids, 0);
    ck_assert_int_eq(room.entity_id_list.list_size, 0);
}
END_TEST

START_TEST(test_add_item_to_room)
{
    Room room = create_test_room();
    ck_assert_int_eq(room.item_id_list.num_ids, 0);
    add_item_to_room(&room, 42);
    ck_assert_int_eq(room.item_id_list.num_ids, 1);
    ck_assert_int_eq(room.item_id_list.ids[0], 42);
    for (int i=0; i<10; i++)
    {
        add_item_to_room(&room, i);
        ck_assert_int_eq(room.item_id_list.num_ids, i+2);
    }
    ck_assert_int_eq(room.item_id_list.list_size,16);
    free_room(&room);
}
END_TEST

START_TEST(test_remove_item_from_room)
{
    Room room = create_test_room();
    for (int i=0; i<10; i++)
        add_item_to_room(&room, i);

    ck_assert_int_eq(room.item_id_list.num_ids, 10);
    remove_item_from_room(&room, 42);
    ck_assert_int_eq(room.item_id_list.num_ids, 10);

    for (int i=0; i<10; i++)
    {
        remove_item_from_room(&room, i);
        ck_assert_int_eq(room.item_id_list.num_ids, 9-i);
    }
    ck_assert_int_eq(room.item_id_list.list_size, 16);
    remove_item_from_room(&room, 42);
    ck_assert_int_eq(room.item_id_list.num_ids, 0);
    free_room(&room);
}
END_TEST

START_TEST(test_add_door_to_room)
{
    Room room = create_test_room();
    Door door = create_test_door();
    add_door_to_room(&room, door);
    ck_assert(room_has_door_in_direction(room, NORTH));
    ID door_id = get_room_door_id_with_direction(room, NORTH);
    ck_assert_str_eq(room.doors.doors[door_id].name, door.name);
    ck_assert_int_eq(room.doors.doors[door_id].roomId, door.roomId);
    ck_assert_int_eq(room.doors.doors[door_id].keyId, door.keyId);
    free_room(&room);
}
END_TEST

START_TEST(test_room_has_door_in_direction)
{
    Room room = create_test_room();
    for (Direction dir=0; dir < NUM_DIRECTIONS; dir++)
    {
        ck_assert(!room_has_door_in_direction(room, dir));
        Door door = create_test_door();
        door.direction = dir;
        add_door_to_room(&room, door);
        ck_assert(room_has_door_in_direction(room, dir));
    }
    free_room(&room);
}
END_TEST

START_TEST(test_room_has_door_with_name)
{
    Room room = create_test_room();
    Door door = create_test_door();
    add_door_to_room(&room, door);
    ck_assert(room_has_door_with_name(room, "A door"));
    free_room(&room);
}
END_TEST

START_TEST(test_add_entity_to_room)
{
    Room room = create_test_room();
    ck_assert_int_eq(room.entity_id_list.num_ids, 0);
    add_entity_to_room(&room, 42);
    ck_assert_int_eq(room.entity_id_list.num_ids, 1);
    ck_assert_int_eq(room.entity_id_list.ids[0], 42);
    for (int i=0; i<10; i++)
    {
        add_entity_to_room(&room, i);
        ck_assert_int_eq(room.entity_id_list.num_ids, i+2);
    }
    ck_assert_int_eq(room.entity_id_list.list_size,16);
    free_room(&room);
}
END_TEST


Suite * makeRoomSuite()
{
    Suite *suite = suite_create("Room Test Suite");

    TCase * test_case = tcase_create("Room");
    tcase_add_test(test_case, test_init_room);
    tcase_add_test(test_case, test_free_room);
    tcase_add_test(test_case, test_add_item_to_room);
    tcase_add_test(test_case, test_remove_item_from_room);
    tcase_add_test(test_case, test_add_door_to_room);
    tcase_add_test(test_case, test_room_has_door_in_direction);
    tcase_add_test(test_case, test_room_has_door_with_name);
    suite_add_tcase(suite, test_case);

    return suite;
}