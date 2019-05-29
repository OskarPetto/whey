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
    memcpy(&(function->opCodeCount), bytes + *byteIndex, 2);
    (*byteIndex) += 2;
    function->opCodes = (unsigned char *)malloc(function->opCodeCount * sizeof(unsigned char));
    assert(function->opCodes != NULL);
    for (uint16_t i = 0; i < function->opCodeCount; i++)
    {
        function->opCodes[i] = bytes[*byteIndex];
        (*byteIndex)++;
    }

    return function;
}

void functionFree(struct Function *function)
{
    free(function->opCodes);
    free(function);
}