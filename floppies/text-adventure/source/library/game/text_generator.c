#include <game/text_generator.h>
#include <io/text_interface.h>
#include <string.h>
#include <ctype.h>

void describe_room(GameState game, RoomID room_id)
{
    Room room = game.rooms[room_id];
    put_text("%s\n", room.description);
    list_items(game, room.item_id_list);
}

void list_items(GameState game, IDList item_list)
{
    if (item_list.num_ids <= 0)
    {
        put_text("It is empty.\n");
        return;
    }
    put_text("There is ");
    for (unsigned item_num = 0; item_num < item_list.num_ids; item_num++)
    {
        if (item_list.num_ids > 1 && item_num == item_list.num_ids-1)
            put_text(" and ");
        else if (item_num > 0)
            put_text(", ");
        Item item = game.items[item_list.ids[item_num]];
        choose_indefinite_article(item.name);
        put_text(" ");
        put_text("%s", item.name);
    }
    put_text(".\n");
}

void choose_indefinite_article(const char * name)
{
    if (strlen(name) < 1)
        return;
    put_text("a");
    char first_char = (char) tolower(name[0]);
    if (is_char_in_array(first_char, "aeiouae")) // Yes, I'm missing the details here.
        put_text("n");
}

bool is_char_in_array(char character, const char * array)
{
    unsigned long array_length = strlen(array);
    for (unsigned long index=0; index < array_length; index++)
    {
        if (character == array[index])
            return true;
    }
    return false;
}