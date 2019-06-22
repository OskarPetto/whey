#include "../Function.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Function *functionNew(uint8_t *bytes, uint32_t *byteIndex)
{
    struct Function *function = (struct Function *)malloc(sizeof(struct Function));
    assert(function != NULL);
    function->localsCount = bytes[*byteIndex];
    (*byteIndex)++;
    memcpy(&(function->codeSize), &bytes[*byteIndex], 2);
    (*byteIndex) += 2;
    function->byteCode = (unsigned char *)malloc(function->codeSize * sizeof(unsigned char));
    assert(function->byteCode != NULL);
    for (uint16_t i = 0; i < function->codeSize; i++)
    {
        function->byteCode[i] = bytes[*byteIndex];
        (*byteIndex)++;
    }

    return function;
}

void functionFree(struct Function *function)
{
    free(function->byteCode);
    free(function);
}