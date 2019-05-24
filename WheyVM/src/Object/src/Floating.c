#include "../Floating.h"

#define FLOAT_STRING_BUFFER_SIZE 50

struct Object *floatingNew(struct Gc *gc, Floating value)
{
    struct Object *floating1 = objectNew(gc, OBJECT_TYPE_FLOATING);
    floating1->value.floating_value = value;
    return floating1;
}

struct Object *floatToString(struct Gc *gc, Floating floating)
{
    char buffer[FLOAT_STRING_BUFFER_SIZE];
 
    snprintf(buffer, FLOAT_STRING_BUFFER_SIZE, "%.10e", floating);

    int charCount = strlen(buffer);

    struct Object *stringObject = stringNew(gc, charCount);

    for (Integer i = 0; i < charCount; i++)
    {
        stringObject->value.string->characters[i] = buffer[i];
    }

    return stringObject;
}