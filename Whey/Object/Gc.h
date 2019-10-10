#ifndef GC_H
#define GC_H

#include "../Types.h"

#define GC_DEBUG_SWEEP     1
#define GC_DEBUG_OBJECT    2
#define GC_DEBUG_MEMORY    4
#define GC_DEBUG_OVERFLOW  8

struct Object;

struct Gc
{
    struct Object *head;
    uint32_t objectCount;
    uint32_t size;
    uint32_t maxSize;
    uint32_t treshold;
    uint32_t sizeBeforeLastMarkAndSweep;
    uint32_t tolerance;
    uint8_t debug;
};

struct Gc *gcNew(uint32_t maxSize, uint8_t debug);
struct Object *gcObjectNew(struct Gc *gc, uint8_t type, uint32_t extraSize);
void gcObjectFree(struct Gc *gc, struct Object *object, uint32_t size);
void *gcMemoryMalloc(struct Gc *gc, struct Object *forObject, uint32_t size);
void *gcMemoryRealloc(struct Gc *gc, struct Object *forObject, void *memory, uint32_t oldSize, uint32_t newSize);
void gcMemoryFree(struct Gc *gc, struct Object *forObject, void *memory, uint32_t size);
uint8_t gcShouldMarkAndSweep(struct Gc *gc);
void gcSweep(struct Gc *gc);
void gcFree(struct Gc *gc);

#endif