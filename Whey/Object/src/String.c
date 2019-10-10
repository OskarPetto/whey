#include "../String.h"
#include "../Object.h"
#include "../Integer.h"
#include "../Array.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PCRE2_CODE_UNIT_WIDTH 32

#include <pcre2.h>


static struct Object *stringSubstringFromString(struct Gc *gc, struct String *string, uint32_t lowerIndex, uint32_t upperIndex)
{
    struct Object *subStringObject = stringNew(gc, upperIndex - lowerIndex);
    struct String *subString = subStringObject->value.subObject;
    memcpy(subString->characters, &string->characters[lowerIndex], subString->characterCount); // no terminating null
    return subStringObject;
}   

#define STRING_INDEX_OF(string1, string2, fromIndex)                                                  \
    do                                                                                                \
    {                                                                                                 \
        for (uint32_t i = fromIndex; i < string1->characterCount; i++)                                \
        {                                                                                             \
            uint8_t occurred = BOOLEAN_TRUE;                                                          \
            for (uint32_t j = 0; j < string2->characterCount && i + j < string1->characterCount; j++) \
            {                                                                                         \
                if (string1->characters[i + j] != string2->characters[j])                             \
                {                                                                                     \
                    occurred = BOOLEAN_FALSE;                                                         \
                    break;                                                                            \
                }                                                                                     \
            }                                                                                         \
            if (occurred == BOOLEAN_TRUE)                                                             \
            {                                                                                         \
                return i;                                                                             \
            }                                                                                         \
        }                                                                                             \
        return -1;                                                                                    \
    } while (0)

static Integer stringIndexOfFromString(struct String *string1, struct String *string2, uint32_t index)
{
    STRING_INDEX_OF(string1, string2, index);
}

struct Object *stringNew(struct Gc *gc, uint32_t characterCount)
{
    struct Object *object = gcObjectNew(gc, OBJECT_TYPE_STRING, sizeof(struct String) + characterCount); //  immutable strings

    struct String *string = object->value.subObject;

    void *memory = object;

    string->characterCount = characterCount;

    string->characters = memory + sizeof(struct Object) + sizeof(struct String);

    return object;
}

Integer stringSize(struct Object *stringObject)
{
    OBJECT_NOT_NULL_CHECK(stringObject, OBJECT_TYPE_STRING);
    ASSERT_OBJECT_TYPE(stringObject, OBJECT_TYPE_STRING);
    struct String *string = stringObject->value.subObject;
    return string->characterCount;
}

struct Object *stringFromArray(struct Gc *gc, struct Object *arrayObject)
{
    OBJECT_NOT_NULL_CHECK(arrayObject, OBJECT_TYPE_ARRAY);
    ASSERT_OBJECT_TYPE(arrayObject, OBJECT_TYPE_ARRAY);
    struct Array *array = arrayObject->value.subObject;
    struct Object *stringObject = stringNew(gc, array->objectCount);
    struct String *string = stringObject->value.subObject;

    for (uint32_t i = 0; i < array->objectCount; i++)
    {
        string->characters[i] = array->objects[i]->value.integerValue;
    }

    return stringObject;
}

struct Object *stringToArray(struct Gc *gc, struct Object *stringObject)
{
    OBJECT_NOT_NULL_CHECK(stringObject, OBJECT_TYPE_STRING);
    ASSERT_OBJECT_TYPE(stringObject, OBJECT_TYPE_STRING);
    struct String *string = stringObject->value.subObject;
    struct Object *arrayObject = arrayNew(gc, string->characterCount, string->characterCount);
    struct Array *array = arrayObject->value.subObject;

    for (uint32_t i = 0; i < string->characterCount; i++)
    {
        array->objects[i] = integerNew(gc, string->characters[i]);
    }

    return arrayObject;
}

Integer stringCompare(struct Object *stringObject1, struct Object *stringObject2)
{
    OBJECT_NOT_NULL_CHECK(stringObject1, OBJECT_TYPE_STRING);
    ASSERT_OBJECT_TYPE(stringObject1, OBJECT_TYPE_STRING);
    struct String *string1 = stringObject1->value.subObject;
    OBJECT_NOT_NULL_CHECK(stringObject2, OBJECT_TYPE_STRING);
    ASSERT_OBJECT_TYPE(stringObject2, OBJECT_TYPE_STRING);
    struct String *string2 = stringObject2->value.subObject;

    Integer l1 = string1->characterCount;
    Integer l2 = string2->characterCount;

    Integer minL = l1 <= l2 ? l1 : l2;

    for (uint32_t i = 0; i < minL; i++)
    {
        char c1 = string1->characters[i];
        char c2 = string2->characters[i];

        if (c1 != c2)
        {
            return c1 - c2;
        }
    }

    return l1 - l2;
}

