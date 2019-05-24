#include "../String.h"

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
        stringObject->value.string->characters[i] = (char) array->objects[i];
    }
    
    return stringObject;
}

struct Object *stringToCharArray(struct Gc *gc, struct String *string)
{
    struct Object *charArrayObject = arrayNew(gc, string->characterCount);

    for (Integer i = 0; i < string->characterCount; i++)
    {
        charArrayObject->value.array->objects[i] = (Integer) string->characters[i];
    }

    return charArrayObject;

}

void stringPrint(struct String *string)
{
    for (Integer i = 0; i < string->characterCount; i++)
    {
        printf("%c", string->characters[i]);
    }
    
    printf("\n");
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