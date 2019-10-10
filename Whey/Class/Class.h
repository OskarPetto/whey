#ifndef CLASS_H
#define CLASS_H

#include <stdint.h>
#include "Constant.h"
#include "Method.h"

struct Class
{
    struct ConstantTable *constantTable;

    struct MethodTable *methodTable;
};

struct Class *classNew(char *fileName, uint8_t debug);

void classFree(struct Class *class);

#endif