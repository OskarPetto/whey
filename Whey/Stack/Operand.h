#ifndef OPERAND_H
#define OPERAND_H

#include "../Types.h"

struct Object;

union OperandValue 
{
    Integer integerValue;
    Double doubleValue;
    struct Object *reference;
};

struct Operand 
{
    uint8_t type;
    union OperandValue value;
};

#endif