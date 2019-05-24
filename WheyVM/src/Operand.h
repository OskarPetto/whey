#ifndef OPERAND_H
#define OPERAND_H

#include <stdint.h>
#include "Object/Object.h"

typedef int32_t Int;
typedef float Float;
typedef uint32_t Character;

#define OPERAND_TYPE_INT            0x01
#define OPERAND_TYPE_FLOAT          0x02
#define OPERAND_TYPE_REFERENCE      0x03

#define BOOL_FALSE 0 
#define BOOL_TRUE 1

union OperandValue 
{
    Int int_value;
    Float float_value;
    struct Object *reference;
};

struct Operand 
{
    uint8_t type;
    union OperandValue value;
};

#endif