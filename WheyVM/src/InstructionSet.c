#include "../InstructionSet.h"
#include "../WheyVM.h"
#include "../Frame.h"
#include "../Operand/Operand.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define JUMP_END(frame) frame->codePointer = frame->function->codeSize

#define CURRENT_FRAME(wvm) ((wvm->callStack[wvm->callStackPointer]))

#define OP_JUMP(frame)                                                                    \
    do                                                                                    \
    {                                                                                     \
        int16_t relativeLocation;                                                         \
        memcpy(&relativeLocation, &frame->function->byteCode[frame->codePointer + 1], 2); \
        assert(relativeLocation != 0);                                                    \
        uint16_t newLocation = frame->codePointer + relativeLocation;                     \
        assert(newLocation >= 0 && newLocation < frame->function->codeSize);              \
        \    
    frame->codePointer = newLocation;                                                     \
    } while (0)

#define CAST_TO_DOUBLE(op1, op2)                                                                \
    do                                                                                          \
    {                                                                                           \
        if (operand1.type == OPERAND_TYPE_DOUBLE && operand2.type == OPERAND_TYPE_INTEGER)      \
        {                                                                                       \
            operand2.type = OPERAND_TYPE_DOUBLE;                                                \
            operand2.value.doubleValue = (double)operand2.value.integerValue;                   \
        }                                                                                       \
        else if (operand2.type == OPERAND_TYPE_DOUBLE && operand1.type == OPERAND_TYPE_INTEGER) \
        {                                                                                       \
            operand1.type = OPERAND_TYPE_DOUBLE;                                                \
            operand1.value.doubleValue = (double)operand1.value.integerValue;                   \
        }                                                                                       \
    } while (0)

#define OP_COMPARISON(wvm, operator)                                                                                                             \
    do                                                                                                                                           \
    {                                                                                                                \
        struct Operand operand1 = wvm->operandStack[wvm->operandStackPointer--];                                                                 \
        struct Operand operand2 = wvm->operandStack[wvm->operandStackPointer];                                                                   \
        CAST_TO_DOUBLE(operand1, operand2);                                                                                                      \
        assert(operand1.type == operand2.type);                                                                                                  \
        wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;                                                                 \
                                                                                                                                                 \
        switch (operand1.type)                                                                                                                   \
        {                                                                                                                                        \
        case OPERAND_TYPE_INTEGER:                                                                                                               \
            wvm->operandStack[wvm->operandStackPointer].value.integerValue = (operand1.value.integerValue operator operand2.value.integerValue); \
            break;                                                                                                                               \
        case OPERAND_TYPE_DOUBLE:                                                                                                                \
            wvm->operandStack[wvm->operandStackPointer].value.integerValue = (operand1.value.doubleValue operator operand2.value.doubleValue);   \
            break;                                                                                                                               \
        case OPERAND_TYPE_REFERENCE:                                                                                                             \
            wvm->operandStack[wvm->operandStackPointer].value.integerValue = (operand1.value.reference operator operand2.value.reference);       \
            break;                                                                                                                               \
        }                                                                                                                                        \
    } while (0)

#define OP_ARITHMETIC(wvm, operator)                                                                                                             \
    do                                                                                                                                           \
    {                                                                                                                 \
        struct Operand operand1 = wvm->operandStack[wvm->operandStackPointer--];                                                                 \
        struct Operand operand2 = wvm->operandStack[wvm->operandStackPointer];                                                                   \
        CAST_TO_DOUBLE(operand1, operand2);                                                                                                      \
        assert(operand1.type == operand2.type);                                                                                                  \
        assert(operand1.type != OPERAND_TYPE_REFERENCE);                                                                                         \
        wvm->operandStack[wvm->operandStackPointer].type = operand1.type;                                                                        \
                                                                                                                                                 \
        switch (operand1.type)                                                                                                                   \
        {                                                                                                                                        \
        case OPERAND_TYPE_INTEGER:                                                                                                               \
            wvm->operandStack[wvm->operandStackPointer].value.integerValue = (operand1.value.integerValue operator operand2.value.integerValue); \
            break;                                                                                                                               \
        case OPERAND_TYPE_DOUBLE:                                                                                                                \
            wvm->operandStack[wvm->operandStackPointer].value.doubleValue = (operand1.value.doubleValue operator operand2.value.doubleValue);    \
            break;                                                                                                                               \
        }                                                                                                                                        \
    } while (0)

