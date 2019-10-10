#ifndef METHOD_H
#define METHOD_H

#include <stdint.h>
#include "Constant.h"

struct Method
{
    uint16_t nameIndex;
    uint8_t argumentCount;
    uint8_t returnsSomething;
    uint8_t localsCount;
    uint8_t maxOperandCount;
    uint16_t codeSize;
    uint8_t *byteCode;
};

struct MethodTable
{
    uint16_t methodCount;
    struct Method *methods; // index 0 is main
};

struct MethodTable *methodTableNew(char *fileName, uint8_t *bytes, uint32_t *byteIndex, uint32_t byteCount, uint8_t debug);

void methodTableFree(struct MethodTable *methodTable);

#endif