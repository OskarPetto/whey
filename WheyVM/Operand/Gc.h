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
    uint64_t newCount;
    uint64_t freeCount;
    uint32_t size;
    uint32_t maxSize;
    uint32_t treshold;
    uint8_t outOfMemory;
    uint32_t sizeBeforeLastMarkAndSweep;
    uint32_t tolerance;
    uint64_t allocatedSize;
    uint64_t claimedSize;
};

struct Gc *gcNew(uint32_t maxSize);
void gcRegisterObject(struct Gc *gc, struct Object *object);
void gcRequestMemory(struct Gc *gc, uint32_t size);
void gcReleaseMemory(struct Gc *gc, uint32_t size);
uint8_t gcShouldMarkAndSweep(struct Gc *gc);
void gcSweep(struct Gc *gc);
void gcFree(struct Gc *gc);

#endif