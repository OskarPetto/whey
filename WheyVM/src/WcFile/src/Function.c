#include "../Function.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Function *functionNew(uint8_t *bytes, uint32_t *byteIndex)
{
    struct Function *function = (struct Function *)malloc(sizeof(struct Function));
    assert(function != NULL);
    function->argumentCount = bytes[*byteIndex];
    (*byteIndex)++;
    memcpy(&(function->byteCount), &bytes[*byteIndex], 2);
    (*byteIndex) += 2;
    function->bytes = (unsigned char *)malloc(function->byteCount * sizeof(unsigned char));
    assert(function->bytes != NULL);
    for (uint16_t i = 0; i < function->byteCount; i++)
    {
        function->bytes[i] = bytes[*byteIndex];
        (*byteIndex)++;
    }

    return function;
}

void functionFree(struct Function *function)
{
    free(function->bytes);
    free(function);
}