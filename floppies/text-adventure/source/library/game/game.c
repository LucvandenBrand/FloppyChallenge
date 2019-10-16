#include <game/game.h>
#include <io/text_interface.h>
#include <string.h>
#include <stdlib.h>
#include <game/room.h>
#include <io/files.h>

void game_loop()
{
    GameState game = init_game_state(GAME_DATA_PATH);
    char input[MAX_INPUT_SIZE] = "";
    while (game.is_running)
    {
        put_text("YOU: ");
        get_text(input);
        apply_input_to_game_state(input, &game);
    }
    free_game_state(&game);
}

GameState init_game_state(const char * game_data_path)
{
    GameState game;
    game.is_running = true;
    game.player = init_player();
    game.num_rooms = 0;
    game.max_rooms = 4;
    game.rooms = malloc(game.max_rooms * sizeof(Room));
    load_game_rooms(&game, game_data_path);
    return game;
}

void load_game_rooms(GameState * game, const char * game_data_path)
{
    long buffer_size = get_file_size(game_data_path);
    if (buffer_size <= 0)
    {
        put_color_text(RED, "Could not find game data file: %s. Exiting game.", game_data_path);
        game->is_running = false;
        return;
    }
    char * game_data_string = malloc(buffer_size * sizeof(char));
    load_file(game_data_path, game_data_string, buffer_size);
    free(game_data_string);
}

void free_game_state(GameState * game)
{
    game->is_running = false;
    free_player(&game->player);
    for (unsigned room_index = 0; room_index < game->num_rooms; room_index++)
        free_room(&game->rooms[room_index]);
    free(game->rooms);
    game->rooms = NULL;
    game->num_rooms = 0;
}

void apply_input_to_game_state(const char * input, GameState * game)
{
    if (strcmp(input, "exit") == 0)
        game->is_running = false;
}