#include "../Stack.h"
#include "../../Class/Constant.h"
#include "../../Object/Object.h"
#include "../../Object/Gc.h"
#include "../../Object/Integer.h"
#include "../../Object/Double.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define GET_METHOD_NAME_CONSTANT(frame) frame->class->constants[frame->method->nameIndex]->value.stringConstant

#define STACK_MALLOC_CHECK(result) NOT_NULL_CHECK(result, ERRCODE_INTERNAL, "Create stack error malloc failed\n")

#define STACK_OVERFLOW_CHECK(newStackSize, stack)  ERROR_CHECK(newStackSize > stack->maxSize, ERRCODE_RUNTIME, "Stack overflow with %d/%d. Set stack size with the 's' option\n", newStackSize, stack->maxSize)                                                                                                                                                                                                                                                                                                                                                       

#define METHOD_INFO(constantTable, method, instruction, byteIndex)                                                                                                                                                   \
    do                                                                                                                                                                                       \
    {                                                                                                                                                                                        \
        struct StringConstant *classNameConstant = constantTable->constants[0].value.stringConstant;                                                                                        \
        if (method->nameIndex == 0)                                                                                                                                                          \
        {                                                                                                                                                                                    \
            printf("\tat "STRING_FORMAT_STRING".%s(%s:%u)\n", classNameConstant->characterCount, classNameConstant->characters, "main", instructionStrings[instruction], byteIndex);                                                                         \
        }                                                                                                                                                                                    \
        else                                                                                                                                                                                 \
        {                                                                                                                                                                                    \
            struct StringConstant *methodNameConstant = constantTable->constants[method->nameIndex].value.stringConstant;                                                                   \
            printf("\tat "STRING_FORMAT_STRING"."STRING_FORMAT_STRING"(%s:%u)\n", (uint32_t)classNameConstant->characterCount, classNameConstant->characters, (uint32_t)methodNameConstant->characterCount, methodNameConstant->characters, instructionStrings[instruction], byteIndex); \
        }                                                                                                                                                                                    \
    } while (0)

struct Stack *stackNew(uint32_t maxSize)
{
    void *memory = malloc(sizeof(struct Stack));
    STACK_MALLOC_CHECK(memory);
    struct Stack *stack = memory;

    stack->size = 0;

    void *stackMemory = malloc(maxSize);
    STACK_MALLOC_CHECK(stackMemory);

    stack->maxSize = maxSize;
    stack->callStack = stackMemory;
    stack->callStackPointer = NULL;

    return stack;
}

struct Frame *stackPush(struct Stack *stack, struct Method *method, struct ConstantTable *constantTable)
{
    struct Frame *newFrame = (void *)stack->callStack + stack->size;

    uint32_t newSize = sizeof(struct Frame) + (method->argumentCount + method->localsCount + method->maxOperandCount) * sizeof(struct Operand);

    uint32_t newStackSize = stack->size + newSize;

    STACK_OVERFLOW_CHECK(newStackSize, stack);

    stack->size = newStackSize;

    struct Frame *currentFrame = stack->callStackPointer;

    newFrame->locals = (void *) newFrame + sizeof(struct Frame);
    newFrame->constantTable = constantTable;
    newFrame->method = method;
    newFrame->operandStack = (void *) newFrame->locals + method->localsCount * sizeof(struct Operand);
    newFrame->operandStackPointer = newFrame->operandStack;
    newFrame->instructionPointer = method->byteCode;
    newFrame->prev = currentFrame;

    if (currentFrame != NULL && method->argumentCount > 0)
    {
        currentFrame->operandStackPointer -= method->argumentCount;  // pop arguments
        newFrame->arguments = (void *) newFrame->operandStack + method->maxOperandCount * sizeof(struct Operand);

        for (size_t i = 0; i < method->argumentCount; i++)
        {
            (newFrame->arguments + i)->type = (currentFrame->operandStackPointer + i)->type;
            (newFrame->arguments + i)->value = (currentFrame->operandStackPointer + i)->value;
        }

    }

    stack->callStackPointer = newFrame;

    return newFrame;
}

struct Frame *stackPop(struct Stack *stack)
{
    struct Frame *currFrame = stack->callStackPointer;

    if (currFrame == NULL)
        return NULL;

    struct Method *currMethod = currFrame->method;
    struct Frame *previousFrame = currFrame->prev;

    if (currMethod->returnsSomething)
    {
        memcpy(OPERAND_STACK_PUSH(previousFrame), OPERAND_STACK_PEEK(currFrame), sizeof(struct Operand));
    }

    uint32_t frameSize = sizeof(struct Frame) + (currMethod->argumentCount + currMethod->localsCount + currMethod->maxOperandCount) * sizeof(struct Operand);

    stack->size -= frameSize;

    if (previousFrame != NULL)
    {
        previousFrame->instructionPointer += 3;
    }

    stack->callStackPointer = previousFrame;

    return previousFrame;
}

void stackPrint(struct Stack *stack)
{
    struct Frame *current = stack->callStackPointer;

    while (current != NULL)
    {
        struct Method *method = current->method;
        struct ConstantTable *constantTable = current->constantTable;
        uint32_t byteIndex = current->instructionPointer - method->byteCode;
        uint8_t instruction = *current->instructionPointer;
        METHOD_INFO(constantTable, method, instruction, byteIndex);
        current = current->prev;
    }
}

void stackMark(struct Stack *stack)
{
    struct Frame *current = stack->callStackPointer;

    while (current != NULL)
    {
        struct Method *method = current->method;

        for (uint8_t i = 0; i < method->argumentCount; i++)
        {
            struct Operand *argument = current->arguments + i;

            if (argument->type == OPERAND_TYPE_REFERENCE)
            {
                objectMark(argument->value.reference);
            }
        }

        for (uint8_t i = 0; i < method->localsCount; i++)
        {
            struct Operand *local = current->locals + i;

            if (local->type == OPERAND_TYPE_REFERENCE)
            {
                objectMark(local->value.reference);
            }
        }

        if (current->operandStackPointer != NULL)
        {
            for (struct Operand *i = current->operandStack; i <= current->operandStackPointer; i++)
            {
                if (i->type == OPERAND_TYPE_REFERENCE)
                {
                    objectMark(i->value.reference);
                }
            }
        }

        current = current->prev;
    }
}

void stackFree(struct Stack *stack)
{
    free(stack->callStack);
    free(stack);
}