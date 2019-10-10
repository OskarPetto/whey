#include "../Array.h"
#include "../String.h"
#include "../Object.h"

#include <stdlib.h>

#define NEXT_SLOT_COUNT(slotCount) slotCount + (slotCount >> 1) + 1

#define ARRAY_INSERT(gc, array, index, insertObject)                                               \
    do                                                                                             \
    {                                                                                              \
        array->objectCount++;                                                                      \
        if (array->objectCount > array->slotCount)                                                 \
        {                                                                                          \
            uint32_t oldSize = array->slotCount * sizeof(struct Object *);                         \
            array->slotCount = NEXT_SLOT_COUNT(array->objectCount);                                \
            array->objects = gcMemoryRealloc(gc, arrayObject, array->objects,                      \
                                             oldSize, array->slotCount * sizeof(struct Object *)); \
        }                                                                                          \
        for (uint32_t i = array->objectCount - 1; i > index; i--)                                  \
        {                                                                                          \
            array->objects[i] = array->objects[i - 1];                                             \
        }                                                                                          \
        array->objects[index] = insertObject;                                                      \
    } while (0)

#define ARRAY_INSERT_ALL(gc, array, index, insertArray)                                            \
    do                                                                                             \
    {                                                                                              \
        if (insertArray->objectCount == 0)                                                         \
        {                                                                                          \
            return;                                                                                \
        }                                                                                          \
        uint32_t insertObjectCount = insertArray->objectCount;                                     \
        uint32_t insertObjectSize = insertObjectCount * sizeof(struct Object *);                   \
        struct Object **insertObjects = gcMemoryMalloc(gc, arrayObject, insertObjectSize);         \
        for (uint32_t i = 0; i < insertObjectCount; i++)                                           \
        {                                                                                          \
            insertObjects[i] = insertArray->objects[i];                                            \
        }                                                                                          \
        struct Array *array = arrayObject->value.subObject;                                        \
        uint32_t newObjectCount = array->objectCount + insertObjectCount;                          \
        if (newObjectCount > array->slotCount)                                                     \
        {                                                                                          \
            uint32_t oldSize = array->slotCount * sizeof(struct Object *);                         \
            array->slotCount = NEXT_SLOT_COUNT(newObjectCount);                                    \
            array->objects = gcMemoryRealloc(gc, arrayObject, array->objects,                      \
                                             oldSize, array->slotCount * sizeof(struct Object *)); \
        }                                                                                          \
        for (Integer i = array->objectCount - 1; i >= index; i--)                                  \
        {                                                                                          \
            array->objects[insertObjectCount + i] = array->objects[i];                             \
        }                                                                                          \
        for (uint32_t i = 0; i < insertObjectCount; i++)                                           \
        {                                                                                          \
            array->objects[index + i] = insertObjects[i];                                          \
        }                                                                                          \
        array->objectCount = newObjectCount;                                                       \
        gcMemoryFree(gc, arrayObject, insertObjects, insertObjectSize);                            \
    } while (0)

#define ARRAY_REMOVE(array, index)                            \
    do                                                        \
    {                                                         \
        struct Object **objects = array->objects;             \
        struct Object *removeObject = objects[index];         \
        array->objectCount--;                                 \
        for (uint32_t i = index; i < array->objectCount; i++) \
        {                                                     \
            objects[i] = objects[i + 1];                      \
        }                                                     \
        return removeObject;                                  \
    } while (0)

struct Object *arrayNew(struct Gc *gc, Integer initialObjectCount, Integer initialSlotCount)
{
    struct Object *object = gcObjectNew(gc, OBJECT_TYPE_ARRAY, sizeof(struct Array));
    struct Array *array = object->value.subObject;
    array->objects = gcMemoryMalloc(gc, object, initialSlotCount * sizeof(struct Object *));

    array->slotCount = initialSlotCount;
    array->objectCount = initialObjectCount;

    return object;
}

Integer arraySize(struct Object *arrayObject)
{
    OBJECT_NOT_NULL_CHECK(arrayObject, OBJECT_TYPE_ARRAY);
    ASSERT_OBJECT_TYPE(arrayObject, OBJECT_TYPE_ARRAY);
    struct Array *array = arrayObject->value.subObject;
    return array->objectCount;
}

