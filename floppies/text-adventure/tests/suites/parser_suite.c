#include <check.h>
#include <game/parsing/parser.h>

START_TEST(test_empty_text_to_tokens)
{
    GameState game = init_game_state(GAME_DATA_PATH);
    TokenList token_list = text_to_tokens("", game);
    ck_assert_ptr_ne(token_list.tokens, NULL);
    ck_assert_int_eq(token_list.length, 0);
    free_tokens(&token_list);
    free_game_state(&game);
}
END_TEST

START_TEST(test_look_at_to_tokens)
    {
        GameState game = init_game_state(GAME_DATA_PATH);
        TokenList token_list = text_to_tokens("look at Game Console", game);
        ck_assert_int_eq(token_list.tokens[0].type, LOOK);
        ck_assert_int_eq(token_list.tokens[1].type, AT);
        ck_assert_int_eq(token_list.tokens[2].type, ITEM);
        ck_assert_int_eq(token_list.tokens[2].value, 0);
        ck_assert_int_eq(token_list.length, 3);
        free_tokens(&token_list);
        free_game_state(&game);
    }
END_TEST


Suite * makeParserSuite()
{
    Suite *suite = suite_create("Parser Test Suite");

    TCase * test_case = tcase_create("Parser");
    tcase_add_test(test_case, test_empty_text_to_tokens);
    tcase_add_test(test_case, test_look_at_to_tokens);
    suite_add_tcase(suite, test_case);

    return suite;
}