#ifndef CLOSURE_H
#define CLOSURE_H

#include "Object.h"
#include "Function.h"
#include <stdlib.h>
#include <stdint.h>

struct Closure 
{
    struct Operand *locals;

    uint8_t *code;

    uint32_t programCounter;

};

#endif