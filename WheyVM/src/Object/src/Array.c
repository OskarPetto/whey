#include "../Array.h"
#include "../Object.h"
#include "../Integer.h"

#include <assert.h>
#include <stdlib.h>

static Integer getNextLargerSlotCount(Integer slotCount)
{
    return slotCount + (slotCount >> 1) + 1;
}

struct Object *arrayNew(struct Gc *gc, Integer initialObjectCount)
{
    Integer slotCount = getNextLargerSlotCount(initialObjectCount);
    struct Object *object = objectNew(gc, OBJECT_TYPE_ARRAY);
    object->value.array->objects = (struct Object **)malloc(slotCount * sizeof(struct Object *));
    assert(object->value.array->objects != NULL);
    object->value.array->slotCount = slotCount;
    object->value.array->objectCount = initialObjectCount;
    return object;
}

Integer arraySize(struct Array *array)
{
    return array->objectCount;
}

struct Object *arrayGet(struct Array *array, Integer index)
{
    return array->objects[index];
}

struct Object *arraySet(struct Array *array, Integer index, struct Object *setObject)
{
    struct Object *currentObject = array->objects[index];
    array->objects[index] = setObject;
    return currentObject;
}

void arrayInsert(struct Array *array, Integer index, struct Object *insertObject)
{
    array->objectCount++;

    if (array->objectCount > array->slotCount)
    {
        array->slotCount = getNextLargerSlotCount(array->objectCount);

        array->objects = (struct Object **)realloc(array->objects,
                                                   array->slotCount * sizeof(struct Object *));

        assert(array->objects != NULL);
    }

    for (Integer i = array->objectCount; i > index; i--)
    {
        array->objects[i] = array->objects[i - 1];
    }

    array->objects[index] = insertObject;

}

void arrayInsertAll(struct Array *array, Integer index, struct Array *insertArray)
{
    if (insertArray->objectCount == 0)
    {
        return;
    }

    Integer insertObjectCount = insertArray->objectCount;
    struct Object **insertObjects = (struct Object **) malloc(insertObjectCount * sizeof(struct Object *));

    for (Integer i = 0; i < insertObjectCount; i++)
    {
        insertObjects[i] = insertArray->objects[i];
    }

    Integer newObjectCount = array->objectCount + insertObjectCount;

    if (newObjectCount > array->slotCount)
    {
        array->slotCount = getNextLargerSlotCount(newObjectCount);

        array->objects = (struct Object **)realloc(array->objects,
                                                   array->slotCount * sizeof(struct Object *));

        assert(array->objects != NULL);
    }

    for (Integer i = array->objectCount - 1; i >= index; i--)
    {
        array->objects[insertObjectCount + i] = array->objects[i];
    }

    for (Integer i = 0; i < insertObjectCount; i++)
    {
        array->objects[index + i] = insertObjects[i];
    }

    free(insertObjects);

    array->objectCount = newObjectCount;
}

struct Object *arrayRemove(struct Array *array, Integer index)
{
    struct Object *removeObject = array->objects[index];

    for (Integer i = index; i < array->objectCount - 1; i++)
    {
        array->objects[i] = array->objects[i + 1];
    }

    array->objectCount--;

    return removeObject;
}

struct Object *arrayCopy(struct Gc *gc, struct Array *array)
{
    struct Object *copy = arrayNew(gc, array->objectCount);

    for (Integer i = 0; i < array->objectCount; i++)
    {
        copy->value.array->objects[i] = objectCopy(gc, array->objects[i]);
    }

    return copy;
}

Integer arrayEquals(struct Array *array1, struct Array *array2)
{
    if (array1->objectCount != array2->objectCount)
    {
        return BOOLEAN_FALSE;
    }

    for (Integer i = 0; i < array1->objectCount; i++)
    {
        if (!objectEquals(array1->objects[i], array2->objects[i]))
        {
            return BOOLEAN_FALSE;
        }
    }

    return BOOLEAN_TRUE;
}

