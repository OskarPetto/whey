#ifndef LAMBDA_H
#define LAMBDA_H

#include "Array.h"
#include "Object.h"

struct Lambda
{

    uint16_t functionIndex;

    struct Array *localVariables;

    uint8_t *byteCode;
    uint16_t codeSize;

};


#endif