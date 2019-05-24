#include "../String.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct Object *stringNew(Integer characterCount)
{
    struct Object *string = objectNew(OBJECT_TYPE_STRING);
    string->value.string->characters = (char *)malloc(characterCount * sizeof(char));
    assert(string->value.string->characters != NULL);
    string->value.string->characterCount = characterCount;
    return string;
}

struct Object *stringFromCharArray(struct Array *array)
{

    struct Object *stringObject = stringNew(array->objectCount);

    for (Integer i = 0; i < array->objectCount; i++)
    {
        stringObject->value.string->characters[i] = (char) array->objects[i];
    }
    
    return stringObject;
}

struct Object *stringToCharArray(struct String *string)
{
    struct Object *charArrayObject = arrayNew(string->characterCount);

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

struct Object *stringCopy(struct String *string)
{
    struct Object *copy = stringNew(string->characterCount);

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
Integer stringHash(struct String *string);

void stringMark(struct String *string);
void stringFree(struct String *string);