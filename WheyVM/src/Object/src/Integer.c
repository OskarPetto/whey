#include "../Integer.h"
#include "../String.h"
#include "../Object.h"

#include <stdio.h>
#include <string.h>

#define INTEGER_STRING_BUFFER_SIZE 50

struct Object *integerNew(struct Gc *gc, Integer value)
{
    struct Object *integer = objectNew(gc, OBJECT_TYPE_INTEGER);
    integer->value.integer_value = value;
    return integer;
}

struct Object *integerToString(struct Gc *gc, Integer integer)
{
    char buffer[INTEGER_STRING_BUFFER_SIZE];

    snprintf(buffer, INTEGER_STRING_BUFFER_SIZE, "%d", integer);

    int charCount = strlen(buffer);

    struct Object *stringObject = stringNew(gc, charCount);

    for (Integer i = 0; i < charCount; i++)
    {
        stringObject->value.string->characters[i] = buffer[i];
    }

    return stringObject;
}