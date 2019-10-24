#include <check.h>
#include <game/parsing/token.h>

START_TEST(test_match_token_none)
{
    GameState game = init_game_state(GAME_DATA_PATH);
    Token token = match_token("foo", game);
    ck_assert_int_eq(token.type, NONE);
    ck_assert_int_eq(token.value, -1);
    free_game_state(&game);
}
END_TEST

START_TEST(test_match_token_look)
{
    GameState game = init_game_state(GAME_DATA_PATH);
    Token token = match_token("look", game);
    ck_assert_int_eq(token.type, LOOK);
    ck_assert_int_eq(token.value, -1);
    free_game_state(&game);
}
END_TEST

START_TEST(test_match_token_at)
{
    GameState game = init_game_state(GAME_DATA_PATH);
    Token token = match_token("at", game);
    ck_assert_int_eq(token.type, AT);
    ck_assert_int_eq(token.value, -1);
    free_game_state(&game);
}
END_TEST

START_TEST(test_match_token_take)
{
    GameState game = init_game_state(GAME_DATA_PATH);
    Token token = match_token("take", game);
    ck_assert_int_eq(token.type, TAKE);
    ck_assert_int_eq(token.value, -1);
    free_game_state(&game);
}
END_TEST

START_TEST(test_match_token_place)
{
    GameState game = init_game_state(GAME_DATA_PATH);
    Token token = match_token("place", game);
    ck_assert_int_eq(token.type, PLACE);
    ck_assert_int_eq(token.value, -1);
    free_game_state(&game);
}
END_TEST

START_TEST(test_match_token_item)
{
    GameState game = init_game_state(GAME_DATA_PATH);
    Token token = match_token("missing_item", game);
    ck_assert_int_eq(token.type, NONE);
    ck_assert_int_eq(token.value, ID_NO_ITEM);
    free_game_state(&game);
}
END_TEST

START_TEST(test_match_token_walk)
{
    GameState game = init_game_state(GAME_DATA_PATH);
    Token token = match_token("walk", game);
    ck_assert_int_eq(token.type, WALK);
    ck_assert_int_eq(token.value, -1);
    free_game_state(&game);
}
END_TEST

START_TEST(test_match_token_direction)
{
    GameState game = init_game_state(GAME_DATA_PATH);
    Token token = match_token("north", game);
    ck_assert_int_eq(token.type, DIRECTION);
    ck_assert_int_eq(token.value, NORTH);
    token = match_token("east", game);
    ck_assert_int_eq(token.type, DIRECTION);
    ck_assert_int_eq(token.value, EAST);
    token = match_token("south", game);
    ck_assert_int_eq(token.type, DIRECTION);
    ck_assert_int_eq(token.value, SOUTH);
    token = match_token("west", game);
    ck_assert_int_eq(token.type, DIRECTION);
    ck_assert_int_eq(token.value, WEST);
    free_game_state(&game);
}
END_TEST

Suite * makeTokenSuite()
{
    Suite *suite = suite_create("Token Test Suite");

    TCase * test_case = tcase_create("Token");
    tcase_add_test(test_case, test_match_token_none);
    tcase_add_test(test_case, test_match_token_look);
    tcase_add_test(test_case, test_match_token_at);
    tcase_add_test(test_case, test_match_token_take);
    tcase_add_test(test_case, test_match_token_place);
    tcase_add_test(test_case, test_match_token_item);
    tcase_add_test(test_case, test_match_token_walk);
    tcase_add_test(test_case, test_match_token_direction);
    suite_add_tcase(suite, test_case);

    return suite;
}