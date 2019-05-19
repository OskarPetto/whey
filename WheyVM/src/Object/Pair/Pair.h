#ifndef PAIR_H
#define PAIR_H

#include "Object.h"
#include "Array.h"

struct Pair
{
    struct Object *first;
    struct Object *second;
};

struct Object *pairGetFirst(struct Pair *pair);
struct Object *pairGetSecond(struct Pair *pair);
struct Object *pairSetFirst(struct Pair *pair, struct Object *first);
struct Object *pairSetSecond(struct Pair *pair, struct Object *second);

struct Object *pairNew();
struct Object *pairLoad(struct Object *pair);
struct Object *pairStore(struct Object *pair);
struct Object *pairCopy(struct Object *pair);
Integer pairEquals(struct Object *pair1, struct Object *pair2);
Integer pairHash(struct Object *pair);
struct Object *pairToString(struct Object *pair);
void pairMark(struct Pair *pair);
void pairFree(struct Pair *pair);

#endif