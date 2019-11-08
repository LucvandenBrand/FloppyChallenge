#include <game/entity.h>
#include <stdlib.h>

Entity init_entity(char * name, char * description, char * attack, char * die, ItemID holding_item,
                   ItemID vulnerability, bool is_solid)
{
    Entity entity;
    entity.name = name;
    entity.description = description;
    entity.attack = attack;
    entity.die = die;
    entity.holding_item = holding_item;
    entity.vulnerability = vulnerability;
    entity.is_solid = is_solid;
    return entity;
}

void free_entity(Entity * entity)
{
    free(entity->name);
    entity->name = NULL;
    free(entity->description);
    entity->description = NULL;
    free(entity->attack);
    entity->attack = NULL;
    free(entity->die);
    entity->die = NULL;
    entity->holding_item = ID_NO_ITEM;
    entity->vulnerability = ID_NO_ITEM;
    entity->is_solid = false;
}