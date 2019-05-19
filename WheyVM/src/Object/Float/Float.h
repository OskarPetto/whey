#ifndef FLOAT_H
#define FLOAT_H

#include "Object.h"
#include "Constant.h"

struct Object *floatConst(struct Constant *constant);
struct Object *floatAdd(struct Object *float1, struct Object *float2);
struct Object *floatSub(struct Object *float1, struct Object *float2);
struct Object *floatMul(struct Object *float1, struct Object *float2);
struct Object *floatDiv(struct Object *float1, struct Object *float2);
struct Object *floatNeg(struct Object *float1);
struct Object *floatGt(struct Object *float1, struct Object *float2);
struct Object *floatGte(struct Object *float1, struct Object *float2);
struct Object *floatLt(struct Object *float1, struct Object *float2);
struct Object *floatLte(struct Object *float1, struct Object *float2);

struct Object *floatNew(Float value);
struct Object *floatLoad(struct Object *float1);
struct Object *floatStore(struct Object *float1);
struct Object *floatCopy(struct Object *float1);
Integer floatEquals(struct Object *float1, struct Object *float2);
Integer floatHash(struct Object *float1);
struct Object *floatToString(struct Object *float1);
void floatMark(struct Object *float1);
void floatFree(struct Object *float1);

#endif