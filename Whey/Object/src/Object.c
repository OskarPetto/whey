#include "../Object.h"
#include "../Gc.h"
#include "../Integer.h"
#include "../Double.h"
#include "../String.h"
#include "../Array.h"
#include "../Map.h"
#include "../Pair.h"

#include <stdlib.h>
#include <string.h>

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
        return arrayCopy(gc, object);

    case OBJECT_TYPE_STRING:
        return stringCopy(gc, object);

    case OBJECT_TYPE_MAP:
        return mapCopy(gc, object);

    case OBJECT_TYPE_PAIR:
        return pairCopy(gc, object);

    default:
        OBJECT_UNKNOWN_TYPE(object);
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

    // mark bit is false
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
        return arrayEquals(object1, object2);

    case OBJECT_TYPE_STRING:
        return stringEquals(object1, object2);

    case OBJECT_TYPE_MAP:
        return mapEquals(object1, object2);

    case OBJECT_TYPE_PAIR:
        return pairEquals(object1, object2);
    
    default:
        OBJECT_UNKNOWN_TYPE(object1);
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
        return arrayHash(object);

    case OBJECT_TYPE_STRING:
        return stringHash(object);

    case OBJECT_TYPE_MAP:
        return mapHash(object);

    case OBJECT_TYPE_PAIR:
        return pairHash(object);
    
    default:
        OBJECT_UNKNOWN_TYPE(object);
    }

    return 0;
}

struct Object *objectToString(struct Gc *gc, struct Object *object)
{
    if (object == NULL)
    {
        struct Object * stringObject = stringNew(gc, 4);
        uint32_t index = 0;

        objectWriteToString(object, stringObject, &index);
        return stringObject;
    }

    switch (object->type)
    {
    case OBJECT_TYPE_INTEGER:
        return integerToString(gc, object);

    case OBJECT_TYPE_DOUBLE:
        return doubleToString(gc, object);

    case OBJECT_TYPE_ARRAY:
        return arrayToString(gc, object);

    case OBJECT_TYPE_STRING:
        return object;  // identity

    case OBJECT_TYPE_MAP:
        return mapToString(gc, object);

    case OBJECT_TYPE_PAIR:
        return pairToString(gc, object);

    default:
        OBJECT_UNKNOWN_TYPE(object);    
    }

    return NULL;
}

void objectMark(struct Object *object)
{
    if (object == NULL)
        return;

    if (object->type & OBJECT_MARK)
        return;

    uint8_t type = object->type;

    object->type |= OBJECT_MARK;

    switch (type)
    {
    case OBJECT_TYPE_ARRAY:
        arrayMark(object);
        break;
    case OBJECT_TYPE_MAP:
        mapMark(object);
        break;
    case OBJECT_TYPE_PAIR:
        pairMark(object);
        break;
    }
}

void objectFree(struct Gc *gc, struct Object *object)
{
    if (object == NULL)
        return;
        
    switch (object->type)
    {
    case OBJECT_TYPE_DOUBLE:
        doubleFree(gc, object);
        break;
    case OBJECT_TYPE_INTEGER:
        integerFree(gc, object);
        break;
    case OBJECT_TYPE_ARRAY:
        arrayFree(gc, object);
        break;
    case OBJECT_TYPE_MAP:
        mapFree(gc, object);
        break;
    case OBJECT_TYPE_PAIR:
        pairFree(gc, object);
        break;
    case OBJECT_TYPE_STRING:
        stringFree(gc, object);
        break;
    default:
        OBJECT_UNKNOWN_TYPE(object);
    }

}

uint32_t objectStringCharacterCount(struct Object *object)
{
    if (object == NULL)
        return 4;

    switch (object->type)
    {
    case OBJECT_TYPE_ARRAY:
        return arrayStringCharacterCount(object);
    case OBJECT_TYPE_DOUBLE:
        return doubleStringCharacterCount(object);
    case OBJECT_TYPE_INTEGER:
        return integerStringCharacterCount(object);
    case OBJECT_TYPE_MAP:
        return mapStringCharacterCount(object);
    case OBJECT_TYPE_PAIR:
        return pairStringCharacterCount(object);
    case OBJECT_TYPE_STRING:
        return stringCharacterCount(object);
    default:
        OBJECT_UNKNOWN_TYPE(object);
    }
    return 0;
}

void objectWriteToString(struct Object *object, struct Object *stringObject, uint32_t *index)
{
    if (object == NULL)
    {
        struct String *string = stringObject->value.subObject;
        string->characters[(*index)++] = 'n';
        string->characters[(*index)++] = 'u';
        string->characters[(*index)++] = 'l';
        string->characters[(*index)++] = 'l';
        return;
    }

    switch (object->type)
    {
    case OBJECT_TYPE_ARRAY:
        arrayWriteToString(object, stringObject, index);
        break;
    case OBJECT_TYPE_DOUBLE:
        doubleWriteToString(object, stringObject, index);
        break;
    case OBJECT_TYPE_INTEGER:
        integerWriteToString(object, stringObject, index);
        break;
    case OBJECT_TYPE_MAP:
        mapWriteToString(object, stringObject, index);
        break;
    case OBJECT_TYPE_PAIR:
        pairWriteToString(object, stringObject, index);
        break;
    case OBJECT_TYPE_STRING:
        stringWriteToString(object, stringObject, index);
        break;
    default:
        OBJECT_UNKNOWN_TYPE(object);
    }
    
}