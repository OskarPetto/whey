#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

struct WheyVM;
struct Frame;

typedef void (*Instruction)(struct WheyVM *wvm, struct Frame *frame);

void opUnknown(struct WheyVM *wvm, struct Frame *frame);

void opHalt(struct WheyVM *wvm, struct Frame *frame);
void opJump(struct WheyVM *wvm, struct Frame *frame);
void opJumpTrue(struct WheyVM *wvm, struct Frame *frame);
void opJumpFalse(struct WheyVM *wvm, struct Frame *frame);

void opLoad(struct WheyVM *wvm, struct Frame *frame);
void opStore(struct WheyVM *wvm, struct Frame *frame);
void opCall(struct WheyVM *wvm, struct Frame *frame);
void opReturn(struct WheyVM *wvm, struct Frame *frame);
void opConstant(struct WheyVM *wvm, struct Frame *frame);
void opPrint(struct WheyVM *wvm, struct Frame *frame);
void opPop(struct WheyVM *wvm, struct Frame *frame);

void opEqual(struct WheyVM *wvm, struct Frame *frame);
void opNotEqual(struct WheyVM *wvm, struct Frame *frame);
void opGreaterThan(struct WheyVM *wvm, struct Frame *frame);
void opGreaterThanOrEqual(struct WheyVM *wvm, struct Frame *frame);
void opLessThan(struct WheyVM *wvm, struct Frame *frame);
void opLessThanOrEqual(struct WheyVM *wvm, struct Frame *frame);

void opAdd(struct WheyVM *wvm, struct Frame *frame);
void opSubtract(struct WheyVM *wvm, struct Frame *frame);
void opMultiply(struct WheyVM *wvm, struct Frame *frame);
void opDivide(struct WheyVM *wvm, struct Frame *frame);
void opPower(struct WheyVM *wvm, struct Frame *frame);
void opNegate(struct WheyVM *wvm, struct Frame *frame);

void opIntegerToDouble(struct WheyVM *wvm, struct Frame *frame);
void opIntegerIncrement(struct WheyVM *wvm, struct Frame *frame);
void opIntegerDecrement(struct WheyVM *wvm, struct Frame *frame);
void opIntegerModulo(struct WheyVM *wvm, struct Frame *frame);
void opIntegerAnd(struct WheyVM *wvm, struct Frame *frame);
void opIntegerOr(struct WheyVM *wvm, struct Frame *frame);
void opIntegerNot(struct WheyVM *wvm, struct Frame *frame);

void opDoubleToInteger(struct WheyVM *wvm, struct Frame *frame);
void opDoubleCeil(struct WheyVM *wvm, struct Frame *frame);
void opDoubleFloor(struct WheyVM *wvm, struct Frame *frame);

void opObjectNull(struct WheyVM *wvm, struct Frame *frame);
void opObjectCopy(struct WheyVM *wvm, struct Frame *frame);
void opObjectEquals(struct WheyVM *wvm, struct Frame *frame);
void opObjectHash(struct WheyVM *wvm, struct Frame *frame);
void opObjectToString(struct WheyVM *wvm, struct Frame *frame);
void opObjectBox(struct WheyVM *wvm, struct Frame *frame);
void opObjectUnbox(struct WheyVM *wvm, struct Frame *frame);

void opArrayNew(struct WheyVM *wvm, struct Frame *frame);
void opArraySize(struct WheyVM *wvm, struct Frame *frame);
void opArrayGet(struct WheyVM *wvm, struct Frame *frame);
void opArraySet(struct WheyVM *wvm, struct Frame *frame);
void opArrayInsert(struct WheyVM *wvm, struct Frame *frame);
void opArrayInsertAll(struct WheyVM *wvm, struct Frame *frame);
void opArrayRemove(struct WheyVM *wvm, struct Frame *frame);
void opArrayForEach(struct WheyVM *wvm, struct Frame *frame);

void opMapNew(struct WheyVM *wvm, struct Frame *frame);
void opMapSize(struct WheyVM *wvm, struct Frame *frame);
void opMapGet(struct WheyVM *wvm, struct Frame *frame);
void opMapPut(struct WheyVM *wvm, struct Frame *frame);
void opMapPutAll(struct WheyVM *wvm, struct Frame *frame);
void opMapRemove(struct WheyVM *wvm, struct Frame *frame);
void opMapHasKey(struct WheyVM *wvm, struct Frame *frame);
void opMapEntries(struct WheyVM *wvm, struct Frame *frame);

void opPairNew(struct WheyVM *wvm, struct Frame *frame);
void opPairGetFirst(struct WheyVM *wvm, struct Frame *frame);
void opPairGetSecond(struct WheyVM *wvm, struct Frame *frame);
void opPairSetFirst(struct WheyVM *wvm, struct Frame *frame);
void opPairSetSecond(struct WheyVM *wvm, struct Frame *frame);

void opStringLength(struct WheyVM *wvm, struct Frame *frame);
void opStringFromArray(struct WheyVM *wvm, struct Frame *frame);
void opStringToArray(struct WheyVM *wvm, struct Frame *frame);
void opStringCompare(struct WheyVM *wvm, struct Frame *frame);
void opStringConcatenate(struct WheyVM *wvm, struct Frame *frame);
void opStringSubstring(struct WheyVM *wvm, struct Frame *frame);
void opStringIndexOf(struct WheyVM *wvm, struct Frame *frame);
void opStringReplace(struct WheyVM *wvm, struct Frame *frame);
void opStringSplit(struct WheyVM *wvm, struct Frame *frame);

#endif