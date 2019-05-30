#ifndef WHEYVM_H
#define WHEYVM_H

#include <stdint.h>
#include "Frame.h"
#include "Object/Object.h"
#include "Object/Gc.h"
#include "WcFile/WcFile.h"

#define WHEYVM_VERSION_MAJOR "0"
#define WHEYVM_VERSION_MINOR "1"

#define WHEYVM_VERSION "Whey " WHEY_VERSION_MAJOR "." WHEY_VERSION_MINOR

#define WHEYVM_OPERAND_STACK_SIZE 255
#define WHEYVM_CALL_STACK_SIZE 255

struct WheyVM 
{
    struct Operand operandStack[WHEYVM_OPERAND_STACK_SIZE];

    uint8_t operandStackPointer;

    struct Frame callStack[WHEYVM_CALL_STACK_SIZE];

    uint8_t callStackPointer;

    struct Gc gc;

    struct ConstantPool constantPool;

    Instruction dispatchTable[256];

};

#endif