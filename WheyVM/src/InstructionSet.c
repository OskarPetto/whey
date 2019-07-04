#include "../InstructionSet.h"
#include "../WheyVM.h"
#include "../Frame.h"
#include "../Operand/Operand.h"
#include "../Operand/Array.h"
#include "../Operand/Double.h"
#include "../Operand/Gc.h"
#include "../Operand/Integer.h"
#include "../Operand/Map.h"
#include "../Operand/Object.h"
#include "../Operand/Pair.h"
#include "../Operand/String.h"
#include "../Operand/Types.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define STOP(wvm) wvm->state |= WHEYVM_STATE_STOPPED

#define CURRENT_FRAME(wvm) ((wvm->callStack[wvm->callStackPointer]))

#define OP_JUMP(frame)                                                                    \
    do                                                                                    \
    {                                                                                     \
        uint16_t codePointer = frame->codePointer;                                         \
        int16_t relativeLocation;                                                         \
        memcpy(&relativeLocation, &frame->function->byteCode[codePointer + 1], 2);        \
        assert(relativeLocation != 0);                                                    \
        uint16_t newLocation = codePointer + relativeLocation;                            \
        assert(newLocation >= 0 && newLocation < frame->function->codeSize);              \
        frame->codePointer = newLocation;                                                 \
    } while (0)

#define OP_COMPARISON(wvm, operator)                                                                                                             \
    do                                                                                                                                           \
    {                                                                                                                                            \
        assert(wvm->operandStackPointer > 0);                                                                                                    \
        struct Operand operand1 = wvm->operandStack[wvm->operandStackPointer--];                                                                 \
        struct Operand operand2 = wvm->operandStack[wvm->operandStackPointer];                                                                   \
        assert(operand1.type == operand2.type);                                                                                                  \
        wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;                                                                 \
        switch (operand1.type)                                                                                                                   \
        {                                                                                                                                        \
        case OPERAND_TYPE_INTEGER:                                                                                                               \
            wvm->operandStack[wvm->operandStackPointer].value.integerValue = (operand2.value.integerValue operator operand1.value.integerValue); \
            break;                                                                                                                               \
        case OPERAND_TYPE_DOUBLE:                                                                                                                \
            wvm->operandStack[wvm->operandStackPointer].value.integerValue = (operand2.value.doubleValue operator operand1.value.doubleValue);   \
            break;                                                                                                                               \
        case OPERAND_TYPE_REFERENCE:                                                                                                             \
            wvm->operandStack[wvm->operandStackPointer].value.integerValue = (operand2.value.reference operator operand1.value.reference);       \
            break;                                                                                                                               \
        }                                                                                                                                        \
    } while (0)

#define OP_ARITHMETIC(wvm, operator)                                                                                                             \
    do                                                                                                                                           \
    {                                                                                                                                            \
        assert(wvm->operandStackPointer > 0);                                                                                                    \
        struct Operand operand1 = wvm->operandStack[wvm->operandStackPointer--];                                                                 \
        struct Operand operand2 = wvm->operandStack[wvm->operandStackPointer];                                                                   \
        assert(operand1.type == operand2.type);                                                                                                  \
        assert(operand1.type != OPERAND_TYPE_REFERENCE);                                                                                         \
                                                                                                                                                 \
        switch (operand1.type)                                                                                                                   \
        {                                                                                                                                        \
        case OPERAND_TYPE_INTEGER:                                                                                                               \
            wvm->operandStack[wvm->operandStackPointer].value.integerValue = (operand2.value.integerValue operator operand1.value.integerValue); \
            break;                                                                                                                               \
        case OPERAND_TYPE_DOUBLE:                                                                                                                \
            wvm->operandStack[wvm->operandStackPointer].value.doubleValue = (operand2.value.doubleValue operator operand1.value.doubleValue);    \
            break;                                                                                                                               \
        }                                                                                                                                        \
    } while (0)

#define OP_INTEGER_BINARY(wvm, operator)                                                                                                     \
    do                                                                                                                                       \
    {                                                                                                                                        \
        assert(wvm->operandStackPointer > 0);                                                                                                \
        struct Operand * stack = wvm->operandStack;                                                                                          \
        int32_t pointer = wvm->operandStackPointer--;                                                                                        \
        Integer const value1 = stack[pointer].value.integerValue;                                                                            \
        Integer const value2 = stack[pointer-1].value.integerValue;                                                                          \
        assert(stack[pointer].type == OPERAND_TYPE_INTEGER);                                                                                 \
        assert(stack[pointer-1].type == OPERAND_TYPE_INTEGER);                                                                               \
        stack[pointer-1].value.integerValue = (value2 operator value1);                                                                      \
    } while (0)

