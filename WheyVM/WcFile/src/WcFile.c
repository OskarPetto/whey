#include "../WcFile.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

static void readConstants(struct WcFile *wcFile, unsigned char *bytes, uint32_t *byteIndex)
{
    memcpy(&(wcFile->constantCount), &bytes[*byteIndex], 2);
    (*byteIndex) += 2;

    wcFile->constants = (struct Constant **)malloc(wcFile->constantCount * sizeof(struct Constant *));
    assert(wcFile->constants != NULL);

    for (uint16_t i = 0; i < wcFile->constantCount; i++)
    {
        wcFile->constants[i] = constantNew(bytes, byteIndex);
    }
    
}

static void readFunctions(struct WcFile *wcFile, unsigned char *bytes, uint32_t *byteIndex)
{
    memcpy(&(wcFile->functionCount), &bytes[*byteIndex], 2);
    (*byteIndex) += 2;

    wcFile->functions = (struct Function **)malloc(wcFile->functionCount * sizeof(struct Function *));
    assert(wcFile->functions != NULL);

    for (uint16_t i = 0; i < wcFile->functionCount; i++)
    {
        wcFile->functions[i] = functionNew(bytes, byteIndex);
    }
    
}

struct WcFile *wcFileNew(char *fileName)
{
    FILE *file = fopen(fileName, "rb");
    assert(file != NULL);

    struct WcFile *wcFile = (struct WcFile *)malloc(sizeof(struct WcFile));

    fseek(file, 0, SEEK_END);

    uint32_t byteCount = (uint32_t) ftell(file);

    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(byteCount * sizeof(unsigned char));

    size_t readCount = fread(buffer, 1, byteCount, file);

    fclose(file);

    if (readCount < byteCount)
    {
        free(buffer);
        free(wcFile);
        fprintf(stderr, "could not read file\n");
        exit(1);
    }

    uint32_t checkSum;
    memcpy(&checkSum, buffer, 4);

    if(checkSum != 4272938682)
    {
        free(buffer);
        free(wcFile);
        fprintf(stderr, "could not parse file\n");
        exit(1);
    }

    uint32_t byteIndex = 4;
    readConstants(wcFile, buffer, &byteIndex);
    readFunctions(wcFile, buffer, &byteIndex);

    free(buffer);

    return wcFile;
}

struct Constant *wcFileGetConstant(struct WcFile *wcFile, uint16_t constantIndex)
{
    return wcFile->constants[constantIndex];
}

struct Function *wcFileGetFunction(struct WcFile *wcFile, uint16_t functionIndex)
{
    return wcFile->functions[functionIndex];
}

void wcFileFree(struct WcFile *wcFile)
{
    for (uint16_t i = 0; i < wcFile->constantCount; i++)
    {
        constantFree(wcFile->constants[i]);
    }

    for (uint16_t i = 0; i < wcFile->functionCount; i++)
    {
        functionFree(wcFile->functions[i]);
    }
    
    free(wcFile->constants);
    free(wcFile->functions);

    free(wcFile);
}