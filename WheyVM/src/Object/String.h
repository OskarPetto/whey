#ifndef STRING_H
#define STRING_H

#include "Object.h"
#include "Gc.h"
#include "Array.h"

struct String 
{
    char *characters;
    Integer characterCount;
};

struct Object *stringNew(struct Gc *gc, Integer characterCount);
struct Object *stringFromCharArray(struct Gc *gc, struct Array *array);
struct Object *stringToCharArray(struct Gc *gc, struct String *string);
Integer stringCompare(struct String *string1, struct String *string2);

struct Object *stringCopy(struct Gc *gc, struct String *string);
Integer stringEquals(struct String *string1, struct String *string2);
Integer stringHash(struct String *string);

void stringFree(struct String *string);

#endif