#define OP_INTEGER_UNARY(wvm, operator)                                                                       \
    do                                                                                                        \
    {                                                                                                         \
        assert(wvm->operandStackPointer >= 0);                                                                \
        Integer const value = wvm->operandStack[wvm->operandStackPointer].value.integerValue;                 \
        assert(wvm->operandStack[wvm->operandStackPointer].type == OPERAND_TYPE_INTEGER);                     \
        wvm->operandStack[wvm->operandStackPointer].value.integerValue = operator value;                      \
    } while (0)

#define OP_DOUBLE_UNARY(wvm, fun)                                                                       \
    do                                                                                                  \
    {                                                                                                   \
        assert(wvm->operandStackPointer >= 0);                                                          \
        struct Operand operand = wvm->operandStack[wvm->operandStackPointer];                           \
        assert(operand.type == OPERAND_TYPE_DOUBLE);                                                    \
        wvm->operandStack[wvm->operandStackPointer].value.doubleValue = fun(operand.value.doubleValue); \
    } while (0)

void opUnknown(struct WheyVM *wvm, struct Frame *frame)
{
    fprintf(stderr, "Unknown opcode error with opcode %d\n", frame->function->byteCode[frame->codePointer]);
    exit(1);
}

void opHalt(struct WheyVM *wvm, struct Frame *frame)
{
    STOP(wvm);
}

void opJump(struct WheyVM *wvm, struct Frame *frame)
{
    OP_JUMP(frame);
}

void opJumpTrue(struct WheyVM *wvm, struct Frame *frame)
{
    if (wvm->operandStack[wvm->operandStackPointer--].value.integerValue)
    {
        OP_JUMP(frame);
    }
    else
    {
        frame->codePointer += 3;
    }
}

void opJumpFalse(struct WheyVM *wvm, struct Frame *frame)
{
    struct Operand currentOperand = wvm->operandStack[wvm->operandStackPointer--];
    assert(currentOperand.type == OPERAND_TYPE_INTEGER);

    if (!currentOperand.value.integerValue)
    {
        OP_JUMP(frame);
    }
    else
    {
        frame->codePointer += 3;
    }
}

void opLoad(struct WheyVM *wvm, struct Frame *frame)
{
    uint8_t localIndex = frame->function->byteCode[++frame->codePointer];
    ++frame->codePointer;
    frameGetLocal(frame, localIndex,&wvm->operandStack[++wvm->operandStackPointer]);
}

void opStore(struct WheyVM *wvm, struct Frame *frame)
{
    uint8_t localIndex = frame->function->byteCode[++frame->codePointer];
    frame->codePointer++;
    assert(wvm->operandStackPointer >= 0);
    frameSetLocal(frame, localIndex, &wvm->operandStack[wvm->operandStackPointer--]);
}

void opCall(struct WheyVM *wvm, struct Frame *frame)
{
    uint16_t functionIndex;
    memcpy(&functionIndex, &frame->function->byteCode[frame->codePointer + 1], 2);
    frame->codePointer += 3;
    struct Function *nextFunction = wcFileGetFunction(wvm->wcFile, functionIndex);

    struct Frame *nextFrame = frameNew(nextFunction);

    for (uint8_t i = 0; i < nextFunction->argumentCount; i++)
    {
        assert(wvm->operandStackPointer >= 0);
        frameSetLocal(nextFrame, i, &wvm->operandStack[wvm->operandStackPointer--]); // pass function arguments
    }

    wvm->callStack[++wvm->callStackPointer] = nextFrame;
}

void opReturn(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->callStackPointer >= 0);

    if (frame->iterator != NULL && frame->iterator->index + 1 < frame->iterator->array->value.array->objectCount)
    {
        frame->codePointer = 0;
        frame->iterator->index++;
        struct Operand operand;
        operand.type = OPERAND_TYPE_REFERENCE;
        operand.value.reference = frame->iterator->array->value.array->objects[frame->iterator->index];
        frameSetLocal(frame, 0, &operand);
        return;
    }

    if (wvm->callStackPointer == 0)
    {
        STOP(wvm);
    }

    wvm->callStackPointer--;
    frameFree(frame);
}

