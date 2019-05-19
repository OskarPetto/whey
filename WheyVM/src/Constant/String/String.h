#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include "Whey.h"

typedef uint32_t Character; 

struct String
{
    size_t characterCount;
    Character *characters;
};

struct String *stringNew(uint8_t *bytes, uint32_t *byteIndex);

void stringFree(struct String *string);

#endif