#include "../Whey.h"
#include "../Runner.h"
#include "../Class/Class.h"
#include "../Stack/Stack.h"
#include "../Object/Gc.h"
#include "../Types.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

static struct Class *class;
static struct Gc *gc;
static struct Stack *stack;

void cleanup(void)
{
    if (returnCode == ERRCODE_RUNTIME)
    {
        stackPrint(stack);
    }

    gcSweep(gc);

    classFree(class);

    stackFree(stack);

    gcFree(gc);
}

void wheyRun(char *sourceFilename, uint32_t callStackSize, uint32_t gcMemorySize, uint8_t debug)
{
    atexit(&cleanup);

    gc = gcNew(gcMemorySize, debug);
    stack = stackNew(callStackSize);
    class = classNew(sourceFilename, debug);
    run(class, gc, stack, debug);
}
