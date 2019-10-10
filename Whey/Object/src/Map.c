#include "../Map.h"
#include "../Array.h"
#include "../Object.h"
#include "../String.h"
#include "../Pair.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INDEX_FOR(hash, length) hash & (length - 1)

#define IMPROVE_HASH(hash) hash ^ (hash >> 16)

static struct Object *mapWithBucketCount(struct Gc *gc, uint32_t initialBucketCount)
{
    struct Object *object = gcObjectNew(gc, OBJECT_TYPE_MAP, sizeof(struct Map));
    struct Map *map = object->value.subObject;
    map->buckets = gcMemoryMalloc(gc, object, initialBucketCount * sizeof(struct MapEntry *));
    memset(map->buckets, 0, initialBucketCount * sizeof(struct MapEntry *));

    map->bucketCount = initialBucketCount;
    map->entryCount = 0;

    return object;
}

static void mapResize(struct Gc *gc, struct Object *mapObject, struct Map *map, uint32_t newBucketCount)
{
    struct MapEntry **buckets = gcMemoryMalloc(gc, mapObject, newBucketCount * sizeof(struct MapEntry *));
    memset(buckets, 0, newBucketCount * sizeof(struct MapEntry *));

    for (uint32_t i = 0; i < map->bucketCount; i++)
    {
        struct MapEntry *currEntryToInsert = map->buckets[i];

        while (currEntryToInsert != NULL)
        {
            struct MapEntry *next = currEntryToInsert->next;

            currEntryToInsert->next = NULL;
            uint32_t index = INDEX_FOR(currEntryToInsert->hash, newBucketCount);
            struct MapEntry *currEntry = buckets[index];
            struct MapEntry *prevEntry = NULL;

            while (currEntry != NULL)
            {
                prevEntry = currEntry;
                currEntry = currEntry->next;
            }

            if (prevEntry == NULL)
            {
                buckets[index] = currEntryToInsert;
            }
            else
            {
                prevEntry->next = currEntryToInsert;
            }

            currEntryToInsert = next;
        }
    }

    gcMemoryFree(gc, mapObject, map->buckets, map->bucketCount);
    map->buckets = buckets;
    map->bucketCount = newBucketCount;
}

static struct Object *mapPutWithHash(struct Gc *gc, struct Object *mapObject, struct Map *map, struct Object *key, struct Object *value, Integer hash)
{
    if (map->entryCount >= map->bucketCount * 3 / 4)
    {
        uint32_t newBucketCount = map->bucketCount * 2;

        mapResize(gc, mapObject, map, newBucketCount);
    }

    uint32_t index = INDEX_FOR(hash, map->bucketCount);
    struct MapEntry *currEntry = map->buckets[index];
    struct MapEntry *prevEntry = NULL;

    while (currEntry != NULL && !objectEquals(currEntry->key, key))
    {
        prevEntry = currEntry;
        currEntry = currEntry->next;
    }

    if (currEntry != NULL) // key found
    {
        struct Object *previousValue = currEntry->value;
        currEntry->value = value;
        currEntry->key = key;
        return previousValue;
    }

    struct MapEntry *newEntry = gcMemoryMalloc(gc, mapObject, sizeof(struct MapEntry));
    newEntry->key = key;
    newEntry->value = value;
    newEntry->hash = hash;
    newEntry->next = NULL;

    if (prevEntry == NULL)
    {
        map->buckets[index] = newEntry;
    }
    else
    {
        prevEntry->next = newEntry;
    }

    map->entryCount++;

    return NULL;
}

static struct MapEntry *mapGetFromMap(struct Map *map, struct Object *key)
{
    Integer improvedHash = IMPROVE_HASH(objectHash(key));

    uint32_t index = INDEX_FOR(improvedHash, map->bucketCount);

    struct MapEntry *currEntry = map->buckets[index];

    while (currEntry != NULL && !objectEquals(currEntry->key, key))
    {
        currEntry = currEntry->next;
    }

    return currEntry;
}

struct Object *mapNew(struct Gc *gc)
{
    return mapWithBucketCount(gc, 8);
}

