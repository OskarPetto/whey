#ifndef ARRAY_H
#define ARRAY_H

#include "../Types.h"

struct Gc;
struct Object;
struct String;

struct Array
{
    struct Object **objects;
    uint32_t objectCount;
    uint32_t slotCount;
};

struct Object *arrayNew(struct Gc *gc, Integer initialObjectCount, Integer initialSlotCount);
Integer arraySize(struct Object *arrayObject);
struct Object *arrayGet(struct Object *arrayObject, Integer index);
struct Object *arraySet(struct Object *arrayObject, Integer index, struct Object *setObject);
void arrayInsert(struct Gc *gc, struct Object *arrayObject, Integer index, struct Object *insertObject);
void arrayInsertAll(struct Gc *gc, struct Object *arrayObject, Integer index, struct Object *insertArrayObject);
struct Object *arrayRemove(struct Object *arrayObject, Integer index);
void arrayPush(struct Gc *gc, struct Object *arrayObject, struct Object *pushObject);
void arrayPushNoNullCheck(struct Gc *gc, struct Object *arrayObject, struct Object *pushObject);
void arrayPushAll(struct Gc *gc, struct Object *arrayObject, struct Object *pushArrayObject);
struct Object *arrayPop(struct Object *arrayObject);
void arraySwap(struct Object *arrayObject, Integer index1, Integer index2);

struct Object *arrayCopy(struct Gc *gc, struct Object *arrayObject);
Integer arrayEquals(struct Object *arrayObject1, struct Object *arrayObject2);
Integer arrayHash(struct Object *arrayObject);
struct Object *arrayToString(struct Gc *gc, struct Object *arrayObject);

void arrayMark(struct Object *arrayObject);
void arrayFree(struct Gc *gc, struct Object *arrayObject);

uint32_t arrayStringCharacterCount(struct Object *arrayObject);
void arrayWriteToString(struct Object *arrayObject, struct Object *stringObject, uint32_t *index);

#endif