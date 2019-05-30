#ifndef FRAME_H
#define FRAME_H

#include "lib/Operand/Operand.h"

struct Frame
{
    struct Operand *locals;

    uint16_t codeSize;
    unsigned char *byteCode;

    uint16_t codePointer;
};


#endif