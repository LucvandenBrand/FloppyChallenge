#include <check.h>
#include <symbol.h>

START_TEST(test_alloc_symbol_list)
{
    SymbolList list = alloc_empty_symbol_list();
    ck_assert_ptr_ne(list.symbols, NULL);
    ck_assert_int_eq(list.length, 0);
    ck_assert_int_eq(list.space, 2);
    free_symbol_list(&list);
    ck_assert_ptr_eq(list.symbols, NULL);
    ck_assert_int_eq(list.length, 0);
    ck_assert_int_eq(list.space, 0);
}
END_TEST

START_TEST(test_add_symbol_to_list)
{
    SymbolList list = alloc_empty_symbol_list();

    Symbol symbol = 'A';
    add_symbol_to_list(symbol, &list);
    ck_assert(list.symbols[0] == 'A');
    ck_assert_int_eq(list.length, 1);
    ck_assert_int_eq(list.space, 2);

    Symbol next_symbol = 'B';
    add_symbol_to_list(next_symbol, &list);
    ck_assert(list.symbols[1] == 'B');
    ck_assert_int_eq(list.length, 2);
    ck_assert_int_eq(list.space, 4);

    free_symbol_list(&list);
}
END_TEST

START_TEST(test_add_symbols_to_list)
{
    SymbolList list = alloc_empty_symbol_list();
    add_symbol_to_list('A', &list);
    add_symbol_to_list('B', &list);
    ck_assert_int_eq(list.length, 2);
    ck_assert_int_eq(list.space, 4);

    SymbolList add_list = alloc_empty_symbol_list();
    add_symbol_to_list('C', &add_list);
    add_symbol_to_list('D', &add_list);
    add_symbol_to_list('E', &add_list);
    add_symbols_to_list(add_list, &list);
    ck_assert(list.symbols[0] == 'A');
    ck_assert(list.symbols[1] == 'B');
    ck_assert(list.symbols[2] == 'C');
    ck_assert(list.symbols[3] == 'D');
    ck_assert(list.symbols[4] == 'E');
    ck_assert_int_eq(list.length, 5);
    ck_assert_int_eq(list.space, 8);

    free_symbol_list(&add_list);
    free_symbol_list(&list);
}
END_TEST

Suite * make_symbol_suite()
{
    Suite *suite = suite_create("Symbol Test Suite");

    TCase * test_case = tcase_create("Test Cases");
    tcase_add_test(test_case, test_alloc_symbol_list);
    tcase_add_test(test_case, test_add_symbol_to_list);
    tcase_add_test(test_case, test_add_symbols_to_list);
    suite_add_tcase(suite, test_case);

    return suite;
}