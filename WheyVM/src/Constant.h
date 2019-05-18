#ifndef CONSTANT_H
#define CONSTANT_H

#include "BooleanConstant.h"
#include "IntegerConstant.h"
#include "FloatConstant.h"
#include "LambdaConstant.h"
#include "ArrayConstant.h"

#define OBJECT_TYPE_UNDEFINED          0x00
#define OBJECT_TYPE_BOOLEAN            0x01
#define OBJECT_TYPE_INTEGER            0x02
#define OBJECT_TYPE_FLOAT              0x03
#define OBJECT_TYPE_LAMBDA             0x04
#define OBJECT_TYPE_ARRAY              0x06
#define OBJECT_TYPE_MAP                0x07
#define OBJECT_TYPE_PAIR               0x08
#define OBJECT_NUM_TYPES               0x09

union ConstantValue
{
    int32_t integer_value;
    float float_value;
    struct LambdaConstant *lambdaConstant;
    struct ArrayConstant *arrayConstant;
};

struct Constant
{
    uint8_t type;
    union ConstantValue value;
};

#endif