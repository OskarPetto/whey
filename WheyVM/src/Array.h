#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include "Object.h"

#define ARRAY_INITIAL_SIZE          10
#define ARRAY_GROW_AT               0.75
#define ARRAY_SHRINK_AT             0.25

#define ARRAY_START_HASH            5381

struct Array 
{
    struct Object **objects;
    size_t objectCount;
    size_t slotCount;
};

void opANew(struct Object *array);
void opASize(struct Object *array, struct Object *size);
void opAPush(struct Object *array, struct Object *pushObject);
void opAPop(struct Object *array, struct Object *popObject);
void opAGet(struct Object *array, struct Object *index, struct Object *getObject);
void opAPut(struct Object *array, struct Object *index, struct Object *putObject);
void opAConcat(struct Object *array, struct Object *arrayToAdd);

size_t arraySize(struct Array *array);
void arrayPush(struct Array *array, struct Object *pushObject);
struct Object *arrayPop(struct Array *array);
struct Object *arrayGet(struct Array *array, size_t index);
void arrayPut(struct Array *array, size_t index, struct Object *putObject);
void arrayConcat(struct Array *array, struct Array *arrayToAdd);

void arrayNew(struct Object *array, size_t initialSize);
void arrayCopy(struct Array *array, struct Array *copy);
bool arrayEquals(struct Array *array1, struct Array *array2);
size_t arrayHash(struct Array *array);
void arrayToString(struct Array *array, struct Object *string);

void arrayMark(struct Array *array);
void arrayFree(struct Array *array);

void arrayPushChar(struct Array *array, char c);

#endif