#define OP_INTEGER_BINARY(wvm, operator)                                                                                                     \
    do                                                                                                                                       \
    {                                                                                                                \
        struct Operand operand1 = wvm->operandStack[wvm->operandStackPointer--];                                                             \
        struct Operand operand2 = wvm->operandStack[wvm->operandStackPointer];                                                               \
        assert(operand1.type == OPERAND_TYPE_INTEGER);                                                                                       \
        assert(operand2.type == OPERAND_TYPE_INTEGER);                                                                                       \
        wvm->operandStack[wvm->operandStackPointer].value.integerValue = (operand1.value.integerValue operator operand2.value.integerValue); \
    } while (0)

#define OP_INTEGER_UNARY(wvm, operator)                                                                       \
    do                                                                                                        \
    {                                                                                \
        struct Operand operand = wvm->operandStack[wvm->operandStackPointer];                                 \
        assert(operand.type == OPERAND_TYPE_INTEGER);                                                         \
        wvm->operandStack[wvm->operandStackPointer].value.integerValue = operator operand.value.integerValue; \
    } while (0)

#define OP_DOUBLE_UNARY(wvm, fun)                                                                       \
    do                                                                                                  \
    {                                                                          \
        struct Operand operand = wvm->operandStack[wvm->operandStackPointer];                           \
        assert(operand.type == OPERAND_TYPE_DOUBLE);                                                    \
        wvm->operandStack[wvm->operandStackPointer].value.doubleValue = fun(operand.value.doubleValue); \
    } while (0)

#define OP_UNBOX(wvm, offset)                                                                                                          \
    do                                                                                                                                 \
    {                                                                                                        \
        struct Operand operand = wvm->operandStack[wvm->operandStackPointer - offset];                                                 \
        if (operand.type == OPERAND_TYPE_REFERENCE)                                                                                    \
        {                                                                                                                              \
            assert(operand.value.reference->type == OBJECT_TYPE_DOUBLE || operand.value.reference->type == OBJECT_TYPE_INTEGER);       \
            switch (operand.value.reference->type)                                                                                     \
            {                                                                                                                          \
            case OBJECT_TYPE_INTEGER:                                                                                                  \
                wvm->operandStack[wvm->operandStackPointer - offset].value.integerValue = operand.value.reference->value.integerValue; \
                break;                                                                                                                 \
            case OBJECT_TYPE_DOUBLE:                                                                                                   \
                wvm->operandStack[wvm->operandStackPointer - offset].value.doubleValue = operand.value.reference->value.doubleValue;   \
                break;                                                                                                                 \
            }                                                                                                                          \
        }                                                                                                                              \
    } while (0)

#define OP_BOX(wvm, offset)                                                                                                         \
    do                                                                                                                              \
    {                                                                                                       \
        struct Operand operand = wvm->operandStack[wvm->operandStackPointer - offset];                                              \
        wvm->operandStack[wvm->operandStackPointer - offset].type = OPERAND_TYPE_REFERENCE;                                         \
        switch (operand.type)                                                                                                       \
        {                                                                                                                           \
        case OPERAND_TYPE_INTEGER:                                                                                                  \
            wvm->operandStack[wvm->operandStackPointer - offset].value.reference = integerNew(wvm->gc, operand.value.integerValue); \
            break;                                                                                                                  \
        case OPERAND_TYPE_DOUBLE:                                                                                                   \
            wvm->operandStack[wvm->operandStackPointer - offset].value.doubleValue = doubleNew(wvm->gc, operand.value.doubleValue); \
            break;                                                                                                                  \
        }                                                                                                                           \
    } while (0)

void opUnknown(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    fprintf(stderr, "Unknown opcode error with opcode %d\n", frame->function->byteCode[frame->codePointer]);
    exit(1);
}

void opHalt(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    JUMP_END(frame);
}

void opJump(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    OP_JUMP(frame);
}

