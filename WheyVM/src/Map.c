#include "Map.h"
#include <assert.h>



void opMNew(struct Object *map)
{
    objectNew(map, OBJECT_TYPE_MAP);
    mapInit(map->value.map, MAP_INITIAL_SIZE);
}

void opMSize(struct Object *map, struct Object *size)
{
    assert(map != NULL);
    assert(map->type == OBJECT_TYPE_MAP);

    objectNew(size, OBJECT_TYPE_INTEGER);
    size->value.integer_value = mapSize(map);
}

void opMKeys(struct Object *map, struct Object *keys)
{
    assert(map != NULL);
    assert(map->type == OBJECT_TYPE_MAP);

    objectNew(keys, OBJECT_TYPE_ARRAY);
    arrayNew(keys->value.array, map->value.map->slotCount);

    mapKeys(map->value.map, keys->value.array);
}

void opMValues(struct Object *map, struct Object *values)
{
    assert(map != NULL);
    assert(map->type == OBJECT_TYPE_MAP);

    objectNew(values, OBJECT_TYPE_ARRAY);
    arrayNew(values->value.array, map->value.map->slotCount);

    mapValues(map->value.map, values->value.array);
}

void opMGet(struct Object *map, struct Object *key, struct Object *value)
{
    assert(map != NULL);
    assert(map->type == OBJECT_TYPE_MAP);

    value = mapGet(map->value.map, key);
}

void opMPut(struct Object *map, struct Object *key, struct Object *value)
{
    assert(map != NULL);
    assert(map->type == OBJECT_TYPE_MAP);

    mapPut(map->value.map, key, value);
}

void opMMerge(struct Object *map, struct Object *mapToAdd)
{
    assert(map != NULL);
    assert(map->type == OBJECT_TYPE_MAP);

    if (mapToAdd == NULL)
        return;

    assert(mapToAdd->type == OBJECT_TYPE_MAP);

    mapMerge(map->value.map, mapToAdd->value.map);
}



size_t mapSize(struct Map *map)
{
    return map->pairCount;
}

void mapKeys(struct Map *map, struct Array *keys)
{
    for (size_t i = 0; i < map->pairCount; i++)
    {
        struct Object *key = map->keyValuePairs[i]->first;

        arrayPut(keys, i, key);
    }
}

void mapValues(struct Map *map, struct Array *values)
{
    for (size_t i = 0; i < map->pairCount; i++)
    {
        struct Object *key = map->keyValuePairs[i]->second;

        arrayPut(values, i, key);
    }
}
struct Object *mapGet(struct Map *map, struct Object *key)
{
    size_t index = object
}

void mapPut(struct Map *map, struct Object *key, struct Object *value);
void mapMerge(struct Map *map, struct Map *mapToAdd);
void mapMark(struct Map *map);
void mapFree(struct Map *map);
        mapInit(copy->value.map, object->value.map->slotCount);

void mapInit(struct Map *map, size_t initialSize)
{
    map->keyValuePairs = (struct Pair **)malloc(initialSize * sizeof(struct Pair *));
    assert(map->keyValuePairs != NULL);
    map->slotCount = initialSize;
    map->pairCount = 0;
}