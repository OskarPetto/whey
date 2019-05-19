#include "Map.h"
#include <assert.h>


void opMSize(struct Object *map, struct Object *size)
{
    assert(map != NULL);
    assert(map->type == OBJECT_TYPE_MAP);

    size = objectNew();
    size->type = OBJECT_TYPE_INTEGER;
    size->value.integer_value = mapSize(map);
}

void opMKeys(struct Object *map, struct Object *keys)
{
    assert(map != NULL);
    assert(map->type == OBJECT_TYPE_MAP);

    keys = mapKeys(map->value.map);
}

void opMValues(struct Object *map, struct Object *values)
{
    assert(map != NULL);
    assert(map->type == OBJECT_TYPE_MAP);

    values = mapValues(map->value.map);
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

void opMPutAll(struct Object *map, struct Object *mapToPut)
{
    assert(map != NULL);
    assert(map->type == OBJECT_TYPE_MAP);

    if (mapToPut == NULL)
        return;

    assert(mapToPut->type == OBJECT_TYPE_MAP);

    mapPutAll(map->value.map, mapToPut->value.map);
}

size_t mapSize(struct Map *map)
{
    return map->keyCount;
}

struct Object *mapKeys(struct Map *map)
{
    struct Object *keys = arrayNew(map->keyCount);

    for (size_t i = 0; i < map->bucketCount; i++)
    {
        struct Pair *currentEntry = map->buckets[i];

        while (currentEntry != NULL)
        {

            struct Object *key = currentEntry->first->value.pair->first;
            arrayPut(keys->value.array, i, key);

            currentEntry = currentEntry->second;
        }
    }

    return keys;
}

struct Object *mapValues(struct Map *map)
{
    struct Object *values = arrayNew(map->keyCount);

    for (size_t i = 0; i < map->bucketCount; i++)
    {
        struct Pair *currentEntry = map->buckets[i];

        while (currentEntry != NULL)
        {
            struct Object *value = currentEntry->first->value.pair->second;
            arrayPut(values->value.array, i, value);

            currentEntry = currentEntry->second;
        }
    }

    return values;
}

struct Object *mapGet(struct Map *map, struct Object *key)
{
    size_t index = objectHash(key) % map->bucketCount;

    struct Pair *currentEntry = map->buckets[index];

    while (currentEntry != NULL && !objectEquals(currentEntry->first->value.pair->first, key))
    {
        currentEntry = currentEntry->second;
    }

    if (currentEntry == NULL)
        return NULL;

    return currentEntry->first->value.pair->second;
}

void mapPut(struct Map *map, struct Object *key, struct Object *value)
{
    size_t index = objectHash(key) % map->bucketCount;

    struct Pair *currentEntry = map->buckets[index];

    while (currentEntry != NULL && !objectEquals(currentEntry->first->value.pair->first, key))
    {
        currentEntry = currentEntry->second;
    }

    if (currentEntry != NULL)
    {
        currentEntry->first->value.pair->second = value;
    } 
    else
    {
        // insert in linked list
        struct Object *keyValue = pairNew();
        keyValue->value.pair->first = key;
        keyValue->value.pair->second = value;

        struct Object *newEntry = pairNew();
        newEntry->value.pair->first = keyValue;
        newEntry->value.pair->second = map->buckets[index]->second;
        map->buckets[index] = newEntry;
    }
    
}

void mapPutAll(struct Map *map, struct Map *mapToPut)
{

    for (size_t i = 0; i < mapToPut->bucketCount; i++)
    {
        struct Pair *currentEntry = mapToPut->buckets[i];

        while (currentEntry != NULL)
        {
            struct Object *key = currentEntry->first->value.pair->first;
            struct Object *value = currentEntry->first->value.pair->second;
            mapPut(map, key, value);

            currentEntry = currentEntry->second;
        }
    }

}

void mapNew(struct Map *map, size_t initialSlotCount)
{
    //TODO
}

void mapCopy(struct Map *map, struct Map *copy);
bool mapEqual(struct Map *map1, struct Map *map2);
size_t mapHash(struct Map *map);
void mapSerialize(struct Map *map, struct Array *serialization);

void mapMark(struct Map *map);
void mapFree(struct Map *map);
