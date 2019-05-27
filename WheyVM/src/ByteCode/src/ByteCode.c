#include "../ByteCode.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

static void readConstants(struct ByteCode *byteCode, unsigned char *bytes, uint32_t *byteIndex)
{
    memcpy(&(byteCode->constantCount), bytes + *byteIndex, 2);
    (*byteIndex) += 2;

    byteCode->constants = (struct Constant **)malloc(byteCode->constantCount * sizeof(struct Constant *));
    assert(byteCode->constants != NULL);

    for (uint16_t i = 0; i < byteCode->constantCount; i++)
    {
        byteCode->constants[i] = constantNew(bytes, byteIndex);
    }
    
}

static void readFunctions(struct ByteCode *byteCode, unsigned char *bytes, uint32_t *byteIndex)
{
    memcpy(&(byteCode->functionCount), bytes + *byteIndex, 2);
    (*byteIndex) += 2;

    byteCode->functions = (struct Function **)malloc(byteCode->functionCount * sizeof(struct Function *));
    assert(byteCode->functions != NULL);

    for (uint16_t i = 0; i < byteCode->functionCount; i++)
    {
        byteCode->functions[i] = functionNew(bytes, byteIndex);
    }
    
}

struct ByteCode *byteCodeNew(char *fileName)
{
    FILE *file = fopen(fileName, "rb");
    assert(file != NULL);

    struct ByteCode *byteCode = (struct ByteCode *)malloc(sizeof(struct ByteCode));

    fseek(file, 0, SEEK_END);

    byteCode->byteCount = (uint32_t) ftell(file);

    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(byteCode->byteCount * sizeof(unsigned char));

    size_t readCount = fread(buffer, 1, byteCode->byteCount, file);

    fclose(file);

    if (readCount < byteCode->byteCount)
    {
        free(buffer);
        free(byteCode);
        fprintf(stderr, "could not read file\n");
        exit(1);
    }

    uint32_t byteIndex = 0;

    readConstants(byteCode, buffer, &byteIndex);
    readFunctions(byteCode, buffer, &byteIndex);

    free(buffer);

    return byteCode;
}

struct Constant *byteCodeGetConstant(struct ByteCode *byteCode, uint16_t constantIndex)
{
    return byteCode->constants[constantIndex];
}

struct Function *byteCodeGetFunction(struct ByteCode *byteCode, uint16_t functionIndex)
{
    return byteCode->functions[functionIndex];
}

void byteCodeFree(struct ByteCode *byteCode)
{
    for (uint16_t i = 0; i < byteCode->constantCount; i++)
    {
        constantFree(byteCode->constants[i]);
    }

    for (uint16_t i = 0; i < byteCode->functionCount; i++)
    {
        functionFree(byteCode->functions[i]);
    }
    
    free(byteCode->constants);
    free(byteCode->functions);

    free(byteCode);
}