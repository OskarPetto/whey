#ifndef WHEYVM_H
#define WHEYVM_H

#include <stdint.h>
#include "Frame.h"
#include "Constant/ConstantPool.h"
#include "OpCode.h"
#include "Object/Gc.h"
#include "Operand.h"

#define WHEYVM_VERSION_MAJOR "0"
#define WHEYVM_VERSION_MINOR "1"

#define WHEYVM_VERSION "Whey " WHEY_VERSION_MAJOR "." WHEY_VERSION_MINOR

#define WHEYVM_VALUE_STACK_SIZE 255
#define WHEYVM_OBJECT_STACK_SIZE 255
#define WHEYVM_CALL_STACK_SIZE 255

typedef void (*Instruction)(struct WheyVM *wvm);

struct WheyVM 
{
    struct Operand operandStack[WHEYVM_VALUE_STACK_SIZE];

    uint8_t operandStackPointer;

    struct Frame callStack[WHEYVM_CALL_STACK_SIZE];

    uint8_t callStackPointer;

    struct Gc gc;

    struct ConstantPool constantPool;

    Instruction dispatchTable[256];

};

#endif