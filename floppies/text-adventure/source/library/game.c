#include <game.h>
#include <io/text_interface.h>
#include <string.h>

void game_loop()
{
    GameState game = init_game_state();
    char input[MAX_INPUT_SIZE] = "";
    while (game.is_running)
    {
        put_text("YOU: ");
        get_text(input);
        apply_input_to_game_state(input, &game);
    }
}

GameState init_game_state()
{
    GameState game;
    game.is_running = true;
    return game;
}

void apply_input_to_game_state(const char * input, GameState * game)
{
    if (strcmp(input, "exit") == 0)
        game->is_running = false;
}