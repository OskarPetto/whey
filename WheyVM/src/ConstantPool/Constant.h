#ifndef CONSTANT_H
#define CONSTANT_H

#include "Function.h"
#include "StringConstant.h"

#define CONSTANT_TYPE_INTEGER            0x01
#define CONSTANT_TYPE_DOUBLE             0x02
#define CONSTANT_TYPE_FUNCTION           0x03
#define CONSTANT_TYPE_STRING             0x04

typedef double DoubleConstant;
typedef int32_t IntegerConstant; 

union ConstantValue
{
    IntegerConstant integerConstant;
    DoubleConstant doubleConstant;
    struct Function *function;
    struct StringConstant *stringConstant;
};

struct Constant
{
    uint8_t type;
    union ConstantValue value;
};

struct Constant *constantNew(uint8_t *bytes, uint32_t *fileIndex);

void constantFree(struct Constant *constant);

#endif