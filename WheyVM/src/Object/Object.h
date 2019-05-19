#ifndef OBJECT_H
#define OBJECT_H

#include <stdbool.h>

#include "Whey.h"
#include "Integer.h"
#include "Float.h"
#include "Lambda.h"
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

typedef float Float;
typedef int32_t Integer; 

union ObjectValue {
    Integer integer_value;
    Float float_value;
    struct Lambda *lambda;
    struct Array *array;
    struct Map *map;
    struct Pair *pair;
};

struct Object
{
    Flag type;
    Flag mark;
    union ObjectValue value;
};

struct Object *objectNew(Flag type);
struct Object *objectConst(struct Constant *constant);
struct Object *objectLoad(struct Object *object);
struct Object *objectStore(struct Object *object);
struct Object *objectCopy(struct Object *object);
Integer objectEquals(struct Object *object1, struct Object *object2);
Integer objectHash(struct Object *object);
struct Object *objectToString(struct Object *object);
void objectMark(struct Object *object);
void objectFree(struct Object *object);

#endif