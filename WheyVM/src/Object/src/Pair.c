#include "../Pair.h"
#include "../Array.h"
#include "../Object.h"

#include <stdlib.h>
#include <assert.h>

struct Object *pairNew(struct Gc *gc, struct Object *first, struct Object *second)
{
    struct Object *pair = objectNew(gc, OBJECT_TYPE_PAIR);
    pair->value.pair = (struct Pair *) malloc(sizeof(struct Pair));
    assert(pair->value.pair != NULL); 
    pair->value.pair->first = first;
    pair->value.pair->second = second;
    return pair;
}

struct Object *pairGetFirst(struct Pair *pair)
{
    return pair->first;
}

struct Object *pairGetSecond(struct Pair *pair)
{
    return pair->second;
}


struct Object *pairSetFirst(struct Pair *pair, struct Object *first)
{
    struct Object *prev = pair->first;
    pair->first = first;
    return prev;
}

struct Object *pairSetSecond(struct Pair *pair, struct Object *second)
{
    struct Object *prev = pair->second;
    pair->second = second;
    return prev;
}

struct Object *pairCopy(struct Gc *gc, struct Pair *pair)
{
    return pairNew(gc, objectCopy(gc, pair->first), objectCopy(gc, pair->second));
}

Integer pairEquals(struct Pair *pair1, struct Pair *pair2)
{
    return objectEquals(pair1->first, pair2->first) && objectEquals(pair1->second, pair2->second);
}

Integer pairHash(struct Pair *pair)
{
    return objectHash(pair->first) + objectHash(pair->second);
}

struct Object *pairToString(struct Gc *gc, struct Pair *pair)
{
    struct Object *stringObject = stringNew(gc, "");
    struct Array *string = stringObject->value.array;

    stringAppendCharacter(string, '(');

    struct Object *subStringObject1 = objectToString(NULL, pair->first);
    struct Array *subString1 = subStringObject1->value.array;
    arrayInsertAll(string, string->objectCount, subString1);

    objectFree(subStringObject1);

    stringAppendCharacter(string, ',');

    struct Object *subStringObject2 = objectToString(NULL, pair->second);
    struct Array *subString2 = subStringObject2->value.array;
    arrayInsertAll(string, string->objectCount, subString2);

    objectFree(subStringObject2);

    stringAppendCharacter(string, ')');

    return stringObject;
}

void pairMark(struct Pair *pair)
{
    objectMark(pair->first);
    objectMark(pair->second);
}