void opConstant(struct WheyVM *wvm, struct Frame *frame)
{
    uint16_t constantIndex;
    memcpy(&constantIndex, &frame->function->byteCode[frame->codePointer + 1], 2);
    frame->codePointer += 3;
    struct Constant *constant = wcFileGetConstant(wvm->wcFile, constantIndex);

    wvm->operandStackPointer++;

    switch (constant->type)
    {
    case CONSTANT_TYPE_INTEGER:
        wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;
        wvm->operandStack[wvm->operandStackPointer].value.integerValue = constant->value.integerConstant;
        break;
    case CONSTANT_TYPE_DOUBLE:
        wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_DOUBLE;
        wvm->operandStack[wvm->operandStackPointer].value.doubleValue = constant->value.doubleConstant;
        break;
    case CONSTANT_TYPE_STRING:
        wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_REFERENCE;
        struct Object *string = stringNew(wvm->gc, constant->value.stringConstant->characterCount);
        memcpy(string->value.string->characters, constant->value.stringConstant->characters, constant->value.stringConstant->characterCount * sizeof(Char));
        wvm->operandStack[wvm->operandStackPointer].value.reference = string;
        break;
    }
}

void opPrint(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    assert(wvm->operandStackPointer >= 0);
    struct Operand operand = wvm->operandStack[wvm->operandStackPointer--];

    switch (operand.type)
    {
    case OPERAND_TYPE_INTEGER:
        printf("%ld\n", operand.value.integerValue);
        break;
    case OPERAND_TYPE_DOUBLE:
        printf("%.10e\n", operand.value.doubleValue);
        break;
    case OPERAND_TYPE_REFERENCE:
        assert(operand.value.reference->type == OBJECT_TYPE_STRING);
        stringPrint(operand.value.reference->value.string);
        break;
    }
}

void opPop(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    assert(wvm->operandStackPointer >= 0);
    wvm->operandStackPointer--;
}

void opEqual(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    OP_COMPARISON(wvm, ==);
}

void opNotEqual(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    OP_COMPARISON(wvm, !=);
}

void opGreaterThan(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;

    OP_COMPARISON(wvm, >);
}

void opGreaterThanOrEqual(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    OP_COMPARISON(wvm, >=);
}

void opLessThan(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    OP_COMPARISON(wvm, <);
}

void opLessThanOrEqual(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    OP_COMPARISON(wvm, <=);
}

void opAdd(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    OP_ARITHMETIC(wvm, +);
}

void opSubtract(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    OP_ARITHMETIC(wvm, -);
}

void opMultiply(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    OP_ARITHMETIC(wvm, *);
}

void opDivide(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 0);
    frame->codePointer++;
    struct Operand operand1 = wvm->operandStack[wvm->operandStackPointer--];
    struct Operand operand2 = wvm->operandStack[wvm->operandStackPointer];
    assert(operand1.type == operand2.type);
    assert(operand1.type != OPERAND_TYPE_REFERENCE);
    wvm->operandStack[wvm->operandStackPointer].type = operand1.type;

    switch (operand1.type)
    {
    case OPERAND_TYPE_INTEGER:
        assert(operand2.value.integerValue != 0);
        wvm->operandStack[wvm->operandStackPointer].value.integerValue = (operand1.value.integerValue / operand2.value.integerValue);
        break;
    case OPERAND_TYPE_DOUBLE:
        assert(operand2.value.doubleValue != 0);
        wvm->operandStack[wvm->operandStackPointer].value.doubleValue = (operand1.value.doubleValue / operand2.value.doubleValue);
        break;
    }
}

void opPower(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 0);
    frame->codePointer++;
    struct Operand operand1 = wvm->operandStack[wvm->operandStackPointer--];
    struct Operand operand2 = wvm->operandStack[wvm->operandStackPointer];
    assert(operand1.type == operand2.type);
    assert(operand1.type != OPERAND_TYPE_REFERENCE);
    wvm->operandStack[wvm->operandStackPointer].type = operand1.type;

    switch (operand1.type)
    {
    case OPERAND_TYPE_INTEGER:
        wvm->operandStack[wvm->operandStackPointer].value.integerValue = (Integer)pow((double)operand1.value.integerValue, (double)operand2.value.integerValue);
        break;
    case OPERAND_TYPE_DOUBLE:
        wvm->operandStack[wvm->operandStackPointer].value.doubleValue = pow(operand1.value.doubleValue, operand2.value.doubleValue);
        break;
    }
}

void opNegate(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer >= 0);
    frame->codePointer++;
    struct Operand operand = wvm->operandStack[wvm->operandStackPointer];
    assert(operand.type != OPERAND_TYPE_REFERENCE);

    switch (operand.type)
    {
    case OPERAND_TYPE_INTEGER:
        wvm->operandStack[wvm->operandStackPointer].value.integerValue = -operand.value.integerValue;
        break;
    case OPERAND_TYPE_DOUBLE:
        wvm->operandStack[wvm->operandStackPointer].value.doubleValue = -operand.value.doubleValue;
        break;
    }
}

