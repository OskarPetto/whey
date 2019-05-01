#ifndef UTF8_H
#define UTF8_H

#include <stdint.h>

struct Utf8
{
    char *bytes;
    uint16_t byteCount;
    uint16_t characterCount;

    uint64_t hash;
};

struct Utf8 *utf8FromBytes(uint8_t *bytes, uint32_t *index);

void freeUtf8(struct Utf8 *utf8);


#endif