#include <id/id_list.h>
#include <stdlib.h>
#include <memory/safe_memory.h>

IDList init_list()
{
    IDList list;
    list.num_ids = 0;
    list.list_size = 4;
    list.ids = safe_malloc(list.list_size * sizeof(ID));
    return list;
}

void free_list(IDList * list)
{
    free(list->ids);
    list->ids = NULL;
    list->num_ids = 0;
    list->list_size = 0;
}

void add_id(IDList * list, ID id)
{
    if (has_id(*list, id))
        return;
    if (list->num_ids+1 >= list->list_size)
    {
        list->list_size *= 2;
        list->ids = safe_realloc(list->ids, list->list_size * sizeof(ID));
    }
    list->ids[list->num_ids++] = id;
}

void remove_id(IDList * list, ID id)
{
    for (unsigned index = 0; index < list->num_ids; index++)
    {
        if (list->ids[index] == id)
        {
            list->num_ids--;
            for (unsigned shift_index = index; shift_index < list->num_ids; shift_index++)
            {
                list->ids[shift_index] = list->ids[shift_index + 1];
            }
            break;
        }
    }
}

bool has_id(IDList list, ID id)
{
    for (unsigned id_num = 0; id_num < list.num_ids; id_num++)
    {
        if (list.ids[id_num] == id)
            return true;
    }
    return false;
}