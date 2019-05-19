#ifndef GC_H
#define GC_H

#include "Object.h"

#define GC_LOAD_FACTOR 0.9
#define GC_SWEEP_FACTOR 0.5

struct GC
{
    struct Array *objects;
}

void gcRegisterObject(struct Object *object);
void gcSweep();
void gcStop();

#endif