#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define CONSTANT_TYPE_INTEGER 0x01
#define CONSTANT_TYPE_DOUBLE 0x02
#define CONSTANT_TYPE_STRING 0x03

#define OBJECT_TYPE_INTEGER 0x01
#define OBJECT_TYPE_DOUBLE 0x02
#define OBJECT_TYPE_ARRAY 0x03
#define OBJECT_TYPE_STRING 0x04
#define OBJECT_TYPE_MAP 0x05
#define OBJECT_TYPE_PAIR 0x06

#define OBJECT_MARK 0x80

#define OPERAND_TYPE_INTEGER 0x01
#define OPERAND_TYPE_DOUBLE 0x02
#define OPERAND_TYPE_REFERENCE 0x03

#define NOT_NULL_CHECK(result, error, ...) \
    do                                     \
    {                                      \
        if (result == NULL)                \
        {                                  \
            EXIT(error, __VA_ARGS__);      \
        }                                  \
    } while (0)

#define ERROR_CHECK(check, error, ...) \
    do                                 \
    {                                  \
        if (check)                     \
        {                              \
            EXIT(error, __VA_ARGS__);  \
        }                              \
    } while (0)

#define EXIT(error, ...)     \
    do                       \
    {                        \
        printf(__VA_ARGS__); \
        returnCode = error;  \
        exit(returnCode);    \
    } while (0);

#define DEBUG_PRINT(debug, ...)  \
    do                           \
    {                            \
        if (debug)               \
        {                        \
            printf(__VA_ARGS__); \
        }                        \
    } while (0)

#ifndef NDEBUG
#define ASSERT(assertion, errorCode, ...) \
    do                                    \
    {                                     \
        if (!(assertion))                 \
        {                                 \
            printf(__VA_ARGS__);          \
            returnCode = errorCode;       \
            exit(returnCode);             \
        }                                 \
    } while (0)
#else
#define ASSERT(assertion, errorCode, ...) ((void)0)
#endif

#define BOOLEAN_TRUE 1
#define BOOLEAN_FALSE 0

typedef int64_t Integer;
typedef double Double;

#define INTEGER_FORMAT_STRING "%ld"
#define DOUBLE_FORMAT_STRING "%e"
#define STRING_FORMAT_STRING "%.*s"

uint8_t returnCode;

extern char *objectTypeStrings[7];
extern char *operandTypeStrings[4];
extern char *constantTypeStrings[4];
extern char *instructionStrings[85];

#define ERRCODE_NO_ERROR 0x00
#define ERRCODE_RUNTIME 0x01
#define ERRCODE_CLASS 0x02
#define ERRCODE_INTERNAL 0x03

#define OBJECT_UNKNOWN_TYPE(object) EXIT(ERRCODE_CLASS, "Unknown object type %u\n", object->type)
#define OBJECT_NOT_NULL_CHECK(object, objectType) NOT_NULL_CHECK(object, ERRCODE_RUNTIME, "%s is null\n", objectTypeStrings[objectType])
#define ASSERT_OBJECT_TYPE(object, objectType) ASSERT(object->type == objectType, ERRCODE_RUNTIME, "%s is required\n", objectTypeStrings[objectType])

#define CHECK_VALID_SIZE(objectType, number) ERROR_CHECK(number < 0, ERRCODE_RUNTIME, "%s size %ld invalid\n", objectTypeStrings[objectType], number)
#define CHECK_VALID_INDEX(objectType, number, size) ERROR_CHECK(number < 0 || number >= size, ERRCODE_RUNTIME, "%s index %ld out of bounds(0-%u)\n", objectTypeStrings[objectType], number, size - 1)
#define CHECK_VALID_INCL_INDEX(objectType, number, size) ERROR_CHECK(number<0 || number> size, ERRCODE_RUNTIME, "%s index %ld out of bounds(0-%u)\n", objectTypeStrings[objectType], number, size)
#define CHECK_INDICES_ORDERED(objectType, index1, index2) ERROR_CHECK(index1 > index2, ERRCODE_RUNTIME, "%s first index %ld must be smaller or equal to first %ld\n", objectTypeStrings[objectType], index2, index1)

#define ASSERT_OPERAND_TYPE(operand, operandType) ASSERT(operand->type == operandType, ERRCODE_RUNTIME, "%s is required\n", operandTypeStrings[operandType]);
#define ASSERT_OPERAND_STACK_MIN_SIZE(frame, min) ASSERT(OPERAND_STACK_SIZE(frame) >= min, ERRCODE_RUNTIME, "Operand stack size must be at least %u\n", min)
#define ASSERT_OPERAND_STACK_NOT_FULL(frame) ASSERT(OPERAND_STACK_SIZE(frame) < frame->method->maxOperandCount, ERRCODE_RUNTIME, "Operand stack is full with size %u\n", frame->method->maxOperandCount)

