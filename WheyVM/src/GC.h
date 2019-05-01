#ifndef GC_H
#define GC_H

#include <stdint.h>
#include <stdlib.h>
#include "Object.h"

#define GCOBJECT_MARK                    0x01
#define GCOBJECT_ROOT                    0x02
#define GCOBJECT_LEAF                    0x04

// https://github.com/orangeduck/tgc

struct GCObject;

struct GCObject
{
    uint8_t flags;
    size_t size, hash;
    struct Object *object;
};

struct GC
{
    struct Object *bottom;
    uintptr_t minPointer, maxPointer;
    struct GCObject *items, *frees;
    double loadFactor, sweepFactor;
    size_t itemCount, slotCount, mitems, nFrees;
};

void gcStart(struct GC *gc, void *stk);
void gcStop(struct GC *gc, void *stk);
void gcRun(struct GC *gc, void *stk);

void gcAdd(struct GC *gc, struct Object *object);


#endif