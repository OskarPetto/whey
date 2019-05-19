#ifndef CONSTANT_H
#define CONSTANT_H

#include "Whey.h"
#include "Function.h"
#include "String.h"

#define CONSTANT_TYPE_UNDEFINED          0x00
#define CONSTANT_TYPE_BOOLEAN            0x01
#define CONSTANT_TYPE_INTEGER            0x02
#define CONSTANT_TYPE_FLOAT              0x03
#define CONSTANT_TYPE_LAMBDA             0x04
#define CONSTANT_TYPE_ARRAY              0x06
#define CONSTANT_NUM_TYPES               0x07

union ConstantValue
{
    Integer integer_value;
    Float float_value;
    struct Function *function;
    struct String *string;
};

struct Constant
{
    Flag type;
    union ConstantValue value;
};

struct Constant *constantNew(uint8_t *bytes, uint32_t *fileIndex);

void constantFree(struct Constant *constant);

#endif