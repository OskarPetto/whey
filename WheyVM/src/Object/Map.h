#ifndef MAP_H
#define MAP_H

#include "Types.h"

struct Object;
struct Gc;

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
    Integer bucketCount;
    Integer entryCount;
};

struct Object *mapNew(struct Gc *gc, Integer initialBucketCount);
Integer mapSize(struct Map *map);
struct Object *mapGet(struct Map *map, struct Object *key);
struct Object *mapPut(struct Map *map, struct Object *key, struct Object *value);
void mapPutAll(struct Map *map, struct Map *mapToPut);
struct Object *mapRemove(struct Map *map, struct Object *key);
Integer mapHasKey(struct Map *map, struct Object *key);
struct Object *mapEntries(struct Gc *gc, struct Map *map);

struct Object *mapCopy(struct Gc *gc, struct Map *map);
Integer mapEquals(struct Map *map1, struct Map *map2);
Integer mapHash(struct Map *map);
struct Object *mapToString(struct Gc *gc, struct Map *map);

void mapMark(struct Map *map);
void mapFree(struct Map *map);


#endif