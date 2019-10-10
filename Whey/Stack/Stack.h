#ifndef STACK_H
#define STACK_H

#include "../Class/Method.h"
#include "../Class/Constant.h"
#include "Operand.h"
#include "../Types.h"

#define OPERAND_STACK_SIZE(frame) (frame->operandStackPointer - frame->operandStack)

#define OPERAND_STACK_PUSH(frame) (frame->operandStackPointer++)

#define OPERAND_STACK_POP(frame) (--frame->operandStackPointer)

#define OPERAND_STACK_PEEK(frame) (frame->operandStackPointer - 1)

struct Frame
{
    struct Frame *prev;

    struct Method *method;
    struct ConstantTable *constantTable;

    struct Operand *arguments;
    struct Operand *locals;

    uint8_t *instructionPointer;

    struct Operand *operandStackPointer;
    struct Operand *operandStack;
};

struct Stack
{
    uint32_t maxSize;
    uint32_t size;

    struct Frame *callStackPointer;
    struct Frame *callStack;
};

struct Stack *stackNew(uint32_t maxSize);

struct Frame *stackPush(struct Stack *stack, struct Method *method, struct ConstantTable *constantTable);
struct Frame *stackPop(struct Stack *stack);

void stackPrint(struct Stack *stack);

void stackMark(struct Stack *stack);

void stackFree(struct Stack *stack);

#endif