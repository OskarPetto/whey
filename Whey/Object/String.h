#ifndef STRING_H
#define STRING_H

#include "../Types.h"

struct Gc;
struct Object;
struct Array;

struct String
{
    char *characters;
    uint32_t characterCount;
};

struct Object *stringNew(struct Gc *gc, uint32_t characterCount);
Integer stringSize(struct Object *stringObject);
struct Object *stringFromArray(struct Gc *gc, struct Object *arrayObject);
struct Object *stringToArray(struct Gc *gc, struct Object *stringObject);
Integer stringCompare(struct Object *stringObject1, struct Object *stringObject2);
struct Object *stringConcatenate(struct Gc *gc, struct Object *stringObject1, struct Object *stringObject2);
struct Object *stringSubstring(struct Gc *gc, struct Object *stringObject, Integer lowerIndex, Integer upperIndex);
Integer stringIndexOf(struct Object *stringObject1, struct Object *stringObject2, Integer fromIndex);
Integer stringContains(struct Object *stringObject1, struct Object *stringObject2);
struct Object *stringReplace(struct Gc *gc, struct Object *stringObject1, struct Object *stringObject2, struct Object *stringObject3);
struct Object *stringSplit(struct Gc *gc, struct Object *stringObject1, struct Object *regexStringObject);

struct Object *stringCopy(struct Gc *gc, struct Object *stringObject);
Integer stringEquals(struct Object *stringObject1, struct Object *stringObject2);
Integer stringHash(struct Object *stringObject);

void stringFree(struct Gc *gc, struct Object *stringObject);

void stringPrint(struct Object *stringObject);

uint32_t stringCharacterCount(struct Object *stringObject);
void stringWriteToString(struct Object *stringObject1, struct Object *stringObject2, uint32_t *index);

struct Object *stringNewFromCString(struct Gc *gc, char *characters);

#endif