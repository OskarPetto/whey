#ifndef STRING_H
#define STRING_H

#include "Types.h"

struct Gc;
struct Object;
struct Array;

struct String
{
    char *characters;
    Integer characterCount;
};


struct Object *stringNew(struct Gc *gc, char *characters);
Integer stringLength(struct String *string);
struct Object *stringFromArray(struct Gc *gc, struct Array *array);
struct Object *stringToArray(struct Gc *gc, struct String *string);
Integer stringCompare(struct String *string1, struct String *string2);
struct Object *stringConcatenate(struct Gc *gc, struct String *string1, struct String *string2);
struct Object *stringSubstring(struct Gc *gc, struct String *string, Integer lowerIndex, Integer upperIndex);

struct Object *stringCopy(struct Gc *gc, struct String *string);
Integer stringEquals(struct String *string1, struct String *string2);
Integer stringHash(struct String *string);

void stringAppendCharacter(struct String *string, char character);
void stringPrint(struct String *string);
void stringFree(struct String *string);


#endif