#include "../Double.h"
#include "../Object.h"
#include "../Integer.h"
#include "../Array.h"

#include <stdio.h>
#include <string.h>

#define FLOAT_STRING_BUFFER_SIZE 50

struct Object *doubleNew(struct Gc *gc, Double value)
{
    struct Object *double1 = objectNew(gc, OBJECT_TYPE_DOUBLE);
    double1->value.doubleValue = value;
    return double1;
}

struct Object *doubleToString(struct Gc *gc, Double double1)
{
    char buffer[FLOAT_STRING_BUFFER_SIZE];
 
    snprintf(buffer, FLOAT_STRING_BUFFER_SIZE, "%.10e", double1);

    struct Object *stringObject = stringNew(gc, buffer);

    return stringObject;
}