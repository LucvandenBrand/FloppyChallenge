#include <game/game.h>
#include <io/text_interface.h>
#include <string.h>
#include <stdlib.h>
#include <game/room.h>
#include <game/game_loader.h>
#include <game/text_generator.h>
#include <game/parsing/parser.h>
#include <memory/safe_memory.h>
#include <string/string_ops.h>

void game_loop()
{
    GameState game = init_game_state(GAME_DATA_PATH);
    RoomID previous_room = ID_NO_ROOM;
    char input[MAX_INPUT_SIZE] = "";
    put_text("%s\n", game.intro_text);
    while (game.is_running)
    {
        if (game.current_room != previous_room)
        {
            describe_room(game, game.current_room);
            previous_room = game.current_room;
        }
        put_text("> ");
        get_text(input);
        apply_input_to_game_state(input, &game);
        update_entities(&game);
    }
    free_game_state(&game);
}

GameState init_game_state(const char * game_data_path)
{
    GameState game;
    game.is_running = true;
    game.player = init_player();
    game.current_room = 0;
    game.num_rooms = 0;
    game.rooms = NULL;
    game.num_items = 0;
    game.items = NULL;
    game.num_entities = 0;
    game.entities = NULL;
    game.win_text = NULL;
    game.intro_text = NULL;
    game.reset_text = NULL;
    load_game_data(&game, game_data_path);
    return game;
}

void free_game_state(GameState * game)
{
    game->is_running = false;

    if (game->intro_text != NULL)
        free(game->intro_text);
    game->intro_text = NULL;

    if (game->win_text != NULL)
        free(game->win_text);
    game->win_text = NULL;

    if (game->reset_text != NULL)
        free(game->reset_text);
    game->reset_text = NULL;

    free_player(&game->player);

    if (game->num_rooms > 0)
    {
        for (unsigned room_index = 0; room_index < game->num_rooms; room_index++)
            free_room(&game->rooms[room_index]);
        free(game->rooms);
        game->rooms = NULL;
        game->num_rooms = 0;
    }

    if (game->num_items > 0)
    {
        for (unsigned item_index = 0; item_index < game->num_items; item_index++)
            free_item(&game->items[item_index]);
        free(game->items);
        game->items = NULL;
        game->num_items = 0;
    }

    if (game->num_entities > 0)
    {
        for (unsigned entity_index = 0; entity_index < game->num_entities; entity_index++)
            free_entity(&game->entities[entity_index]);
        free(game->entities);
        game->entities = NULL;
        game->num_entities = 0;
    }
}

ItemID get_item_id(const char * search_name, GameState game)
{
    for (ItemID item_id=0; item_id < game.num_items; item_id++)
    {
        const char * item_name = game.items[item_id].name;
        unsigned long item_name_length = strlen(item_name);
        char * lower_item_name = safe_malloc((item_name_length+1) * sizeof(char));
        strncpy(lower_item_name, item_name, item_name_length+1);
        string_to_lowercase(lower_item_name, item_name_length);
        int equality = strncmp(lower_item_name, search_name, sizeof(item_name));
        free(lower_item_name);

        if (equality == 0)
            return item_id;
    }

    return ID_NO_ITEM;
}

void update_entities(GameState * game)
{
    // TODO check current room, kill player if stayed in room for two turns.
    // TODO move entity to neighbouring rooms (random chance to stay?).
}