#ifndef PAIR_H
#define PAIR_H

#include "../Types.h"

struct Object;
struct Gc;
struct String;

struct Pair
{
    struct Object *first;
    struct Object *second;
};

struct Object *pairNew(struct Gc *gc, struct Object *first, struct Object *second);
struct Object *pairGetFirst(struct Object *pairObject);
struct Object *pairSetFirst(struct Object *pairObject, struct Object *first);
struct Object *pairGetSecond(struct Object *pairObject);
struct Object *pairSetSecond(struct Object *pairObject, struct Object *second);
void pairSwap(struct Object *pairObject);

struct Object *pairCopy(struct Gc *gc, struct Object *pairObject);
Integer pairEquals(struct Object *pairObject1, struct Object *pairObject2);
Integer pairHash(struct Object *pairObject);
struct Object *pairToString(struct Gc *gc, struct Object *pairObject);

void pairMark(struct Object *pairObject);
void pairFree(struct Gc *gc, struct Object *pairObject);

uint32_t pairStringCharacterCount(struct Object *pairObject);
void pairWriteToString(struct Object *pairObject, struct Object *stringObject, uint32_t *index);

#endif