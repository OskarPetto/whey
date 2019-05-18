#ifndef PAIR_H
#define PAIR_H

#include "Object.h"
#include "Array.h"

struct Pair
{
    struct Object *first;
    struct Object *second;
};

void opPGetFst(struct Object *pair, struct Object *first);
void opPGetSnd(struct Object *pair, struct Object *second);
void opPSetFst(struct Object *pair, struct Object *first, struct Object *previousFirst);
void opPSetSnd(struct Object *pair, struct Object *second, struct Object *previousSecond);

struct Object *pairGetFirst(struct Pair *pair);
struct Object *pairGetSecond(struct Pair *pair);
struct Object *pairSetFirst(struct Pair *pair, struct Object *first);
struct Object *pairSetSecond(struct Pair *pair, struct Object *second);

struct Object *pairNew();
struct Object *pairCopy(struct Pair *pair);
bool pairEquals(struct Pair *pair1, struct Pair *pair2);
uint64_t pairHash(struct Pair *pair);
struct Object *pairToString(struct Pair *pair);

void pairMark(struct Pair *pair);
void pairFree(struct Pair *pair);

#endif