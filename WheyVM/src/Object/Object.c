#include "Object.h"
#include <assert.h>

void opONew(uint8_t type, struct Object *newObject)
{
    assert(type < OBJECT_NUM_TYPES);

    switch (type)
    {
    case OBJECT_TYPE_BOOLEAN:
        newObject = booleanNew();
        break;
    case OBJECT_TYPE_INTEGER:
        newObject = integerNew();
        break;
    case OBJECT_TYPE_FLOAT:
        newObject = floatNew();
        break;
    case OBJECT_TYPE_LAMBDA:
        newObject = lambdaNew();
        break;
    case OBJECT_TYPE_ARRAY:
        newObject = arrayNew(ARRAY_INITIAL_SIZE);
        break;
    case OBJECT_TYPE_MAP:
        newObject = mapNew(MAP_INITIAL_SIZE);
        break;
    case OBJECT_TYPE_PAIR:
        newObject = pairNew();
        break;
    default:
        break;
    }
}

void opOConst(uint16_t constantPoolIndex, struct Object *constObject)
{
    constObject = objectConstant(constantPoolIndex);
}

void opOCopy(struct Object *object, struct Object *copy)
{
    copy = objectCopy(object);
}

void opOEq(struct Object *object1, struct Object *object2, struct Object *isEqual)
{
    isEqual = objectNew(OBJECT_TYPE_BOOLEAN);
    isEqual->value.integer_value = objectEqual(object1, object2);
}

void opOHash(struct Object *object, struct Object *hash)
{
    hash = objectNew(OBJECT_TYPE_INTEGER);
    hash->value.integer_value = (int64_t)objectHash(object);
}

void opOToString(struct Object *object, struct Object *string)
{
    string = objectToString(object);
}

struct Object *objectNew(uint8_t type)
{
    struct Object *object;
    object = (struct Object *)malloc(sizeof(struct Object));
    assert(object != NULL);
    object->mark = OBJECT_MARK_FALSE;
    object->type = type;

    gcRegisterObject(object);

    return object;
}

struct Object *objectConstant(uint16_t constantPoolIndex)
{
    
}

struct Object *objectCopy(struct Object *object)
{
    if (object == NULL)
    {
        return NULL;
    }

    switch (object->type)
    {
    case OBJECT_TYPE_BOOLEAN:
        return booleanCopy(object->value.integer_value);

    case OBJECT_TYPE_INTEGER:
        return integerCopy(object->value.integer_value);

    case OBJECT_TYPE_FLOAT:
        return floatCopy(object->value.float_value);

    case OBJECT_TYPE_LAMBDA:
        return lambdaCopy(object->value.lambda);

    case OBJECT_TYPE_ARRAY:
        return arrayCopy(object->value.array);

    case OBJECT_TYPE_MAP:
        return mapCopy(object->value.map);

    case OBJECT_TYPE_PAIR:
        return pairCopy(object->value.pair);

    }

    return NULL;

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
    case OBJECT_TYPE_BOOLEAN:
        return booleanEquals(object1->value.integer_value, object2->value.integer_value);

    case OBJECT_TYPE_INTEGER:
        return integerEquals(object1->value.integer_value, object2->value.integer_value);

    case OBJECT_TYPE_FLOAT:
        return floatEquals(object1->value.float_value, object2->value.float_value);

    case OBJECT_TYPE_LAMBDA:
        return lambdaEquals(object1->value.lambda, object2->value.lambda);

    case OBJECT_TYPE_ARRAY:
        return arrayEquals(object1->value.array, object2->value.array);

    case OBJECT_TYPE_MAP:
        return mapEquals(object1->value.map, object2->value.map);

    case OBJECT_TYPE_PAIR:
        return pairEquals(object1->value.pair, object2->value.pair);

    }
}

size_t objectHash(struct Object *object)
{
    if (object == NULL)
        return 0;

    switch (object->type)
    {
    case OBJECT_TYPE_BOOLEAN:
        return booleanHash(object->value.integer_value);

    case OBJECT_TYPE_INTEGER:
        return integerHash(object->value.integer_value);

    case OBJECT_TYPE_FLOAT:
        return floatHash(object->value.float_value);

    case OBJECT_TYPE_LAMBDA:
        return lambdaHash(object->value.lambda);

    case OBJECT_TYPE_ARRAY:
        return arrayHash(object->value.array);

    case OBJECT_TYPE_MAP:
        return mapHash(object->value.map);

    case OBJECT_TYPE_PAIR:
        return pairHash(object->value.pair);

    }
}

void objectToString(struct Object *object)
{
    struct Object *string = stringNew(STRING_INITIAL_SIZE);
    struct Array *charArray = string->value.array;

    if (object == NULL)
        arrayPushChar(charArray, 'n');
        arrayPushChar(charArray, 'u');
        arrayPushChar(charArray, 'l');
        arrayPushChar(charArray, 'l');
    return;

    char buffer[OBJECT_serialization_BUFFER_SIZE];

    switch (object->type)
    {
    case OBJECT_TYPE_ARRAY:
        arraySerialize(object->value.array, serialization);
        return;
    case OBJECT_TYPE_MAP:
        mapSerialize(object->value.map, serialization);
        return;

    case OBJECT_TYPE_PAIR:
        pairSerialize(object->value.pair, serialization);
        return;
    case OBJECT_TYPE_FLOATING_POINT:

        int result = snprintf(buffer, OBJECT_serialization_BUFFER_SIZE, "%.10e", object->value.float_value);
        assert(result >= 0);
        break;

    case OBJECT_TYPE_BOOLEAN:

        if (object->value.integer_value)
        {
            int result = snprintf(buffer, OBJECT_serialization_BUFFER_SIZE, "True");
            assert(result >= 0);
        }
        else
        {
            int result = snprintf(buffer, OBJECT_serialization_BUFFER_SIZE, "False");
            assert(result >= 0);
        }

        break;

    case OBJECT_TYPE_INTEGER:

        int result = snprintf(buffer, OBJECT_serialization_BUFFER_SIZE, "%" PRId64, object->value.integer_value);
        assert(result >= 0);
        break;
    }

    for (size_t i = 0; i < OBJECT_serialization_BUFFER_SIZE; i++)
    {
        if (buffer[i] == '\0')
            break;

        arrayPushChar(charArray, buffer[i]);
    }
}

void objectMark(struct Object *object)
{
    if (object == NULL) return;

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
    if (object == NULL) return;

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