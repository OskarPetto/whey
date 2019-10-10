#include "../Runner.h"
#include "../Stack/Stack.h"
#include "../Stack/Operand.h"
#include "../Object/Array.h"
#include "../Object/Double.h"
#include "../Object/Gc.h"
#include "../Object/Integer.h"
#include "../Object/Map.h"
#include "../Object/Object.h"
#include "../Object/Pair.h"
#include "../Object/String.h"
#include "../Types.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>
#include <time.h>

#define OPERAND_STACK_PEEK_TYPE(frame, operand, expectedType) \
    do                                                        \
    {                                                         \
        operand = OPERAND_STACK_PEEK(frame);                  \
        ASSERT_OPERAND_TYPE(operand, expectedType);           \
    } while (0)

#define OPERAND_STACK_POP_TYPE(frame, operand, expectedType) \
    do                                                       \
    {                                                        \
        operand = OPERAND_STACK_POP(frame);                  \
        ASSERT_OPERAND_TYPE(operand, expectedType);          \
    } while (0)

#define CHECK_DIVIDE_ZERO(number) ERROR_CHECK(number == 0, ERRCODE_RUNTIME, "Number operand is 0\n")

#define COPY_OPERAND(operand1, operand2)   \
    do                                     \
    {                                      \
        operand2->type = operand1->type;   \
        operand2->value = operand1->value; \
    } while (0)

#define BYTECODE_GET_NEXT_BYTES(frame, count, result) memcpy(result, frame->instructionPointer + 1, count);

#define AUTO_CAST(operand1, operand2)                                                                                                                                                                                  \
    do                                                                                                                                                                                                                 \
    {                                                                                                                                                                                                                  \
        uint8_t type1 = operand1->type;                                                                                                                                                                                \
        uint8_t type2 = operand2->type;                                                                                                                                                                                \
        ASSERT(type1 != OPERAND_TYPE_REFERENCE && type2 != OPERAND_TYPE_REFERENCE, ERRCODE_RUNTIME, "Operands must be %s or %s\n", operandTypeStrings[OPERAND_TYPE_INTEGER], operandTypeStrings[OPERAND_TYPE_DOUBLE]); \
        if (type1 != type2)                                                                                                                                                                                            \
        {                                                                                                                                                                                                              \
            if (type1 == OPERAND_TYPE_INTEGER)                                                                                                                                                                         \
            {                                                                                                                                                                                                          \
                operand1->type = OPERAND_TYPE_DOUBLE;                                                                                                                                                                  \
                operand1->value.doubleValue = (Double)operand1->value.integerValue;                                                                                                                                    \
            }                                                                                                                                                                                                          \
            else if (type2 == OPERAND_TYPE_INTEGER)                                                                                                                                                                    \
            {                                                                                                                                                                                                          \
                operand2->type = OPERAND_TYPE_DOUBLE;                                                                                                                                                                  \
                operand2->value.doubleValue = (Double)operand1->value.integerValue;                                                                                                                                    \
            }                                                                                                                                                                                                          \
        }                                                                                                                                                                                                              \
    } while (0)

#define AUTO_BOX(gc, operand)                                                       \
    do                                                                              \
    {                                                                               \
        switch (operand->type)                                                      \
        {                                                                           \
        case OPERAND_TYPE_INTEGER:                                                  \
            operand->type = OPERAND_TYPE_REFERENCE;                                 \
            operand->value.reference = integerNew(gc, operand->value.integerValue); \
            break;                                                                  \
        case OPERAND_TYPE_DOUBLE:                                                   \
            operand->type = OPERAND_TYPE_REFERENCE;                                 \
            operand->value.reference = doubleNew(gc, operand->value.doubleValue);   \
            break;                                                                  \
        }                                                                           \
    } while (0)

#define AUTO_UNBOX(operand)                                                   \
    do                                                                        \
    {                                                                         \
        if (operand->type == OPERAND_TYPE_REFERENCE)                          \
        {                                                                     \
            struct Object *object = operand->value.reference;                 \
            if (object != NULL)                                               \
            {                                                                 \
                switch (object->type)                                         \
                {                                                             \
                case OBJECT_TYPE_INTEGER:                                     \
                    operand->type = OPERAND_TYPE_INTEGER;                     \
                    operand->value.integerValue = object->value.integerValue; \
                    break;                                                    \
                case OBJECT_TYPE_DOUBLE:                                      \
                    operand->type = OPERAND_TYPE_DOUBLE,                      \
                    operand->value.doubleValue = object->value.doubleValue;   \
                    break;                                                    \
                }                                                             \
            }                                                                 \
        }                                                                     \
    } while (0)

