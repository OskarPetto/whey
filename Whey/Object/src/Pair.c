#include "../Pair.h"
#include "../Object.h"
#include "../String.h"

#include <stdlib.h>

struct Object *pairNew(struct Gc *gc, struct Object *first, struct Object *second)
{
    struct Object *object = gcObjectNew(gc, OBJECT_TYPE_PAIR, sizeof(struct Pair));
    struct Pair *pair = object->value.subObject;
    pair->first = first;
    pair->second = second;
    return object;
}

struct Object *pairGetFirst(struct Object *pairObject)
{
    OBJECT_NOT_NULL_CHECK(pairObject, OBJECT_TYPE_PAIR);
    ASSERT_OBJECT_TYPE(pairObject, OBJECT_TYPE_PAIR);
    struct Pair *pair = pairObject->value.subObject;
    return pair->first;
}

struct Object *pairSetFirst(struct Object *pairObject, struct Object *first)
{
    OBJECT_NOT_NULL_CHECK(pairObject, OBJECT_TYPE_PAIR);
    ASSERT_OBJECT_TYPE(pairObject, OBJECT_TYPE_PAIR);
    struct Pair *pair = pairObject->value.subObject;
    struct Object *prev = pair->first;
    pair->first = first;
    return prev;
}

struct Object *pairGetSecond(struct Object *pairObject)
{
    OBJECT_NOT_NULL_CHECK(pairObject, OBJECT_TYPE_PAIR);
    ASSERT_OBJECT_TYPE(pairObject, OBJECT_TYPE_PAIR);
    struct Pair *pair = pairObject->value.subObject;
    return pair->second;
}

struct Object *pairSetSecond(struct Object *pairObject, struct Object *second)
{
    OBJECT_NOT_NULL_CHECK(pairObject, OBJECT_TYPE_PAIR);
    ASSERT_OBJECT_TYPE(pairObject, OBJECT_TYPE_PAIR);
    struct Pair *pair = pairObject->value.subObject;
    struct Object *prev = pair->second;
    pair->second = second;
    return prev;
}

void pairSwap(struct Object *pairObject)
{
    OBJECT_NOT_NULL_CHECK(pairObject, OBJECT_TYPE_PAIR);
    ASSERT_OBJECT_TYPE(pairObject, OBJECT_TYPE_PAIR);
    struct Pair *pair = pairObject->value.subObject;
    struct Object *temp = pair->first;
    pair->first = pair->second;
    pair->second = temp;
}

struct Object *pairCopy(struct Gc *gc, struct Object *pairObject)
{
    struct Pair *pair = pairObject->value.subObject;
    return pairNew(gc, objectCopy(gc, pair->first), objectCopy(gc, pair->second));
}

Integer pairEquals(struct Object *pairObject1, struct Object *pairObject2)
{
    struct Pair *pair1 = pairObject1->value.subObject;
    struct Pair *pair2 = pairObject2->value.subObject;
    return objectEquals(pair1->first, pair2->first) && objectEquals(pair1->second, pair2->second);
}

Integer pairHash(struct Object *pairObject)
{
    struct Pair *pair = pairObject->value.subObject;
    return objectHash(pair->first) + objectHash(pair->second);
}

struct Object *pairToString(struct Gc *gc, struct Object *pairObject)
{
    uint32_t characterCount = pairStringCharacterCount(pairObject);

    struct Object *stringObject = stringNew(gc, characterCount);

    uint32_t index = 0;

    pairWriteToString(pairObject, stringObject, &index);

    return stringObject;
}

void pairMark(struct Object *pairObject)
{
    struct Pair *pair = pairObject->value.subObject;
    objectMark(pair->first);
    objectMark(pair->second);
}

void pairFree(struct Gc *gc, struct Object *pairObject)
{
    gcObjectFree(gc, pairObject, sizeof(struct Object) + sizeof(struct Pair));
}

uint32_t pairStringCharacterCount(struct Object *pairObject)
{
    struct Pair *pair = pairObject->value.subObject;
    return 3 + objectStringCharacterCount(pair->first) + objectStringCharacterCount(pair->second);
}

void pairWriteToString(struct Object *pairObject, struct Object *stringObject, uint32_t *index)
{
    struct Pair *pair = pairObject->value.subObject;
    struct String *string = stringObject->value.subObject;

    string->characters[(*index)++] = '(';

    objectWriteToString(pair->first, stringObject, index);

    string->characters[(*index)++] = ',';

    objectWriteToString(pair->second, stringObject, index);

    string->characters[(*index)++] = ')';
}