void opIntegerToDouble(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer >= 0);
    frame->codePointer++;
    assert(wvm->operandStack[wvm->operandStackPointer].type == OPERAND_TYPE_INTEGER);
    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_DOUBLE;
    wvm->operandStack[wvm->operandStackPointer].value.doubleValue = (Double)wvm->operandStack[wvm->operandStackPointer].value.integerValue;
}

void opIntegerIncrement(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    OP_INTEGER_UNARY(wvm, 1 +);
}

void opIntegerDecrement(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    OP_INTEGER_UNARY(wvm, -1 +);
}

void opIntegerModulo(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    OP_INTEGER_BINARY(wvm, %);
}

void opIntegerAnd(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    OP_INTEGER_BINARY(wvm, &);
}

void opIntegerOr(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    OP_INTEGER_BINARY(wvm, %);
}

void opIntegerNot(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    OP_INTEGER_UNARY(wvm, ~);
}

void opDoubleToInteger(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer >= 0);
    frame->codePointer++;
    assert(wvm->operandStack[wvm->operandStackPointer].type == OPERAND_TYPE_DOUBLE);
    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;
    wvm->operandStack[wvm->operandStackPointer].value.integerValue = (Integer)wvm->operandStack[wvm->operandStackPointer].value.doubleValue;
}

void opDoubleCeil(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    OP_DOUBLE_UNARY(wvm, ceil);
}

void opDoubleFloor(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    OP_DOUBLE_UNARY(wvm, floor);
}

void opObjectNull(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;
    wvm->operandStackPointer++;
    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_REFERENCE;
    wvm->operandStack[wvm->operandStackPointer].value.reference = NULL;
}

void opObjectCopy(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer >= 0);
    frame->codePointer++;
    struct Operand operand = wvm->operandStack[wvm->operandStackPointer];
    assert(operand.type == OPERAND_TYPE_REFERENCE);
    wvm->operandStack[wvm->operandStackPointer].value.reference = objectCopy(wvm->gc, operand.value.reference);
}

void opObjectEquals(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 0);
    frame->codePointer++;
    struct Operand operand1 = wvm->operandStack[wvm->operandStackPointer--];
    struct Operand operand2 = wvm->operandStack[wvm->operandStackPointer];
    assert(operand1.type == OPERAND_TYPE_REFERENCE);
    assert(operand2.type == OPERAND_TYPE_REFERENCE);
    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;
    wvm->operandStack[wvm->operandStackPointer].value.integerValue = objectEquals(operand1.value.reference, operand2.value.reference);
}

void opObjectHash(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer >= 0);
    frame->codePointer++;
    struct Operand operand = wvm->operandStack[wvm->operandStackPointer];
    assert(operand.type == OPERAND_TYPE_REFERENCE);
    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;
    wvm->operandStack[wvm->operandStackPointer].value.integerValue = objectHash(operand.value.reference);
}

void opObjectToString(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer >= 0);
    frame->codePointer++;
    struct Operand operand = wvm->operandStack[wvm->operandStackPointer];
    assert(operand.type == OPERAND_TYPE_REFERENCE);
    wvm->operandStack[wvm->operandStackPointer].value.reference = objectToString(wvm->gc, operand.value.reference);
}

void opObjectBox(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer >= 0);
    frame->codePointer++;

    struct Operand operand = wvm->operandStack[wvm->operandStackPointer];
    assert(operand.type == OPERAND_TYPE_INTEGER || operand.type == OPERAND_TYPE_DOUBLE);

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_REFERENCE;

    switch (operand.type)
    {
    case OPERAND_TYPE_INTEGER:
        wvm->operandStack[wvm->operandStackPointer].value.reference = integerNew(wvm->gc, operand.value.integerValue);
        break;
    case OPERAND_TYPE_DOUBLE:
        wvm->operandStack[wvm->operandStackPointer].value.reference = doubleNew(wvm->gc, operand.value.doubleValue);
        break;
    }
}

void opObjectUnbox(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer >= 0);
    frame->codePointer++;

    struct Operand operand = wvm->operandStack[wvm->operandStackPointer];
    assert(operand.type == OPERAND_TYPE_REFERENCE);
    assert(operand.value.reference->type == OBJECT_TYPE_INTEGER || operand.value.reference->type == OBJECT_TYPE_DOUBLE);

    switch (operand.value.reference->type)
    {
    case OBJECT_TYPE_INTEGER:
        wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;
        wvm->operandStack[wvm->operandStackPointer].value.integerValue = operand.value.reference->value.integerValue;
        break;
    case OBJECT_TYPE_DOUBLE:
        wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_DOUBLE;
        wvm->operandStack[wvm->operandStackPointer].value.doubleValue = operand.value.reference->value.doubleValue;
        break;
    }
}

