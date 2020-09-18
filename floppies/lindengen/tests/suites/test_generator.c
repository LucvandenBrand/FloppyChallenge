#include <check.h>
#include "generator/generator.h"

LSystem alloc_test_system()
{
    SymbolList symbol_list = alloc_empty_symbol_list();
    add_symbol_to_list('A', &symbol_list);
    add_symbol_to_list('B', &symbol_list);

    RuleList rule_list = alloc_empty_rule_list();
    Rule rule = alloc_rule('A', "AB");
    add_rule_to_list(rule, &rule_list);
    Rule next_rule = alloc_rule('B', "A");
    add_rule_to_list(next_rule, &rule_list);
    LSystem system = {symbol_list, rule_list};
    return system;
}

START_TEST(test_generate_system)
{
    LSystem system = alloc_test_system();
    generate_system(&system, 2);
    ck_assert_int_eq(system.axiom.length, 5);
    ck_assert(system.axiom.symbols[0] == 'A');
    ck_assert(system.axiom.symbols[1] == 'B');
    ck_assert(system.axiom.symbols[2] == 'A');
    ck_assert(system.axiom.symbols[3] == 'A');
    ck_assert(system.axiom.symbols[4] == 'B');
    free_system(&system);
}
END_TEST

START_TEST(test_rewrite_symbols)
{
    LSystem system = alloc_test_system();
    rewrite_symbols(&system);
    ck_assert_int_eq(system.axiom.length, 3);
    ck_assert(system.axiom.symbols[0] == 'A');
    ck_assert(system.axiom.symbols[1] == 'B');
    ck_assert(system.axiom.symbols[2] == 'A');
    free_system(&system);
}
END_TEST

Suite * make_generator_suite()
{
    Suite * suite = suite_create("Generator Test Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_generate_system);
    tcase_add_test(test_case, test_rewrite_symbols);
    suite_add_tcase(suite, test_case);

    return suite;
}