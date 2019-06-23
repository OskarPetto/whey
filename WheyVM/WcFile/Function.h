#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdint.h>

struct Function
{
    uint8_t argumentCount;
    uint8_t localsCount;
    uint16_t codeSize;
    unsigned char *byteCode;
};

struct Function *functionNew(uint8_t *bytes, uint32_t *byteIndex);

void functionFree(struct Function *function);

#endif