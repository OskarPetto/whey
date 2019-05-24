#include "../String.h"
#include "../Array.h"
#include "../Object.h"
#include "../Integer.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct Object *stringNew(struct Gc *gc, Integer characterCount)
{
    struct Object *string = objectNew(gc, OBJECT_TYPE_STRING);
    string->value.string->characters = (char *)malloc(characterCount * sizeof(char));
    assert(string->value.string->characters != NULL);
    string->value.string->characterCount = characterCount;
    return string;
}

struct Object *stringFromCharArray(struct Gc *gc, struct Array *array)
{
    struct Object *stringObject = stringNew(gc, array->objectCount);

    for (Integer i = 0; i < array->objectCount; i++)
    {
        stringObject->value.string->characters[i] = (char) array->objects[i]->value.integer_value;
    }
    
    return stringObject;
}

struct Object *stringToCharArray(struct Gc *gc, struct String *string)
{
    struct Object *charArrayObject = arrayNew(gc, string->characterCount);

    for (Integer i = 0; i < string->characterCount; i++)
    {
        charArrayObject->value.array->objects[i] = integerNew(gc, (Integer) string->characters[i]);
    }

    return charArrayObject;

}

Integer stringCompare(struct String *string1, struct String *string2)
{
    Integer l1 = string1->characterCount;
    Integer l2 = string2->characterCount;

    Integer minL = l1 <= l2 ? l1 : l2;

    for (Integer i = 0; i < minL; i++)
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

struct Object *stringCopy(struct Gc *gc, struct String *string)
{
    struct Object *copy = stringNew(gc, string->characterCount);

    for (Integer i = 0; i < string->characterCount; i++)
    {
        copy->value.string->characters[i] = string->characters[i];
    }

    return copy;
}

Integer stringEquals(struct String *string1, struct String *string2)
{
    if (string1->characterCount != string2->characterCount)
    {
        return BOOLEAN_FALSE;
    }

    for (Integer i = 0; i < string1->characterCount; i++)
    {
        if (string1->characters[i] != string2->characters[i])
        {
            return BOOLEAN_FALSE;
        }
    }

    return BOOLEAN_TRUE;
}

Integer stringHash(struct String *string)
{
    Integer hash = 1;

    for (Integer i = 0; i < string->characterCount; i++)
    {
        hash = hash * 31  + string->characters[i];
    }

    return hash;
}

void stringFree(struct String *string)
{
    free(string->characters);
}