#ifndef OBJECT_H
#define OBJECT_H

#include <stdint.h>
#include "Gc.h"
#include "Array.h"
#include "Map.h"
#include "Pair.h"
#include "String.h"

#define OBJECT_TYPE_INTEGER            0x01
#define OBJECT_TYPE_FLOATING           0x02
#define OBJECT_TYPE_ARRAY              0x03
#define OBJECT_TYPE_MAP                0x04
#define OBJECT_TYPE_PAIR               0x05
#define OBJECT_TYPE_STRING             0x06

#define OBJECT_MARK_FALSE              0x00
#define OBJECT_MARK_TRUE               0x01 

#define BOOLEAN_TRUE 1
#define BOOLEAN_FALSE 0

typedef int32_t Integer;
typedef float Floating;

union ObjectValue {
    Integer integer_value;
    Floating floating_value;
    struct Array *array;
    struct Map *map;
    struct Pair *pair;
    struct String *string;
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
void objectMark(struct Object *object);
void objectFree(struct Object *object);

#endif