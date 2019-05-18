#include "Array.h"
#include <assert.h>

void opASize(struct Object *array, struct Object *size)
{
    assert(array != NULL);
    assert(array->type == OBJECT_TYPE_ARRAY);

    size = objectNew(OBJECT_TYPE_INTEGER);
    size->value.integer_value = arraySize(array);
}

void opAGet(struct Object *array, struct Object *index, struct Object *getObject)
{
    assert(array != NULL);
    assert(index != NULL);
    assert(array->type == OBJECT_TYPE_ARRAY);
    assert(index->type == OBJECT_TYPE_INTEGER);
    assert(index->value.integer_value >= 0);
    assert(index->value.integer_value < array->value.array->objectCount);

    getObject = arrayGet(array->value.array, (size_t) index->value.integer_value);
}

void opASet(struct Object *array, struct Object *index, struct Object *setObject, struct Object *previousObject)
{
    assert(array != NULL);
    assert(index != NULL);
    assert(array->type == OBJECT_TYPE_ARRAY);
    assert(index->type == OBJECT_TYPE_INTEGER);
    assert(index->value.integer_value >= 0);
    assert(index->value.integer_value < array->value.array->objectCount);

    previousObject = arraySet(array->value.array, (size_t) index->value.integer_value, setObject);
}

void opAInsert(struct Object *array, struct Object *index, struct Object *insertObject)
{
    assert(array != NULL);
    assert(array->type == OBJECT_TYPE_ARRAY);
    assert(index->type == OBJECT_TYPE_INTEGER);
    assert(index->value.integer_value >= 0);
    assert(index->value.integer_value <= array->value.array->objectCount);
    
    arrayInsert(array, (size_t) index->value.integer_value, insertObject);
}

void opARemove(struct Object *array, struct Object *index, struct Object *removeObject)
{
    assert(array != NULL);
    assert(array->type == OBJECT_TYPE_ARRAY);
    assert(index->type == OBJECT_TYPE_INTEGER);
    assert(index->value.integer_value >= 0);
    assert(index->value.integer_value < array->value.array->objectCount);

    removeObject = arrayRemove(array, (size_t) index->value.integer_value);
}

void opAInsertAll(struct Object *array, struct Object *index, struct Object *insertArray)
{
    assert(array != NULL);
    assert(array->type == OBJECT_TYPE_ARRAY);
    assert(index->type == OBJECT_TYPE_INTEGER);
    assert(index->value.integer_value >= 0);
    assert(index->value.integer_value <= array->value.array->objectCount);

    if (insertArray == NULL) return;

    assert(insertArray->type == OBJECT_TYPE_ARRAY);
    
    arrayInsertAll(array->value.array,  (size_t) index->value.integer_value, insertArray->value.array);

}

size_t arraySize(struct Array *array) 
{
    return (size_t) array->objectCount;
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
    if (array->objectCount >= (size_t) (((double) array->slotCount) * ARRAY_GROW_AT))
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

struct Object *arrayRemove(struct Array *array, size_t index)
{
    struct Object *popObject = array->objects[--array->objectCount];

    if (array->objectCount < (size_t) (((double) array->slotCount) * ARRAY_SHRINK_AT))
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

void arrayInsertAll(struct Array *array, size_t index, struct Array *insertArray)
{
    size_t newObjectCount = array->objectCount + insertArray->objectCount;

    if (newObjectCount >= (size_t) (((double) array->slotCount) * ARRAY_GROW_AT))
    {
        array->slotCount = newObjectCount * 2;

        array->objects = (struct Object **)realloc(array->objects,
                                                   array->slotCount * sizeof(struct Object *));

        assert(array->objects != NULL);

    }

    for (size_t i = 0; i < insertArray->objectCount; i++)
    {
        array->objects[array->objectCount + i] = insertArray->objects[i];
    }

    array->objectCount = newObjectCount;
}

struct Object *arrayNew(size_t initialSize)
{
    struct Object *object = objectNew(OBJECT_TYPE_ARRAY);
    object->value.array->objects = (struct Object **)malloc(initialSize * sizeof(struct Object *));
    assert(object->value.array->objects != NULL);
    object->value.array->slotCount = initialSize;
    object->value.array->objectCount = 0;
    return object;
}

struct Object *arrayCopy(struct Array *array)
{
    struct Object *copy = arrayNew(array->slotCount);

    for (size_t i = 0; i < array->objectCount; i++)
    {
        copy->value.array->objects[i] = objectCopy(array->objects[i]);
    }    

    return copy;
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

struct Object *arraytoString(struct Array *array)
{
    struct Object *string = arrayNew(array->objectCount * 2);

    stringAppendChar(string->value.array, '[');

    for (size_t i = 0; i < array->objectCount; i++)
    {
        struct Array *subString = objectSerialize(array->objects[i]);
        arrayPushAll(string->value.array, subString);
        stringAppendChar(string->value.array, ',');
    }

    if (array->objectCount > 0) {
        arrayRemove(string->value.array, string->value.array->objectCount - 1);
    }
    
    stringAppendChar(string->value.array, ']');

    return string;
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

void stringAppendChar(struct Array *array, char c)
{
    struct Object *character = objectNew(OBJECT_TYPE_INTEGER);
    character->value.integer_value = c;

    arrayInsert(array, array->objectCount, character);
}

