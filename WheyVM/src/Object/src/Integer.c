#include "../Integer.h"
#include "../Array.h"
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

    struct Object *stringObject = stringNew(gc, buffer);

    return stringObject;
}