struct Object *stringConcatenate(struct Gc *gc, struct Object *stringObject1, struct Object *stringObject2)
{

    OBJECT_NOT_NULL_CHECK(stringObject1, OBJECT_TYPE_STRING);
    ASSERT_OBJECT_TYPE(stringObject1, OBJECT_TYPE_STRING);
    struct String *string1 = stringObject1->value.subObject;
    OBJECT_NOT_NULL_CHECK(stringObject2, OBJECT_TYPE_STRING);
    ASSERT_OBJECT_TYPE(stringObject2, OBJECT_TYPE_STRING);
    struct String *string2 = stringObject2->value.subObject;
    struct Object *concatObject = stringNew(gc, string1->characterCount + string2->characterCount);
    struct String *concatString = concatObject->value.subObject;
    memcpy(concatString->characters, string1->characters, string1->characterCount);                           // no terminating null
    memcpy(&concatString->characters[string1->characterCount], string2->characters, string2->characterCount); // no terminating null

    return concatObject;
}

struct Object *stringSubstring(struct Gc *gc, struct Object *stringObject, Integer lowerIndex, Integer upperIndex)
{
    OBJECT_NOT_NULL_CHECK(stringObject, OBJECT_TYPE_STRING);
    ASSERT_OBJECT_TYPE(stringObject, OBJECT_TYPE_STRING);
    struct String *string = stringObject->value.subObject;
    CHECK_VALID_INCL_INDEX(OBJECT_TYPE_STRING, lowerIndex, string->characterCount);
    CHECK_VALID_INCL_INDEX(OBJECT_TYPE_STRING, upperIndex, string->characterCount);
    CHECK_INDICES_ORDERED(OBJECT_TYPE_STRING, lowerIndex, upperIndex);
    struct Object *subStringObject = stringNew(gc, upperIndex - lowerIndex);
    struct String *subString = subStringObject->value.subObject;
    memcpy(subString->characters, &string->characters[lowerIndex], subString->characterCount); // no terminating null
    return subStringObject;
}

Integer stringIndexOf(struct Object *stringObject1, struct Object *stringObject2, Integer fromIndex)
{
    OBJECT_NOT_NULL_CHECK(stringObject1, OBJECT_TYPE_STRING);
    ASSERT_OBJECT_TYPE(stringObject1, OBJECT_TYPE_STRING);
    struct String *string1 = stringObject1->value.subObject;
    OBJECT_NOT_NULL_CHECK(stringObject2, OBJECT_TYPE_STRING);
    ASSERT_OBJECT_TYPE(stringObject2, OBJECT_TYPE_STRING);
    struct String *string2 = stringObject2->value.subObject;
    CHECK_VALID_INDEX(OBJECT_TYPE_STRING, fromIndex, string1->characterCount);
    STRING_INDEX_OF(string1, string2, fromIndex);
}

Integer stringContains(struct Object *stringObject1, struct Object *stringObject2)
{
    OBJECT_NOT_NULL_CHECK(stringObject1, OBJECT_TYPE_STRING);
    ASSERT_OBJECT_TYPE(stringObject1, OBJECT_TYPE_STRING);
    struct String *string1 = stringObject1->value.subObject;
    OBJECT_NOT_NULL_CHECK(stringObject2, OBJECT_TYPE_STRING);
    ASSERT_OBJECT_TYPE(stringObject2, OBJECT_TYPE_STRING);
    struct String *string2 = stringObject2->value.subObject;
    return stringIndexOfFromString(string1, string2, 0) >= 0;
}

struct Object *stringReplace(struct Gc *gc, struct Object *stringObject1, struct Object *stringObject2, struct Object *stringObject3)
{
    OBJECT_NOT_NULL_CHECK(stringObject1, OBJECT_TYPE_STRING);
    ASSERT_OBJECT_TYPE(stringObject1, OBJECT_TYPE_STRING);
    struct String *string1 = stringObject1->value.subObject;
    OBJECT_NOT_NULL_CHECK(stringObject2, OBJECT_TYPE_STRING);
    ASSERT_OBJECT_TYPE(stringObject2, OBJECT_TYPE_STRING);
    struct String *string2 = stringObject2->value.subObject;
    OBJECT_NOT_NULL_CHECK(stringObject3, OBJECT_TYPE_STRING);
    ASSERT_OBJECT_TYPE(stringObject3, OBJECT_TYPE_STRING);
    struct String *string3 = stringObject3->value.subObject;

    if (string2->characterCount == 0)
    {
        return stringCopy(gc, stringObject1);
    }

    uint32_t occurrencesCount = 0;

    Integer i = 0;

    while ((i = stringIndexOfFromString(string1, string2, i)) >= 0)
    {
        i += string2->characterCount;
        occurrencesCount++;
    }

