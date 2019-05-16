#ifndef PAIR_H
#define PAIR_H

#include "Object.h"
#include "Array.h"

struct Pair
{
    struct Object *first;
    struct Object *second;
};

void opPNew(struct Object *pair);
void opPGetFirst(struct Object *pair, struct Object *first);
void opPGetSecond(struct Object *pair, struct Object *second);
void opPPutFirst(struct Object *pair, struct Object *first);
void opPPutSecond(struct Object *pair, struct Object *second);

struct Object *pairGetFirst(struct Pair *pair);
struct Object *pairGetSecond(struct Pair *pair);
void pairPutFirst(struct Pair *pair, struct Object *first);
void pairPutSecond(struct Pair *pair, struct Object *second);

void pairNew(struct Object *pair);
void pairCopy(struct Pair *pair, struct Pair *copy);
bool pairEquals(struct Pair *pair1, struct Pair *pair2);
size_t pairHash(struct Pair *pair);
void pairToString(struct Pair *pair, struct Object *string);

void pairMark(struct Pair *pair);
void pairFree(struct Pair *pair);

#endif