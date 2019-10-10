#include "../Double.h"
#include "../Object.h"
#include "../String.h"

#include <stdio.h>
#include <string.h>

#define DOUBLE_BUFFER_SIZE 40

struct Object *doubleNew(struct Gc *gc, Double value)
{
    struct Object *double1 = gcObjectNew(gc, OBJECT_TYPE_DOUBLE, 0);
    double1->value.doubleValue = value;
    return double1;
}

struct Object *doubleToString(struct Gc *gc, struct Object *doble)
{
    uint32_t charCount = doubleStringCharacterCount(doble);
 
    struct Object *stringObject = stringNew(gc, charCount);

    uint32_t index = 0;

    doubleWriteToString(doble, stringObject, &index);

    return stringObject;
}

void doubleFree(struct Gc *gc, struct Object *doble)
{
    gcObjectFree(gc, doble, sizeof(struct Object));
}

uint32_t doubleStringCharacterCount(struct Object *doble)
{
    Double value = doble->value.doubleValue;
    return snprintf(NULL, 0, DOUBLE_FORMAT_STRING, value);
}

void doubleWriteToString(struct Object *doble, struct Object *stringObject, uint32_t *index)
{
    struct String *string = stringObject->value.subObject;
    Double value = doble->value.doubleValue;
    uint32_t charCount = doubleStringCharacterCount(doble);

    char buffer[DOUBLE_BUFFER_SIZE];

    snprintf(buffer, charCount + 1, DOUBLE_FORMAT_STRING, value);

    memcpy(&(string->characters[*index]), buffer, charCount);

    *index = (*index) + charCount;
}
