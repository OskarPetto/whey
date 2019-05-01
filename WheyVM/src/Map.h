#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <stdbool.h>
#include "Object.h"
#include "Array.h"

struct Map 
{
    uint8_t type;
    union ObjectValue *objectValues;
    size_t objectCount;
    size_t slotCount;
};

void mapNew(struct Map *map, size_t length);
size_t mapSize(struct Map *map);
void mapKeys(struct Map *map, struct Array *keysArray);
void mapValues(struct Map *map, struct Array *valuesArray);
void mapAdd(struct Map *map, struct Object *keyObject, struct Object *valueObject);
void mapRemove(struct Map *map, struct Object *keyObject);
void mapGet(struct Map *map, struct Object *keyObject, struct Object *getObject);
void mapSet(struct Map *map, struct Object *keyObject, struct Object *setObject);
void mapFree(struct Map *map);

#endif