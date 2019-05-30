#ifndef WHEYVM_H
#define WHEYVM_H

#include <stdint.h>
#include "Frame.h"
#include "lib/Operand/Operand.h"
#include "lib/Operand/Gc.h"
#include "lib/WcFile/WcFile.h"

#define WHEYVM_OPERAND_STACK_SIZE 255
#define WHEYVM_CALL_STACK_SIZE 1000

struct WheyVM 
{
    struct Operand operandStack[WHEYVM_OPERAND_STACK_SIZE];

    uint8_t operandStackPointer;

    struct Frame callStack[WHEYVM_CALL_STACK_SIZE];

    uint16_t callStackPointer;

    struct Gc *gc;

    struct WcFile *wcFile;

};

#endif