struct Object *arrayGet(struct Object *arrayObject, Integer index)
{
    OBJECT_NOT_NULL_CHECK(arrayObject, OBJECT_TYPE_ARRAY);
    ASSERT_OBJECT_TYPE(arrayObject, OBJECT_TYPE_ARRAY);
    struct Array *array = arrayObject->value.subObject;
    CHECK_VALID_INDEX(OBJECT_TYPE_ARRAY, index, array->objectCount);
    return array->objects[index];
}

struct Object *arraySet(struct Object *arrayObject, Integer index, struct Object *setObject)
{
    OBJECT_NOT_NULL_CHECK(arrayObject, OBJECT_TYPE_ARRAY);
    ASSERT_OBJECT_TYPE(arrayObject, OBJECT_TYPE_ARRAY);
    struct Array *array = arrayObject->value.subObject;
    struct Object **objects = array->objects;
    CHECK_VALID_INDEX(OBJECT_TYPE_ARRAY, index, array->objectCount);
    struct Object *currentObject = objects[index];
    objects[index] = setObject;
    return currentObject;
}

void arrayInsert(struct Gc *gc, struct Object *arrayObject, Integer index, struct Object *insertObject)
{
    OBJECT_NOT_NULL_CHECK(arrayObject, OBJECT_TYPE_ARRAY);
    ASSERT_OBJECT_TYPE(arrayObject, OBJECT_TYPE_ARRAY);
    struct Array *array = arrayObject->value.subObject;
    CHECK_VALID_INDEX(OBJECT_TYPE_ARRAY, index, array->objectCount);
    ARRAY_INSERT(gc, array, index, insertObject);
}

void arrayInsertAll(struct Gc *gc, struct Object *arrayObject, Integer index, struct Object *insertArrayObject)
{
    OBJECT_NOT_NULL_CHECK(arrayObject, OBJECT_TYPE_ARRAY);
    ASSERT_OBJECT_TYPE(arrayObject, OBJECT_TYPE_ARRAY);
    struct Array *array = arrayObject->value.subObject;
    OBJECT_NOT_NULL_CHECK(insertArrayObject, OBJECT_TYPE_ARRAY);
    ASSERT_OBJECT_TYPE(insertArrayObject, OBJECT_TYPE_ARRAY);
    struct Array *insertArray = insertArrayObject->value.subObject;
    CHECK_VALID_INDEX(OBJECT_TYPE_ARRAY, index, array->objectCount);
    ARRAY_INSERT_ALL(gc, array, index, insertArray);
}

struct Object *arrayRemove(struct Object *arrayObject, Integer index)
{
    OBJECT_NOT_NULL_CHECK(arrayObject, OBJECT_TYPE_ARRAY);
    ASSERT_OBJECT_TYPE(arrayObject, OBJECT_TYPE_ARRAY);
    struct Array *array = arrayObject->value.subObject;
    CHECK_VALID_INDEX(OBJECT_TYPE_ARRAY, index, array->objectCount);
    ARRAY_REMOVE(array, index);
}

void arrayPush(struct Gc *gc, struct Object *arrayObject, struct Object *pushObject)
{
    OBJECT_NOT_NULL_CHECK(arrayObject, OBJECT_TYPE_ARRAY);
    ASSERT_OBJECT_TYPE(arrayObject, OBJECT_TYPE_ARRAY);
    struct Array *array = arrayObject->value.subObject;
    uint32_t index = array->objectCount;
    ARRAY_INSERT(gc, array, index, pushObject);
}

void arrayPushNoNullCheck(struct Gc *gc, struct Object *arrayObject, struct Object *pushObject)
{
    struct Array *array = arrayObject->value.subObject;
    uint32_t index = array->objectCount;
    ARRAY_INSERT(gc, array, index, pushObject);
}

void arrayPushAll(struct Gc *gc, struct Object *arrayObject, struct Object *pushArrayObject)
{
    OBJECT_NOT_NULL_CHECK(arrayObject, OBJECT_TYPE_ARRAY);
    ASSERT_OBJECT_TYPE(arrayObject, OBJECT_TYPE_ARRAY);
    struct Array *array = arrayObject->value.subObject;
    uint32_t index = array->objectCount;
    OBJECT_NOT_NULL_CHECK(pushArrayObject, OBJECT_TYPE_ARRAY);
    ASSERT_OBJECT_TYPE(pushArrayObject, OBJECT_TYPE_ARRAY);
    struct Array *pushArray = pushArrayObject->value.subObject;
    ARRAY_INSERT_ALL(gc, array, index, pushArray);
}

