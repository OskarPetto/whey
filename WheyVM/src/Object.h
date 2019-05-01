#ifndef OBJECT_H
#define OBJECT_H

#include <stdint.h>
#include "Closure.h"
#include "Array.h"

#define CONSTANT_INTEGER           0x00
#define CONSTANT_FLOATING_POINT    0x01
#define CONSTANT_UTF8              0x02 
#define CONSTANT_PROTOTYPE         0x03
#define CONSTANT_ARRAY             0x04

#define OPERAND_NULL               0x00
#define OPERAND_BOOLEAN            0x01
#define OPERAND_INTEGER            0x02
#define OPERAND_FLOATING_POINT     0x03
#define OPERAND_CLOSURE            0x04
#define OPERAND_VECTOR             0x05
#define OPERAND_OBJECT             0x06

union ObjectValue {
    int64_t integer;
    double floatingPoint;
    struct Closure *closure;
    struct Array *vector;
};

struct Object
{
    uint8_t type;
    union ObjectValue value;
};

struct Object *objectFromType(uint8_t type);
struct Object *objectFromConstant(struct Constant *constant);
void freeObject(struct Object *object);

#endif