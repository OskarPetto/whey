#include "../Gc.h"
#include "../Object.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define GC_TOLERANCE 0.01
#define GC_LOAD_FACTOR 0.6

struct Gc *gcNew(uint32_t maxSize)
{
    struct Gc *gc = (struct Gc *)malloc(sizeof(struct Gc));
    assert(gc != NULL);
    gc->head = NULL;
    gc->newCount = 0;
    gc->freeCount = 0;
    gc->maxSize = maxSize;
    gc->treshold =  (uint32_t) (maxSize * GC_LOAD_FACTOR);
    gc->size = 0;
    gc->outOfMemory = 0;
    gc->sizeBeforeLastMarkAndSweep = 0;
    gc->tolerance = (uint32_t) (maxSize * GC_TOLERANCE);
    gc->allocatedSize = 0;
    gc->claimedSize = 0;
    return gc;
}

void gcRegisterObject(struct Gc *gc, struct Object *object)
{
    if (gc == NULL || object == NULL)
        return;

    gc->newCount++;

    struct GcObject *newHead = (struct GcObject *)malloc(sizeof(struct GcObject));
    assert(newHead != NULL);

    newHead->object = object;
    newHead->next = gc->head;

    gc->head = newHead;
}

void gcRequestMemory(struct Gc *gc, uint32_t size)
{
    if (gc == NULL)
        return;

    gc->size += size;
    gc->allocatedSize += size;

    if (gc->size > gc->maxSize)
    {
        gc->outOfMemory = 1;
    }
}

void gcReleaseMemory(struct Gc *gc, uint32_t size)
{
    if (gc == NULL)
        return;

    gc->size -= size;
    gc->claimedSize += size;
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
    struct GcObject *curr = gc->head;
    struct GcObject *prev = NULL;

    while (curr != NULL)
    {
        struct GcObject *next = curr->next;

        if (curr->object == NULL || curr->object->mark == OBJECT_MARK_FALSE)
        {
            if (prev == NULL)
            {
                gc->head = next;
            }
            else
            {
                prev->next = next;
            }

            gc->freeCount++;
            objectFree(gc, curr->object);
            free(curr);
        }
        else
        {
            curr->object->mark = OBJECT_MARK_FALSE;
            prev = curr;
        }

        curr = next;
    }
}

void gcFree(struct Gc *gc)
{
    free(gc);
}
