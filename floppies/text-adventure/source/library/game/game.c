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
    char input[MAX_INPUT_SIZE] = "";
    put_text("%s\n", game.intro_text);
    while (game.is_running)
    {
        if (game.current_room != game.previous_room)
        {
            describe_room(game, game.current_room);
            game.previous_room = game.current_room;
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
    game.previous_room = ID_NO_ROOM;
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
    game->current_room = 0;
    game->previous_room = ID_NO_ROOM;

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

EntityID get_entity_id(const char * search_name, GameState game)
{
    for (EntityID entity_id=0; entity_id < game.num_entities; entity_id++)
    {
        const char * entity_name = game.entities[entity_id].name;
        unsigned long entity_name_length = strlen(entity_name);
        char * lower_entity_name = safe_malloc((entity_name_length + 1) * sizeof(char));
        strncpy(lower_entity_name, entity_name, entity_name_length + 1);
        string_to_lowercase(lower_entity_name, entity_name_length);
        int equality = strncmp(lower_entity_name, search_name, sizeof(entity_name));
        free(lower_entity_name);

        if (equality == 0)
            return entity_id;
    }

    return ID_NO_ITEM;
}

void update_entities(GameState * game)
{
    if (!game->is_running)
        return;

    if (game->current_room != game->previous_room)
    {
        reset_kill_count(game);
        return;
    }

    tick_entity_kill_count(game);
    if (game->rooms[game->current_room].entity_id_list.num_ids > 0)
    {
        put_color_text(RED, "Danger approaches...\n");
    }
    if (check_kill_player(*game))
    {
        put_color_text(BLUE, "%s\n", game->reset_text);
        free_game_state(game);
        *game = init_game_state(GAME_DATA_PATH);
    }
}

void reset_kill_count(GameState * game)
{
    Room room = game->rooms[game->previous_room];
    for (unsigned entity_index = 0; entity_index < room.entity_id_list.num_ids; entity_index++)
    {
        EntityID entity_id = room.entity_id_list.ids[entity_index];
        Entity * entity = &game->entities[entity_id];
        entity->kill_count = entity->start_kill_count;
    }
}

void tick_entity_kill_count(GameState * game)
{
    Room room = game->rooms[game->current_room];
    for (unsigned entity_index = 0; entity_index < room.entity_id_list.num_ids; entity_index++)
    {
        EntityID entity_id = room.entity_id_list.ids[entity_index];
        Entity * entity = &game->entities[entity_id];
        if (entity->kill_count > 0)
            entity->kill_count--;
    }
}

bool check_kill_player(GameState game) {
    for (unsigned entity_index = 0; entity_index < game.num_entities; entity_index++)
    {
        if (game.entities[entity_index].kill_count == 0)
        {
            put_color_text(RED, "%s\n",game.entities[entity_index].attack);
            return true;
        }
    }
    return false;
}
