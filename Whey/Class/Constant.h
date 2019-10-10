#ifndef CONSTANT_H
#define CONSTANT_H

#include <stdint.h>
#include "../Types.h"

#define ASSERT_READ_IN_BOUNDS(byteIndex, readSize, byteCount) ASSERT(byteIndex + readSize <= byteCount, ERRCODE_CLASS, "Read at %u out of bounds\n", byteIndex)

struct StringConstant
{
    uint32_t characterCount;
    char *characters;
};

union ConstantValue
{
    Integer integerConstant;
    Double doubleConstant;
    struct StringConstant *stringConstant;
};

struct Constant
{
    uint8_t type;
    union ConstantValue value;
};

struct ConstantTable
{
    uint16_t constantCount;
    struct Constant *constants;    // index 0 is class name
};

struct ConstantTable *constantTableNew(char *fileName, uint8_t *bytes, uint32_t *byteIndex, uint32_t byteCount, uint8_t debug);

void constantTableFree(struct ConstantTable *constantTable);

#endif