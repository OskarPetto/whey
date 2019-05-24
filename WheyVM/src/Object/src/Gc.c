#include "../Gc.h"
#include "../Array.h"
#include "../Object.h"

#include <assert.h>
#include <stdlib.h>

struct Gc *gcNew()
{
    struct Gc *gc = (struct Gc *)malloc(sizeof(struct Gc));
    assert(gc != NULL);
    struct Object *temp = arrayNew(NULL, GC_INITIAL_SIZE);
    gc->objects = temp->value.array;
    free(temp);
    gc->newCount = 0;
    gc->freeCount = 0;
    return gc;
}

void gcRegisterObject(struct Gc *gc, struct Object *object)
{
    gc->newCount++;
    arrayInsert(gc->objects, gc->objects->objectCount, object);
}

void gcSweep(struct Gc *gc)
{
    struct Object *temp = arrayNew(NULL, GC_INITIAL_SIZE);
    struct Array *newArray = temp->value.array;
    free(temp);

    for (Integer i = 0; i < gc->objects->objectCount; i++)
    {
        if (gc->objects->objects[i]->mark == OBJECT_MARK_TRUE) 
        {
            gc->objects->objects[i]->mark = OBJECT_MARK_FALSE;
            arrayInsert(newArray, newArray->objectCount, gc->objects->objects[i]);
        } 
        else
        {
            gc->freeCount++;
            objectFree(gc->objects->objects[i]);
        }
        
    }

    free(gc->objects);

    gc->objects = newArray;
}

void gcFree(struct Gc *gc)
{
    arrayFree(gc->objects);
    free(gc);
}