void opJumpTrue(struct WheyVM *wvm)
{
    struct Operand currentOperand = wvm->operandStack[wvm->operandStackPointer--];
    struct Frame *frame = CURRENT_FRAME(wvm);

    assert(currentOperand.type == OPERAND_TYPE_INTEGER);

    if (currentOperand.value.integerValue)
    {
        OP_JUMP(frame);
    }
    else
    {
        frame->codePointer += 3;
    }
}

void opJumpFalse(struct WheyVM *wvm)
{
    struct Operand currentOperand = wvm->operandStack[wvm->operandStackPointer--];
    struct Frame *frame = CURRENT_FRAME(wvm);

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

void opLoad(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    uint8_t localIndex = frame->function->byteCode[++frame->codePointer];
    frame->codePointer++;
    wvm->operandStack[++wvm->operandStackPointer] = frameGetLocal(frame, localIndex);
}

void opStore(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    uint8_t localIndex = frame->function->byteCode[++frame->codePointer];
    frame->codePointer++;
    frameSetLocal(frame, localIndex, wvm->operandStack[wvm->operandStackPointer--]);
}

void opCall(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    uint16_t functionIndex;
    memcpy(&functionIndex, &frame->function->byteCode[frame->codePointer + 1], 2);
    frame->codePointer += 3;
    struct Function *nextFunction = wcFileGetFunction(wvm->wcFile, functionIndex);

    struct Frame *nextFrame = frameNew(nextFunction);
    wvm->callStack[++wvm->callStackPointer] = nextFrame;
}

void opReturn(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);

    if (wvm->callStackPointer == 0)
    {
        JUMP_END(frame);
    }
    else
    {
        frameFree(frame);
        wvm->callStackPointer--;
    }
}

void opConstant(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);

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

void opPrint(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    frame->codePointer++;

    struct Operand operand = wvm->operandStack[wvm->operandStackPointer--];

    switch (operand.type)
    {
    case OPERAND_TYPE_INTEGER:
        printf("%d\n", operand.value.integerValue);
        break;
    case OPERAND_TYPE_DOUBLE:
        printf("%.10e\n", operand.value.doubleValue);
        break;
    case OPERAND_TYPE_REFERENCE:
        assert(operand.value.reference->type == OBJECT_TYPE_STRING);
        stringPrint(operand.value.reference->value.string);
        break;
    default:
        fprintf(stderr, "Unknown operand error.\n");
    }
}

void opPop(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    frame->codePointer++;
    wvm->operandStackPointer--;
}

void opEqual(struct WheyVM *wvm)
{                                                                                                            
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_COMPARISON(wvm, ==);
}

void opNotEqual(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_COMPARISON(wvm, !=);
}

void opGreaterThan(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_COMPARISON(wvm, >);
}

void opGreaterThanOrEqual(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_COMPARISON(wvm, >=);
}

void opLessThan(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_COMPARISON(wvm, <);
}

void opLessThanOrEqual(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_COMPARISON(wvm, <=);
}

void opAdd(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_ARITHMETIC(wvm, +);
}

void opSubtract(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_ARITHMETIC(wvm, -);
}

void opMultiply(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_ARITHMETIC(wvm, *);
}

