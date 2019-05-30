#include "../Constant.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Constant *constantNew(uint8_t *bytes, uint32_t *byteIndex)
{
    struct Constant *constant = (struct Constant *)malloc(sizeof(struct Constant));
    assert(constant != NULL);
    constant->type = bytes[*byteIndex];
    (*byteIndex)++;

    switch (constant->type)
    {
    case CONSTANT_TYPE_INTEGER:
        memcpy(&(constant->value.integerConstant), &bytes[*byteIndex], 4);
        (*byteIndex) += 4;
        break;

    case CONSTANT_TYPE_DOUBLE:
        memcpy(&(constant->value.doubleConstant), &bytes[*byteIndex], 8);
        (*byteIndex) += 8;
        break;

    case CONSTANT_TYPE_STRING:
        constant->value.stringConstant = (struct StringConstant *)malloc(sizeof(struct StringConstant));
        assert(constant->value.stringConstant != NULL);
        memcpy(&(constant->value.stringConstant->characterCount), &bytes[*byteIndex], 2);
        (*byteIndex) += 2;
        constant->value.stringConstant->characters = (char *)malloc(constant->value.stringConstant->characterCount * sizeof(char));
        assert(constant->value.stringConstant->characters != NULL);
        for (uint16_t i = 0; i < constant->value.stringConstant->characterCount; i++)
        {
            constant->value.stringConstant->characters[i] = bytes[*byteIndex];
            (*byteIndex)++;
        }
        break;
    }

    return constant;
}

void constantFree(struct Constant *constant)
{
    if (constant->type == CONSTANT_TYPE_STRING)
    {
        free(constant->value.stringConstant->characters);
        free(constant->value.stringConstant);
    }

    free(constant);
}