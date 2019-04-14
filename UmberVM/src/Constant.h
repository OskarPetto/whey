#pragma once

#include <stdint.h>
#include "Umber.h"
#include "Utf8.h"
#include "Prototype.h"
#include "Array.h"

struct Constant
{
    uint8_t type;
    union ConstantValue *value;
};

union ConstantValue
{
    uint8_t boolean;
    int64_t integer;
    double floatingPoint;
    struct Utf8 *utf8;
    struct Prototype *prototype;
    struct Array *array;
};

struct Constant *constantFromBytes(uint8_t *bytes, uint32_t *index);

void freeConstant(struct Constant *constant);