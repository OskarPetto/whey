#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdint.h>

struct Function
{
    uint8_t maxArgumentCount;
    uint16_t opCodeCount;
    uint8_t *opCodes;
};

struct Function *functionNew(uint8_t *bytes, uint32_t *byteIndex);

void functionFree(struct Function *function);

#endif