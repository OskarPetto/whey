#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "Object.h"
#include "Constant.h"

struct Object *booleanConst(struct Constant *constant);
struct Object *booleanAnd(struct Object *boolean1, struct Object *boolean2);
struct Object *booleanOr(struct Object *boolean1, struct Object *boolean2);
struct Object *booleanNot(struct Object *boolean);
struct Object *booleanXor(struct Object *boolean1, struct Object *boolean2);

struct Object *booleanNew(Integer value);
struct Object *booleanLoad(struct Object *boolean);
struct Object *booleanStore(struct Object *boolean);
struct Object *booleanCopy(struct Object *boolean);
Integer booleanEquals(struct Object *boolean1, struct Object *boolean2);
Integer booleanHash(struct Object *boolean);
struct Object *booleanToString(struct Object *boolean);
void booleanMark(struct Object *boolean);
void booleanFree(struct Object *boolean);

#endif