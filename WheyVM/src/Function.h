#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdint.h>

struct Function
{
    uint8_t maxLocalVariableCount;

    uint32_t codeLength;
    uint8_t *code;
};

struct Function *functionFromBytes(uint8_t *bytes, uint32_t *index);

void freeFunction(struct Function *function);

#endif