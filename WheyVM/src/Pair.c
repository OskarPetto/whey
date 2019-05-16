#include "Pair.h"
#include <assert.h>

void opPNew(struct Object *pair)
{
    objectNew(pair, OBJECT_TYPE_PAIR);
}

void opPGetFirst(struct Object *pair, struct Object *first)
{
    assert(pair != NULL);
    assert(pair->type == OBJECT_TYPE_PAIR);
    first = pairGetFirst(pair->value.pair);
}

void opPGetSecond(struct Object *pair, struct Object *second)
{
    assert(pair != NULL);
    assert(pair->type == OBJECT_TYPE_PAIR);
    second = pairGetSecond(pair->value.pair);
}

void opPPutFirst(struct Object *pair, struct Object *first)
{
    assert(pair != NULL);
    assert(pair->type == OBJECT_TYPE_PAIR);
    pairPutFirst(pair->value.pair, first);
}

void opPPutSecond(struct Object *pair, struct Object *second)
{
    assert(pair != NULL);
    assert(pair->type == OBJECT_TYPE_PAIR);
    pairPutSecond(pair->value.pair, second);
}

struct Object *pairGetFirst(struct Pair *pair)
{
    return pair->first;
}

struct Object *pairGetSecond(struct Pair *pair)
{
    return pair->second;
}

void pairPutFirst(struct Pair *pair, struct Object *first)
{
    pair->first = first;
}

void pairPutSecond(struct Pair *pair, struct Object *second)
{
    pair->second = second;
}

void pairNew(struct Pair *pair)
{
    objectNew(pair, OBJECT_TYPE_PAIR);
}

void pairCopy(struct Pair *pair, struct Pair *copy)
{
    objectCopy(pair->first, pair->first);
    objectCopy(pair->second, pair->second);
}

bool pairEquals(struct Pair *pair1, struct Pair *pair2)
{
    return objectEquals(pair1->first, pair2->first) && objectEquals(pair1->second, pair2->second);
}

size_t pairHash(struct Pair *pair)
{
    return objectHash(pair->first) + objectHash(pair->second);
}

void pairToString(struct Pair *pair, struct Object *string)
{
    struct Array *charArray = string->value.array;

    arrayPushChar(charArray, '(');

    struct Object *firstString;
    objectToString(pair->first, firstString);
    arrayConcat(charArray, firstString);

    arrayPushChar(charArray, ',');

    struct Object *secondString;
    objectToString(pair->second, secondString);
    arrayConcat(charArray, secondString);

    arrayPushChar(charArray, ')');
}

void pairMark(struct Pair *pair)
{
    if (pair->first != NULL)
    {
        objectMark(pair->first);
    }

    if (pair->second != NULL)
    {
        objectMark(pair->second);
    }

}

void pairFree(struct Pair *pair)
{
    if (pair->first != NULL)
    {
        objectFree(pair->first);
    }

    if (pair->second != NULL)
    {
        objectFree(pair->second);
    }

    free(pair);
}
