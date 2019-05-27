#include "../Array.h"
#include "../Object.h"
#include "../Integer.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static Integer getNextLargerSlotCount(Integer slotCount)
{
    return slotCount + (slotCount >> 1) + 1;
}

struct Object *arrayNew(struct Gc *gc, Integer initialObjectCount)
{
    Integer slotCount = getNextLargerSlotCount(initialObjectCount);
    struct Object *object = objectNew(gc, OBJECT_TYPE_ARRAY);
    object->value.array = (struct Array *) malloc(sizeof(struct Array));
    assert(object->value.array != NULL);
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

    for (Integer i = array->objectCount - 1; i > index; i--)
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
    struct Object *stringObject = stringNew(gc, "");
    struct Array *string = stringObject->value.array;

    stringAppendCharacter(string, '[');

    for (Integer i = 0; i < array->objectCount; i++)
    {
        struct Object *subStringObject = objectToString(NULL, array->objects[i]);

        struct Array *subString = subStringObject->value.array;

        arrayInsertAll(string, string->objectCount, subString);

        stringAppendCharacter(string, ',');

        free(subString->objects);
        free(subString);
        free(subStringObject);
    }

    if (array->objectCount > 0)
    {

        free(arrayRemove(string, string->objectCount - 1));
        stringAppendCharacter(string, ']');
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
    free(array);

}

struct Object *stringNew(struct Gc *gc, char *characters)
{
    Integer initialObjectCount = strlen(characters);

    struct Object *string = arrayNew(gc, initialObjectCount);
    string->type = OBJECT_TYPE_STRING;

    for (Integer i = 0; i < initialObjectCount; i++)
    {
        string->value.array->objects[i] = integerNew(NULL, characters[i]);
    }

    return string;
}

struct Object *stringFromArray(struct Gc *gc, struct Array *array)
{
    return stringCopy(gc, array);
}

struct Object *stringToArray(struct Gc *gc, struct Array *string)
{
    struct Object *array = arrayNew(gc, string->objectCount);

    for (Integer i = 0; i < string->objectCount; i++)
    {
        array->value.array->objects[i] = integerNew(gc, (char) string->objects[i]->value.integerValue);
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
        char c1 = (char) array1->objects[i]->value.integerValue;
        char c2 = (char) array2->objects[i]->value.integerValue;

        if (c1 != c2) 
        {
            return c1 - c2;
        }
    }

    return l1 - l2;
}

struct Object *stringCopy(struct Gc *gc, struct Array *string)
{
    char *buffer = (char *)malloc((string->objectCount + 1)* sizeof(char)); 
    assert(buffer != NULL);

    for (size_t i = 0; i < string->objectCount; i++)
    {
        buffer[i] = (char) string->objects[i]->value.integerValue;
    }

    buffer[string->objectCount] = '\0';

    struct Object *copy = stringNew(gc, buffer);

    free(buffer);

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
        if (string1->objects[i]->value.integerValue != string2->objects[i]->value.integerValue)
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
        hash = 31 * hash + string->objects[i]->value.integerValue;
    }

    return hash;
}

void stringAppendCharacter(struct Array *string, char character)
{
    struct Object *characterObject = integerNew(NULL, (Integer) character);
    arrayInsert(string, string->objectCount, characterObject);
}

void stringPrint(struct Array *string)
{
    for (Integer i = 0; i < string->objectCount; i++)
    {
        printf("%c", string->objects[i]->value.integerValue);
    }
    printf("\n");
}

void stringFree(struct Array *string)
{
    for (Integer i = 0; i < string->objectCount; i++)
    {
        if (string->objects[i] != NULL) 
        {
            free(string->objects[i]);
        }
    }

    free(string->objects);
    free(string);
}