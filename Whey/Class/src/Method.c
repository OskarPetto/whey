#include "../Method.h"
#include "../../Types.h"

#include <stdlib.h>
#include <string.h>

void readMethod(struct Method *method, uint8_t *bytes, uint32_t *byteIndex, uint32_t byteCount)
{
    uint16_t nameIndex;
    uint8_t argumentCount;
    uint8_t returnsSomething;
    uint8_t localsCount;
    uint8_t maxOperandCount;
    uint16_t codeSize;

    uint32_t byteIndexTemp = *byteIndex;
    ASSERT_READ_IN_BOUNDS(byteIndexTemp, 8, byteCount);

    memcpy(&nameIndex, bytes + byteIndexTemp, 2);
    byteIndexTemp +=2;
    argumentCount = bytes[byteIndexTemp];
    ++byteIndexTemp;
    returnsSomething = bytes[byteIndexTemp];
    ++byteIndexTemp;
    localsCount = bytes[byteIndexTemp];
    ++byteIndexTemp;
    maxOperandCount = bytes[byteIndexTemp];
    ++byteIndexTemp;
    memcpy(&codeSize, bytes + byteIndexTemp, 2);
    byteIndexTemp += 2;

    ASSERT_READ_IN_BOUNDS(byteIndexTemp, codeSize, byteCount);

    method->nameIndex = nameIndex;
    method->argumentCount = argumentCount;
    method->returnsSomething = returnsSomething;
    method->localsCount = localsCount;
    method->maxOperandCount = maxOperandCount;
    method->codeSize = codeSize;
    method->byteCode = malloc(codeSize);
    NOT_NULL_CHECK(method->byteCode, ERRCODE_CLASS, "Cannot create Bytes for Method\n");

    memcpy(method->byteCode, bytes + byteIndexTemp, codeSize);
    byteIndexTemp += codeSize;

    *byteIndex = byteIndexTemp;

}

struct MethodTable *methodTableNew(char *fileName, uint8_t *bytes, uint32_t *byteIndex, uint32_t byteCount, uint8_t debug)
{
    uint16_t methodCount;
    ASSERT_READ_IN_BOUNDS(*byteIndex, 2, byteCount);
    memcpy(&(methodCount), bytes + *byteIndex, 2);
    (*byteIndex) += 2;

    void *memory = malloc(sizeof(struct MethodTable) + methodCount * sizeof(struct Method));
    NOT_NULL_CHECK(memory, ERRCODE_CLASS, "Cannot create MethodTable for %s\n", fileName);

    struct MethodTable *methodTable = memory;
    methodTable->methodCount = methodCount;
    methodTable->methods = memory + sizeof(struct MethodTable);

    for (uint16_t i = 0; i < methodCount; i++)
    {
        DEBUG_PRINT(debug, "Reading Method %u from index %u\n", i, *byteIndex);
        readMethod(methodTable->methods + i , bytes, byteIndex, byteCount);
    }

    return methodTable;
}

void methodTableFree(struct MethodTable *methodTable)
{   
    for (size_t i = 0; i < methodTable->methodCount; i++)
    {
        struct Method *method = methodTable->methods + i;
        free(method->byteCode);
    }
    
    free(methodTable);
}