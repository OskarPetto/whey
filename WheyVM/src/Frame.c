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
    return frame;
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
    free(frame->locals);
    free(frame);
}