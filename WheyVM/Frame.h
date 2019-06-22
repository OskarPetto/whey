#ifndef FRAME_H
#define FRAME_H

#include "Operand/Operand.h"
#include "WcFile/WcFile.h"

struct Iterator
{
    struct Object *array;
    uint32_t index;
};

struct Frame
{
    struct Function *function;
    struct Operand *locals;
    uint16_t codePointer;

    struct Iterator *iterator;
};

struct Frame *frameNew(struct Function *function);

struct Frame *frameNewWithIterator(struct Function *function, struct Object *array);

struct Operand frameGetLocal(struct Frame *frame, uint8_t localIndex);
void frameSetLocal(struct Frame *frame, uint8_t localIndex, struct Operand local);

void frameMark(struct Frame *frame);

void frameFree(struct Frame *frame);

#endif