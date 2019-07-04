#include "../Pair.h"
#include "../Object.h"
#include "../String.h"

#include <stdlib.h>
#include <assert.h>

struct Object *pairNew(struct Gc *gc, struct Object *first, struct Object *second)
{
    struct Object *pair = objectNew(gc, OBJECT_TYPE_PAIR);
    gcRequestMemory(gc, sizeof(struct Pair));
    pair->value.pair = (struct Pair *) malloc(sizeof(struct Pair));
    assert(pair->value.pair != NULL); 
    pair->value.pair->first = first;
    pair->value.pair->second = second;
    return pair;
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
    struct Object *stringObject = stringNewFromCString(NULL, "(");

    struct Object *subStringObject1 = objectToString(NULL, pair->first);
    
    struct Object *temp = stringConcatenate(NULL, stringObject->value.string, subStringObject1->value.string);

    objectFree(NULL, stringObject);
    objectFree(NULL, subStringObject1);
    stringObject = temp;

    stringAppendCharacter(stringObject->value.string, ',');

    struct Object *subStringObject2 = objectToString(NULL, pair->second);
    
    temp = stringConcatenate(NULL, stringObject->value.string, subStringObject2->value.string);
    
    objectFree(NULL, stringObject);
    objectFree(NULL, subStringObject2);
    stringObject = temp;

    stringAppendCharacter(stringObject->value.string, ')');

    gcRequestMemory(gc, sizeof(struct Object) + sizeof(struct String) + stringObject->value.string->characterCount * sizeof(Char));
    gcRegisterObject(gc, stringObject);

    return stringObject;
}

void pairMark(struct Pair *pair)
{
    objectMark(pair->first);
    objectMark(pair->second);
}
