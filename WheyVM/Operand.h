#ifndef OPERAND_H
#define OPERAND_H

#include "Object/Types.h"

#define OPERAND_TYPE_INTEGER        0x01
#define OPERAND_TYPE_DOUBLE         0x02
#define OPERAND_TYPE_REFERENCE      0x03

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