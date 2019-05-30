#include "../Gc.h"
#include "../Object.h"

#include <assert.h>
#include <stdlib.h>

struct Gc *gcNew()
{
    struct Gc *gc = (struct Gc *)malloc(sizeof(struct Gc));
    assert(gc != NULL);
    gc->head = NULL;
    gc->newCount = 0;
    gc->freeCount = 0;
    return gc;
}

void gcRegisterObject(struct Gc *gc, struct Object *object)
{
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

void gcSweep(struct Gc *gc)
{
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
            objectFree(curr->object);
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

}

void gcFree(struct Gc *gc)
{
    struct GcObject *curr = gc->head;

    while (curr != NULL)
    {
        objectFree(curr->object);
        struct GcObject *temp = curr->next;
        free(curr);
        curr = temp;
    }

    free(gc);
}
