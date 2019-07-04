#include "../Frame.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Frame *frameNew(struct Function *function)
{
    char* memory = malloc(sizeof(struct Frame) + function->localsCount * sizeof(struct Operand));
    struct Frame *frame = (struct Frame *) memory;
    assert(frame != NULL);

    struct Operand *locals = (struct Operand *) (memory + sizeof(struct Frame));
    assert(locals != NULL);

    memset(locals,0,function->localsCount);
    frame->locals = locals;
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
    return frame;
}


struct Operand frameGetLocal(struct Frame *frame, uint8_t localIndex)
{
    assert(localIndex < frame->function->localsCount);
    return frame->locals[localIndex];
}

void frameSetLocal(struct Frame *frame, uint8_t localIndex, struct Operand operand)
{
    assert(localIndex < frame->function->localsCount);
    frame->locals[localIndex] = operand;
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

    if (frame->iterator != NULL)
    {
        objectMark(frame->iterator->array);
    }
}

void frameFree(struct Frame *frame)
{
    if (frame->iterator != NULL)
    {
        free(frame->iterator);
    }
    free(frame);
}