struct Object *arrayPop(struct Object *arrayObject)
{
    OBJECT_NOT_NULL_CHECK(arrayObject, OBJECT_TYPE_ARRAY);
    ASSERT_OBJECT_TYPE(arrayObject, OBJECT_TYPE_ARRAY);
    struct Array *array = arrayObject->value.subObject;
    uint32_t index = array->objectCount - 1;
    ARRAY_REMOVE(array, index);
}

void arraySwap(struct Object *arrayObject, Integer index1, Integer index2)
{
    OBJECT_NOT_NULL_CHECK(arrayObject, OBJECT_TYPE_ARRAY);
    ASSERT_OBJECT_TYPE(arrayObject, OBJECT_TYPE_ARRAY);
    struct Array *array = arrayObject->value.subObject;
    CHECK_VALID_INDEX(OBJECT_TYPE_ARRAY, index1, array->objectCount);
    CHECK_VALID_INDEX(OBJECT_TYPE_ARRAY, index2, array->objectCount);

    struct Object *temp = array->objects[index1];
    array->objects[index1] = array->objects[index2];
    array->objects[index2] = temp;
}

struct Object *arrayCopy(struct Gc *gc, struct Object *arrayObject)
{
    struct Array *array = arrayObject->value.subObject;
    struct Object *copy = arrayNew(gc, array->objectCount, array->slotCount);

    struct Array *copyArray = copy->value.subObject;

    for (uint32_t i = 0; i < array->objectCount; i++)
    {
        copyArray->objects[i] = objectCopy(gc, array->objects[i]);
    }

    return copy;
}

Integer arrayEquals(struct Object *arrayObject1, struct Object *arrayObject2)
{
    struct Array *array1 = arrayObject1->value.subObject;
    struct Array *array2 = arrayObject2->value.subObject;

    if (array1->objectCount != array2->objectCount)
    {
        return BOOLEAN_FALSE;
    }

    for (uint32_t i = 0; i < array1->objectCount; i++)
    {
        if (!objectEquals(array1->objects[i], array2->objects[i]))
        {
            return BOOLEAN_FALSE;
        }
    }

    return BOOLEAN_TRUE;
}

Integer arrayHash(struct Object *arrayObject)
{
    struct Array *array = arrayObject->value.subObject;
    Integer hash = 1;

    for (uint32_t i = 0; i < array->objectCount; i++)
    {
        hash = 31 * hash + objectHash(array->objects[i]);
    }

    return hash;
}

struct Object *arrayToString(struct Gc *gc, struct Object *arrayObject)
{
    uint32_t characterCount = arrayStringCharacterCount(arrayObject);

    struct Object *stringObject = stringNew(gc, characterCount);

    uint32_t index = 0;

    arrayWriteToString(arrayObject, stringObject, &index);

    return stringObject;
}

void arrayMark(struct Object *arrayObject)
{
    struct Array *array = arrayObject->value.subObject;
    for (uint32_t i = 0; i < array->objectCount; i++)
    {
        objectMark(array->objects[i]);
    }
}

void arrayFree(struct Gc *gc, struct Object *arrayObject)
{
    struct Array *array = arrayObject->value.subObject;
    gcMemoryFree(gc, arrayObject, array->objects, array->slotCount * sizeof(struct Object *));
    gcObjectFree(gc, arrayObject, sizeof(struct Object) + sizeof(struct Array));
}

uint32_t arrayStringCharacterCount(struct Object *arrayObject)
{
    struct Array *array = arrayObject->value.subObject;
    uint32_t count = (2 + (array->objectCount > 0 ? array->objectCount - 1 : 0));

    for (uint32_t i = 0; i < array->objectCount; i++)
    {
        count += objectStringCharacterCount(array->objects[i]);
    }

    return count;
}

void arrayWriteToString(struct Object *arrayObject, struct Object *stringObject, uint32_t *index)
{
    struct String *string = stringObject->value.subObject;
    string->characters[(*index)++] = '[';

    struct Array *array = arrayObject->value.subObject;
    for (uint32_t i = 0; i < array->objectCount; i++)
    {
        objectWriteToString(array->objects[i], stringObject, index);
        string->characters[(*index)++] = ',';
    }

    if (array->objectCount > 0)
    {
        --(*index);
    }

    string->characters[(*index)++] = ']';
}