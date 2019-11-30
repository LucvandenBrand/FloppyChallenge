#include <check.h>
#include <game/entity.h>
#include <stdlib.h>

Entity create_test_entity()
{
    char * name = malloc(7 * sizeof(char));
    strcpy(name, "Entity\0");
    char * description = malloc(10 * sizeof(char));
    strcpy(description, "An entity\0");
    char * attack = malloc(10 * sizeof(char));
    strcpy(attack, "An attack\0");
    char * die = malloc(8 * sizeof(char));
    strcpy(die, "It dies!\0");
    return init_entity(name, description, attack, die, 2, 0, 1);
}

START_TEST(test_init_entity)
{
    Entity entity = create_test_entity();
    ck_assert_str_eq(entity.name, "Entity");
    ck_assert_str_eq(entity.description, "An entity");
    ck_assert_str_eq(entity.attack, "An attack");
    ck_assert_str_eq(entity.die, "It dies!");
    ck_assert_int_eq(entity.kill_count, 2);
    ck_assert_int_eq(entity.start_kill_count, 2);
    ck_assert_int_eq(entity.holding_item, 0);
    ck_assert_int_eq(entity.vulnerability,1);
    free_entity(&entity);
}
END_TEST

START_TEST(test_free_entity)
{
    Entity entity = create_test_entity();
    free_entity(&entity);
    ck_assert_ptr_eq(entity.name, NULL);
    ck_assert_ptr_eq(entity.description, NULL);
    ck_assert_ptr_eq(entity.attack, NULL);
    ck_assert_ptr_eq(entity.die, NULL);
    ck_assert_int_eq(entity.kill_count, -1);
    ck_assert_int_eq(entity.start_kill_count, -1);
    ck_assert_int_eq(entity.holding_item, ID_NO_ITEM);
    ck_assert_int_eq(entity.vulnerability,ID_NO_ITEM);
}
END_TEST

Suite * makeEntitySuite()
{
    Suite *suite = suite_create("Entity Test Suite");

    TCase * test_case = tcase_create("Entity");
    tcase_add_test(test_case, test_init_entity);
    tcase_add_test(test_case, test_free_entity);
    suite_add_tcase(suite, test_case);

    return suite;
}