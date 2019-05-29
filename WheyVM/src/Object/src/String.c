#include "../String.h"
#include "../Object.h"
#include "../Integer.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRING_MAX_LENGTH 10000

struct Object *stringNew(struct Gc *gc, char *characters)
{
    struct Object *string = objectNew(gc, OBJECT_TYPE_STRING);
    string->value.string = (struct String *) malloc(sizeof(struct String));
    assert(string->value.string != NULL);

    string->value.string->characterCount = strlen(characters);

    string->value.string->characters = (char *) malloc(string->value.string->characterCount * sizeof (char));
    assert(string->value.string->characters != NULL);
    memcpy(string->value.string->characters, characters, string->value.string->characterCount * sizeof(char)); // no terminating null

    return string;
}

struct Object *stringFromArray(struct Gc *gc, struct Array *array)
{
    struct Object *string = objectNew(gc, OBJECT_TYPE_STRING);
    string->value.string = (struct String *) malloc(sizeof(struct String));
    assert(string->value.string != NULL);
    string->value.string->characterCount = array->objectCount;
    string->value.string->characters = (char *) malloc(string->value.string->characterCount * sizeof (char));
    assert(string->value.string->characters != NULL);

    for (Integer i = 0; i < array->objectCount; i++)
    {
        string->value.string->characters[i] = (char) array->objects[i]->value.integerValue;
    }
    
    return string;
}

struct Object *stringToArray(struct Gc *gc, struct String *string)
{
    struct Object *array = arrayNew(gc, string->characterCount);

    for (Integer i = 0; i < string->characterCount; i++)
    {
        array->value.array->objects[i] = integerNew(gc, string->characters[i]);
    }
    
    return array;
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

struct Object *stringConcatenate(struct Gc *gc, struct String *string1, struct String *string2)
{
    struct Object *concat = objectNew(gc, OBJECT_TYPE_STRING);
    concat->value.string = (struct String *) malloc(sizeof(struct String));
    assert(concat->value.string != NULL);
    concat->value.string->characterCount = string1->characterCount + string2->characterCount;
    concat->value.string->characters = (char *) malloc(concat->value.string->characterCount * sizeof (char));
    assert(concat->value.string->characters != NULL);
    memcpy(concat->value.string->characters, string1->characters, string1->characterCount * sizeof(char)); // no terminating null
    memcpy(&concat->value.string->characters[string1->characterCount], string2->characters, string2->characterCount * sizeof(char)); // no terminating null

    return concat;
}

struct Object *stringSubstring(struct Gc *gc, struct String *string, Integer lowerIndex, Integer upperIndex)
{
    struct Object *subString = objectNew(gc, OBJECT_TYPE_STRING);
    subString->value.string = (struct String *) malloc(sizeof(struct String));
    assert(subString->value.string != NULL);
    subString->value.string->characterCount = upperIndex - lowerIndex;
    subString->value.string->characters = (char *) malloc(subString->value.string->characterCount * sizeof (char));
    assert(subString->value.string->characters != NULL);
    memcpy(subString->value.string->characters, &string->characters[lowerIndex], subString->value.string->characterCount); // no terminating null
    return subString;
}

struct Object *stringCopy(struct Gc *gc, struct String *string)
{
    struct Object *copy = objectNew(gc, OBJECT_TYPE_STRING);
    copy->value.string = (struct String *) malloc(sizeof(struct String));
    assert(copy->value.string != NULL);
    copy->value.string->characterCount = string->characterCount;
    copy->value.string->characters = (char *) malloc(string->characterCount * sizeof (char));
    assert(copy->value.string->characters != NULL);
    memcpy(copy->value.string->characters, string->characters, string->characterCount * sizeof(char)); // no terminating null

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
        hash = 31 * hash + string->characters[i];
    }

    return hash;
}

void stringAppendCharacter(struct String *string, char character)
{
    string->characters = (char *) realloc(string->characters, string->characterCount + 1);
    assert(string->characters != NULL);
    string->characters[string->characterCount] = character;
    string->characterCount++;
}

void stringPrint(struct String *string)
{
    for (Integer i = 0; i < string->characterCount; i++)
    {
        printf("%c", string->characters[i]);
    }
    printf("\n");
}

void stringFree(struct String *string)
{
    free(string->characters);
    free(string);
}