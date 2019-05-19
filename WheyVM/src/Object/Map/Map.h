#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include "Object.h"
#include "Pair.h"

#define MAP_INITIAL_SIZE            10
#define MAP_GROW_AT                 0.75
#define MAP_SHRINK_AT               0.25

#define MAP_START_HASH              5212

struct Map 
{
    struct Pair **buckets;
    size_t bucketCount;
    size_t keyCount;
};

size_t mapSize(struct Map *map);
struct Object *mapGet(struct Map *map, struct Object *key);
struct Object *mapPut(struct Map *map, struct Object *key, struct Object *value);
void mapPutAll(struct Map *map, struct Map *mapToPut);
struct Object *mapRemove(struct Map *map, struct Object *key);
Integer mapHasKey(struct Object *map, struct Object *key);
struct Object *mapEntries(struct Object *map);

struct Object *mapNew(size_t initialBucketCount);
struct Object *mapLoad(struct Object *map);
struct Object *mapStore(struct Object *map);
struct Object *mapCopy(struct Object *map);
Integer mapEquals(struct Object *map1, struct Object *map2);
Integer mapHash(struct Object *map);
struct Object *mapToString(struct Object *map);
void mapMark(struct Map *map);
void mapFree(struct Map *map);


#endif