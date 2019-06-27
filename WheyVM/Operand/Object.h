#ifndef OBJECT_H
#define OBJECT_H

#include "Types.h"
#include <stdint.h>
#include "Gc.h"
#include "Array.h"
#include "Map.h"
#include "Pair.h"
#include "String.h"

#define OBJECT_TYPE_INTEGER            0x01
#define OBJECT_TYPE_DOUBLE             0x02
#define OBJECT_TYPE_ARRAY              0x03
#define OBJECT_TYPE_STRING             0x04
#define OBJECT_TYPE_MAP                0x05
#define OBJECT_TYPE_PAIR               0x06

#define OBJECT_MARK_FALSE              0x00
#define OBJECT_MARK_TRUE               0x01 

union ObjectValue {
    Integer integerValue;
    Double doubleValue;
    struct Array *array;                // must not be NULL
    struct Map *map;                    // must not be NULL
    struct Pair *pair;                  // must not be NULL 
    struct String *string;              // must not be NULL 
};

struct Object
{
    uint8_t type;
    uint8_t mark;
    union ObjectValue value;
};

struct Object *objectCopy(struct Gc *gc, struct Object *object);
Integer objectEquals(struct Object *object1, struct Object *object2);
Integer objectHash(struct Object *object);
struct Object *objectToString(struct Gc *gc, struct Object *object);

struct Object *objectNew(struct Gc *gc, uint8_t type);
uint32_t objectMark(struct Object *object);
void objectFree(struct Gc *gc, struct Object *object);

#endif