#define OPCODE_UNKNOWN 0x00
#define OPCODE_JUMP 0x01
#define OPCODE_JUMP_TRUE 0x02
#define OPCODE_JUMP_FALSE 0x03
#define OPCODE_LOAD 0x04
#define OPCODE_LOAD_ARGUMENT 0x05
#define OPCODE_STORE 0x06
#define OPCODE_CALL 0x07
#define OPCODE_RETURN 0x08
#define OPCODE_CONSTANT 0x09
#define OPCODE_POP 0x0A
#define OPCODE_DUP 0x0B
#define OPCODE_PRINT 0x0C
#define OPCODE_EQUAL 0x0D
#define OPCODE_NOT_EQUAL 0x0E
#define OPCODE_GREATER_THAN 0x0F
#define OPCODE_GREATER_THAN_OR_EQUAL 0x10
#define OPCODE_LESS_THAN 0x11
#define OPCODE_LESS_THAN_OR_EQUAL 0x12
#define OPCODE_NUMBER_ADD 0x13
#define OPCODE_NUMBER_SUBTRACT 0x14
#define OPCODE_NUMBER_MULTIPLY 0x15
#define OPCODE_NUMBER_DIVIDE 0x16
#define OPCODE_NUMBER_POWER 0x17
#define OPCODE_NUMBER_NEGATE 0x18
#define OPCODE_NUMBER_SQRT 0x19
#define OPCODE_INTEGER_TO_DOUBLE 0x1A
#define OPCODE_INTEGER_INCREMENT 0x1B
#define OPCODE_INTEGER_DECREMENT 0x1C
#define OPCODE_INTEGER_MODULO 0x1D
#define OPCODE_INTEGER_AND 0x1E
#define OPCODE_INTEGER_OR 0x1F
#define OPCODE_INTEGER_NOT 0x20
#define OPCODE_INTEGER_XOR 0x21
#define OPCODE_DOUBLE_TO_INTEGER 0x22
#define OPCODE_DOUBLE_CEIL 0x23
#define OPCODE_DOUBLE_FLOOR 0x24
#define OPCODE_OBJECT_NULL 0x25
#define OPCODE_OBJECT_IS_NULL 0x26
#define OPCODE_OBJECT_COPY 0x27
#define OPCODE_OBJECT_EQUALS 0x28
#define OPCODE_OBJECT_HASH 0x29
#define OPCODE_OBJECT_TO_STRING 0x2A
#define OPCODE_ARRAY_NEW 0x2B
#define OPCODE_ARRAY_NEW_WITH_SIZE 0x2C
#define OPCODE_ARRAY_SIZE 0x2D
#define OPCODE_ARRAY_IS_EMPTY 0x2E
#define OPCODE_ARRAY_GET 0x2F
#define OPCODE_ARRAY_SET 0x30
#define OPCODE_ARRAY_INSERT 0x31
#define OPCODE_ARRAY_INSERT_ALL 0x32
#define OPCODE_ARRAY_REMOVE 0x33
#define OPCODE_ARRAY_PUSH 0x34
#define OPCODE_ARRAY_PUSH_ALL 0x35
#define OPCODE_ARRAY_POP 0x36
#define OPCODE_ARRAY_SWAP 0x37
#define OPCODE_MAP_NEW 0x38
#define OPCODE_MAP_SIZE 0x39
#define OPCODE_MAP_IS_EMPTY 0x3A
#define OPCODE_MAP_GET 0x3B
#define OPCODE_MAP_PUT 0x3C
#define OPCODE_MAP_PUT_ALL 0x3D
#define OPCODE_MAP_REMOVE 0x3E
#define OPCODE_MAP_HAS_KEY 0x3F
#define OPCODE_MAP_ENTRIES 0x40
#define OPCODE_MAP_KEYS 0x41
#define OPCODE_MAP_VALUES 0x42
#define OPCODE_MAP_SWAP 0x43
#define OPCODE_PAIR_NEW 0x44
#define OPCODE_PAIR_GET_FIRST 0x45
#define OPCODE_PAIR_SET_FIRST 0x46
#define OPCODE_PAIR_GET_SECOND 0x47
#define OPCODE_PAIR_SET_SECOND 0x48
#define OPCODE_PAIR_SWAP 0x49
#define OPCODE_STRING_SIZE 0x4A
#define OPCODE_STRING_IS_EMPTY 0x4B
#define OPCODE_STRING_FROM_ARRAY 0x4C
#define OPCODE_STRING_TO_ARRAY 0x4D
#define OPCODE_STRING_COMPARE 0x4E
#define OPCODE_STRING_CONCATENATE 0x4F
#define OPCODE_STRING_SUBSTRING 0x50
#define OPCODE_STRING_INDEX_OF 0x51
#define OPCODE_STRING_CONTAINS 0x52
#define OPCODE_STRING_REPLACE 0x53
#define OPCODE_STRING_SPLIT 0x54

#endif