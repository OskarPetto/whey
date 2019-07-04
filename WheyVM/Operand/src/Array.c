#include "../Array.h"
#include "../Object.h"
#include "../Gc.h"

#include <assert.h>
#include <stdlib.h>

static Integer getNextLargerSlotCount(Integer slotCount)
{
    return slotCount + (slotCount >> 1) + 1;
}

struct Object *arrayNew(struct Gc *gc, Integer initialObjectCount, Integer initialSlotCount)
{
    struct Object *object = objectNew(gc, OBJECT_TYPE_ARRAY);
    gcRequestMemory(gc, sizeof(struct Array) + initialSlotCount * sizeof(struct Object *));
    object->value.array = (struct Array *) malloc(sizeof(struct Array));
    assert(object->value.array != NULL);
    object->value.array->objects = (struct Object **)calloc(initialSlotCount, sizeof(struct Object *));
    assert(object->value.array->objects != NULL);
    object->value.array->slotCount = initialSlotCount;
    object->value.array->objectCount = initialObjectCount;
    return object;
}

struct Object *arraySet(struct Array *array, Integer index, struct Object *setObject)
{
    struct Object *currentObject = array->objects[index];
    array->objects[index] = setObject;
    return currentObject;
}

void arrayInsert(struct Gc *gc, struct Array *array, Integer index, struct Object *insertObject)
{
    array->objectCount++;

    if (array->objectCount > array->slotCount)
    {
        uint64_t oldSize = array->slotCount * sizeof(struct Object *);

        array->slotCount = getNextLargerSlotCount(array->objectCount);

        gcRequestMemory(gc, array->slotCount * sizeof(struct Object *) - oldSize);

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

void arrayInsertAll(struct Gc *gc, struct Array *array, Integer index, struct Array *insertArray)
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
        uint64_t oldSize = array->slotCount * sizeof(struct Object *);

        array->slotCount = getNextLargerSlotCount(newObjectCount);

        gcRequestMemory(gc, array->slotCount * sizeof(struct Object *) - oldSize);

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
    struct Object *copy = arrayNew(gc, array->objectCount, array->slotCount);

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
    struct Object *stringObject = stringNewFromCString(NULL, "[");

    for (Integer i = 0; i < array->objectCount; i++)
    {
        struct Object *subStringObject = objectToString(NULL, array->objects[i]);

        struct Object *temp = stringConcatenate(NULL, stringObject->value.string, subStringObject->value.string);

        objectFree(NULL, stringObject);
        objectFree(NULL, subStringObject);
        stringObject = temp;

        stringAppendCharacter(stringObject->value.string, ',');
    }

    if (array->objectCount > 0)
    {
        stringObject->value.string->characters[stringObject->value.string->characterCount - 1] = ']';
    }
    else
    {
        stringAppendCharacter(stringObject->value.string, ']');
    }

    gcRequestMemory(gc, sizeof(struct Object) + sizeof(struct String) + stringObject->value.string->characterCount * sizeof(Char));
    gcRegisterObject(gc, stringObject);
    
    return stringObject;    
}

void arrayMark(struct Array *array)
{
    for (Integer i = 0; i < array->objectCount; i++)
    {
        objectMark(array->objects[i]);
    }
}

void arrayFree(struct Gc *gc, struct Array *array)
{
    gcReleaseMemory(gc, sizeof(struct Array) + array->slotCount * sizeof(struct Object *));
    free(array->objects);
    free(array);
}