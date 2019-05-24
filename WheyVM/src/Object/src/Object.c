#include "../Object.h"

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
        return integerNew(gc, object->value.integer_value);

    case OBJECT_TYPE_FLOATING:
        return floatingNew(gc, object->value.floating_value);

    case OBJECT_TYPE_ARRAY:
        return arrayCopy(gc, object->value.array);

    case OBJECT_TYPE_MAP:
        return mapCopy(gc, object->value.map);

    case OBJECT_TYPE_PAIR:
        return pairCopy(gc, object->value.pair);

    case OBJECT_TYPE_STRING:
        return stringCopy(gc, object->value.string);
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
        return object1->value.integer_value == object2->value.integer_value;

    case OBJECT_TYPE_FLOATING:
        return object1->value.floating_value == object2->value.floating_value;

    case OBJECT_TYPE_ARRAY:
        return arrayEquals(object1->value.array, object2->value.array);

    case OBJECT_TYPE_MAP:
        return mapEquals(object1->value.map, object2->value.map);

    case OBJECT_TYPE_PAIR:
        return pairEquals(object1->value.pair, object2->value.pair);
    
    case OBJECT_TYPE_STRING:
        return stringEquals(object1->value.string, object2->value.string);
    
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
        return object->value.integer_value;

    case OBJECT_TYPE_FLOATING:
        return object->value.integer_value; //nonsense

    case OBJECT_TYPE_ARRAY:
        return arrayHash(object->value.array);

    case OBJECT_TYPE_MAP:
        return mapHash(object->value.map);

    case OBJECT_TYPE_PAIR:
        return pairHash(object->value.pair);

    case OBJECT_TYPE_STRING:
        return stringHash(object->value.string);
    }

    return 0;
}

struct Object *objectToString(struct Gc *gc, struct Object *object)
{

    if (object == NULL)
    {
        struct Object *stringObject = stringNew(gc, 4);
        struct String *string = stringObject->value.string;
        string->characters[0] = 'n';
        string->characters[1] = 'u';
        string->characters[2] = 'l';
        string->characters[3] = 'l';
        return stringObject;
    }

    switch (object->type)
    {
    case OBJECT_TYPE_INTEGER:
        return integerToString(gc, object->value.integer_value);

    case OBJECT_TYPE_FLOATING:
        return floatingToString(gc, object->value.floating_value);

    case OBJECT_TYPE_ARRAY:
        return arrayToString(gc, object->value.array);

    case OBJECT_TYPE_MAP:
        return mapToString(gc, object->value.map);

    case OBJECT_TYPE_PAIR:
        return pairToString(gc, object->value.pair);
    
    case OBJECT_TYPE_STRING:
        return object;  // No copy
    
    }

    return NULL;
}

struct Object *objectNew(struct Gc *gc, uint8_t type)
{
    struct Object *object;
    object = (struct Object *)malloc(sizeof(struct Object));
    assert(object != NULL);
    object->mark = OBJECT_MARK_TRUE;
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
    case OBJECT_TYPE_STRING:
        stringMark(object->value.string);
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
    case OBJECT_TYPE_STRING:
        stringFree(object->value.string);
        break;
    }

    free(object);
}