Integer mapSize(struct Object *mapObject)
{
    OBJECT_NOT_NULL_CHECK(mapObject, OBJECT_TYPE_MAP);
    ASSERT_OBJECT_TYPE(mapObject, OBJECT_TYPE_MAP);
    struct Map *map = mapObject->value.subObject;
    return map->entryCount;
}

struct Object *mapGet(struct Object *mapObject, struct Object *key)
{
    OBJECT_NOT_NULL_CHECK(mapObject, OBJECT_TYPE_MAP);
    ASSERT_OBJECT_TYPE(mapObject, OBJECT_TYPE_MAP);
    struct Map *map = mapObject->value.subObject;

    struct MapEntry *entry = mapGetFromMap(map, key);

    if (entry == NULL)
        return NULL;

    return entry->value;
}

struct Object *mapPut(struct Gc *gc, struct Object *mapObject, struct Object *key, struct Object *value)
{
    OBJECT_NOT_NULL_CHECK(mapObject, OBJECT_TYPE_MAP);
    ASSERT_OBJECT_TYPE(mapObject, OBJECT_TYPE_MAP);
    struct Map *map = mapObject->value.subObject;

    Integer improvedHash = IMPROVE_HASH(objectHash(key));

    struct Object *prevObject = mapPutWithHash(gc, mapObject, map, key, value, improvedHash);

    return prevObject;
}

void mapPutAll(struct Gc *gc, struct Object *mapObject, struct Object *mapObjectToPut)
{
    OBJECT_NOT_NULL_CHECK(mapObject, OBJECT_TYPE_MAP);
    ASSERT_OBJECT_TYPE(mapObject, OBJECT_TYPE_MAP);
    struct Map *map = mapObject->value.subObject;
    OBJECT_NOT_NULL_CHECK(mapObjectToPut, OBJECT_TYPE_MAP);
    ASSERT_OBJECT_TYPE(mapObjectToPut, OBJECT_TYPE_MAP);
    struct Map *mapToPut = mapObjectToPut->value.subObject;
    
    for (uint32_t i = 0; i < mapToPut->bucketCount; i++)
    {
        struct MapEntry *currEntry = mapToPut->buckets[i];

        while (currEntry != NULL)
        {
            mapPutWithHash(gc, mapObject, map, currEntry->key, currEntry->value, currEntry->hash);
            currEntry = currEntry->next;
        }
    }
}

struct Object *mapRemove(struct Gc *gc, struct Object *mapObject, struct Object *key)
{
    OBJECT_NOT_NULL_CHECK(mapObject, OBJECT_TYPE_MAP);
    ASSERT_OBJECT_TYPE(mapObject, OBJECT_TYPE_MAP);
    struct Map *map = mapObject->value.subObject;
    if (map->entryCount == 0)
    {
        return NULL;
    }

    Integer improvedHash = IMPROVE_HASH(objectHash(key));

    uint32_t index = INDEX_FOR(improvedHash, map->bucketCount);
    struct MapEntry *currEntry = map->buckets[index];
    struct MapEntry *prevEntry = NULL;

    while (currEntry != NULL && !objectEquals(currEntry->key, key))
    {
        prevEntry = currEntry;
        currEntry = currEntry->next;
    }

    if (currEntry == NULL) // key not found
    {
        return NULL;
    }

    struct Object *previousValue = currEntry->value;

    if (prevEntry == NULL)
    {
        map->buckets[index] = currEntry->next;
    }
    else
    {
        prevEntry->next = currEntry->next;
    }

    gcMemoryFree(gc, mapObject, currEntry, sizeof(struct MapEntry));
    map->entryCount--;

    return previousValue;
}

Integer mapHasKey(struct Object *mapObject, struct Object *key)
{
    OBJECT_NOT_NULL_CHECK(mapObject, OBJECT_TYPE_MAP);
    ASSERT_OBJECT_TYPE(mapObject, OBJECT_TYPE_MAP);
    struct Map *map = mapObject->value.subObject;
    Integer improvedHash = IMPROVE_HASH(objectHash(key));

    uint32_t index = INDEX_FOR(improvedHash, map->bucketCount);

    struct MapEntry *currEntry = map->buckets[index];

    while (currEntry != NULL && !objectEquals(currEntry->key, key))
    {
        currEntry = currEntry->next;
    }

    if (currEntry == NULL)
        return BOOLEAN_FALSE;

    return BOOLEAN_TRUE;
}

