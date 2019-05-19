#ifndef INTEGER_H
#define INTEGER_H

#include "Object.h"
#include "Constant.h"

struct Object *integerConst(struct Constant *constant);
struct Object *integerAdd(struct Object *integer1, struct Object *integer2);
struct Object *integerSub(struct Object *integer1, struct Object *integer2);
struct Object *integerMul(struct Object *integer1, struct Object *integer2);
struct Object *integerDiv(struct Object *integer1, struct Object *integer2);
struct Object *integerNeg(struct Object *integer);
struct Object *integerInc(struct Object *integer);
struct Object *integerDec(struct Object *integer);
struct Object *integerMod(struct Object *integer1, struct Object *integer2);
struct Object *integerPow(struct Object *integer1, struct Object *integer2);
struct Object *integerGt(struct Object *integer1, struct Object *integer2);
struct Object *integerGte(struct Object *integer1, struct Object *integer2);
struct Object *integerLt(struct Object *integer1, struct Object *integer2);
struct Object *integerLte(struct Object *integer1, struct Object *integer2);


struct Object *integerNew(Integer value);
struct Object *integerLoad(struct Object *integer);
struct Object *integerStore(struct Object *integer);
struct Object *integerCopy(struct Object *integer);
Integer integerEquals(struct Object *integer1, struct Object *integer2);
Integer integerHash(struct Object *integer);
struct Object *integerToString(struct Object *integer);
void integerMark(struct Object *integer);
void integerFree(struct Object *integer);

#endif