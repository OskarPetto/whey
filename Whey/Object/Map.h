#ifndef MAP_H
#define MAP_H

#include "../Types.h"

struct Object;
struct Gc;
struct String;
struct MapEntry;

struct MapEntry
{
    struct Object *key;
    struct Object *value;
    Integer hash;
    struct MapEntry *next;
};

struct Map 
{
    struct MapEntry **buckets;
    uint32_t bucketCount;
    uint32_t entryCount;
};

struct Object *mapNew(struct Gc *gc);
Integer mapSize(struct Object *mapObject);
struct Object *mapGet(struct Object *mapObject, struct Object *key);
struct Object *mapPut(struct Gc *gc, struct Object *mapObject, struct Object *key, struct Object *value);
void mapPutAll(struct Gc *gc, struct Object *mapObject, struct Object *mapObjectToPut);
struct Object *mapRemove(struct Gc *gc, struct Object *mapObject, struct Object *key);
Integer mapHasKey(struct Object *mapObject, struct Object *key);
struct Object *mapEntries(struct Gc *gc, struct Object *mapObject);
struct Object *mapKeys(struct Gc *gc, struct Object *mapObject);
struct Object *mapValues(struct Gc *gc, struct Object *mapObject);
void mapSwap(struct Object *mapObject, struct Object *key1, struct Object *key2);

struct Object *mapCopy(struct Gc *gc, struct Object *mapObject);
Integer mapEquals(struct Object *mapObject1, struct Object *mapObject2);
Integer mapHash(struct Object *mapObject);
struct Object *mapToString(struct Gc *gc, struct Object *mapObject);

void mapMark(struct Object *mapObject);
void mapFree(struct Gc *gc, struct Object *mapObject);

uint32_t mapStringCharacterCount(struct Object *mapObject);
void mapWriteToString(struct Object *mapObject, struct Object *stringObject, uint32_t *index);

#endif