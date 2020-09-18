#include <check.h>
#define JSMN_HEADER
#include "io/loader.h"

START_TEST(test_load_system_from_json_string)
{
    const char * test_json =
            "{\n"
            "  \"axiom\": \"A\",\n"
            "  \"rules\":\n"
            "  [\n"
            "    {\n"
            "      \"antecedent\": \"A\",\n"
            "      \"consequent\": \"AB\"\n"
            "    },\n"
            "    {\n"
            "      \"antecedent\": \"B\",\n"
            "      \"consequent\": \"A\"\n"
            "    }\n"
            "  ]\n"
            "}";

    LSystem system = alloc_empty_system();
    MoveMap move_map = alloc_empty_move_map();
    try_load_system_from_json_string(&system, &move_map, test_json);

    ck_assert_int_eq(system.axiom.length, 1);
    ck_assert(system.axiom.symbols[0] == 'A');

    ck_assert_int_eq(system.rules.length, 2);
    ck_assert(system.rules.rules[0].antecedent == 'A');
    ck_assert_int_eq(system.rules.rules[0].consequent.length, 2);
    ck_assert(system.rules.rules[0].consequent.symbols[0] == 'A');
    ck_assert(system.rules.rules[0].consequent.symbols[1] == 'B');

    ck_assert(system.rules.rules[1].antecedent == 'B');
    ck_assert_int_eq(system.rules.rules[1].consequent.length, 1);
    ck_assert(system.rules.rules[1].consequent.symbols[0] == 'A');

    free_system(&system);
    free_move_map(&move_map);
}
END_TEST

Suite * make_loader_suite()
{
    Suite * suite = suite_create("Loader Test Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_load_system_from_json_string);
    suite_add_tcase(suite, test_case);

    return suite;
}