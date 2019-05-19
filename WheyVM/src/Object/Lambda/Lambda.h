#ifndef LAMBDA_H
#define LAMBDA_H

#include "WheyVM.h"
#include "Object.h"
#include "Function.h"

struct Lambda
{
    struct Array *arguments;
    struct Function *function;
};

struct Object *lambdaConst(struct Function *function);
struct Lambda *lambdaBind(struct Lambda *lambda, struct Object *argument);
void lambdaCall(struct WheyVM *wvm, struct Lambda *lambda);

struct Object *lambdaNew(uint8_t *bytes, uint32_t *byteIndex);
struct Object *lambdaLoad(struct Object *lambda);
struct Object *lambdaStore(struct Object *lambda);
struct Object *lambdaCopy(struct Object *lambda);
Integer lambdaEquals(struct Object *lambda1, struct Object *lambda2);
Integer lambdaHash(struct Object *lambda);
struct Object *lambdaToString(struct Object *lambda);
void lambdaMark(struct Lambda *lambda);
void lambdaFree(struct Lambda *lambda);

#endif