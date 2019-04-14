#ifndef OBJECT_H
#define OBJECT_H

#include <stdint.h>
#include "HeapObject.h"

union ObjectValue {
    uint8_t boolean;
    int64_t integer;
    double floatingPoint;
    struct HeapObject *heapObject;
};

struct Object
{
    uint8_t type;
    union ObjectValue value;
};

struct Object *objectFromType(uint8_t type);
struct Object *objectFromConstant(struct Constant *constant);

#endif