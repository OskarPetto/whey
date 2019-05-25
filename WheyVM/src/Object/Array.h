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

struct Object *arrayNew(struct Gc *gc, Integer initialObjectCount);
Integer arraySize(struct Array *array);
struct Object *arrayGet(struct Array *array, Integer index);
struct Object *arraySet(struct Array *array, Integer index, struct Object *setObject);
void arrayInsert(struct Array *array, Integer index, struct Object *insertObject);
void arrayInsertAll(struct Array *array, Integer index, struct Array *insertArray);
struct Object *arrayRemove(struct Array *array, Integer index);

struct Object *arrayCopy(struct Gc *gc, struct Array *array);
Integer arrayEquals(struct Array *array1, struct Array *array2);
Integer arrayHash(struct Array *array);
struct Object *arrayToString(struct Gc *gc, struct Array *array);

void arrayMark(struct Array *array);
void arrayFree(struct Array *array);

struct Object *stringNew(struct Gc *gc, Integer initialObjectCount);
struct Object *stringFromArray(struct Gc *gc, struct Array *array);
struct Object *stringToArray(struct Gc *gc, struct Array *string);
Integer stringCompare(struct Array *array1, struct Array *array2);

struct Object *stringCopy(struct Gc *gc, struct Array *string);
Integer stringEquals(struct Array *string1, struct Array *string2);
Integer stringHash(struct Array *string);

void stringAppendCharacter(struct Array *string, char character);
void stringFree(struct Array *string);


#endif