void opArrayNew(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;

    struct Operand operand = wvm->operandStack[wvm->operandStackPointer];
    assert(operand.type == OPERAND_TYPE_INTEGER);
    assert(operand.value.integerValue >= 0);

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_REFERENCE;
    wvm->operandStack[wvm->operandStackPointer].value.reference = arrayNew(wvm->gc, operand.value.integerValue, operand.value.integerValue);
}

void opArraySize(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer >= 0);
    frame->codePointer++;
    struct Operand operand = wvm->operandStack[wvm->operandStackPointer];
    assert(operand.type == OPERAND_TYPE_REFERENCE);
    assert(operand.value.reference->type == OBJECT_TYPE_ARRAY);
    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;
    wvm->operandStack[wvm->operandStackPointer].value.integerValue = operand.value.reference->value.array->objectCount;
}

void opArrayGet(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 0);
    frame->codePointer++;
    struct Operand index = wvm->operandStack[wvm->operandStackPointer];
    assert(index.type == OPERAND_TYPE_INTEGER);
    assert(index.value.integerValue >= 0);
    struct Operand array = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(array.type == OPERAND_TYPE_REFERENCE);
    assert(array.value.reference->type == OBJECT_TYPE_ARRAY);
    wvm->operandStack[wvm->operandStackPointer - 1].value.reference = array.value.reference->value.array->objects[index.value.integerValue];
    wvm->operandStackPointer--;
}

void opArraySet(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 1);
    frame->codePointer++;
    struct Operand value = wvm->operandStack[wvm->operandStackPointer];
    assert(value.type == OPERAND_TYPE_REFERENCE);

    struct Operand index = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(index.type == OPERAND_TYPE_INTEGER);
    assert(index.value.integerValue >= 0);

    struct Operand array = wvm->operandStack[wvm->operandStackPointer - 2];
    assert(array.type == OPERAND_TYPE_REFERENCE);
    assert(array.value.reference->type == OBJECT_TYPE_ARRAY);
    wvm->operandStack[wvm->operandStackPointer - 2].value.reference = arraySet(array.value.reference->value.array, index.value.integerValue, value.value.reference);
    wvm->operandStackPointer -= 2;
}

void opArrayInsert(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 1);
    frame->codePointer++;
    struct Operand value = wvm->operandStack[wvm->operandStackPointer];
    assert(value.type == OPERAND_TYPE_REFERENCE);

    struct Operand index = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(index.type == OPERAND_TYPE_INTEGER);
    assert(index.value.integerValue >= 0);

    struct Operand array = wvm->operandStack[wvm->operandStackPointer - 2];
    assert(array.type == OPERAND_TYPE_REFERENCE);
    assert(array.value.reference->type == OBJECT_TYPE_ARRAY);
    arrayInsert(wvm->gc, array.value.reference->value.array, index.value.integerValue, value.value.reference);
    wvm->operandStackPointer -= 3;
}

void opArrayInsertAll(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 0);
    frame->codePointer++;
    struct Operand array1 = wvm->operandStack[wvm->operandStackPointer];
    assert(array1.type == OPERAND_TYPE_REFERENCE);
    assert(array1.value.reference->type == OBJECT_TYPE_ARRAY);

    struct Operand index = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(index.type == OPERAND_TYPE_INTEGER);
    assert(index.value.integerValue >= 0);

    struct Operand array2 = wvm->operandStack[wvm->operandStackPointer - 2];
    assert(array2.type == OPERAND_TYPE_REFERENCE);
    assert(array2.value.reference->type == OBJECT_TYPE_ARRAY);

    arrayInsertAll(wvm->gc, array2.value.reference->value.array, index.value.integerValue, array1.value.reference->value.array);
    wvm->operandStackPointer -= 3;
}

void opArrayRemove(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 0);
    frame->codePointer++;

    struct Operand index = wvm->operandStack[wvm->operandStackPointer];
    assert(index.type == OPERAND_TYPE_INTEGER);
    assert(index.value.integerValue >= 0);

    struct Operand array = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(array.type == OPERAND_TYPE_REFERENCE);
    assert(array.value.reference->type == OBJECT_TYPE_ARRAY);

    wvm->operandStack[wvm->operandStackPointer - 1].value.reference = arrayRemove(array.value.reference->value.array, index.value.integerValue);
    wvm->operandStackPointer--;
}