void opDivide(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    frame->codePointer++;
    struct Operand operand1 = wvm->operandStack[wvm->operandStackPointer--];
    struct Operand operand2 = wvm->operandStack[wvm->operandStackPointer];
    CAST_TO_DOUBLE(operand1, operand2);
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

void opPower(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    frame->codePointer++;
    struct Operand operand1 = wvm->operandStack[wvm->operandStackPointer--];
    struct Operand operand2 = wvm->operandStack[wvm->operandStackPointer];
    CAST_TO_DOUBLE(operand1, operand2);
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

void opNegate(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
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

void opIntegerToDouble(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    frame->codePointer++;
    assert(wvm->operandStack[wvm->operandStackPointer].type == OPERAND_TYPE_INTEGER);
    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_DOUBLE;
    wvm->operandStack[wvm->operandStackPointer].value.doubleValue = (Double)wvm->operandStack[wvm->operandStackPointer].value.integerValue;
}

void opIntegerIncrement(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_INTEGER_UNARY(wvm, 1 +);
}

void opIntegerDecrement(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_INTEGER_UNARY(wvm, -1 +);
}

void opIntegerModulo(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_INTEGER_BINARY(wvm, %);
}

void opIntegerAnd(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_INTEGER_BINARY(wvm, &);
}

void opIntegerOr(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_INTEGER_BINARY(wvm, %);
}

void opIntegerNot(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_INTEGER_UNARY(wvm, ~);
}

void opDoubleToInteger(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    frame->codePointer++;
    assert(wvm->operandStack[wvm->operandStackPointer].type == OPERAND_TYPE_DOUBLE);
    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;
    wvm->operandStack[wvm->operandStackPointer].value.integerValue = (Integer)wvm->operandStack[wvm->operandStackPointer].value.doubleValue;
}

void opDoubleCeil(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_DOUBLE_UNARY(wvm, ceil);
}

void opDoubleFloor(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   
    frame->codePointer++;
    OP_DOUBLE_UNARY(wvm, floor);
}

void opObjectNull(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    frame->codePointer++;
    wvm->operandStackPointer++;
    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_REFERENCE;
    wvm->operandStack[wvm->operandStackPointer].value.reference = NULL;
}

void opObjectCopy(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    frame->codePointer++;
    struct Operand operand = wvm->operandStack[wvm->operandStackPointer];
    assert(operand.type == OPERAND_TYPE_REFERENCE);
    wvm->operandStack[wvm->operandStackPointer].value.reference = objectCopy(wvm->gc, operand.value.reference);
}

void opObjectEquals(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    frame->codePointer++;
    struct Operand operand1 = wvm->operandStack[wvm->operandStackPointer--];
    struct Operand operand2 = wvm->operandStack[wvm->operandStackPointer];
    assert(operand1.type == OPERAND_TYPE_REFERENCE);
    assert(operand2.type == OPERAND_TYPE_REFERENCE);
    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;
    wvm->operandStack[wvm->operandStackPointer].value.integerValue = objectEquals(operand1.value.reference, operand2.value.reference);
}

void opObjectHash(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    frame->codePointer++;
    struct Operand operand = wvm->operandStack[wvm->operandStackPointer];
    assert(operand.type == OPERAND_TYPE_REFERENCE);
    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;
    wvm->operandStack[wvm->operandStackPointer].value.integerValue = objectHash(operand.value.reference);
}

void opObjectToString(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    frame->codePointer++;
    struct Operand operand = wvm->operandStack[wvm->operandStackPointer];
    assert(operand.type == OPERAND_TYPE_REFERENCE);
    wvm->operandStack[wvm->operandStackPointer].value.reference = objectToString(wvm->gc, operand.value.reference);
}

void opArrayNew(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);                                                                                   

    uint16_t constantIndex;
    memcpy(&constantIndex, &frame->function->byteCode[frame->codePointer + 1], 2);
    frame->codePointer += 3;
    struct Constant *constant = wcFileGetConstant(wvm->wcFile, constantIndex);

    wvm->operandStackPointer++;

    assert(constant->type == CONSTANT_TYPE_INTEGER);
    assert(constant->value.integerConstant >= 0);
    Integer size = constant->value.integerConstant;

    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_REFERENCE;
    wvm->operandStack[wvm->operandStackPointer].value.reference = arrayNew(wvm->gc, size, size);
}

void opArraySize(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    frame->codePointer++;
    struct Operand operand = wvm->operandStack[wvm->operandStackPointer];
    assert(operand.type == OPERAND_TYPE_REFERENCE);
    assert(operand.value.reference->type == OBJECT_TYPE_ARRAY);
    wvm->operandStack[wvm->operandStackPointer].type = OPERAND_TYPE_INTEGER;
    wvm->operandStack[wvm->operandStackPointer].value.integerValue = arraySize(operand.value.reference->value.array);
}

void opArrayGet(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    frame->codePointer++;
    OP_UNBOX(wvm, 0);
    struct Operand index = wvm->operandStack[wvm->operandStackPointer];
    assert(index.type == OPERAND_TYPE_INTEGER);
    assert(index.value.integerValue >= 0);
    struct Operand array = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(array.type == OPERAND_TYPE_REFERENCE);
    assert(array.value.reference->type == OBJECT_TYPE_ARRAY);
    wvm->operandStack[wvm->operandStackPointer - 1].value.reference = array.value.reference->value.array->objects[index.value.integerValue];
    wvm->operandStackPointer--;
}

void opArraySet(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    frame->codePointer++;
    OP_BOX(wvm, 0);
    struct Operand value = wvm->operandStack[wvm->operandStackPointer];
    OP_UNBOX(wvm, 1);
    struct Operand index = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(index.type == OPERAND_TYPE_INTEGER);
    assert(index.value.integerValue >= 0);

    struct Operand array = wvm->operandStack[wvm->operandStackPointer - 2];
    assert(array.type == OPERAND_TYPE_REFERENCE);
    assert(array.value.reference->type == OBJECT_TYPE_ARRAY);
    wvm->operandStack[wvm->operandStackPointer - 2].value.reference = arraySet(array.value.reference->value.array, index.value.integerValue, value.value.reference);
    wvm->operandStackPointer-=2;
}

void opArrayInsert(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    frame->codePointer++;
    OP_BOX(wvm, 0);
    struct Operand value = wvm->operandStack[wvm->operandStackPointer];
    OP_UNBOX(wvm, 1);
    struct Operand index = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(index.type == OPERAND_TYPE_INTEGER);
    assert(index.value.integerValue >= 0);

    struct Operand array = wvm->operandStack[wvm->operandStackPointer - 2];
    assert(array.type == OPERAND_TYPE_REFERENCE);
    assert(array.value.reference->type == OBJECT_TYPE_ARRAY);
    arrayInsert(wvm->gc, array.value.reference->value.array, index.value.integerValue, value.value.reference);
    wvm->operandStackPointer-=3;
}

void opArrayInsertAll(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
    frame->codePointer++;
    struct Operand array1 = wvm->operandStack[wvm->operandStackPointer];
    assert(array1.type == OPERAND_TYPE_REFERENCE);
    assert(array1.value.reference->type == OBJECT_TYPE_ARRAY);
    OP_UNBOX(wvm, 1);
    struct Operand index = wvm->operandStack[wvm->operandStackPointer - 1];
    assert(index.type == OPERAND_TYPE_INTEGER);
    assert(index.value.integerValue >= 0);
    struct Operand array2 = wvm->operandStack[wvm->operandStackPointer - 2];
    assert(array2.type == OPERAND_TYPE_REFERENCE);
    assert(array2.value.reference->type == OBJECT_TYPE_ARRAY);

    arrayInsertAll(wvm->gc, array2.value.reference->value.array, index.value.integerValue, array1.value.reference->value.array);
    wvm->operandStackPointer-=3;
}

void opArrayRemove(struct WheyVM *wvm)
{
    struct Frame *frame = CURRENT_FRAME(wvm);
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

void opArrayForEach(struct WheyVM *wvm);
void opArrayMap(struct WheyVM *wvm);
void opArrayFilter(struct WheyVM *wvm);
void opArrayReduce(struct WheyVM *wvm);

void opMapNew(struct WheyVM *wvm);
void opMapSize(struct WheyVM *wvm);
void opMapGet(struct WheyVM *wvm);
void opMapPut(struct WheyVM *wvm);
void opMapPutAll(struct WheyVM *wvm);
void opMapRemove(struct WheyVM *wvm);
void opMapHasKey(struct WheyVM *wvm);
void opMapEntries(struct WheyVM *wvm);

void opPairNew(struct WheyVM *wvm);
void opPairGetFirst(struct WheyVM *wvm);
void opPairGetSecond(struct WheyVM *wvm);
void opPairSetFirst(struct WheyVM *wvm);
void opPairSetSecond(struct WheyVM *wvm);

void opStringLength(struct WheyVM *wvm);
void opStringFromArray(struct WheyVM *wvm);
void opStringToArray(struct WheyVM *wvm);
void opStringCompare(struct WheyVM *wvm);
void opStringConcatenate(struct WheyVM *wvm);
void opStringSubstring(struct WheyVM *wvm);
void opStringIndexOf(struct WheyVM *wvm);
void opStringReplace(struct WheyVM *wvm);