#define COMPARISON(frame, operator)                                                                              \
    do                                                                                                           \
    {                                                                                                            \
        ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);                                                                 \
        operand1 = OPERAND_STACK_POP(frame);                                                                     \
        operand2 = OPERAND_STACK_PEEK(frame);                                                                    \
        ASSERT(operand1->type == operand2->type, ERRCODE_RUNTIME, "Operand types must be the same\n");           \
        operand2->type = OPERAND_TYPE_INTEGER;                                                                   \
        switch (operand1->type)                                                                                  \
        {                                                                                                        \
        case OPERAND_TYPE_INTEGER:                                                                               \
            operand2->value.integerValue = (operand2->value.integerValue operator operand1->value.integerValue); \
            break;                                                                                               \
        case OPERAND_TYPE_DOUBLE:                                                                                \
            operand2->value.integerValue = (operand2->value.doubleValue operator operand1->value.doubleValue);   \
            break;                                                                                               \
        case OPERAND_TYPE_REFERENCE:                                                                             \
            operand2->value.integerValue = (operand2->value.reference operator operand1->value.reference);       \
            break;                                                                                               \
        }                                                                                                        \
    } while (0)

#define ARITHMETIC(frame, integerCalculation, doubleCalculation) \
    do                                                           \
    {                                                            \
        ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);                 \
        operand1 = OPERAND_STACK_POP(frame);                     \
        operand2 = OPERAND_STACK_PEEK(frame);                    \
        AUTO_CAST(operand1, operand2);                           \
        switch (operand1->type)                                  \
        {                                                        \
        case OPERAND_TYPE_INTEGER:                               \
            operand2->value.integerValue = integerCalculation;   \
            break;                                               \
        case OPERAND_TYPE_DOUBLE:                                \
            operand2->value.doubleValue = doubleCalculation;     \
            break;                                               \
        }                                                        \
    } while (0)

#define SIMPLE_ARITHMETIC(frame, operator) ARITHMETIC(frame, (operand2->value.integerValue operator operand1->value.integerValue), (operand2->value.doubleValue operator operand1->value.doubleValue))

#define DIVIDE(frame)                                                                                     \
    do                                                                                                    \
    {                                                                                                     \
        ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);                                                          \
        operand1 = OPERAND_STACK_POP(frame);                                                              \
        operand2 = OPERAND_STACK_PEEK(frame);                                                             \
        AUTO_CAST(operand1, operand2);                                                                    \
        switch (operand1->type)                                                                           \
        {                                                                                                 \
        case OPERAND_TYPE_INTEGER:                                                                        \
            CHECK_DIVIDE_ZERO(operand1->value.integerValue);                                              \
            operand2->value.integerValue = (operand2->value.integerValue / operand1->value.integerValue); \
            break;                                                                                        \
        case OPERAND_TYPE_DOUBLE:                                                                         \
            CHECK_DIVIDE_ZERO(operand1->value.doubleValue);                                               \
            operand2->value.doubleValue = (operand2->value.doubleValue / operand1->value.doubleValue);    \
            break;                                                                                        \
        }                                                                                                 \
    } while (0)

#define NUMBER_UNARY(frame, operator)                                                                                                                                                                                              \
    do                                                                                                                                                                                                                             \
    {                                                                                                                                                                                                                              \
        ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);                                                                                                                                                                                   \
        operand1 = OPERAND_STACK_PEEK(frame);                                                                                                                                                                                      \
        ASSERT(operand1->type == OPERAND_TYPE_INTEGER || operand1->type == OPERAND_TYPE_DOUBLE, ERRCODE_RUNTIME, "Operand must be %s or %s\n", operandTypeStrings[OPERAND_TYPE_INTEGER], operandTypeStrings[OPERAND_TYPE_DOUBLE]); \
        switch (operand1->type)                                                                                                                                                                                                    \
        {                                                                                                                                                                                                                          \
        case OPERAND_TYPE_INTEGER:                                                                                                                                                                                                 \
            operand1->value.integerValue = operator operand1->value.integerValue;                                                                                                                                                  \
            break;                                                                                                                                                                                                                 \
        case OPERAND_TYPE_DOUBLE:                                                                                                                                                                                                  \
            operand1->value.doubleValue = operator operand1->value.doubleValue;                                                                                                                                                    \
            break;                                                                                                                                                                                                                 \
        }                                                                                                                                                                                                                          \
    } while (0)

