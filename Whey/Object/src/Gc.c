#include "../Gc.h"
#include "../Object.h"
#include "../Array.h"
#include "../Double.h"
#include "../Integer.h"
#include "../Map.h"
#include "../Pair.h"
#include "../String.h"

#include <stdlib.h>
#include <stdio.h>

#define GC_TOLERANCE 0.01
#define GC_LOAD_FACTOR 0.5

#define GC_MALLOC_CHECK(memory) NOT_NULL_CHECK(memory, ERRCODE_INTERNAL, "Cannot create Gc\n")
#define GC_OBJECT_CREATE_CHECK(memory, type) NOT_NULL_CHECK(memory, ERRCODE_INTERNAL, "Cannot create %s\n", objectTypeStrings[type])
#define GC_OBJECT_MALLOC_CHECK(memory, object) NOT_NULL_CHECK(memory, ERRCODE_INTERNAL, "Cannot change memory for %s (%p)\n", objectTypeStrings[object->type], object)

#define GC_MALLOC_INFO(object, size) printf("Malloc %u bytes for %s (%p)\n", size, objectTypeStrings[object->type], object)
#define GC_REALLOC_INFO(object, old, new) printf("Realloc %u to %u bytes for %s (%p)\n", old, new, objectTypeStrings[object->type], object)
#define GC_FREE_INFO(object, size) printf("Free %u bytes for %s (%p)\n", size, objectTypeStrings[object->type], object)

#define GC_OBJECT_NEW_INFO(object) printf("New %s (%p)\n", objectTypeStrings[object->type], object) 
#define GC_OBJECT_FREE_INFO(object) printf("Remove %s (%p)\n", objectTypeStrings[object->type], object) 

#define GC_SWEEP_INFO(collectedObjects, totalObjects, collectedSize, totalSize) printf("Garbage collected %u/%u objects with %u/%u bytes\n", collectedObjects, totalObjects, collectedSize, totalSize)

#define GC_OUT_OF_MEMORY_CHECK(gc, newSize) ERROR_CHECK(!(gc->debug & GC_DEBUG_OVERFLOW) && newSize > gc->maxSize, ERRCODE_RUNTIME, "Out of memory with %u/%u bytes set memory size with the 'm' option\n", newSize, gc->maxSize)

#define GC_REMOVE_SIZE(gc, size)       \
    do                              \
    {                               \
        gc->size -= size;           \
    } while (0)

#define GC_ADD_SIZE(gc, size)       \
    do                              \
    {                               \
        uint32_t checkSize = gc->size + size;           \
        GC_OUT_OF_MEMORY_CHECK(gc, checkSize);  \
        gc->size = checkSize;\
    } while (0)

#define GC_CHANGE_SIZE(gc, oldSize, newSize) \
    do                                       \
    {                                        \
        uint32_t checkSize = gc->size + (newSize - oldSize);     \
        GC_OUT_OF_MEMORY_CHECK(gc, checkSize);  \
        gc->size = checkSize;\
    } while (0)

#define GC_MALLOC(gc, size)

struct Gc *gcNew(uint32_t maxSize, uint8_t debug)
{
    struct Gc *gc = (struct Gc *)malloc(sizeof(struct Gc));
    GC_MALLOC_CHECK(gc);
    gc->head = NULL;
    gc->objectCount = 0;
    gc->maxSize = maxSize;
    gc->treshold = (uint32_t)(maxSize * GC_LOAD_FACTOR);
    gc->size = 0;
    gc->sizeBeforeLastMarkAndSweep = 0;
    gc->tolerance = (uint32_t)(maxSize * GC_TOLERANCE);
    gc->debug = debug;
    return gc;
}

struct Object *gcObjectNew(struct Gc *gc, uint8_t type, uint32_t extraSize)
{
    uint32_t size = sizeof(struct Object) + extraSize;
    
    GC_ADD_SIZE(gc, size);

    void *memory = malloc(size);
    GC_OBJECT_CREATE_CHECK(memory, type);

    ++gc->objectCount;
    struct Object *object = memory;

    object->next = gc->head;
    gc->head = object;
    object->type = type;    // mark is false

    object->value.subObject = memory + sizeof(struct Object); 

    if (gc->debug & GC_DEBUG_OBJECT)
    {
        GC_OBJECT_NEW_INFO(object);
    }

    if (gc->debug & GC_DEBUG_MEMORY)
    {
        GC_MALLOC_INFO(object, size);
    }

    return object;
}

void *gcMemoryMalloc(struct Gc *gc, struct Object *object, uint32_t size)
{
    GC_ADD_SIZE(gc, size);

    void *memory = malloc(size);
    GC_OBJECT_MALLOC_CHECK(memory, object);

    if (gc->debug & GC_DEBUG_MEMORY)
    {
        GC_MALLOC_INFO(object, size);
    }

    return memory;
}

void *gcMemoryRealloc(struct Gc *gc, struct Object *object, void *memory, uint32_t oldSize, uint32_t newSize)
{
    GC_CHANGE_SIZE(gc, oldSize, newSize);

    void *newMemory = realloc(memory, newSize);
    GC_OBJECT_MALLOC_CHECK(memory, object);
    
    if (gc->debug & GC_DEBUG_MEMORY)
    {
        GC_REALLOC_INFO(object, oldSize, newSize);
    }

    return newMemory;
}

void gcMemoryFree(struct Gc *gc, struct Object *object, void *memory, uint32_t size)
{
    GC_REMOVE_SIZE(gc, size);

    free(memory);
    
    if (gc->debug & GC_DEBUG_MEMORY)
    {
        GC_FREE_INFO(object, size);
    }
}

void gcObjectFree(struct Gc *gc, struct Object *object, uint32_t size)
{
    GC_REMOVE_SIZE(gc, size);

    --gc->objectCount;

    if (gc->debug & GC_DEBUG_MEMORY)
    {
        GC_FREE_INFO(object, size);
    }
    
    if (gc->debug & GC_DEBUG_OBJECT)
    {
        GC_OBJECT_FREE_INFO(object);
    }

    free(object);
}


uint8_t gcShouldMarkAndSweep(struct Gc *gc)
{
    if (gc->size > gc->treshold)
    {
        if (gc->sizeBeforeLastMarkAndSweep > gc->size + gc->tolerance || gc->sizeBeforeLastMarkAndSweep < gc->size - gc->tolerance)
        {
            gc->sizeBeforeLastMarkAndSweep = gc->size;
            return 1;
        }

        return 0;
    }

    return 0;
}

void gcSweep(struct Gc *gc)
{
    struct Object *curr = gc->head;

    if (curr == NULL)
        return;

    uint32_t objectCountBeforeSweep = gc->objectCount;
    uint32_t sizeBeforeSweep = gc->size;

    struct Object *prev = NULL;

    while (curr != NULL)
    {
        struct Object *next = curr->next;

        if (curr->type & OBJECT_MARK)
        {
            curr->type &= ~OBJECT_MARK;
            prev = curr;
        }
        else
        {
            if (prev == NULL)
            {
                gc->head = next;
            }
            else
            {
                prev->next = next;
            }

            objectFree(gc, curr);
        }

        curr = next;
    }

    if (gc->debug & GC_DEBUG_SWEEP) 
    {
        uint32_t collectedObjectCount = objectCountBeforeSweep - gc->objectCount;
        uint32_t collectedSize = sizeBeforeSweep - gc->size;
        GC_SWEEP_INFO(collectedObjectCount, objectCountBeforeSweep, collectedSize, sizeBeforeSweep);    
    }
}

void gcFree(struct Gc *gc)
{
    free(gc);
}
