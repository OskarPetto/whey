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
    struct Pair **keyValuePairs;
    size_t pairCount;
    size_t slotCount;
};

void opMNew(struct Object *map);
void opMSize(struct Object *map, struct Object *size);
void opMKeys(struct Object *map, struct Object *keys);
void opMValues(struct Object *map, struct Object *values);
void opMGet(struct Object *map, struct Object *key, struct Object *value);
void opMPut(struct Object *map, struct Object *key, struct Object *value);
void opMMerge(struct Object *map, struct Object *mapToAdd);

size_t mapSize(struct Map *map);
void mapKeys(struct Map *map, struct Array *keys);
void mapValues(struct Map *map, struct Array *values);
struct Object *mapGet(struct Map *map, struct Object *key);
void mapPut(struct Map *map, struct Object *key, struct Object *putValue);
void mapMerge(struct Map *map, struct Map *mapToAdd);

void mapNew(struct Map *map, size_t initialSize);
void mapCopy(struct Map *map, struct Map *copy);
bool mapEqual(struct Map *map1, struct Map *map2);
size_t mapHash(struct Map *map);
void mapToString(struct Map *map, struct Array *string);

void mapMark(struct Map *map);
void mapFree(struct Map *map);


#endif