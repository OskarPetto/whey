#include "Array.h"
#include <assert.h>

void opANew(struct Object *array)
{
    objectNew(array, OBJECT_TYPE_ARRAY);
    arrayInit(array->value.array, ARRAY_INITIAL_SIZE);
}

void opASize(struct Object *array, struct Object *size)
{
    assert(array != NULL);
    assert(array->type == OBJECT_TYPE_ARRAY);

    objectNew(size, OBJECT_TYPE_INTEGER);
    size->value.integer_value = arraySize(array);
}

void opAPush(struct Object *array, struct Object *pushObject)
{
    assert(array != NULL);
    assert(array->type == OBJECT_TYPE_ARRAY);

    arrayPush(array, pushObject);
}

void opAPop(struct Object *array, struct Object *popObject)
{
    assert(array != NULL);
    assert(array->type == OBJECT_TYPE_ARRAY);
    assert(array->value.array->objectCount > 0);

    popObject = arrayPop(array);
}

void opAGet(struct Object *array, struct Object *index, struct Object *getObject)
{
    assert(array != NULL);
    assert(index != NULL);
    assert(array->type == OBJECT_TYPE_ARRAY);
    assert(index->type == OBJECT_TYPE_INTEGER);
    assert(index->value.integer_value >= 0);
    assert(index->value.integer_value < array->value.array->objectCount);

    getObject = arrayGet(array, (size_t) index->value.integer_value);
}

void opAPut(struct Object *array, struct Object *index, struct Object *putObject)
{
    assert(array != NULL);
    assert(index != NULL);
    assert(array->type == OBJECT_TYPE_ARRAY);
    assert(index->type == OBJECT_TYPE_INTEGER);
    assert(index->value.integer_value >= 0);
    assert(index->value.integer_value < array->value.array->objectCount);

    arrayPut(array->value.array, index->value.integer_value, putObject);
}

void opAConcat(struct Object *array, struct Object *arrayToAdd)
{
    assert(array != NULL);
    assert(array->type == OBJECT_TYPE_ARRAY);

    if (arrayToAdd == NULL) return;

    assert(arrayToAdd->type == OBJECT_TYPE_ARRAY);
    
    arrayConcat(array->value.array, arrayToAdd->value.array);

}

size_t arraySize(struct Array *array) 
{
    return (size_t) array->objectCount;
}

void arrayPush(struct Array *array, struct Array *pushObject)
{
    if (array->objectCount >= (size_t) (((double) array->slotCount) * ARRAY_GROW_AT))
    {
        array->slotCount *= 2;

        array->objects = (struct Object **)realloc(array->objects,
                                                   array->slotCount * sizeof(struct Object *));

        assert(array->objects != NULL);

    }

    array->objects[array->objectCount++] = pushObject;
}

struct Object *arrayPop(struct Array *array)
{
    struct Object *popObject = array->objects[--array->objectCount];

    if (array->objectCount <= (size_t) (((double) array->slotCount) * ARRAY_SHRINK_AT))
    {
        array->slotCount /= 2;

        array->objects = (struct Object **)realloc(array->objects,
                                                   array->slotCount * sizeof(struct Object *));
    
        assert(array->objects != NULL);
    
    }

    return popObject;
}

struct Object *arrayGet(struct Array *array, size_t index)
{
    return array->objects[index];
}

void arrayPut(struct Array *array, size_t index, struct Object *putObject)
{
    array->objects[index] = putObject;
}

void arrayConcat(struct Array *array, struct Array *arrayToAdd)
{
    for (size_t i = 0; i < arrayToAdd->objectCount; i++)
    {
        arrayPush(array, arrayToAdd->objects[i]);
    }
    
}

void arrayNew(struct Object *array, size_t initialSize)
{
    objectNew(array, OBJECT_TYPE_ARRAY);
    array->value.array->objects = (struct Object **)malloc(initialSize * sizeof(struct Object *));
    assert(array->value.array->objects != NULL);
    array->value.array->slotCount = initialSize;
    array->value.array->objectCount = 0;
}

void arrayCopy(struct Array *array, struct Array *copy)
{
    for (size_t i = 0; i < array->objectCount; i++)
    {
        objectCopy(array->objects[i], copy->objects[i]);
    }    
}

bool arrayEquals(struct Array *array1, struct Array *array2)
{
    if (array1 == array2)
    {
        return true;
    }

    if (array1->objectCount != array2->objectCount)
    {
        return false;
    }

    for (size_t i = 0; i < array1->objectCount; i++)
    {
        if (!objectEqual(array1->objects[i], array2->objects[i]))
        {
            return false;
        }
    }
    
    return true;
}

size_t arrayHash(struct Array *array)
{
    size_t hash = ARRAY_START_HASH;

    for (size_t i = 0; i < array->objectCount; i++)
    {
        hash = ((hash << 5) + hash) + objectHash(array->objects[i]); 
    }
    return hash;
}

void arrayToString(struct Array *array, struct Object *string)
{
    struct Array *charArray = string->value.array;

    for (size_t i = 0; i < array->objectCount; i++)
    {
        struct Object *subString;
        objectToString(array->objects[i], subString->value.array);
        arrayConcat(charArray, subString);
        arrayPushChar(charArray, ",");
    }
    
    struct Object *character;
    objectNew(character, OBJECT_TYPE_INTEGER);
    character->value.integer_value = ']';

    arrayPut(charArray, charArray->objectCount - 1, character);
}

void arrayMark(struct Array *array)
{
    for (size_t i = 0; i < array->objectCount; i++)
    {
        if (array->objects[i] != NULL) {
            objectMark(array->objects[i]);
        }
    }   
}

void arrayFree(struct Array *array)
{
    for (size_t i = 0; i < array->objectCount; i++)
    {
        if (array->objects[i] != NULL) {
            objectFree(array->objects[i]);       
        }
    }

    free(array->objects);
}

void arrayPushChar(struct Array *array, char c)
{
    struct Object *Character;
    objectNew(Character, OBJECT_TYPE_INTEGER);
    Character->value.integer_value = c;

    arrayPush(array, Character);
}

