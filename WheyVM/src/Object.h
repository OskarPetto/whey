#ifndef OBJECT_H
#define OBJECT_H

#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>
#include "Lambda.h"
#include "String.h"
#include "Array.h"
#include "Map.h"
#include "Pair.h"

#define OBJECT_TYPE_UNDEFINED          0x00
#define OBJECT_TYPE_BOOLEAN            0x01
#define OBJECT_TYPE_INTEGER            0x02
#define OBJECT_TYPE_FLOAT              0x03
#define OBJECT_TYPE_LAMBDA             0x04
#define OBJECT_TYPE_ARRAY              0x06
#define OBJECT_TYPE_MAP                0x07
#define OBJECT_TYPE_PAIR               0x08
#define OBJECT_NUM_TYPES               0x09

#define OBJECT_MARK_FALSE              0x00
#define OBJECT_MARK_TRUE               0x01

union ObjectValue {
    int32_t integer_value;
    float float_value;
    struct Lambda *lambda;
    struct String *string;
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

void opONew(uint8_t type, struct Object *newObject);
void opOConst(uint16_t constantIndex, struct Object *constObject);
void opOCopy(struct Object *object, struct Object *copy);
void opOEq(struct Object *object1, struct Object *object2, struct Object *isEqual);
void opOHash(struct Object *object, struct Object *hash);
void opOToString(struct Object *object, struct Object *string);

struct Object *objectNew(uint8_t type);
struct Object *objectConstant(uint16_t constantIndex);
struct Object *objectCopy(struct Object *object);
bool objectEquals(struct Object *object1, struct Object *object2);
uint16_t objectHash(struct Object *object);
struct Object *objectToString(struct Object *object);

void objectMark(struct Object *object);
void objectFree(struct Object *object);

#endif