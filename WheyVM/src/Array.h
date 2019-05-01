#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <stdbool.h>
#include "Object.h"

struct Array 
{
    uint8_t type;
    union ObjectValue *objectValues;
    size_t objectCount;
    size_t slotCount;
};

void arrayNew(struct Array *array, size_t length);
size_t arraySize(struct Array *array);
bool arrayContains(struct Array *array, struct Object *containsObject);
void arrayAdd(struct Array *array, struct Object *addObject);
void arrayRemove(struct Array *array, struct Object *removeObject);
void arrayGet(struct Array *array, size_t index, struct Object *getObject);
void arraySet(struct Array *array, size_t index, struct Object *setObject);
void arrayFree(struct Array *array);

#endif