#ifndef ARRAY_H
#define ARRAY_H

#include "Types.h"

struct Gc;
struct Object;

struct Array
{
    struct Object **objects;
    Integer objectCount;
    Integer slotCount;
};

struct Object *arrayNew(struct Gc *gc, Integer initialObjectCount, Integer initialSlotCount);
struct Object *arraySet(struct Array *array, Integer index, struct Object *setObject);
void arrayInsert(struct Gc *gc, struct Array *array, Integer index, struct Object *insertObject);
void arrayInsertAll(struct Gc *gc, struct Array *array, Integer index, struct Array *insertArray);
struct Object *arrayRemove(struct Array *array, Integer index);

struct Object *arrayCopy(struct Gc *gc, struct Array *array);
Integer arrayEquals(struct Array *array1, struct Array *array2);
Integer arrayHash(struct Array *array);
struct Object *arrayToString(struct Gc *gc, struct Array *array);

void arrayMark(struct Array *array);
void arrayFree(struct Gc *gc, struct Array *array);



#endif