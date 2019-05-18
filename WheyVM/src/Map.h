#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <stdbool.h>
#include "Object.h"
#include "Array.h"
#include "Pair.h"

#define MAP_INITIAL_SIZE            10
#define MAP_GROW_AT                 0.75
#define MAP_SHRINK_AT               0.25

#define MAP_START_HASH              5381

struct Map 
{
    struct Pair **buckets;
    size_t bucketCount;
    size_t keyCount;
};

void opMSize(struct Object *map, struct Object *size);
void opMGet(struct Object *map, struct Object *key, struct Object *value);
void opMPut(struct Object *map, struct Object *key, struct Object *value, struct Object *previousValue);
void opMRemove(struct Object *map, struct Object *key, struct Object *value);
void opMPutAll(struct Object *map, struct Object *mapToPut);
void opMHasKey(struct Object *map, struct Object *key, struct Object *hasKey);
void opMEntries(struct Object *map, struct Object *entries);

size_t mapSize(struct Map *map);
struct Object *mapGet(struct Map *map, struct Object *key);
struct Object *mapPut(struct Map *map, struct Object *key, struct Object *value);
struct Object *mapRemove(struct Map *map, struct Object *key);
void mapPutAll(struct Map *map, struct Map *mapToPut);
bool mapHasKey(struct Object *map, struct Object *key);
struct Object *mapEntries(struct Object *map);

struct Object *mapNew(size_t initialSize);
struct Object *mapCopy(struct Map *map);
bool mapEqual(struct Map *map1, struct Map *map2);
uint64_t mapHash(struct Map *map);
struct Array *mapSerialize(struct Map *map);

void mapMark(struct Map *map);
void mapFree(struct Map *map);


#endif