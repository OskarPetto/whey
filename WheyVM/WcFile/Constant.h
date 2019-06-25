#ifndef CONSTANT_H
#define CONSTANT_H

#include <stdint.h>

#define CONSTANT_TYPE_INTEGER            0x01
#define CONSTANT_TYPE_DOUBLE             0x02
#define CONSTANT_TYPE_STRING             0x04

typedef double DoubleConstant;
typedef int64_t IntegerConstant; 

struct StringConstant
{
    uint16_t characterCount;
    char *characters;
};

union ConstantValue
{
    IntegerConstant integerConstant;
    DoubleConstant doubleConstant;
    struct StringConstant *stringConstant;
};

struct Constant
{
    uint8_t type;
    union ConstantValue value;
};

struct Constant *constantNew(uint8_t *bytes, uint32_t *byteIndex);

void constantFree(struct Constant *constant);

#endif