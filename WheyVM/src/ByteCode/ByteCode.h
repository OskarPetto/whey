#ifndef BYTE_CODE_H
#define BYTE_CODE_H

#include <stdint.h>
#include "Constant.h"
#include "Function.h"

struct ByteCode
{
    uint32_t byteCount;

    uint16_t constantCount;
    struct Constant **constants;

    uint16_t functionCount;
    struct Function **functions;
};

struct ByteCode *byteCodeNew(char *fileName);

struct Constant *byteCodeGetConstant(struct ByteCode *byteCode, uint16_t constantIndex);

struct Function *byteCodeGetFunction(struct ByteCode *byteCode, uint16_t functionIndex);

void byteCodeFree(struct ByteCode *byteCode);

#endif