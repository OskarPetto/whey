#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

struct WheyVM;

typedef void (*Instruction)(struct WheyVM *wvm);

void opUnknown(struct WheyVM *wvm);

void opHalt(struct WheyVM *wvm);
void opJump(struct WheyVM *wvm);
void opJumpTrue(struct WheyVM *wvm);
void opJumpFalse(struct WheyVM *wvm);

void opLoad(struct WheyVM *wvm);
void opStore(struct WheyVM *wvm);
void opCall(struct WheyVM *wvm);
void opReturn(struct WheyVM *wvm);
void opConstant(struct WheyVM *wvm);
void opPrint(struct WheyVM *wvm);
void opPop(struct WheyVM *wvm);

void opEqual(struct WheyVM *wvm);
void opNotEqual(struct WheyVM *wvm);
void opGreaterThan(struct WheyVM *wvm);
void opGreaterThanOrEqual(struct WheyVM *wvm);
void opLessThan(struct WheyVM *wvm);
void opLessThanOrEqual(struct WheyVM *wvm);

void opAdd(struct WheyVM *wvm);
void opSubtract(struct WheyVM *wvm);
void opMultiply(struct WheyVM *wvm);
void opDivide(struct WheyVM *wvm);
void opPower(struct WheyVM *wvm);
void opNegate(struct WheyVM *wvm);

void opIntegerToDouble(struct WheyVM *wvm);
void opIntegerIncrement(struct WheyVM *wvm);
void opIntegerDecrement(struct WheyVM *wvm);
void opIntegerModulo(struct WheyVM *wvm);
void opIntegerAnd(struct WheyVM *wvm);
void opIntegerOr(struct WheyVM *wvm);
void opIntegerNot(struct WheyVM *wvm);

void opDoubleToInteger(struct WheyVM *wvm);
void opDoubleCeil(struct WheyVM *wvm);
void opDoubleFloor(struct WheyVM *wvm);

void opObjectNull(struct WheyVM *wvm);
void opObjectCopy(struct WheyVM *wvm);
void opObjectEquals(struct WheyVM *wvm);
void opObjectHash(struct WheyVM *wvm);
void opObjectToString(struct WheyVM *wvm);
void opObjectBox(struct WheyVM *wvm);
void opObjectUnbox(struct WheyVM *wvm);

void opArrayNew(struct WheyVM *wvm);
void opArraySize(struct WheyVM *wvm);
void opArrayGet(struct WheyVM *wvm);
void opArraySet(struct WheyVM *wvm);
void opArrayInsert(struct WheyVM *wvm);
void opArrayInsertAll(struct WheyVM *wvm);
void opArrayRemove(struct WheyVM *wvm);
void opArrayForEach(struct WheyVM *wvm);

void opMapNew(struct WheyVM *wvm);
void opMapSize(struct WheyVM *wvm);
void opMapGet(struct WheyVM *wvm);
void opMapPut(struct WheyVM *wvm);
void opMapPutAll(struct WheyVM *wvm);
void opMapRemove(struct WheyVM *wvm);
void opMapHasKey(struct WheyVM *wvm);
void opMapEntries(struct WheyVM *wvm);

void opPairNew(struct WheyVM *wvm);
void opPairGetFirst(struct WheyVM *wvm);
void opPairGetSecond(struct WheyVM *wvm);
void opPairSetFirst(struct WheyVM *wvm);
void opPairSetSecond(struct WheyVM *wvm);

void opStringLength(struct WheyVM *wvm);
void opStringFromArray(struct WheyVM *wvm);
void opStringToArray(struct WheyVM *wvm);
void opStringCompare(struct WheyVM *wvm);
void opStringConcatenate(struct WheyVM *wvm);
void opStringSubstring(struct WheyVM *wvm);
void opStringIndexOf(struct WheyVM *wvm);
void opStringReplace(struct WheyVM *wvm);
void opStringSplit(struct WheyVM *wvm);

#endif