void opArrayForEach(struct WheyVM *wvm, struct Frame *frame)
{
    uint16_t functionIndex;
    memcpy(&functionIndex, &frame->function->byteCode[frame->codePointer + 1], 2);
    frame->codePointer += 3;
    struct Function *nextFunction = wcFileGetFunction(wvm->wcFile, functionIndex);

    struct Operand array = wvm->operandStack[wvm->operandStackPointer];
    assert(array.type == OPERAND_TYPE_REFERENCE);
    assert(array.value.reference->type == OBJECT_TYPE_ARRAY);
    wvm->operandStackPointer--;

    if (array.value.reference->value.array->objectCount > 0)
    {
        struct Frame *nextFrame = frameNewWithIterator(nextFunction, array.value.reference);

        for (uint8_t i = 1; i < nextFunction->argumentCount; i++)
        {
            assert(wvm->operandStackPointer >= 0);
            nextFrame->locals[i] = wvm->operandStack[wvm->operandStackPointer--];
        }

        wvm->callStack[++wvm->callStackPointer] = nextFrame;
    }
}

void opMapNew(struct WheyVM *wvm, struct Frame *frame)
{
    frame->codePointer++;

    wvm->operandStackPointer++;

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_REFERENCE;
    wvm->operandStack[wvm->operandStackPointer].value.reference = mapNew(wvm->gc);
}

void opMapSize(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer >= 0);
    frame->codePointer++;

    struct Operand operand = wvm->operandStack[wvm->operandStackPointer];
    assert(operand.type == OPERAND_TYPE_REFERENCE);
    assert(operand.value.reference->type == OBJECT_TYPE_MAP);

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;
    wvm->operandStack[wvm->operandStackPointer].value.integerValue = operand.value.reference->value.map->entryCount;
}

void opMapGet(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 0);
    frame->codePointer++;

    struct Operand key = wvm->operandStack[wvm->operandStackPointer];
    assert(key.type == OPERAND_TYPE_REFERENCE);

    struct Operand map = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(map.type == OPERAND_TYPE_REFERENCE);
    assert(map.value.reference->type == OBJECT_TYPE_MAP);

    wvm->operandStackPointer--;

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_REFERENCE;
    wvm->operandStack[wvm->operandStackPointer].value.reference = mapGet(map.value.reference->value.map, key.value.reference);
}

void opMapPut(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 1);

    frame->codePointer++;

    struct Operand value = wvm->operandStack[wvm->operandStackPointer];
    assert(value.type == OPERAND_TYPE_REFERENCE);

    struct Operand key = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(key.type == OPERAND_TYPE_REFERENCE);

    struct Operand map = wvm->operandStack[wvm->operandStackPointer - 2];
    assert(map.type == OPERAND_TYPE_REFERENCE);
    assert(map.value.reference->type == OBJECT_TYPE_MAP);

    wvm->operandStackPointer -= 2;

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_REFERENCE;
    wvm->operandStack[wvm->operandStackPointer].value.reference = mapPut(wvm->gc, map.value.reference->value.map, key.value.reference, value.value.reference);
}

void opMapPutAll(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 0);

    frame->codePointer++;

    struct Operand map1 = wvm->operandStack[wvm->operandStackPointer];
    assert(map1.type == OPERAND_TYPE_REFERENCE);
    assert(map1.value.reference->type == OBJECT_TYPE_MAP);

    struct Operand map2 = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(map2.type == OPERAND_TYPE_REFERENCE);
    assert(map2.value.reference->type == OBJECT_TYPE_MAP);

    wvm->operandStackPointer--;

    mapPutAll(wvm->gc, map2.value.reference->value.map, map1.value.reference->value.map);
}

void opMapRemove(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 0);

    frame->codePointer++;

    struct Operand key = wvm->operandStack[wvm->operandStackPointer];
    assert(key.type == OPERAND_TYPE_REFERENCE);

    struct Operand map = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(map.type == OPERAND_TYPE_REFERENCE);
    assert(map.value.reference->type == OBJECT_TYPE_MAP);

    wvm->operandStackPointer--;

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_REFERENCE;
    wvm->operandStack[wvm->operandStackPointer].value.reference = mapRemove(wvm->gc, map.value.reference->value.map, key.value.reference);
}

void opMapHasKey(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 0);

    frame->codePointer++;

    struct Operand key = wvm->operandStack[wvm->operandStackPointer];
    assert(key.type == OPERAND_TYPE_REFERENCE);

    struct Operand map = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(map.type == OPERAND_TYPE_REFERENCE);
    assert(map.value.reference->type == OBJECT_TYPE_MAP);

    wvm->operandStackPointer--;

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;
    wvm->operandStack[wvm->operandStackPointer].value.integerValue = mapHasKey(map.value.reference->value.map, key.value.reference);
}

