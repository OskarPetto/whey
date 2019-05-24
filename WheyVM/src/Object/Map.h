#ifndef MAP_H
#define MAP_H

#include "Object.h"
#include "Array.h"
#include "Gc.h"

struct ListEntry;

struct ListEntry
{
    struct Object *key;
    struct Object *value;
    Integer hash;
    struct ListEntry *next;
};

struct Map 
{
    struct ListEntry **buckets;
    Integer bucketCount;
    Integer entryCount;
};

struct Object *mapNew(struct Gc *gc, Integer initialEntryCount);
Integer mapSize(struct Map *map);
struct Object *mapGet(struct Map *map, struct Object *key);
struct Object *mapPut(struct Map *map, struct Object *key, struct Object *value);
void mapPutAll(struct Map *map, struct Map *mapToPut);
struct Object *mapRemove(struct Map *map, struct Object *key);
Integer mapHasKey(struct Map *map, struct Object *key);
struct Object *mapEntries(struct Gc *gc, struct Map *map);

struct Object *mapCopy(struct Gc *gc, struct Object *map);
Integer mapEquals(struct Object *map1, struct Object *map2);
Integer mapHash(struct Object *map);
struct Object *mapToString(struct Gc *gc, struct Object *map);

void mapMark(struct Map *map);
void mapFree(struct Map *map);


#endif