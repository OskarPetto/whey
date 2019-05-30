#ifndef FRAME_H
#define FRAME_H

#include "Operand.h"

struct Frame
{
    struct Operand *locals;

    uint16_t byteCount;
    unsigned char *bytes;

    uint16_t instructionPointer;
};


#endif