#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include "Object.h"

#define ARRAY_INITIAL_SIZE          10
#define ARRAY_GROW_AT               0.75 // [0.5, 1]
#define ARRAY_SHRINK_AT             0.25 // [0, 0.5]

#define ARRAY_START_HASH            5381

struct Array 
{
    struct Object **objects;
    size_t objectCount;
    size_t slotCount;
};

void opASize(struct Object *array, struct Object *size);
void opAGet(struct Object *array, struct Object *index, struct Object *getObject);
void opASet(struct Object *array, struct Object *index, struct Object *setObject, struct Object *previousObject);
void opAInsert(struct Object *array, struct Object *index, struct Object *insertObject);
void opARemove(struct Object *array, struct Object *index, struct Object *removeObject);
void opAInsertAll(struct Object *array, struct Object *index, struct Object *insertArray);

size_t arraySize(struct Array *array);
struct Object *arrayGet(struct Array *array, size_t index);
struct Object *arraySet(struct Array *array, size_t index, struct Object *setObject);
void arrayInsert(struct Array *array, size_t index, struct Object *insertObject);
struct Object *arrayRemove(struct Array *array, size_t index);
void arrayInsertAll(struct Array *array, size_t index, struct Array *insertArray);

struct Object *arrayNew(size_t initialSize);
struct Object *arrayCopy(struct Array *array);
bool arrayEquals(struct Array *array1, struct Array *array2);
uint64_t arrayHash(struct Array *array);
struct Object *arraySerialize(struct Array *array);

void arrayMark(struct Array *array);
void arrayFree(struct Array *array);

void stringAppendChar(struct Array *array, char c);

#endif