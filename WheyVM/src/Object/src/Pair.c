#include "../Pair.h"
#include "../String.h"
#include "../Array.h"

struct Object *pairNew(struct Gc *gc, struct Object *first, struct Object *second)
{
    struct Object *pair = objectNew(gc, OBJECT_TYPE_PAIR);
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

struct Object *pairPutSecond(struct Pair *pair, struct Object *second)
{
    pair->second = second;
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
    struct Object *arrayObject = arrayNew(gc, 0);
    struct Array *charArray = arrayObject->value.array;

    arrayAppendInteger(gc, charArray, '(');

    struct Object *subStringObject1 = objectToString(gc, pair->first);
    struct Array *subCharArray1 = stringToCharArray(gc, subStringObject1->value.string)->value.array;
    arrayInsertAll(charArray, charArray->objectCount, subCharArray1);

    arrayAppendInteger(gc, charArray, ',');

    struct Object *subStringObject2 = objectToString(gc, pair->second);
    struct Array *subCharArray2 = stringToCharArray(gc, subStringObject2->value.string)->value.array;
    arrayInsertAll(charArray, charArray->objectCount, subCharArray2);

    arrayAppendInteger(gc, charArray, ')');

    return stringFromCharArray(gc, charArray);
}

void pairMark(struct Pair *pair)
{
    objectMark(pair->first);
    objectMark(pair->second);
}
