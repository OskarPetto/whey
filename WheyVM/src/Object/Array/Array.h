#ifndef ARRAY_H
#define ARRAY_H

#include "WheyVM.h"
#include "Object.h"
#include "String.h"
#include <stdlib.h>

#define ARRAY_INITIAL_SIZE 10
#define ARRAY_GROW_AT 0.75   // [0.5, 1]
#define ARRAY_SHRINK_AT 0.25 // [0, 0.5]

#define ARRAY_START_HASH 5381

struct Array
{
    struct Object **objects;
    size_t objectCount;
    size_t slotCount;
};

struct Object *arrayConst(struct String *stringConstant);
size_t arraySize(struct Array *array);
struct Object *arrayGet(struct Array *array, size_t index);
struct Object *arraySet(struct Array *array, size_t index, struct Object *setObject);
void arrayInsert(struct Array *array, size_t index, struct Object *insertObject);
void arrayInsertAll(struct Array *array, size_t index, struct Array *insertArray);
struct Object *arrayRemove(struct Array *array, size_t index);
void arrayForEach(struct WheyVM *wvm, struct Array *array, struct Lambda *lambda);
void stringAppendCharacter(struct Array *array, Character character);

struct Object *arrayNew(size_t initialObjectCount);
struct Object *arrayLoad(struct Object *object);
struct Object *arrayStore(struct Object *object);
struct Object *arrayCopy(struct Object *object);
Integer arrayEquals(struct Object *object1, struct Object *object2);
Integer arrayHash(struct Object *object);
struct Object *arrayToString(struct Object *object);
void arrayMark(struct Object *object);
void arrayFree(struct Object *object);

#endif