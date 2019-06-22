#include "../Frame.h"

#include <assert.h>
#include <stdlib.h>

struct Frame *frameNew(struct Function *function)
{
    struct Frame *frame = (struct Frame *) malloc(sizeof(struct Frame));
    assert(frame != NULL);
    frame->locals = (struct Operand *) calloc(function->localsCount, sizeof(struct Operand));
    assert(frame->locals != NULL);
    frame->function = function;
    frame->codePointer = 0;
    frame->iterator = NULL;
    return frame;
}

struct Frame *frameNewWithIterator(struct Function *function, struct Object *array)
{
    struct Frame *frame = frameNew(function);
    frame->iterator = (struct Iterator *)malloc(sizeof(struct Iterator));
    assert(frame->iterator != NULL);
    frame->iterator->array = array;
    frame->iterator->index = 0;
    frame->locals[0].type = OPERAND_TYPE_REFERENCE;
    frame->locals[0].value.reference = array->value.array->objects[0];
}


struct Operand frameGetLocal(struct Frame *frame, uint8_t localIndex)
{
    assert(localIndex < frame->function->localsCount);
    return frame->locals[localIndex];
}

void frameSetLocal(struct Frame *frame, uint8_t localIndex, struct Operand local)
{
    assert(localIndex < frame->function->localsCount);
    frame->locals[localIndex] = local;
}

void frameMark(struct Frame *frame)
{
    for (uint8_t i = 0; i < frame->function->localsCount; i++)
    {
        struct Operand current = frame->locals[i];

        if (current.type == OPERAND_TYPE_REFERENCE)
        {
            objectMark(current.value.reference);
        }
    }
    
}

void frameFree(struct Frame *frame)
{
    if (frame->iterator != NULL)
    {
        free(frame->iterator);
    }
    free(frame->locals);
    free(frame);
}