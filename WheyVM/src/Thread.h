#ifndef THREAD_H
#define THREAD_H

#include "Whey.h"
#include "Object.h"

struct Thread 
{
    struct Object operandStack[WHEY_SIZE_OPERAND_STACK];
};

#endif