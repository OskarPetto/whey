#include "../Gc.h"
#include "../Object.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct Gc *gcNew(uint32_t maxSize, double loadFactor, uint16_t coolDown)
{
    struct Gc *gc = (struct Gc *)malloc(sizeof(struct Gc));
    assert(gc != NULL);
    gc->head = NULL;
    gc->newCount = 0;
    gc->freeCount = 0;
    gc->maxSize = maxSize;
    gc->size = 0;
    gc->loadFactor = loadFactor;
    gc->outOfMemory = 0;
    gc->coolDown = coolDown;
    gc->timeSinceLastMarkAndSweep = coolDown;
    gc->claimedSize = 0;
    return gc;
}

void gcRegisterObject(struct Gc *gc, struct Object *object)
{
    if (gc == NULL)
        return;

    gc->newCount++;

    struct GcObject *newHead = (struct GcObject *)malloc(sizeof(struct GcObject));
    assert(newHead != NULL);

    newHead->object = object;

    if (gc->head != NULL)
    {
        newHead->next = gc->head;
    }
    else
    {
        newHead->next = NULL;
    }

    gc->head = newHead;
}

void gcRequestMemory(struct Gc *gc, uint32_t size)
{
    if (gc == NULL)
        return;

    gc->size += size;

    if (gc->size > gc->maxSize)
    {
        fprintf(stderr, "Out of memory with %d/%d after allocating %d bytes.\n", gc->size, gc->maxSize, size);
        gc->outOfMemory = 1;
    }
}

void gcReleaseMemory(struct Gc *gc, uint32_t size)
{
    if (gc == NULL)
        return;

    gc->size -= size;
}

uint8_t gcShouldMarkAndSweep(struct Gc *gc)
{
    if (gc->size >= (uint32_t)(gc->maxSize * gc->loadFactor))
    {
        if (gc->timeSinceLastMarkAndSweep == gc->coolDown)
        {

            gc->timeSinceLastMarkAndSweep = 0;
            return 1;
        }
        else
        {
            gc->timeSinceLastMarkAndSweep++;
            return 0;
        }
    }

    return 0;
}

void gcSweep(struct Gc *gc)
{
    uint32_t oldSize = gc->size;

    struct GcObject *curr = gc->head;
    struct GcObject *prev = NULL;

    while (curr != NULL)
    {
        struct GcObject *next = curr->next;

        if (curr->object->mark == OBJECT_MARK_TRUE)
        {
            curr->object->mark = OBJECT_MARK_FALSE;
            prev = curr;
        }
        else
        {
            gc->freeCount++;
            objectFree(gc, curr->object);
            free(curr);

            if (prev == NULL)
            {
                gc->head = next;
            }
            else
            {
                prev->next = next;
            }
        }

        curr = next;
    }

    gc->claimedSize += (oldSize - gc->size);
}

void gcFree(struct Gc *gc)
{
    struct GcObject *curr = gc->head;

    while (curr != NULL)
    {
        objectFree(gc, curr->object);
        struct GcObject *temp = curr->next;
        free(curr);
        curr = temp;
    }

    free(gc);
}
