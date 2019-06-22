#ifndef FRAME_H
#define FRAME_H

#include "Operand/Operand.h"
#include "WcFile/WcFile.h"

struct Frame
{
    struct Function *function;
    struct Operand *locals;
    uint16_t codePointer;
};

struct Frame *frameNew(struct Function *function);

struct Operand frameGetLocal(struct Frame *frame, uint8_t localIndex);
void frameSetLocal(struct Frame *frame, uint8_t localIndex, struct Operand local);

void frameMark(struct Frame *frame);

void frameFree(struct Frame *frame);

#endif