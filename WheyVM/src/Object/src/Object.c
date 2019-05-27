#include "../Object.h"

#include "../Integer.h"
#include "../Double.h"

#include <assert.h>
#include <stdlib.h>

struct Object *objectCopy(struct Gc *gc, struct Object *object)
{
    if (object == NULL)
    {
        return NULL;
    }

    switch (object->type)
    {
    case OBJECT_TYPE_INTEGER:
        return integerNew(gc, object->value.integerValue);

    case OBJECT_TYPE_DOUBLE:
        return doubleNew(gc, object->value.doubleValue);

    case OBJECT_TYPE_ARRAY:
        return arrayCopy(gc, object->value.array);

    case OBJECT_TYPE_STRING:
        return stringCopy(gc, object->value.array);

    case OBJECT_TYPE_MAP:
        return mapCopy(gc, object->value.map);

    case OBJECT_TYPE_PAIR:
        return pairCopy(gc, object->value.pair);

    }

    return NULL;
}

Integer objectEquals(struct Object *object1, struct Object *object2)
{
    if (object1 == object2)
    {
        return BOOLEAN_TRUE;
    }

    if (object1 == NULL || object2 == NULL)
    {
        return BOOLEAN_FALSE;
    }

    if (object1->type != object2->type)
    {
        return BOOLEAN_FALSE;
    }

    switch (object1->type)
    {
    case OBJECT_TYPE_INTEGER:
        return object1->value.integerValue == object2->value.integerValue;

    case OBJECT_TYPE_DOUBLE:
        return object1->value.doubleValue == object2->value.doubleValue;

    case OBJECT_TYPE_ARRAY:
        return arrayEquals(object1->value.array, object2->value.array);

    case OBJECT_TYPE_STRING:
        return stringEquals(object1->value.array, object2->value.array);

    case OBJECT_TYPE_MAP:
        return mapEquals(object1->value.map, object2->value.map);

    case OBJECT_TYPE_PAIR:
        return pairEquals(object1->value.pair, object2->value.pair);
    
    }

    return BOOLEAN_FALSE;
}

Integer objectHash(struct Object *object)
{
    if (object == NULL)
        return 0;

    switch (object->type)
    {
    case OBJECT_TYPE_INTEGER:
        return object->value.integerValue;

    case OBJECT_TYPE_DOUBLE:
        return object->value.integerValue; //nonsense

    case OBJECT_TYPE_ARRAY:
        return arrayHash(object->value.array);

    case OBJECT_TYPE_STRING:
        return stringHash(object->value.array);

    case OBJECT_TYPE_MAP:
        return mapHash(object->value.map);

    case OBJECT_TYPE_PAIR:
        return pairHash(object->value.pair);

    }

    return 0;
}

struct Object *objectToString(struct Gc *gc, struct Object *object)
{

    if (object == NULL)
    {
        return stringNew(gc, "null");
    }

    switch (object->type)
    {
    case OBJECT_TYPE_INTEGER:
        return integerToString(gc, object->value.integerValue);

    case OBJECT_TYPE_DOUBLE:
        return doubleToString(gc, object->value.doubleValue);

    case OBJECT_TYPE_ARRAY:
        return arrayToString(gc, object->value.array);

    case OBJECT_TYPE_STRING:
        return stringCopy(gc, object->value.array);  // copy

    case OBJECT_TYPE_MAP:
        return mapToString(gc, object->value.map);

    case OBJECT_TYPE_PAIR:
        return pairToString(gc, object->value.pair);
    
    }

    return NULL;
}

struct Object *objectNew(struct Gc *gc, uint8_t type)
{
    struct Object *object = (struct Object *)malloc(sizeof(struct Object));
    assert(object != NULL);
    object->mark = OBJECT_MARK_FALSE;
    object->type = type;

    if (gc != NULL)
    {
        gcRegisterObject(gc, object);
    }

    return object;
}

void objectMark(struct Object *object)
{
    if (object == NULL)
        return;

    if (object->mark == OBJECT_MARK_TRUE)
        return;

    object->mark = OBJECT_MARK_TRUE;

    switch (object->type)
    {
    case OBJECT_TYPE_ARRAY:
        arrayMark(object->value.array);
        break;
    case OBJECT_TYPE_MAP:
        mapMark(object->value.map);
        break;
    case OBJECT_TYPE_PAIR:
        pairMark(object->value.pair);
        break;
    }
}

void objectFree(struct Object *object)
{
    if (object == NULL)
        return;

    switch (object->type)
    {
    case OBJECT_TYPE_ARRAY:
        arrayFree(object->value.array);
        break;
    case OBJECT_TYPE_MAP:
        mapFree(object->value.map);
        break;
    case OBJECT_TYPE_PAIR:
        free(object->value.pair);
        break;
    case OBJECT_TYPE_STRING:
        stringFree(object->value.array);
        break;
    }

    free(object);
}