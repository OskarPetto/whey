#ifndef GC_H
#define GC_H

#include "Types.h"

struct Object;

struct GcObject;

struct GcObject
{
    struct Object *object;
    struct GcObject *next;
};

struct Gc
{
    struct GcObject *head;
    Integer newCount;
    Integer freeCount;
};

struct Gc *gcNew();
void gcRegisterObject(struct Gc *gc, struct Object *object);
void gcSweep(struct Gc *gc);
void gcFree(struct Gc *gc);

#endif