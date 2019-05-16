#include "Object.h"
#include <assert.h>

void opOCopy(struct Object *object, struct Object *copy, struct GC *gc)
{
    objectCopy(object, copy);
}

void opOEq(struct Object *object1, struct Object *object2, struct Object *isEqual, struct GC *gc)
{
    objectNew(isEqual, OBJECT_TYPE_BOOLEAN);
    isEqual->value.integer_value = objectEqual(object1, object2);
}

void opONeq(struct Object *object1, struct Object *object2, struct Object *isNotEqual, struct GC *gc)
{
    objectNew(isNotEqual, OBJECT_TYPE_BOOLEAN);
    isNotEqual->value.integer_value = !objectEqual(object1, object2);
}

void opOHash(struct Object *object, struct Object *hash)
{
    objectNew(hash, OBJECT_TYPE_INTEGER);
    hash->value.integer_value = objectHash(object);
}

void opOString(struct Object *object, struct Object *string)
{
    objectNew(string, OBJECT_TYPE_ARRAY);
    arrayNew(string->value.array, OBJECT_STRING_BUFFER_SIZE);

    objectToString(object, string->value.array);
}

void objectNew(struct Object *object, uint8_t type)
{
    object = (struct Object *)malloc(sizeof(struct Object));
    assert(object != NULL);
    object->type = type;
    object->mark = OBJECT_MARK_FALSE;

    gcRegisterObject(getGC(), object);
}

void objectCopy(struct Object *object, struct Object *copy)
{
    if (object == NULL)
    {
        return;
    }

    switch (object->type)
    {
    case OBJECT_TYPE_ARRAY:
        arrayNew(copy, object->value.array->objectCount);
        arrayCopy(object->value.array, copy->value.array);
        return;

    case OBJECT_TYPE_DOUBLE:
        objectNew(copy, OBJECT_TYPE_DOUBLE);
        copy->value.double_value = object->value.double_value;
        return;

    case OBJECT_TYPE_MAP:
        mapNew(copy, object->value.map->pairCount);
        mapCopy(object->value.map, copy->value.map);
        return;

    case OBJECT_TYPE_PAIR:
        pairNew(copy);
        pairCopy(object->value.pair, copy->value.pair);
        return;

    case OBJECT_TYPE_BOOLEAN:
    case OBJECT_TYPE_INTEGER:
        objectNew(copy, object->type);
        copy->value.integer_value = object->value.integer_value;
        return;
    }
}

bool objectEquals(struct Object *object1, struct Object *object2)
{
    if (object1 == object2)
    {
        return true;
    }

    if (object1 == NULL)
    {
        return false;
    }

    if (object2 == NULL)
    {
        return false;
    }

    if (object1->type != object2->type)
    {
        return false;
    }

    switch (object1->type)
    {
    case OBJECT_TYPE_ARRAY:
        return arrayEquals(object1->value.array, object2->value.array);
    case OBJECT_TYPE_MAP:
        return mapEquals(object1->value.map, object2->value.map);
    case OBJECT_TYPE_PAIR:
        return pairEquals(object1->value.pair, object2->value.pair);
    case OBJECT_TYPE_DOUBLE:
        return object1->value.double_value == object2->value.double_value;
    case OBJECT_TYPE_BOOLEAN:
    case OBJECT_TYPE_INTEGER:
        return object1->value.integer_value == object2->value.integer_value;
    }
}

size_t objectHash(struct Object *object)
{
    if (object == NULL)
        return 0;

    switch (object->type)
    {
    case OBJECT_TYPE_ARRAY:
        return arrayHash(object->value.array);
    case OBJECT_TYPE_MAP:
        return mapHash(object->value.map);
    case OBJECT_TYPE_PAIR:
        return pairHash(object->value.pair);
    case OBJECT_TYPE_DOUBLE:
        return (size_t)object->value.double_value;
    case OBJECT_TYPE_BOOLEAN:
    case OBJECT_TYPE_INTEGER:
        return (size_t)object->value.integer_value;
    }
}

void objectToString(struct Object *object, struct Object *string)
{
    arrayNew(string, OBJECT_STRING_BUFFER_SIZE);
    struct Array *charArray = string->value.array;

    if (object == NULL)
        arrayPushChar(charArray, 'n');
        arrayPushChar(charArray, 'u');
        arrayPushChar(charArray, 'l');
        arrayPushChar(charArray, 'l');
        return;

    char buffer[OBJECT_STRING_BUFFER_SIZE];

    switch (object->type)
    {
    case OBJECT_TYPE_ARRAY:
        arrayToString(object->value.array, string);
        return;
    case OBJECT_TYPE_MAP:
        mapToString(object->value.map, string);
        return;
    
    case OBJECT_TYPE_PAIR:
        pairToString(object->value.pair, string);
        return; 
    case OBJECT_TYPE_DOUBLE:

        int result = snprintf(buffer, OBJECT_STRING_BUFFER_SIZE, "%.10e", object->value.double_value);
        assert(result >= 0);
        break;

    case OBJECT_TYPE_BOOLEAN:

        if (object->value.integer_value)
        {
            int result = snprintf(buffer, OBJECT_STRING_BUFFER_SIZE, "True");
            assert(result >= 0);
        }
        else
        {
            int result = snprintf(buffer, OBJECT_STRING_BUFFER_SIZE, "False");
            assert(result >= 0);
        }

        break;

    case OBJECT_TYPE_INTEGER:

        int result = snprintf(buffer, OBJECT_STRING_BUFFER_SIZE, "%" PRId64, object->value.integer_value);
        assert(result >= 0);
        break;
    }

    for (size_t i = 0; i < OBJECT_STRING_BUFFER_SIZE; i++)
    {
        if (buffer[i] == '\0')
            break;

        arrayPushChar(charArray, buffer[i]);
    }
}

void objectMark(struct Object *object)
{
    if (object->mark == OBJECT_MARK_TRUE)
        return;

    object->mark = OBJECT_MARK_TRUE;

    switch (object->type)
    {
    case OBJECT_TYPE_ARRAY:
        arrayMark(object->value.array);
        return;
    case OBJECT_TYPE_MAP:
        mapMark(object->value.map);
        return;
    case OBJECT_TYPE_PAIR:
        pairMark(object->value.pair);
        return;
    }
}

void objectFree(struct Object *object)
{
    switch (object->type)
    {
    case OBJECT_TYPE_ARRAY:
        arrayFree(object->value.array);
        return;
    case OBJECT_TYPE_MAP:
        mapFree(object->value.map);
        return;
    case OBJECT_TYPE_PAIR:
        pairFree(object->value.pair);
        return;
    }

    free(object);
}