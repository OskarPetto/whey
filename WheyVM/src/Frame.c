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


void frameGetLocal(struct Frame *frame, uint8_t localIndex, struct Operand *result)
{
    assert(localIndex < frame->function->localsCount);
    memcpy(result,&frame->locals[localIndex],sizeof(struct Operand));
}

void frameSetLocal(struct Frame *frame, uint8_t localIndex, struct Operand* local)
{
    assert(localIndex < frame->function->localsCount);
    memcpy(&frame->locals[localIndex],local,sizeof(struct Operand));
}

uint32_t frameMark(struct Frame *frame)
{
    uint32_t count = 0;

    for (uint8_t i = 0; i < frame->function->localsCount; i++)
    {
        struct Operand current = frame->locals[i];

        if (current.type == OPERAND_TYPE_REFERENCE)
        { 
            count += objectMark(current.value.reference);
        }

    }

    if (frame->iterator != NULL)
    {
        count += objectMark(frame->iterator->array);
    }

    return count;
}

void frameFree(struct Frame *frame)
{
    if (frame->iterator != NULL)
    {
        free(frame->iterator);
    }
    free(frame);
}