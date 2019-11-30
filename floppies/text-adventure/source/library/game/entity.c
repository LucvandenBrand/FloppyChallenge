#include <game/entity.h>
#include <stdlib.h>

Entity init_entity(char * name, char * description, char * attack, char * die, int kill_count, ItemID holding_item,
                   ItemID vulnerability)
{
    Entity entity;
    entity.name = name;
    entity.description = description;
    entity.attack = attack;
    entity.die = die;
    entity.kill_count = kill_count;
    entity.start_kill_count = kill_count;
    entity.holding_item = holding_item;
    entity.vulnerability = vulnerability;
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
    entity->kill_count = -1;
    entity->start_kill_count = -1;
    entity->holding_item = ID_NO_ITEM;
    entity->vulnerability = ID_NO_ITEM;
}