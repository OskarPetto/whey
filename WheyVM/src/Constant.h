#ifndef CONSTANT_H
#define CONSTANT_H

#include <stdint.h>
#include "Whey.h"
#include "Utf8.h"

struct Constant
{
    uint8_t type;
    union ConstantValue value;
};

union ConstantValue
{
    uint8_t boolean;
    int64_t integer;
    double floatingPoint;
    struct Utf8 *utf8;
};

struct Constant *constantFromBytes(uint8_t *bytes, uint32_t *index);

void freeConstant(struct Constant *constant);

#endif