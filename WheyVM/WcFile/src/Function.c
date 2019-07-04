#include "../Function.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Function *functionNew(uint8_t *bytes, uint32_t *byteIndex)
{
    uint32_t index = *byteIndex;
    uint8_t argumentCount = bytes[index];
    index++;
    uint8_t localsCount = bytes[index];
    index++;
    uint16_t codeSize = bytes[index];
    memcpy(&codeSize, &bytes[index], 2);
    index += 2;

    unsigned char* memory = malloc(sizeof(struct Function) + codeSize * sizeof(unsigned char));
    assert(memory != NULL);
    struct Function *function = (struct Function *)memory;
    function->argumentCount = argumentCount;
    function->localsCount = localsCount;
    function->codeSize = codeSize;
    function->byteCode = memory + sizeof(struct Function);
    
    for (uint16_t i = 0; i < function->codeSize; i++)
    {
        function->byteCode[i] = bytes[index];
        index++;
    }

    *byteIndex = index;

    return function;
}

void functionFree(struct Function *function)
{
    free(function);
}