Integer arrayHash(struct Array *array)
{
    Integer hash = 1;

    for (Integer i = 0; i < array->objectCount; i++)
    {
        hash = 31 * hash + objectHash(array->objects[i]);
    }

    return hash;
}

struct Object *arrayToString(struct Gc *gc, struct Array *array)
{
    struct Object *stringObject = stringNew(gc, 0);
    struct Array *string = stringObject->value.array;

    stringAppendCharacter(string, '[');

    for (Integer i = 0; i < array->objectCount; i++)
    {
        struct Object *subStringObject = objectToString(NULL, array->objects[i]);

        struct Array *subString = subStringObject->value.array;

        arrayInsertAll(string, string->objectCount, subString);

        objectFree(subStringObject);
    }

    if (array->objectCount > 0)
    {
        struct Object *lastInteger = integerNew(NULL, ']');
        string->objects[string->objectCount - 1] = lastInteger;
    }
    else
    {
        stringAppendCharacter(string, ']');
    }

    return stringObject;    
}

void arrayMark(struct Array *array)
{
    for (Integer i = 0; i < array->objectCount; i++)
    {
        objectMark(array->objects[i]);
    }
}

void arrayFree(struct Array *array)
{
    free(array->objects);
}

struct Object *stringNew(struct Gc *gc, Integer initialObjectCount)
{
    struct Object *string = arrayNew(gc, initialObjectCount);
    string->type = OBJECT_TYPE_STRING;
    return string;
}

struct Object *stringFromArray(struct Gc *gc, struct Array *array)
{
    return stringCopy(gc, array);
}

struct Object *stringToArray(struct Gc *gc, struct Array *string)
{
    struct Object *array = stringNew(gc, string->objectCount);

    for (Integer i = 0; i < string->objectCount; i++)
    {
        array->value.array->objects[i] = integerNew(gc, string->objects[i]->value.integer_value);
    }
    
    return array;
}

Integer stringCompare(struct Array *array1, struct Array *array2)
{
    Integer l1 = array1->objectCount;
    Integer l2 = array2->objectCount;

    Integer minL = l1 <= l2 ? l1 : l2;

    for (Integer i = 0; i < minL; i++)
    {
        char c1 = (char) array1->objects[i]->value.integer_value;
        char c2 = (char) array2->objects[i]->value.integer_value;

        if (c1 != c2) 
        {
            return c1 - c2;
        }
    }

    return l1 - l2;
}

struct Object *stringCopy(struct Gc *gc, struct Array *string)
{
    struct Object *copy = stringNew(gc, string->objectCount);

    for (Integer i = 0; i < string->objectCount; i++)
    {
        copy->value.array->objects[i] = integerNew(NULL, (char) string->objects[i]->value.integer_value);
    }

    return copy;
}

Integer stringEquals(struct Array *string1, struct Array *string2)
{
    if (string1->objectCount != string2->objectCount)
    {
        return BOOLEAN_FALSE;
    }

    for (Integer i = 0; i < string1->objectCount; i++)
    {
        if (string1->objects[i]->value.integer_value != string2->objects[i]->value.integer_value)
        {
            return BOOLEAN_FALSE;
        }
    }

    return BOOLEAN_TRUE;
}

Integer stringHash(struct Array *string)
{
    Integer hash = 1;

    for (Integer i = 0; i < string->objectCount; i++)
    {
        hash = 31 * hash + string->objects[i]->value.integer_value;
    }

    return hash;
}

void stringAppendCharacter(struct Array *string, char character)
{
    struct Object *characterObject = integerNew(NULL, (Integer) character);
    arrayInsert(string, string->objectCount, characterObject);
}

void stringFree(struct Array *string)
{
    for (Integer i = 0; i < string->objectCount; i++)
    {
        objectFree(string->objects[i]);
    }

    free(string->objects);
}