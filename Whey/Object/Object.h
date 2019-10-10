#ifndef OBJECT_H
#define OBJECT_H

#include "../Types.h"
#include <stdint.h>
#include "Gc.h"

struct Object;
struct String;

union ObjectValue {
    Integer integerValue;
    Double doubleValue;
    void *subObject;                   
};

struct Object
{
    uint8_t type;                       // mark is encoded in the MSB
    struct Object *next;                // for GC
    union ObjectValue value;
};

struct Object *objectCopy(struct Gc *gc, struct Object *object);
Integer objectEquals(struct Object *object1, struct Object *object2);
Integer objectHash(struct Object *object);
struct Object *objectToString(struct Gc *gc, struct Object *object);

void objectMark(struct Object *object);
void objectFree(struct Gc *gc, struct Object *object);

uint32_t objectStringCharacterCount(struct Object *object);
void objectWriteToString(struct Object *object, struct Object *stringObject, uint32_t *index);

#endif