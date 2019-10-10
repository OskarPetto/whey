#ifndef RUNNER_H
#define RUNNER_H

#include "Class/Class.h"
#include "Object/Object.h"
#include "Stack/Stack.h"

/**
 *  Should always exit 
 */
void run(struct Class *class, struct Gc *gc, struct Stack *stack, uint8_t debug);

#endif