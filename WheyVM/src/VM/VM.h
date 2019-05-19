#ifndef WHEYVM_H
#define WHEYVM_H

#include <stdint.h>
#include "Object.h"
#include "Lambda.h"
#include "GC.h"
#include "ConstantPool.h"
#include "OpCode.h"

#define WHEYVM_VERSION_MAJOR "0"
#define WHEYVM_VERSION_MINOR "1"

#define WHEYVM_VERSION "Whey " WHEY_VERSION_MAJOR "." WHEY_VERSION_MINOR

#define WHEYVM_OPERAND_STACK_SIZE 255
#define WHEYVM_LAMBDA_STACK_SIZE 255

typedef void (*Instruction)(struct WheyVM *wvm);

struct WheyVM 
{
    struct Object operandStack[WHEYVM_OPERAND_STACK_SIZE];

    uint8_t operandStackPointer;

    struct Lambda lambdaStack[WHEYVM_LAMBDA_STACK_SIZE];

    uint8_t lambdaStackPointer;

    struct GC gc;

    struct ConstantPool constantPool;

    Instruction dispatchTable[256];

};

void opOLoad(struct WheyVM *wvm);
void opOStore(struct WheyVM *wvm);
void opOCopy(struct WheyVM *wvm);
void opOEquals(struct WheyVM *wvm);
void opOHash(struct WheyVM *wvm);
void opOToString(struct WheyVM *wvm);

void opBConst(struct WheyVM *wvm);
void opBAnd(struct WheyVM *wvm);
void opBOr(struct WheyVM *wvm);
void opBNot(struct WheyVM *wvm);
void opBXor(struct WheyVM *wvm);

void opIConst(struct WheyVM *wvm);
void opIAdd(struct WheyVM *wvm);
void opISub(struct WheyVM *wvm);
void opIMul(struct WheyVM *wvm);
void opIDiv(struct WheyVM *wvm);
void opINeg(struct WheyVM *wvm);
void opIInc(struct WheyVM *wvm);
void opIDec(struct WheyVM *wvm);
void opIMod(struct WheyVM *wvm);
void opIPow(struct WheyVM *wvm);
void opIGt(struct WheyVM *wvm);
void opIGte(struct WheyVM *wvm);
void opILt(struct WheyVM *wvm);
void opILte(struct WheyVM *wvm);

void opFConst(struct WheyVM *wvm);
void opFAdd(struct WheyVM *wvm);
void opFSub(struct WheyVM *wvm);
void opFMul(struct WheyVM *wvm);
void opFDiv(struct WheyVM *wvm);
void opFNeg(struct WheyVM *wvm);
void opFGt(struct WheyVM *wvm);
void opFGte(struct WheyVM *wvm);
void opFLt(struct WheyVM *wvm);
void opFLte(struct WheyVM *wvm);

void opLConst(struct WheyVM *wvm);
void opLApply(struct WheyVM *wvm);
void opLCall(struct WheyVM *wvm);

void opANew(struct WheyVM *wvm);
void opAConst(struct WheyVM *wvm);
void opASize(struct WheyVM *wvm);
void opAGet(struct WheyVM *wvmt);
void opASet(struct WheyVM *wvm);
void opAInsert(struct WheyVM *wvm);
void opAInsertAll(struct WheyVM *wvm);
void opARemove(struct WheyVM *wvm);
void opAForEach(struct WheyVM *wvm);

void opMNew(struct WheyVM *wvm);
void opMSize(struct WheyVM *wvm);
void opMGet(struct WheyVM *wvm);
void opMPut(struct WheyVM *wvm);
void opMPutAll(struct WheyVM *wvm);
void opMRemove(struct WheyVM *wvm);
void opMHasKey(struct WheyVM *wvm);
void opMEntries(struct WheyVM *wvm);

void opPNew(struct WheyVM *wvm);
void opPGetFst(struct WheyVM *wvm);
void opPGetSnd(struct WheyVM *wvm);
void opPSetFst(struct WheyVM *wvm);
void opPSetSnd(struct WheyVM *wvm);

#endif