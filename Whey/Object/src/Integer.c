#include "../Integer.h"
#include "../Array.h"
#include "../Object.h"
#include "../String.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#define INTEGER_BUFFER_SIZE 50

struct Object *integerNew(struct Gc *gc, Integer value)
{
    struct Object *integer = gcObjectNew(gc, OBJECT_TYPE_INTEGER, 0);
    integer->value.integerValue = value;
    return integer;
}

struct Object *integerToString(struct Gc *gc, struct Object *integer)
{   
    uint32_t charCount = integerStringCharacterCount(integer);

    struct Object *stringObject = stringNew(gc, charCount);

    uint32_t index = 0;

    integerWriteToString(integer, stringObject, &index);

    return stringObject;
}

void integerFree(struct Gc *gc, struct Object *integer)
{
    gcObjectFree(gc, integer, sizeof(struct Object));
}

uint32_t integerStringCharacterCount(struct Object *integer)
{
    Integer value = integer->value.integerValue;
    return snprintf(NULL, 0, INTEGER_FORMAT_STRING, value);
}

void integerWriteToString(struct Object *integer, struct Object *stringObject, uint32_t *index)
{   
    Integer value = integer->value.integerValue;
    struct String *string = stringObject->value.subObject;
    uint32_t charCount = integerStringCharacterCount(integer);

    char buffer[INTEGER_BUFFER_SIZE];

    snprintf(buffer, charCount + 1, INTEGER_FORMAT_STRING, value);

    memcpy(&(string->characters[*index]), buffer, charCount);

    *index = *index + charCount;
}