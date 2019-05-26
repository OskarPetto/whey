#include "../Map.h"
#include "../Array.h"
#include "../Object.h"
#include "../Integer.h"

#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define MAP_INITIAL_BUCKET_COUNT 8

static Integer indexFor(Integer hash, Integer length)
{
    return hash & (length - 1);
}

static Integer improveHash(Integer hash)
{
    return hash ^ (hash >> 16);
}

static void mapResize(struct Map *map, Integer newBucketCount)
{
    struct MapEntry **buckets = (struct MapEntry **)calloc(newBucketCount, sizeof(struct MapEntry *));
    assert(buckets != NULL);

    for (Integer i = 0; i < map->bucketCount; i++)
    {
        struct MapEntry *currEntryToInsert = map->buckets[i];

        while (currEntryToInsert != NULL)
        {
            struct MapEntry *next = currEntryToInsert->next;

            currEntryToInsert->next = NULL;
            Integer index = indexFor(currEntryToInsert->hash, newBucketCount);
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

    free(map->buckets);
    map->buckets = buckets;
    map->bucketCount = newBucketCount;
}

static struct Object *mapPutWithHash(struct Map *map, struct Object *key, struct Object *value, Integer hash)
{
    if (map->entryCount >= map->bucketCount * 3 / 4)
    {
        Integer newBucketCount = map->bucketCount * 2;

        mapResize(map, newBucketCount);
    }

    Integer index = indexFor(hash, map->bucketCount);
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
        return previousValue;
    }

    struct MapEntry *newEntry = (struct MapEntry *)malloc(sizeof(struct MapEntry));
    assert(newEntry != NULL);
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

struct Object *mapNew(struct Gc *gc)
{
    struct Object *map = objectNew(gc, OBJECT_TYPE_MAP);
    map->value.map = (struct Map *)malloc(sizeof(struct Map));
    assert(map->value.map != NULL);
    map->value.map->buckets = (struct MapEntry **)calloc(MAP_INITIAL_BUCKET_COUNT, sizeof(struct MapEntry *));
    assert(map->value.map->buckets != NULL);
    map->value.map->bucketCount = MAP_INITIAL_BUCKET_COUNT;
    map->value.map->entryCount = 0;
    return map;
}

Integer mapSize(struct Map *map)
{
    return map->entryCount;
}

struct Object *mapGet(struct Map *map, struct Object *key)
{
    Integer improvedHash = improveHash(objectHash(key));

    Integer index = indexFor(improvedHash, map->bucketCount);

    struct MapEntry *currEntry = map->buckets[index];

    while (currEntry != NULL && !objectEquals(currEntry->key, key))
    {
        currEntry = currEntry->next;
    }

    if (currEntry == NULL)
        return NULL;

    return currEntry->value;
}

struct Object *mapPut(struct Map *map, struct Object *key, struct Object *value)
{
    Integer improvedHash = improveHash(objectHash(key));

    struct Object *prevObject = mapPutWithHash(map, key, value, improvedHash);

    return prevObject;
}

void mapPutAll(struct Map *map, struct Map *mapToPut)
{
    for (Integer i = 0; i < mapToPut->bucketCount; i++)
    {
        struct MapEntry *currEntry = mapToPut->buckets[i];

        while (currEntry != NULL)
        {
            mapPutWithHash(map, currEntry->key, currEntry->value, currEntry->hash);
            currEntry = currEntry->next;
        }
    }
}

struct Object *mapRemove(struct Map *map, struct Object *key)
{
    if (map->entryCount == 0)
    {
        return NULL;
    }

    Integer improvedHash = improveHash(objectHash(key));

    Integer index = indexFor(improvedHash, map->bucketCount);
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
    free(currEntry);
    map->entryCount--;
    return previousValue;
}

Integer mapHasKey(struct Map *map, struct Object *key)
{
    Integer improvedHash = improveHash(objectHash(key));

    Integer index = indexFor(improvedHash, map->bucketCount);

    struct MapEntry *currEntry = map->buckets[index];

    while (currEntry != NULL && !objectEquals(currEntry->key, key))
    {
        currEntry = currEntry->next;
    }

    if (currEntry == NULL)
        return BOOLEAN_FALSE;

    return BOOLEAN_TRUE;
}

struct Object *mapEntries(struct Gc *gc, struct Map *map)
{
    struct Object *entries = arrayNew(gc, map->entryCount);
    struct Array *entriesArray = entries->value.array;
    Integer entriesAdded = 0;

    for (Integer i = 0; i < map->bucketCount; i++)
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

struct Object *mapCopy(struct Gc *gc, struct Map *map)
{
    struct Object *copy = mapNew(gc);
    struct Map *copyMap = copy->value.map;

    for (Integer i = 0; i < copyMap->bucketCount; i++)
    {
        struct MapEntry *currEntry = copyMap->buckets[i];

        while (currEntry != NULL)
        {
            mapPutWithHash(copyMap, objectCopy(gc, currEntry->key), objectCopy(gc, currEntry->value), currEntry->hash);
            currEntry = currEntry->next;
        }
    }

    return copy;
}

Integer mapEquals(struct Map *map1, struct Map *map2)
{
    if (map1->entryCount != map2->entryCount)
    {
        return BOOLEAN_FALSE;
    }

    for (Integer i = 0; i < map1->bucketCount; i++)
    {
        struct MapEntry *currEntry = map1->buckets[i];

        while (currEntry != NULL)
        {
            struct Object *otherValue = mapGet(map2, currEntry->key);

            if (!objectEquals(currEntry->value, otherValue))
            {
                return BOOLEAN_FALSE;
            }

            currEntry = currEntry->next;
        }
    }

    return BOOLEAN_TRUE;
}

Integer mapHash(struct Map *map)
{
    Integer hash = 1;

    for (Integer i = 0; i < map->bucketCount; i++)
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

struct Object *mapToString(struct Gc *gc, struct Map *map)
{
    struct Object *stringObject = stringNew(gc, 0);
    struct Array *string = stringObject->value.array;

    stringAppendCharacter(string, '{');

    for (Integer i = 0; i < map->bucketCount; i++)
    {
        struct MapEntry *currEntry = map->buckets[i];

        while (currEntry != NULL)
        {
            struct Object *subStringObject1 = objectToString(NULL, currEntry->key);

            struct Array *subString1 = subStringObject1->value.array;
            arrayInsertAll(string, string->objectCount, subString1);

            objectFree(subStringObject1);

            stringAppendCharacter(string, ':');

            struct Object *subStringObject2 = objectToString(NULL, currEntry->value);

            struct Array *subString2 = subStringObject2->value.array;
            arrayInsertAll(string, string->objectCount, subString2);

            stringAppendCharacter(string, ',');

            objectFree(subStringObject2);

            currEntry = currEntry->next;
        }
    }

    if (map->entryCount > 0)
    {
        struct Object *lastChar = integerNew(NULL, '}');
        string->objects[string->objectCount - 1] = lastChar;
    }
    else
    {
        stringAppendCharacter(string, '}');
    }

    return stringObject;
}

void mapMark(struct Map *map)
{
    for (Integer i = 0; i < map->bucketCount; i++)
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

void mapFree(struct Map *map)
{
    for (Integer i = 0; i < map->bucketCount; i++)
    {
        struct MapEntry *currEntry = map->buckets[i];

        while (currEntry != NULL)
        {
            struct MapEntry *nextEntry = currEntry->next;

            free(currEntry);

            currEntry = nextEntry;
        }
    }

    free(map->buckets);
    free(map);
}
