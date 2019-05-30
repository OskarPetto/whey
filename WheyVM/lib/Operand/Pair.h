#ifndef PAIR_H
#define PAIR_H

#include "Types.h"

struct Object;
struct Gc;

struct Pair
{
    struct Object *first;
    struct Object *second;
};

struct Object *pairNew(struct Gc *gc, struct Object *first, struct Object *second);
struct Object *pairSetFirst(struct Pair *pair, struct Object *first);
struct Object *pairSetSecond(struct Pair *pair, struct Object *second);

struct Object *pairCopy(struct Gc *gc, struct Pair *pair);
Integer pairEquals(struct Pair *pair1, struct Pair *pair2);
Integer pairHash(struct Pair *pair);
struct Object *pairToString(struct Gc *gc, struct Pair *pair);

void pairMark(struct Pair *pair);

#endif