void opMapEntries(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer >= 0);

    frame->codePointer++;

    struct Operand map = wvm->operandStack[wvm->operandStackPointer];
    assert(map.type == OPERAND_TYPE_REFERENCE);
    assert(map.value.reference->type == OBJECT_TYPE_MAP);

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_REFERENCE;
    wvm->operandStack[wvm->operandStackPointer].value.reference = mapEntries(wvm->gc, map.value.reference->value.map);
}

void opPairNew(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 0);

    frame->codePointer++;

    struct Operand first = wvm->operandStack[wvm->operandStackPointer];
    assert(first.type == OPERAND_TYPE_REFERENCE);

    struct Operand second = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(second.type == OPERAND_TYPE_REFERENCE);

    wvm->operandStackPointer--;

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_REFERENCE;
    wvm->operandStack[wvm->operandStackPointer].value.reference = pairNew(wvm->gc, first.value.reference, second.value.reference);
}

void opPairGetFirst(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer >= 0);

    frame->codePointer++;

    struct Operand pair = wvm->operandStack[wvm->operandStackPointer];
    assert(pair.type == OPERAND_TYPE_REFERENCE);
    assert(pair.value.reference->type == OBJECT_TYPE_PAIR);

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_REFERENCE;
    wvm->operandStack[wvm->operandStackPointer].value.reference = pair.value.reference->value.pair->first;
}

void opPairGetSecond(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer >= 0);

    frame->codePointer++;

    struct Operand pair = wvm->operandStack[wvm->operandStackPointer];
    assert(pair.type == OPERAND_TYPE_REFERENCE);
    assert(pair.value.reference->type == OBJECT_TYPE_PAIR);

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_REFERENCE;
    wvm->operandStack[wvm->operandStackPointer].value.reference = pair.value.reference->value.pair->second;
}

void opPairSetFirst(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 0);

    frame->codePointer++;

    struct Operand first = wvm->operandStack[wvm->operandStackPointer];
    assert(first.type == OPERAND_TYPE_REFERENCE);

    struct Operand pair = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(pair.type == OPERAND_TYPE_REFERENCE);
    assert(pair.value.reference->type == OBJECT_TYPE_PAIR);

    wvm->operandStackPointer--;

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_REFERENCE;
    wvm->operandStack[wvm->operandStackPointer].value.reference = pairSetFirst(pair.value.reference->value.pair, first.value.reference);
}

void opPairSetSecond(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 0);

    frame->codePointer++;

    struct Operand second = wvm->operandStack[wvm->operandStackPointer];
    assert(second.type == OPERAND_TYPE_REFERENCE);

    struct Operand pair = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(pair.type == OPERAND_TYPE_REFERENCE);
    assert(pair.value.reference->type == OBJECT_TYPE_PAIR);

    wvm->operandStackPointer--;

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_REFERENCE;
    wvm->operandStack[wvm->operandStackPointer].value.reference = pairSetSecond(pair.value.reference->value.pair, second.value.reference);
}

void opStringLength(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer >= 0);

    frame->codePointer++;

    struct Operand string = wvm->operandStack[wvm->operandStackPointer];
    assert(string.type == OPERAND_TYPE_REFERENCE);
    assert(string.value.reference->type == OBJECT_TYPE_STRING);

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;
    wvm->operandStack[wvm->operandStackPointer].value.integerValue = string.value.reference->value.string->characterCount;
}

void opStringFromArray(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer >= 0);

    frame->codePointer++;

    struct Operand array = wvm->operandStack[wvm->operandStackPointer];
    assert(array.type == OPERAND_TYPE_REFERENCE);
    assert(array.value.reference->type == OBJECT_TYPE_ARRAY);

    wvm->operandStack[wvm->operandStackPointer].value.reference = stringFromArray(wvm->gc, array.value.reference->value.array);
}

void opStringToArray(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer >= 0);

    frame->codePointer++;

    struct Operand string = wvm->operandStack[wvm->operandStackPointer];
    assert(string.type == OPERAND_TYPE_REFERENCE);
    assert(string.value.reference->type == OBJECT_TYPE_STRING);

    wvm->operandStack[wvm->operandStackPointer].value.reference = stringToArray(wvm->gc, string.value.reference->value.string);
}