#define INTEGER_BINARY(frame, operator)                                                                      \
    do                                                                                                       \
    {                                                                                                        \
        ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);                                                             \
        OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_INTEGER);                                       \
        OPERAND_STACK_PEEK_TYPE(frame, operand2, OPERAND_TYPE_INTEGER);                                      \
        operand2->value.integerValue = (operand2->value.integerValue operator operand1->value.integerValue); \
    } while (0)

#define INTEGER_UNARY(frame, operator)                                        \
    do                                                                        \
    {                                                                         \
        ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);                              \
        OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_INTEGER);       \
        operand1->value.integerValue = operator operand1->value.integerValue; \
    } while (0)

#define DOUBLE_UNARY(frame, fun)                                        \
    do                                                                  \
    {                                                                   \
        ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);                        \
        OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_DOUBLE);  \
        operand1->value.doubleValue = fun(operand1->value.doubleValue); \
    } while (0)

#define JUMP(frame)                                                    \
    do                                                                 \
    {                                                                  \
        BYTECODE_GET_NEXT_BYTES(frame, 2, &index16);                   \
        frame->instructionPointer = frame->method->byteCode + index16; \
    } while (0)

#define CONDITION_JUMP(frame, condition)                               \
    do                                                                 \
    {                                                                  \
        ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);                       \
        OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_INTEGER); \
        if (condition operand1->value.integerValue)                    \
            JUMP(frame);                                               \
        else                                                           \
            frame->instructionPointer += 3;                            \
    } while (0)

#define CONSTANT_TO_OPERAND(constant, operand)                                                      \
    do                                                                                              \
    {                                                                                               \
        switch (constant->type)                                                                     \
        {                                                                                           \
        case CONSTANT_TYPE_INTEGER:                                                                 \
            operand->type = OPERAND_TYPE_INTEGER;                                                   \
            operand->value.integerValue = constant->value.integerConstant;                          \
            break;                                                                                  \
        case CONSTANT_TYPE_DOUBLE:                                                                  \
            operand->type = OPERAND_TYPE_DOUBLE;                                                    \
            operand->value.doubleValue = constant->value.doubleConstant;                            \
            break;                                                                                  \
        case CONSTANT_TYPE_STRING:                                                                  \
            operand->type = OPERAND_TYPE_REFERENCE;                                                 \
            struct StringConstant *stringConstant = constant->value.stringConstant;                 \
            struct Object *stringObject = stringNew(gc, stringConstant->characterCount);            \
            struct String *string = stringObject->value.subObject;                                  \
            memcpy(string->characters, stringConstant->characters, stringConstant->characterCount); \
            operand->value.reference = stringObject;                                                \
            break;                                                                                  \
        }                                                                                           \
    } while (0)

#define PRINT(operand)                                                       \
    do                                                                       \
    {                                                                        \
        struct Object *string;                                               \
        switch (operand->type)                                               \
        {                                                                    \
        case OPERAND_TYPE_INTEGER:                                           \
            printf(INTEGER_FORMAT_STRING "\n", operand->value.integerValue); \
            break;                                                           \
        case OPERAND_TYPE_DOUBLE:                                            \
            printf(DOUBLE_FORMAT_STRING "\n", operand->value.doubleValue);   \
            break;                                                           \
        case OPERAND_TYPE_REFERENCE:                                         \
            string = objectToString(gc, operand->value.reference);           \
            stringPrint(string);                                             \
            break;                                                           \
        }                                                                    \
    } while (0)