struct Object *mapEntries(struct Gc *gc, struct Object *mapObject)
{
    OBJECT_NOT_NULL_CHECK(mapObject, OBJECT_TYPE_MAP);
    ASSERT_OBJECT_TYPE(mapObject, OBJECT_TYPE_MAP);
    struct Map *map = mapObject->value.subObject;
    struct Object *entries = arrayNew(gc, map->entryCount, map->entryCount);
    struct Array *entriesArray = entries->value.subObject;
    uint32_t entriesAdded = 0;

    for (uint32_t i = 0; i < map->bucketCount; i++)
    {
        struct MapEntry *currEntry = map->buckets[i];

        while (currEntry != NULL)
        {
            struct Object *newPair = pairNew(gc, currEntry->key, currEntry->value);

            entriesArray->objects[entriesAdded++] = newPair;
            currEntry = currEntry->next;
        }
    }

    return entries;
}

struct Object *mapKeys(struct Gc *gc, struct Object *mapObject) 
{
    OBJECT_NOT_NULL_CHECK(mapObject, OBJECT_TYPE_MAP);
    ASSERT_OBJECT_TYPE(mapObject, OBJECT_TYPE_MAP);
    struct Map *map = mapObject->value.subObject;
    struct Object *keys = arrayNew(gc, map->entryCount, map->entryCount);
    struct Array *keysArray = keys->value.subObject;
    uint32_t keysAdded = 0;

    for (uint32_t i = 0; i < map->bucketCount; i++)
    {
        struct MapEntry *currEntry = map->buckets[i];

        while (currEntry != NULL)
        {
            keysArray->objects[keysAdded++] = currEntry->key;
            currEntry = currEntry->next;
        }
    }

    return keys;
}

struct Object *mapValues(struct Gc *gc, struct Object *mapObject)
{
    OBJECT_NOT_NULL_CHECK(mapObject, OBJECT_TYPE_MAP);
    ASSERT_OBJECT_TYPE(mapObject, OBJECT_TYPE_MAP);
    struct Map *map = mapObject->value.subObject;
    struct Object *values = arrayNew(gc, map->entryCount, map->entryCount);
    struct Array *valuesArray = values->value.subObject;
    uint32_t valuesAdded = 0;

    for (uint32_t i = 0; i < map->bucketCount; i++)
    {
        struct MapEntry *currEntry = map->buckets[i];

        while (currEntry != NULL)
        {
            valuesArray->objects[valuesAdded++] = currEntry->value;
            currEntry = currEntry->next;
        }
    }

    return values;
}

void mapSwap(struct Object *mapObject, struct Object *key1, struct Object *key2)
{
    OBJECT_NOT_NULL_CHECK(mapObject, OBJECT_TYPE_MAP);
    ASSERT_OBJECT_TYPE(mapObject, OBJECT_TYPE_MAP);
    struct Map *map = mapObject->value.subObject;
    
    struct MapEntry *entry1 = mapGetFromMap(map, key1);
    NOT_NULL_CHECK(entry1, ERRCODE_RUNTIME, "Map does not contain first key\n");
    struct MapEntry *entry2 = mapGetFromMap(map, key2);
    NOT_NULL_CHECK(entry2, ERRCODE_RUNTIME, "Map does not contain second key\n");

    struct Object *temp = entry1->value;
    entry1->value = entry2->value;
    entry2->value = temp;
}

struct Object *mapCopy(struct Gc *gc, struct Object *mapObject)
{
    struct Map *map = mapObject->value.subObject;
    struct Object *copy = mapWithBucketCount(gc, map->bucketCount);
    struct Map *copyMap = copy->value.subObject;
    for (uint32_t i = 0; i < map->bucketCount; i++)
    {
        struct MapEntry *currEntry = map->buckets[i];

        while (currEntry != NULL)
        {
            mapPutWithHash(gc, copy, copyMap, objectCopy(gc, currEntry->key), objectCopy(gc, currEntry->value), currEntry->hash);
            currEntry = currEntry->next;
        }
    }

