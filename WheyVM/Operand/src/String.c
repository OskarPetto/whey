#include "../String.h"
#include "../Object.h"
#include "../Integer.h"
#include "../Gc.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Object *stringNew(struct Gc *gc, Integer characterCount)
{
    struct Object *string = objectNew(gc, OBJECT_TYPE_STRING);
    gcRequestMemory(gc, sizeof(struct String) + characterCount * sizeof(Char));
    string->value.string = (struct String *) malloc(sizeof(struct String));
    assert(string->value.string != NULL);
    string->value.string->characterCount = characterCount;
    
    string->value.string->characters = (Char *) malloc(characterCount * sizeof (Char));
    assert(string->value.string->characters != NULL);
    
    return string;
}

struct Object *stringNewFromCString(struct Gc *gc, char *characters)
{
    struct Object *string = stringNew(gc, strlen(characters));

    memcpy(string->value.string->characters, characters, string->value.string->characterCount * sizeof(Char)); // no terminating null

    return string;
}

struct Object *stringFromArray(struct Gc *gc, struct Array *array)
{
    struct Object *string = stringNew(gc, array->objectCount);

    for (Integer i = 0; i < array->objectCount; i++)
    {
        string->value.string->characters[i] = (Char) array->objects[i]->value.integerValue;
    }
    
    return string;
}

struct Object *stringToArray(struct Gc *gc, struct String *string)
{
    struct Object *array = arrayNew(gc, string->characterCount, string->characterCount);

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
    struct Object *concat = stringNew(gc, string1->characterCount + string2->characterCount);
    memcpy(concat->value.string->characters, string1->characters, string1->characterCount * sizeof(Char)); // no terminating null
    memcpy(&concat->value.string->characters[string1->characterCount], string2->characters, string2->characterCount * sizeof(Char)); // no terminating null

    return concat;
}

struct Object *stringSubstring(struct Gc *gc, struct String *string, Integer lowerIndex, Integer upperIndex)
{
    struct Object *subString = stringNew(gc, upperIndex - lowerIndex);
    memcpy(subString->value.string->characters, &string->characters[lowerIndex], subString->value.string->characterCount * sizeof(Char)); // no terminating null
    return subString;
}


Integer stringIndexOf(struct String *string1, struct String *string2, Integer fromIndex)
{
    for (Integer i = fromIndex; i < string1->characterCount; i++)
    {
        uint8_t occurred = BOOLEAN_TRUE;

        for (Integer j = 0; j < string2->characterCount && i + j < string1->characterCount; j++)
        {
            if (string1->characters[i+j] != string2->characters[j]) 
            {
                occurred = BOOLEAN_FALSE;
                break;
            }
        }
        
        if (occurred == BOOLEAN_TRUE)
        {
            return i;
        } 
        
    }

    return -1;
}

struct Object *stringReplace(struct Gc *gc, struct String *string, struct String *stringToReplace, struct String *replacementString)
{
    if (stringToReplace->characterCount == 0)
    {
        return stringCopy(gc, string);
    }

    Integer occurrencesCount = 0;

    Integer i = 0;

    while((i = stringIndexOf(string, stringToReplace, i)) >= 0)
    {
        i += stringToReplace->characterCount;
        occurrencesCount++;
    }

    Integer newSize = string->characterCount + occurrencesCount * (replacementString->characterCount - stringToReplace->characterCount);

    struct Object *replacedString = stringNew(gc, newSize);
    
    Integer newStringIndex = 0;
    Integer oldStringIndex = 0;

    while(newStringIndex < newSize)
    {
        uint8_t occurred = BOOLEAN_TRUE;

        for (Integer i = 0; i < stringToReplace->characterCount && oldStringIndex + i < string->characterCount; i++)
        {
            if (string->characters[oldStringIndex + i] != stringToReplace->characters[i]) 
            {
                occurred = BOOLEAN_FALSE;
                break;
            }
        }
        
        if (occurred == BOOLEAN_TRUE)
        {
            for (Integer i = 0; i < replacementString->characterCount; i++)
            {
                replacedString->value.string->characters[newStringIndex + i] = replacementString->characters[i];
            }

            newStringIndex += replacementString->characterCount;
            oldStringIndex += stringToReplace->characterCount;
        } 
        else
        {
            replacedString->value.string->characters[newStringIndex] = string->characters[oldStringIndex];
            newStringIndex++;
            oldStringIndex++;
        }
        
    }

    return replacedString;
}

struct Object *stringSplit(struct Gc *gc, struct String *string1, struct String *string2)
{
    struct Object *array = arrayNew(gc, 0, 0);

    Integer last = 0;
    Integer curr = -1;

    while((curr = stringIndexOf(string1, string2, last)) >= 0)
    {
        arrayInsert(gc, array->value.array, array->value.array->objectCount, stringSubstring(gc, string1, last, curr));
        last = curr + string2->characterCount;
    }

    arrayInsert(gc, array->value.array, array->value.array->objectCount, stringSubstring(gc, string1, last, string1->characterCount));

    return array;
}

struct Object *stringCopy(struct Gc *gc, struct String *string)
{
    struct Object *copy = stringNew(gc, string->characterCount);
    memcpy(copy->value.string->characters, string->characters, string->characterCount * sizeof(Char)); // no terminating null

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
    string->characters = (Char *) realloc(string->characters, (string->characterCount + 1) * sizeof(Char));
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

void stringFree(struct Gc *gc, struct String *string)
{
    gcReleaseMemory(gc, sizeof(struct String) + string->characterCount * sizeof(Char));
    free(string->characters);
    free(string);
}