void opStringCompare(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 0);

    frame->codePointer++;

    struct Operand string1 = wvm->operandStack[wvm->operandStackPointer];
    assert(string1.type == OPERAND_TYPE_REFERENCE);
    assert(string1.value.reference->type == OBJECT_TYPE_STRING);

    struct Operand string2 = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(string2.type == OPERAND_TYPE_REFERENCE);
    assert(string2.value.reference->type == OBJECT_TYPE_STRING);

    wvm->operandStackPointer--;

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;
    wvm->operandStack[wvm->operandStackPointer].value.integerValue = stringCompare(string2.value.reference->value.string, string1.value.reference->value.string);
}

void opStringConcatenate(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 0);

    frame->codePointer++;

    struct Operand string1 = wvm->operandStack[wvm->operandStackPointer];
    assert(string1.type == OPERAND_TYPE_REFERENCE);
    assert(string1.value.reference->type == OBJECT_TYPE_STRING);

    struct Operand string2 = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(string2.type == OPERAND_TYPE_REFERENCE);
    assert(string2.value.reference->type == OBJECT_TYPE_STRING);

    wvm->operandStackPointer--;

    wvm->operandStack[wvm->operandStackPointer].value.reference = stringConcatenate(wvm->gc, string2.value.reference->value.string, string1.value.reference->value.string);
}

void opStringSubstring(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 1);

    frame->codePointer++;

    struct Operand integer1 = wvm->operandStack[wvm->operandStackPointer];
    assert(integer1.type == OPERAND_TYPE_INTEGER);

    struct Operand integer2 = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(integer2.type == OPERAND_TYPE_INTEGER);

    struct Operand string = wvm->operandStack[wvm->operandStackPointer - 2];
    assert(string.type == OPERAND_TYPE_REFERENCE);
    assert(string.value.reference->type == OBJECT_TYPE_STRING);

    wvm->operandStackPointer -= 2;

    wvm->operandStack[wvm->operandStackPointer].value.reference = stringSubstring(wvm->gc, string.value.reference->value.string, integer2.value.integerValue, integer1.value.integerValue);
}

void opStringIndexOf(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 1);

    frame->codePointer++;

    struct Operand integer1 = wvm->operandStack[wvm->operandStackPointer];
    assert(integer1.type == OPERAND_TYPE_INTEGER);

    struct Operand string1 = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(string1.type == OPERAND_TYPE_REFERENCE);
    assert(string1.value.reference->type == OBJECT_TYPE_STRING);

    struct Operand string2 = wvm->operandStack[wvm->operandStackPointer - 2];
    assert(string2.type == OPERAND_TYPE_REFERENCE);
    assert(string2.value.reference->type == OBJECT_TYPE_STRING);

    wvm->operandStackPointer -= 2;

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;
    wvm->operandStack[wvm->operandStackPointer].value.integerValue = stringIndexOf(string2.value.reference->value.string, string1.value.reference->value.string, integer1.value.integerValue);
}

void opStringReplace(struct WheyVM *wvm, struct Frame *frame)
{
    assert(wvm->operandStackPointer > 1);

    frame->codePointer++;

    struct Operand string1 = wvm->operandStack[wvm->operandStackPointer];
    assert(string1.type == OPERAND_TYPE_REFERENCE);
    assert(string1.value.reference->type == OBJECT_TYPE_STRING);

    struct Operand string2 = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(string2.type == OPERAND_TYPE_REFERENCE);
    assert(string2.value.reference->type == OBJECT_TYPE_STRING);

    struct Operand string3 = wvm->operandStack[wvm->operandStackPointer - 2];
    assert(string3.type == OPERAND_TYPE_REFERENCE);
    assert(string3.value.reference->type == OBJECT_TYPE_STRING);

    wvm->operandStackPointer -= 2;

    wvm->operandStack[wvm->operandStackPointer].value.reference = stringReplace(wvm->gc, string3.value.reference->value.string, string2.value.reference->value.string, string1.value.reference->value.string);
}

void opStringSplit(struct WheyVM *wvm, struct Frame *frame) 
{
    assert(wvm->operandStackPointer > 0);

    frame->codePointer++;

    struct Operand string1 = wvm->operandStack[wvm->operandStackPointer];
    assert(string1.type == OPERAND_TYPE_REFERENCE);
    assert(string1.value.reference->type == OBJECT_TYPE_STRING);

    struct Operand string2 = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(string2.type == OPERAND_TYPE_REFERENCE);
    assert(string2.value.reference->type == OBJECT_TYPE_STRING);

    wvm->operandStackPointer--;

    wvm->operandStack[wvm->operandStackPointer].value.reference = stringSplit(wvm->gc, string2.value.reference->value.string, string1.value.reference->value.string);
}