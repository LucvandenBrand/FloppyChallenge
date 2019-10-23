#include <check.h>
#include <game/parsing/parser.h>

START_TEST(test_empty_text_to_tokens)
{
    TokenList token_list = text_to_tokens("");
    ck_assert_ptr_eq(token_list.tokens, NULL);
    ck_assert_int_eq(token_list.length, 0);
    free_tokens(&token_list);
}
END_TEST

Suite * makeParserSuite()
{
    Suite *suite = suite_create("Parser Test Suite");

    TCase * test_case = tcase_create("Parser");
    tcase_add_test(test_case, test_empty_text_to_tokens);
    suite_add_tcase(suite, test_case);

    return suite;
}