#ifndef CONSTANT_POOL_H
#define CONSTANT_POOL_H

#include "Constant.h"

struct ConstantPool
{
    struct Constant **constants;
    uint16_t constantCount;
};

struct ConstantPool *constantPoolNew(uint8_t *bytes, uint32_t fileSize);

struct Constant *constantPoolGet(uint16_t constantPoolIndex);

void constantPoolFree(struct ConstantPool *constantPool);

#endif