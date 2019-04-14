#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <stdint.h>

struct Prototype
{
    uint8_t parameterCount;
    uint8_t maxStackSize;

    uint32_t codeLength;
    uint8_t *code;
};

struct Prototype *prototypeFromBytes(uint8_t *bytes, uint32_t *index);

void freePrototype(struct Prototype *prototype);

#endif