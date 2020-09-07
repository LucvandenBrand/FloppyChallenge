#include <check.h>
#include <rule.h>

START_TEST(test_alloc_empty_rule)
{
    Rule rule = alloc_empty_rule();
    ck_assert(rule.antecedent == '\0');
    ck_assert_int_eq(rule.consequent.length, 0);
    ck_assert_int_eq(rule.consequent.space, 2);
    free_rule(&rule);
}
END_TEST

START_TEST(test_alloc_rule)
{
    Rule rule = alloc_rule('A', "AB");
    ck_assert(rule.antecedent == 'A');
    ck_assert_int_eq(rule.consequent.length, 2);
    ck_assert(rule.consequent.symbols[0] == 'A');
    ck_assert(rule.consequent.symbols[1] == 'B');
    free_rule(&rule);
    ck_assert(rule.antecedent == '\0');
    ck_assert_int_eq(rule.consequent.length, 0);
}
END_TEST

START_TEST(test_alloc_rule_list)
{
    RuleList list = alloc_empty_rule_list();
    ck_assert_ptr_ne(list.rules, NULL);
    ck_assert_int_eq(list.length, 0);
    ck_assert_int_eq(list.space, 2);
    free_rule_list(&list);
    ck_assert_ptr_eq(list.rules, NULL);
    ck_assert_int_eq(list.length, 0);
    ck_assert_int_eq(list.space, 0);
}
END_TEST

START_TEST(test_add_rule_to_list)
{
    RuleList list = alloc_empty_rule_list();

    Rule rule = alloc_rule('A', "AB");
    add_rule_to_list(rule, &list);
    ck_assert_int_eq(list.length, 1);
    ck_assert_int_eq(list.space, 2);

    Rule next_rule = alloc_rule('B', "A");
    add_rule_to_list(next_rule, &list);
    ck_assert_int_eq(list.length, 2);
    ck_assert_int_eq(list.space, 4);

    free_rule_list(&list);
}
END_TEST

START_TEST(test_search_matching_rule_index)
{
    RuleList list = alloc_empty_rule_list();

    Rule rule = alloc_rule('A', "AB");
    add_rule_to_list(rule, &list);
    Rule next_rule = alloc_rule('B', "A");
    add_rule_to_list(next_rule, &list);

    int a_index = search_matching_rule_index(list, 'A');
    ck_assert_int_eq(a_index, 0);

    int b_index = search_matching_rule_index(list, 'B');
    ck_assert_int_eq(b_index, 1);

    int c_index = search_matching_rule_index(list, 'C');
    ck_assert_int_eq(c_index, -1);

    free_rule_list(&list);
}
END_TEST

Suite * make_rule_suite()
{
    Suite * suite = suite_create("Rule Test Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_alloc_empty_rule);
    tcase_add_test(test_case, test_alloc_rule);
    tcase_add_test(test_case, test_alloc_rule_list);
    tcase_add_test(test_case, test_add_rule_to_list);
    tcase_add_test(test_case, test_search_matching_rule_index);
    suite_add_tcase(suite, test_case);

    return suite;
}