    return copy;
}

Integer mapEquals(struct Object *mapObject1, struct Object *mapObject2)
{
    struct Map *map1 = mapObject1->value.subObject;
    struct Map *map2 = mapObject2->value.subObject;

    if (map1->entryCount != map2->entryCount)
    {
        return BOOLEAN_FALSE;
    }

    // map1 subset map2
    for (uint32_t i = 0; i < map1->bucketCount; i++)
    {
        struct MapEntry *currEntry = map1->buckets[i];

        while (currEntry != NULL)
        {
            struct MapEntry *other = mapGetFromMap(map2, currEntry->key);

            if (other == NULL)
            {
                return BOOLEAN_FALSE;
            }

            if (!objectEquals(currEntry->value, other->value))
            {
                return BOOLEAN_FALSE;
            }

            currEntry = currEntry->next;
        }
    }

    return BOOLEAN_TRUE;
}

Integer mapHash(struct Object *mapObject)
{
    Integer hash = 1;
    struct Map *map = mapObject->value.subObject;

    for (uint32_t i = 0; i < map->bucketCount; i++)
    {
        struct MapEntry *currEntry = map->buckets[i];

        while (currEntry != NULL)
        {
            hash = 31 * hash + currEntry->hash + objectHash(currEntry->value);
            currEntry = currEntry->next;
        }
    }

    return hash;
}

struct Object *mapToString(struct Gc *gc, struct Object *mapObject)
{
    uint32_t characterCount = mapStringCharacterCount(mapObject);

    struct Object *stringObject = stringNew(gc, characterCount);

    uint32_t index = 0;

    mapWriteToString(mapObject, stringObject, &index);

    return stringObject;
}

void mapMark(struct Object *mapObject)
{
    struct Map *map = mapObject->value.subObject;

    for (uint32_t i = 0; i < map->bucketCount; i++)
    {
        struct MapEntry *currEntry = map->buckets[i];

        while (currEntry != NULL)
        {
            objectMark(currEntry->key);
            objectMark(currEntry->value);

            currEntry = currEntry->next;
        }
    }
}

void mapFree(struct Gc *gc, struct Object *mapObject)
{
    struct Map *map = mapObject->value.subObject;
    for (uint32_t i = 0; i < map->bucketCount; i++)
    {
        struct MapEntry *currEntry = map->buckets[i];

        while (currEntry != NULL)
        {
            struct MapEntry *nextEntry = currEntry->next;

            gcMemoryFree(gc, mapObject, currEntry, sizeof(struct MapEntry));

            currEntry = nextEntry;
        }
    }

    gcMemoryFree(gc, mapObject, map->buckets, map->bucketCount * sizeof(struct MapEntry *));
    gcObjectFree(gc, mapObject, sizeof(struct Object) + sizeof(struct Map));
}


uint32_t mapStringCharacterCount(struct Object *mapObject)
{
    struct Map *map = mapObject->value.subObject;
    uint32_t count = 2 + (map->entryCount) + (map->entryCount > 0 ? map->entryCount - 1 : 0);
    
    for (uint32_t i = 0; i < map->bucketCount; i++)
    {
        struct MapEntry *currEntry = map->buckets[i];

        while (currEntry != NULL)
        {
            count += objectStringCharacterCount(currEntry->key); 
            count += objectStringCharacterCount(currEntry->value);

            currEntry = currEntry->next;
        }
    }

    return count;
}

void mapWriteToString(struct Object *mapObject, struct Object *stringObject, uint32_t *index)
{
    struct String *string = stringObject->value.subObject;
    struct Map *map = mapObject->value.subObject;
    string->characters[(*index)++] = '{';

    for (uint32_t i = 0; i < map->bucketCount; i++)
    {
        struct MapEntry *currEntry = map->buckets[i];

        while (currEntry != NULL)
        {
            objectWriteToString(currEntry->key, stringObject, index);

            string->characters[(*index)++] = ':';

            objectWriteToString(currEntry->value, stringObject, index);

            string->characters[(*index)++] = ',';

            currEntry = currEntry->next;
        }
    }

    if (map->entryCount > 0)
    {
        (*index)--;
    }

    string->characters[(*index)++] = '}';
}