void run(struct Class *class, struct Gc *gc, struct Stack *stack, uint8_t debug)
{
    clock_t begin = clock();

    struct MethodTable *methodTable = class->methodTable;
    struct ConstantTable *constantTable = class->constantTable;

    struct Method *mainMethod = methodTable->methods;
    struct StringConstant *className = constantTable->constants->value.stringConstant;

    DEBUG_PRINT(debug, "Running " STRING_FORMAT_STRING ".main\n", className->characterCount, className->characters);

    struct Frame *frame = stackPush(stack, mainMethod, class->constantTable);

    while (frame != NULL)
    {
        uint8_t const instruction = *(frame->instructionPointer);

        struct Operand *operand1;
        struct Operand *operand2;
        struct Operand *operand3;

        uint8_t index8;
        uint16_t index16;

        struct Constant *constant;
        struct Method *nextMethod;

        if (gcShouldMarkAndSweep(gc))
        {
            stackMark(stack);
            gcSweep(gc);
        }

        switch (instruction) // https://badootech.badoo.com/when-pigs-fly-optimising-bytecode-interpreters-f64fb6bfa20f
        {
        default:
            EXIT(ERRCODE_RUNTIME, "Unknown opcode %u\n", instruction);
            break;
        case OPCODE_JUMP:
            JUMP(frame);
            break;
        case OPCODE_JUMP_TRUE:
            CONDITION_JUMP(frame, !!);
            break;
        case OPCODE_JUMP_FALSE:
            CONDITION_JUMP(frame, !);
            break;
        case OPCODE_LOAD:
            ASSERT_OPERAND_STACK_NOT_FULL(frame);
            BYTECODE_GET_NEXT_BYTES(frame, 1, &index8);
            operand1 = frame->locals + index8;
            operand2 = OPERAND_STACK_PUSH(frame);
            COPY_OPERAND(operand1, operand2);
            frame->instructionPointer += 2;
            break;
        case OPCODE_LOAD_ARGUMENT:
            ASSERT_OPERAND_STACK_NOT_FULL(frame);
            BYTECODE_GET_NEXT_BYTES(frame, 1, &index8);
            operand1 = frame->arguments + index8;
            operand2 = OPERAND_STACK_PUSH(frame);
            COPY_OPERAND(operand1, operand2);
            frame->instructionPointer += 2;
            break;
        case OPCODE_STORE:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            BYTECODE_GET_NEXT_BYTES(frame, 1, &index8);
            operand1 = OPERAND_STACK_POP(frame);
            operand2 = frame->locals + index8;
            COPY_OPERAND(operand1, operand2);
            frame->instructionPointer += 2;
            break;
        case OPCODE_CALL:
            BYTECODE_GET_NEXT_BYTES(frame, 2, &index16);
            ASSERT(index16 < methodTable->methodCount, ERRCODE_RUNTIME, "Method index %u out of bounds\n", index16);
            nextMethod = methodTable->methods + index16;
            frame = stackPush(stack, nextMethod, constantTable);
            break;
        case OPCODE_RETURN:
            frame = stackPop(stack);
            break;
        case OPCODE_CONSTANT:
            ASSERT_OPERAND_STACK_NOT_FULL(frame);
            BYTECODE_GET_NEXT_BYTES(frame, 2, &index16);
            ASSERT(index16 < constantTable->constantCount, ERRCODE_RUNTIME, "Constant index %u out of bounds\n", index16);
            constant = constantTable->constants + index16;
            operand1 = OPERAND_STACK_PUSH(frame);
            CONSTANT_TO_OPERAND(constant, operand1);
            frame->instructionPointer += 3;
            break;
        case OPCODE_POP:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_POP(frame);
            ++frame->instructionPointer;
            break;
        case OPCODE_DUP:
            ASSERT_OPERAND_STACK_NOT_FULL(frame);
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            operand1 = OPERAND_STACK_PEEK(frame);
            operand2 = OPERAND_STACK_PUSH(frame);
            COPY_OPERAND(operand1, operand2);
            ++frame->instructionPointer;
            break;
        case OPCODE_PRINT:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            operand1 = OPERAND_STACK_POP(frame);
            PRINT(operand1);
            ++frame->instructionPointer;
            break;
        case OPCODE_EQUAL:
            COMPARISON(frame, ==);
            ++frame->instructionPointer;
            break;
        case OPCODE_NOT_EQUAL:
            COMPARISON(frame, !=);
            ++frame->instructionPointer;
            break;
        case OPCODE_GREATER_THAN:
            COMPARISON(frame, >);
            ++frame->instructionPointer;
            break;
        case OPCODE_GREATER_THAN_OR_EQUAL:
            COMPARISON(frame, >=);
            ++frame->instructionPointer;
            break;
        case OPCODE_LESS_THAN:
            COMPARISON(frame, <);
            ++frame->instructionPointer;
            break;
        case OPCODE_LESS_THAN_OR_EQUAL:
            COMPARISON(frame, <=);
            ++frame->instructionPointer;
            break;
        case OPCODE_NUMBER_ADD:
            SIMPLE_ARITHMETIC(frame, +);
            ++frame->instructionPointer;
            break;
        case OPCODE_NUMBER_SUBTRACT:
            SIMPLE_ARITHMETIC(frame, -);
            ++frame->instructionPointer;
            break;
        case OPCODE_NUMBER_MULTIPLY:
            SIMPLE_ARITHMETIC(frame, *);
            break;
        case OPCODE_NUMBER_DIVIDE:
            DIVIDE(frame);
            ++frame->instructionPointer;
            break;
        case OPCODE_NUMBER_POWER:
            ARITHMETIC(frame, (Integer)pow(operand2->value.integerValue, operand1->value.integerValue), (Double)pow(operand2->value.doubleValue, operand1->value.doubleValue));
            ++frame->instructionPointer;
            break;
        case OPCODE_NUMBER_NEGATE:
            NUMBER_UNARY(frame, -);
            ++frame->instructionPointer;
            break;
        case OPCODE_NUMBER_SQRT:
            ARITHMETIC(frame, (Integer)pow(operand2->value.integerValue, 0.5), (Double)pow(operand2->value.doubleValue, 0.5));
            ++frame->instructionPointer;
            break;
        case OPCODE_INTEGER_TO_DOUBLE:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_INTEGER);
            operand1->type = OPERAND_TYPE_DOUBLE;
            operand1->value.doubleValue = (Double)operand1->value.integerValue;
            ++frame->instructionPointer;
            break;
        case OPCODE_INTEGER_INCREMENT:
            INTEGER_UNARY(frame, 1 +);
            ++frame->instructionPointer;
            break;
        case OPCODE_INTEGER_DECREMENT:
            INTEGER_UNARY(frame, -1 +);
            ++frame->instructionPointer;
            break;
        case OPCODE_INTEGER_MODULO:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_INTEGER);
            OPERAND_STACK_PEEK_TYPE(frame, operand2, OPERAND_TYPE_INTEGER);
            CHECK_DIVIDE_ZERO(operand1->value.integerValue);
            operand2->value.integerValue = (operand2->value.integerValue % operand1->value.integerValue);
            ++frame->instructionPointer;
            break;
        case OPCODE_INTEGER_AND:
            INTEGER_BINARY(frame, &);
            ++frame->instructionPointer;
            break;
        case OPCODE_INTEGER_OR:
            INTEGER_BINARY(frame, |);
            ++frame->instructionPointer;
            break;
        case OPCODE_INTEGER_NOT:
            INTEGER_UNARY(frame, ~);
            ++frame->instructionPointer;
            break;
        case OPCODE_INTEGER_XOR:
            INTEGER_BINARY(frame, ^);
            ++frame->instructionPointer;
            break;
        case OPCODE_DOUBLE_TO_INTEGER:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_DOUBLE);
            operand1->type = OPERAND_TYPE_INTEGER;
            operand1->value.integerValue = (Integer)operand1->value.doubleValue;
            ++frame->instructionPointer;
            break;
        case OPCODE_DOUBLE_CEIL:
            DOUBLE_UNARY(frame, ceil);
            ++frame->instructionPointer;
            break;
        case OPCODE_DOUBLE_FLOOR:
            DOUBLE_UNARY(frame, floor);
            ++frame->instructionPointer;
            break;
        case OPCODE_OBJECT_NULL:
            ASSERT_OPERAND_STACK_NOT_FULL(frame);
            operand1 = OPERAND_STACK_PUSH(frame);
            operand1->type = OPERAND_TYPE_REFERENCE;
            operand1->value.reference = NULL;
            ++frame->instructionPointer;
            break;
        case OPCODE_OBJECT_IS_NULL:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->type = OPERAND_TYPE_INTEGER;
            operand1->value.integerValue = operand1->value.reference == NULL;
            ++frame->instructionPointer;
            break;
        case OPCODE_OBJECT_COPY:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->value.reference = objectCopy(gc, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_OBJECT_EQUALS:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            OPERAND_STACK_PEEK_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            operand2->type = OPERAND_TYPE_INTEGER;
            operand2->value.integerValue = objectEquals(operand1->value.reference, operand2->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_OBJECT_HASH:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->type = OPERAND_TYPE_INTEGER;
            operand1->value.integerValue = objectHash(operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_OBJECT_TO_STRING:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->value.reference = objectToString(gc, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_ARRAY_NEW:
            ASSERT_OPERAND_STACK_NOT_FULL(frame);
            operand1 = OPERAND_STACK_PUSH(frame);
            operand1->type = OPERAND_TYPE_REFERENCE;
            operand1->value.reference = arrayNew(gc, 0, 10);
            ++frame->instructionPointer;
            break;
        case OPCODE_ARRAY_NEW_WITH_SIZE:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_INTEGER);
            operand1->type = OPERAND_TYPE_REFERENCE;
            operand1->value.reference = arrayNew(gc, 0, operand1->value.integerValue);
            ++frame->instructionPointer;
            break;
        case OPCODE_ARRAY_SIZE:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->type = OPERAND_TYPE_INTEGER;
            operand1->value.integerValue = arraySize(operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_ARRAY_IS_EMPTY:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->type = OPERAND_TYPE_INTEGER;
            operand1->value.integerValue = arraySize(operand1->value.reference) == 0;
            ++frame->instructionPointer;
            break;
        case OPCODE_ARRAY_GET:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_INTEGER);
            OPERAND_STACK_PEEK_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            operand2->value.reference = arrayGet(operand2->value.reference, operand1->value.integerValue);
            AUTO_UNBOX(operand2);
            ++frame->instructionPointer;
            break;
        case OPCODE_ARRAY_SET:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 3);
            operand1 = OPERAND_STACK_POP(frame);
            AUTO_BOX(gc, operand1);
            OPERAND_STACK_POP_TYPE(frame, operand2, OPERAND_TYPE_INTEGER);
            OPERAND_STACK_PEEK_TYPE(frame, operand3, OPERAND_TYPE_REFERENCE);
            operand3->value.reference = arraySet(operand3->value.reference, operand2->value.integerValue, operand1->value.reference);
            AUTO_UNBOX(operand3);
            ++frame->instructionPointer;
            break;
        case OPCODE_ARRAY_INSERT:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 3);
            operand1 = OPERAND_STACK_POP(frame);
            AUTO_BOX(gc, operand1);
            OPERAND_STACK_POP_TYPE(frame, operand2, OPERAND_TYPE_INTEGER);
            OPERAND_STACK_POP_TYPE(frame, operand3, OPERAND_TYPE_REFERENCE);
            arrayInsert(gc, operand3->value.reference, operand2->value.integerValue, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_ARRAY_INSERT_ALL:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 3);
            OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            OPERAND_STACK_POP_TYPE(frame, operand2, OPERAND_TYPE_INTEGER);
            OPERAND_STACK_POP_TYPE(frame, operand3, OPERAND_TYPE_REFERENCE);
            arrayInsertAll(gc, operand3->value.reference, operand2->value.integerValue, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_ARRAY_REMOVE:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_INTEGER);
            OPERAND_STACK_PEEK_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            operand2->value.reference = arrayRemove(operand2->value.reference, operand1->value.integerValue);
            AUTO_UNBOX(operand2);
            ++frame->instructionPointer;
            break;
        case OPCODE_ARRAY_PUSH:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            operand1 = OPERAND_STACK_POP(frame);
            AUTO_BOX(gc, operand1);
            OPERAND_STACK_POP_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            arrayPush(gc, operand2->value.reference, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_ARRAY_PUSH_ALL:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            OPERAND_STACK_POP_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            arrayPushAll(gc, operand2->value.reference, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_ARRAY_POP:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->value.reference = arrayPop(operand1->value.reference);
            AUTO_UNBOX(operand1);
            ++frame->instructionPointer;
            break;
        case OPCODE_ARRAY_SWAP:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 3);
            OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_INTEGER);
            OPERAND_STACK_POP_TYPE(frame, operand2, OPERAND_TYPE_INTEGER);
            OPERAND_STACK_POP_TYPE(frame, operand3, OPERAND_TYPE_REFERENCE);
            arraySwap(operand3->value.reference, operand2->value.integerValue, operand1->value.integerValue);
            ++frame->instructionPointer;
            break;
        case OPCODE_MAP_NEW:
            ASSERT_OPERAND_STACK_NOT_FULL(frame);
            operand1 = OPERAND_STACK_PUSH(frame);
            operand1->type = OPERAND_TYPE_REFERENCE;
            operand1->value.reference = mapNew(gc);
            ++frame->instructionPointer;
            break;
        case OPCODE_MAP_SIZE:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->type = OPERAND_TYPE_INTEGER;
            operand1->value.integerValue = mapSize(operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_MAP_IS_EMPTY:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->type = OPERAND_TYPE_INTEGER;
            operand1->value.integerValue = mapSize(operand1->value.reference) == 0;
            ++frame->instructionPointer;
            break;
        case OPCODE_MAP_GET:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            operand1 = OPERAND_STACK_POP(frame);
            AUTO_BOX(gc, operand1);
            OPERAND_STACK_PEEK_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            operand2->value.reference = mapGet(operand2->value.reference, operand1->value.reference);
            AUTO_UNBOX(operand2);
            ++frame->instructionPointer;
            break;
        case OPCODE_MAP_PUT:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 3);
            operand1 = OPERAND_STACK_POP(frame);
            AUTO_BOX(gc, operand1);
            operand2 = OPERAND_STACK_POP(frame);
            AUTO_BOX(gc, operand2);
            OPERAND_STACK_PEEK_TYPE(frame, operand3, OPERAND_TYPE_REFERENCE);
            operand3->value.reference = mapPut(gc, operand3->value.reference, operand2->value.reference, operand1->value.reference);
            AUTO_UNBOX(operand3);
            ++frame->instructionPointer;
            break;
        case OPCODE_MAP_PUT_ALL:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            OPERAND_STACK_POP_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            mapPutAll(gc, operand2->value.reference, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_MAP_REMOVE:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            operand1 = OPERAND_STACK_POP(frame);
            AUTO_BOX(gc, operand1);
            OPERAND_STACK_PEEK_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            operand2->value.reference = mapRemove(gc, operand2->value.reference, operand1->value.reference);
            AUTO_UNBOX(operand2);
            ++frame->instructionPointer;
            break;
        case OPCODE_MAP_HAS_KEY:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            operand1 = OPERAND_STACK_POP(frame);
            AUTO_BOX(gc, operand1);
            OPERAND_STACK_PEEK_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            operand2->type = OPERAND_TYPE_INTEGER;
            operand2->value.integerValue = mapHasKey(operand2->value.reference, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_MAP_ENTRIES:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->value.reference = mapEntries(gc, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_MAP_KEYS:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->value.reference = mapKeys(gc, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_MAP_VALUES:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->value.reference = mapValues(gc, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_MAP_SWAP:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 3);
            operand1 = OPERAND_STACK_POP(frame);
            AUTO_BOX(gc, operand1);
            operand2 = OPERAND_STACK_POP(frame);
            AUTO_BOX(gc, operand2);
            OPERAND_STACK_POP_TYPE(frame, operand3, OPERAND_TYPE_REFERENCE);
            mapSwap(operand3->value.reference, operand2->value.reference, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_PAIR_NEW:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            operand1 = OPERAND_STACK_POP(frame);
            AUTO_BOX(gc, operand1);
            operand2 = OPERAND_STACK_PEEK(frame);
            AUTO_BOX(gc, operand2);
            operand2->value.reference = pairNew(gc, operand2->value.reference, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_PAIR_GET_FIRST:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->value.reference = pairGetFirst(operand1->value.reference);
            AUTO_UNBOX(operand1);
            ++frame->instructionPointer;
            break;
        case OPCODE_PAIR_SET_FIRST:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            operand1 = OPERAND_STACK_POP(frame);
            AUTO_BOX(gc, operand1);
            OPERAND_STACK_PEEK_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            operand2->value.reference = pairSetFirst(operand2->value.reference, operand1->value.reference);
            AUTO_UNBOX(operand2);
            ++frame->instructionPointer;
            break;
        case OPCODE_PAIR_GET_SECOND:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->value.reference = pairGetSecond(operand1->value.reference);
            AUTO_UNBOX(operand1);
            ++frame->instructionPointer;
            break;
        case OPCODE_PAIR_SET_SECOND:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            operand1 = OPERAND_STACK_POP(frame);
            AUTO_BOX(gc, operand1);
            OPERAND_STACK_PEEK_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            operand2->value.reference = pairSetSecond(operand2->value.reference, operand1->value.reference);
            AUTO_UNBOX(operand2);
            ++frame->instructionPointer;
            break;
        case OPCODE_PAIR_SWAP:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            pairSwap(operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_STRING_SIZE:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->type = OPERAND_TYPE_INTEGER;
            operand1->value.integerValue = stringSize(operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_STRING_IS_EMPTY:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->type = OPERAND_TYPE_INTEGER;
            operand1->value.integerValue = stringSize(operand1->value.reference) == 0;
            ++frame->instructionPointer;
            break;
        case OPCODE_STRING_FROM_ARRAY:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->value.reference = stringFromArray(gc, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_STRING_TO_ARRAY:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 1);
            OPERAND_STACK_PEEK_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            operand1->value.reference = stringToArray(gc, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_STRING_COMPARE:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            OPERAND_STACK_PEEK_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            operand2->type = OPERAND_TYPE_INTEGER;
            operand2->value.integerValue = stringCompare(operand2->value.reference, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_STRING_CONCATENATE:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            OPERAND_STACK_PEEK_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            operand2->value.reference = stringConcatenate(gc, operand2->value.reference, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_STRING_SUBSTRING:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 3);
            OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_INTEGER);
            OPERAND_STACK_POP_TYPE(frame, operand2, OPERAND_TYPE_INTEGER);
            OPERAND_STACK_PEEK_TYPE(frame, operand3, OPERAND_TYPE_REFERENCE);
            operand3->value.reference = stringSubstring(gc, operand3->value.reference, operand2->value.integerValue, operand1->value.integerValue);
            ++frame->instructionPointer;
            break;
        case OPCODE_STRING_INDEX_OF:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 3);
            OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_INTEGER);
            OPERAND_STACK_POP_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            OPERAND_STACK_PEEK_TYPE(frame, operand3, OPERAND_TYPE_REFERENCE);
            operand3->type = OPERAND_TYPE_INTEGER;
            operand3->value.integerValue = stringIndexOf(operand3->value.reference, operand2->value.reference, operand1->value.integerValue);
            ++frame->instructionPointer;
            break;
        case OPCODE_STRING_CONTAINS:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            OPERAND_STACK_PEEK_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            operand2->type = OPERAND_TYPE_INTEGER;
            operand2->value.integerValue = stringContains(operand2->value.reference, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_STRING_REPLACE:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 3);
            OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            OPERAND_STACK_POP_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            OPERAND_STACK_PEEK_TYPE(frame, operand3, OPERAND_TYPE_REFERENCE);
            operand3->value.reference = stringReplace(gc, operand3->value.reference, operand2->value.reference, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        case OPCODE_STRING_SPLIT:
            ASSERT_OPERAND_STACK_MIN_SIZE(frame, 2);
            OPERAND_STACK_POP_TYPE(frame, operand1, OPERAND_TYPE_REFERENCE);
            OPERAND_STACK_PEEK_TYPE(frame, operand2, OPERAND_TYPE_REFERENCE);
            operand2->value.reference = stringSplit(gc, operand2->value.reference, operand1->value.reference);
            ++frame->instructionPointer;
            break;
        }

        // printf("%s\n", instructionStrings[instruction]);
    }
    double time = (double)(clock() - begin) / CLOCKS_PER_SEC;
    EXIT(ERRCODE_NO_ERROR, "Program finished in %f seconds\n", time);
}