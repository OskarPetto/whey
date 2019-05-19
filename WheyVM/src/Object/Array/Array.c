#include "Array.h"

struct Object *arrayConst(struct String *stringConstant)
{
    struct Object *array = arrayNew(stringConstant->characterCount);
    for (size_t i = 0; i < stringConstant->characterCount; i++)
    {
        array->value.array->objects[i] = integerNew((Integer)stringConstant->characters[i]);
    }
}

size_t arraySize(struct Array *array)
{
    return (size_t)array->objectCount;
}

struct Object *arrayGet(struct Array *array, size_t index)
{
    return array->objects[index];
}

struct Object *arraySet(struct Array *array, size_t index, struct Object *setObject)
{
    struct Object *currentObject = array->objects[index];
    array->objects[index] = setObject;
    return currentObject;
}

void arrayInsert(struct Array *array, size_t index, struct Array *insertObject)
{
    if (array->objectCount >= (size_t)(((double)array->slotCount) * ARRAY_GROW_AT))
    {
        array->slotCount *= 2;

        if (array->slotCount == 0)
        {
            array->slotCount = 1;
        }

        array->objects = (struct Object **)realloc(array->objects,
                                                   array->slotCount * sizeof(struct Object *));

        assert(array->objects != NULL);
    }

    for (size_t i = array->objectCount; i > index; i--)
    {
        array->objects[i] = array->objects[i - 1];
    }

    array->objects[index] = insertObject;

    array->objectCount++;
}

void arrayInsertAll(struct Array *array, size_t index, struct Array *insertArray)
{
    size_t newObjectCount = array->objectCount + insertArray->objectCount;

    if (newObjectCount >= (size_t)(((double)array->slotCount) * ARRAY_GROW_AT))
    {
        array->slotCount = newObjectCount * 2;

        array->objects = (struct Object **)realloc(array->objects,
                                                   array->slotCount * sizeof(struct Object *));

        assert(array->objects != NULL);
    }

    for (size_t i = index; i < array->objectCount; i++)
    {
        array->objects[insertArray->objectCount + i] = array->objects[i];
    }

    for (size_t i = index; i < insertArray->objectCount; i++)
    {
        array->objects[i] = insertArray->objects[i];
    }

    array->objectCount = newObjectCount;
}

struct Object *arrayRemove(struct Array *array, size_t index)
{
    if (array->objectCount <= (size_t)(((double)array->slotCount) * ARRAY_SHRINK_AT))
    {
        array->slotCount /= 2;

        array->objects = (struct Object **)realloc(array->objects,
                                                   array->slotCount * sizeof(struct Object *));

        assert(array->objects != NULL);
    }

    struct Object *removeObject = array->objects[index];

    for (size_t i = index; i < array->objectCount - 1; i++)
    {
        array->objects[i] = array->objects[i + 1];
    }

    array->objectCount--;

    return removeObject;
}

void arrayForEach(struct WheyVM *wvm, struct Array *array, struct Lambda *lambda)
{
    for (size_t i = 0; i < array->objectCount; i++)
    {
        struct Object *boundLambda = lambdaBind(lambda, array->objects[i]);

        lambdaCall(wvm, boundLambda);
    }
}

void stringAppendCharacter(struct Array *array, Character character)
{
    struct Object *characterObject = integerNew((Integer)character);
    arrayInsert(array, array->objectCount, characterObject);
}

struct Object *arrayNew(size_t initialObjectCount)
{
    size_t slotCount = initialObjectCount * 2;
    struct Object *object = objectNew(OBJECT_TYPE_ARRAY);
    object->value.array->objects = (struct Object **)malloc(slotCount * sizeof(struct Object *));
    assert(object->value.array->objects != NULL);
    object->value.array->slotCount = slotCount;
    object->value.array->objectCount = initialObjectCount;
    return object;
}

struct Object *arrayLoad(struct Object *object)
{
    // per reference
    return object;
}

struct Object *arrayStore(struct Object *object)
{
    // per reference
    return object;
}

struct Object *arrayCopy(struct Object *object)
{
    struct Array *array = object->value.array;
    struct Object *copy = arrayNew(array->objectCount);

    for (size_t i = 0; i < array->objectCount; i++)
    {
        copy->value.array->objects[i] = objectCopy(array->objects[i]);
    }

    return copy;
}

Integer arrayEquals(struct Object *object1, struct Object *object2)
{
    struct Array *array1 = object1->value.array;
    struct Array *array2 = object2->value.array;

    if (array1 == array2)
    {
        return 1;
    }

    if (array1->objectCount != array2->objectCount)
    {
        return 0;
    }

    for (size_t i = 0; i < array1->objectCount; i++)
    {
        if (!objectEqual(array1->objects[i], array2->objects[i]))
        {
            return 0;
        }
    }

    return 1;
}

Integer arrayHash(struct Object *object)
{
    struct Array *array = object->value.array;

    Integer hash = ARRAY_START_HASH;

    for (size_t i = 0; i < array->objectCount; i++)
    {
        hash = ((hash << 5) + hash) + objectHash(array->objects[i]);
    }

    return hash;
}

struct Object *arrayToString(struct Object *object)
{
    struct Array *array = object->value.array;

    struct Object *string = arrayNew(array->objectCount);
    struct Array *charArray = string->value.array;

    stringAppendCharacter(charArray, '[');

    for (size_t i = 0; i < array->objectCount; i++)
    {
        struct Object *subString = objectToString(array->objects[i]);
        struct Array *subCharArray = subString->value.array;
        arrayInsertAll(charArray, charArray->objectCount, subCharArray);
    }

    if (array->objectCount > 0)
    {
        arrayRemove(string->value.array, string->value.array->objectCount - 1);
    }

    stringAppendCharacter(string->value.array, ']');

    return string;
}

void arrayMark(struct Object *object)
{
    struct Array *array = object->value.array;

    for (size_t i = 0; i < array->objectCount; i++)
    {
        objectMark(array->objects[i]);
    }
}

void arrayFree(struct Object *object)
{
    struct Array *array = object->value.array;

    for (size_t i = 0; i < array->objectCount; i++)
    {
        objectFree(array->objects[i]);
    }

    free(array->objects);
}