    uint32_t newSize = string1->characterCount + occurrencesCount * (string3->characterCount - string2->characterCount);

    struct Object *replacedStringObject = stringNew(gc, newSize);
    struct String *replacedString = replacedStringObject->value.subObject;

    uint32_t newStringIndex = 0;
    uint32_t oldStringIndex = 0;

    while (newStringIndex < newSize)
    {
        uint8_t occurred = BOOLEAN_TRUE;

        for (uint32_t i = 0; i < string2->characterCount && oldStringIndex + i < string1->characterCount; i++)
        {
            if (string1->characters[oldStringIndex + i] != string2->characters[i])
            {
                occurred = BOOLEAN_FALSE;
                break;
            }
        }

        if (occurred == BOOLEAN_TRUE)
        {
            for (uint32_t i = 0; i < string3->characterCount; i++)
            {
                replacedString->characters[newStringIndex + i] = string3->characters[i];
            }

            newStringIndex += string3->characterCount;
            oldStringIndex += string2->characterCount;
        }
        else
        {
            replacedString->characters[newStringIndex] = string1->characters[oldStringIndex];
            newStringIndex++;
            oldStringIndex++;
        }
    }

    return replacedStringObject;
}

struct Object *stringSplit(struct Gc *gc, struct Object *stringObject1, struct Object *stringObject2)
{
    OBJECT_NOT_NULL_CHECK(stringObject1, OBJECT_TYPE_STRING);
    ASSERT_OBJECT_TYPE(stringObject1, OBJECT_TYPE_STRING);
    struct String *string1 = stringObject1->value.subObject;
    OBJECT_NOT_NULL_CHECK(stringObject2, OBJECT_TYPE_STRING);
    ASSERT_OBJECT_TYPE(stringObject2, OBJECT_TYPE_STRING);
    struct String *string2 = stringObject2->value.subObject;

    struct Object *arrayObject = arrayNew(gc, 0, 0);

    uint32_t last = 0;
    Integer curr;

    struct Object *subString;

    while ((curr = stringIndexOfFromString(string1, string2, last)) >= 0)
    {
        subString = stringSubstringFromString(gc, string1, last, curr);
        arrayPushNoNullCheck(gc, arrayObject, subString);
        last = curr + string2->characterCount;
    }

    subString = stringSubstringFromString(gc, string1, last, string1->characterCount);
    arrayPushNoNullCheck(gc, arrayObject, subString);

    return arrayObject;
}

struct Object *stringCopy(struct Gc *gc, struct Object *stringObject)
{
    struct String *string = stringObject->value.subObject;
    struct Object *copyObject = stringNew(gc, string->characterCount);
    struct String *copyString = copyObject->value.subObject;
    memcpy(copyString->characters, string->characters, string->characterCount); // no terminating null

    return copyObject;
}

Integer stringEquals(struct Object *stringObject1, struct Object *stringObject2)
{
    struct String *string1 = stringObject1->value.subObject;
    struct String *string2 = stringObject2->value.subObject;

    if (string1->characterCount != string2->characterCount)
    {
        return BOOLEAN_FALSE;
    }

    for (uint32_t i = 0; i < string1->characterCount; i++)
    {
        if (string1->characters[i] != string2->characters[i])
        {
            return BOOLEAN_FALSE;
        }
    }

    return BOOLEAN_TRUE;
}

Integer stringHash(struct Object *stringObject)
{
    Integer hash = 1;

    struct String *string = stringObject->value.subObject;

    for (uint32_t i = 0; i < string->characterCount; i++)
    {
        hash = 31 * hash + string->characters[i];
    }

    return hash;
}

void stringFree(struct Gc *gc, struct Object *stringObject)
{
    gcObjectFree(gc, stringObject, sizeof(struct Object) + sizeof(struct String) + ((struct String *)stringObject->value.subObject)->characterCount);
}

void stringPrint(struct Object *stringObject)
{
    struct String *string = stringObject->value.subObject;
    printf(STRING_FORMAT_STRING"\n", (uint32_t)string->characterCount, string->characters);
}

uint32_t stringCharacterCount(struct Object *stringObject)
{
    struct String *string = stringObject->value.subObject;
    return string->characterCount;
}

void stringWriteToString(struct Object *stringObject1, struct Object *stringObject2, uint32_t *index)
{
    struct String *string1 = stringObject1->value.subObject;
    struct String *string2 = stringObject2->value.subObject;

    memcpy(&string2->characters[*index], string1->characters, string1->characterCount);
    (*index) += string1->characterCount;
}

struct Object *stringNewFromCString(struct Gc *gc, char *characters)
{
    struct Object *object = stringNew(gc, strlen(characters));

    struct String *string = object->value.subObject;

    memcpy(string->characters, characters, string->characterCount); // no terminating null

    return object;
}
