#ifndef OBJECT_H
#define OBJECT_H

#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>
#include "Array.h"
#include "Map.h"
#include "GC.h"

#define OBJECT_TYPE_BOOLEAN            0x00
#define OBJECT_TYPE_INTEGER            0x01
#define OBJECT_TYPE_DOUBLE             0x02
#define OBJECT_TYPE_ARRAY              0x04
#define OBJECT_TYPE_MAP                0x05
#define OBJECT_TYPE_PAIR               0x06

#define OBJECT_MARK_FALSE              0x00
#define OBJECT_MARK_TRUE               0x01

#define OBJECT_STRING_BUFFER_SIZE      50

union ObjectValue {
    int64_t integer_value;
    double double_value;
    struct Array *array;
    struct Map *map;
    struct Pair *pair;
};

struct Object
{
    uint8_t type;
    uint8_t mark;
    union ObjectValue value;
};

void opOCopy(struct Object *object, struct Object *copy);
void opOEq(struct Object *object1, struct Object *object2, struct Object *isEqual);
void opONeq(struct Object *object1, struct Object *object2, struct Object *isNotEqual);
void opOHash(struct Object *object, struct Object *hash);
void opOString(struct Object *object, struct Object *string);

void objectNew(struct Object *object, uint8_t type);
void objectCopy(struct Object *object, struct Object *copy);
bool objectEquals(struct Object *object1, struct Object *object2);
size_t objectHash(struct Object *object);
void objectToString(struct Object *object, struct Object *string);

void objectMark(struct Object *object);
void objectFree(struct Object *object);

#endif