#include "../Class.h"
#include "../../Types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Class *classNew(char *fileName, uint8_t debug)
{
    FILE *file = fopen(fileName, "rb");
    NOT_NULL_CHECK(file, ERRCODE_CLASS, "Cannot open %s\n", fileName);

    struct Class *class = malloc(sizeof(struct Class));

    fseek(file, 0, SEEK_END);

    uint32_t byteCount = (uint32_t) ftell(file);

    rewind(file);

    unsigned char *buffer = malloc(byteCount);
    NOT_NULL_CHECK(buffer, ERRCODE_CLASS, "Create buffer with size %u failed\n", byteCount);

    DEBUG_PRINT(debug, "Reading %s with size %u\n", fileName, byteCount);

    size_t readCount = fread(buffer, 1, byteCount, file);

    fclose(file);

    if (readCount < byteCount)
    {
        free(buffer);
        free(class);
        EXIT(ERRCODE_CLASS, "Cannot read %s\n", fileName);
    }

    uint32_t checkSum;

    memcpy(&checkSum, buffer, 4);

    if(checkSum != 4272938682)
    {
        free(buffer);
        free(class);
        EXIT(ERRCODE_CLASS, "Invalid checksum\n");
    }

    uint32_t byteIndex = 4;

    class->constantTable = constantTableNew(fileName, buffer, &byteIndex, byteCount, debug);

    class->methodTable = methodTableNew(fileName, buffer, &byteIndex, byteCount, debug);

    free(buffer);

    ASSERT(byteIndex == byteCount, ERRCODE_CLASS, "Not completely read\n");

    return class;
}

void classFree(struct Class *class)
{
    if (class == NULL)
        return;
        
    constantTableFree(class->constantTable);

    methodTableFree(class->methodTable);

    free(class);
}