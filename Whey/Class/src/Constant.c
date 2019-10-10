#include "../Constant.h"
#include "../../Types.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void readConstant(struct Constant *constant, uint8_t *bytes, uint32_t *byteIndex, uint32_t byteCount)
{
    uint32_t byteIndexTemp = *byteIndex;
    ASSERT_READ_IN_BOUNDS(byteIndexTemp, 1, byteCount);
    constant->type = bytes[byteIndexTemp];
    ++byteIndexTemp;

    uint32_t characterCount;
    void *memory; 
    switch (constant->type)
    {
    case CONSTANT_TYPE_INTEGER:
        ASSERT_READ_IN_BOUNDS(byteIndexTemp, sizeof(Integer), byteCount);
        memcpy(&(constant->value.integerConstant), bytes + byteIndexTemp, sizeof(Integer));
        byteIndexTemp += sizeof(Integer);
        break;

    case CONSTANT_TYPE_DOUBLE:
        ASSERT_READ_IN_BOUNDS(byteIndexTemp, sizeof(Double), byteCount);
        memcpy(&(constant->value.doubleConstant), bytes + byteIndexTemp, sizeof(Double));
        byteIndexTemp += sizeof(Double);
        break;

    case CONSTANT_TYPE_STRING:
        ASSERT_READ_IN_BOUNDS(byteIndexTemp, sizeof(uint32_t), byteCount);
        memcpy(&characterCount, bytes + byteIndexTemp, sizeof(uint32_t));
        byteIndexTemp += 4;

        memory = malloc(sizeof(struct StringConstant) + characterCount);
        NOT_NULL_CHECK(memory, ERRCODE_CLASS, "Cannot create StringConstant\n");
        
        constant->value.stringConstant = memory;
        constant->value.stringConstant->characterCount = characterCount;
        constant->value.stringConstant->characters = memory + sizeof(struct StringConstant);

        if (characterCount > 0)
        {
            ASSERT_READ_IN_BOUNDS(byteIndexTemp, sizeof(uint32_t), byteCount);
            memcpy(constant->value.stringConstant->characters, bytes + byteIndexTemp, characterCount);
            byteIndexTemp += characterCount;
        }

        break;
    default:
        EXIT(ERRCODE_CLASS, "Illegal constant type %u\n", constant->type);
        break;
    }

    *byteIndex = byteIndexTemp;
}

struct ConstantTable *constantTableNew(char *fileName, uint8_t *bytes, uint32_t *byteIndex, uint32_t byteCount, uint8_t debug)
{
    uint16_t constantCount;
    ASSERT_READ_IN_BOUNDS(*byteIndex, 2, byteCount);
    memcpy(&(constantCount), bytes + *byteIndex, 2);
    (*byteIndex) += 2;

    void *memory = malloc(sizeof(struct ConstantTable) + constantCount * sizeof(struct Constant));
    NOT_NULL_CHECK(memory, ERRCODE_CLASS, "Cannot create ConstantTable for %s\n", fileName);

    struct ConstantTable *constantTable = memory;
    constantTable->constantCount = constantCount;
    constantTable->constants = memory + sizeof(struct ConstantTable);

    for (uint16_t i = 0; i < constantCount; i++)
    {
        DEBUG_PRINT(debug, "Reading Constant %u from index %u\n", i, *byteIndex);
        readConstant(constantTable->constants + i, bytes, byteIndex, byteCount);
    }

    return constantTable;
}

void constantTableFree(struct ConstantTable *constantTable)
{
    for (uint16_t i = 0; i < constantTable->constantCount; i++)
    {
        struct Constant *constant = constantTable->constants + i;
        if (constant->type == CONSTANT_TYPE_STRING)
        {
            free(constant->value.stringConstant);
        }
    }

    free(constantTable);
}