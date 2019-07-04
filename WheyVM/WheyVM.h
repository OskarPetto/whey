#ifndef WHEYVM_H
#define WHEYVM_H

#include <stdint.h>
#include "Frame.h"
#include "Operand/Operand.h"
#include "Operand/Gc.h"
#include "WcFile/WcFile.h"

#define WHEYVM_STATE_STOPPED  1
#define WHEYVM_STATE_DEBUG    2 

struct WheyVM 
{
    struct Operand *operandStack;

    int32_t operandStackPointer;
    int32_t operandStackSize;

    struct Frame **callStack;

    int32_t callStackPointer;
    int32_t callStackSize;

    struct Gc *gc;

    struct WcFile *wcFile;

    uint8_t state;

    uint64_t executedInstructions;
};

int wvmRun(struct WcFile *wcFile, uint16_t callStackSize, uint16_t operandStackSize, uint64_t gcMemorySize, uint8_t state);

#endif