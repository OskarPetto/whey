#ifndef ARRAY_H
#define ARRAY_H

#include <stdint.h>

struct Constant;

struct Array
{
    uint8_t type;
    uint16_t length;
    struct Constant *elements;
};

struct Array *arrayFromBytes(uint8_t *bytes, uint32_t *index);

void freeArray(struct Array *array);

#endif