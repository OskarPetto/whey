#ifndef STRING_H
#define STRING_H

#include <stdlib.h>

struct String
{
    uint16_t characterCount;
    char *characters;
};

struct String *stringNew(uint8_t *bytes, uint32_t *byteIndex);

void stringFree(struct String *string);

#endif