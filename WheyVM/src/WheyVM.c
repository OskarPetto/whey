#include "../WheyVM.h"
#include "../InstructionSet.h"

#include <assert.h>
#include <stdlib.h>

static void wvmExecute(struct WheyVM *wvm)
{
    struct Function *mainFunction = wcFileGetFunction(wvm->wcFile, 0);

    wvm->callStack[++wvm->callStackPointer] = frameNew(mainFunction);

    while (wvm->callStack[wvm->callStackPointer]->codePointer < wvm->callStack[wvm->callStackPointer]->function->codeSize)
    {
        if (wvm->state & WHEYVM_STATE_STOPPED)
            break;

        unsigned char instruction = wvm->callStack[wvm->callStackPointer]->function->byteCode[wvm->callStack[wvm->callStackPointer]->codePointer];
        
        instructionSet[instruction](wvm);

    }

}

void wvmRun(struct WcFile *wcFile, uint16_t callStackSize, uint16_t operandStackSize, uint64_t gcMemorySize, double gcLoadFactor, uint8_t state)
{
    struct WheyVM *wvm = (struct WheyVM *)malloc(sizeof(struct WheyVM));
    assert(wvm != NULL);
    wvm->callStack = (struct Frame **)malloc(callStackSize * sizeof(struct Frame *));
    assert(wvm->callStack != NULL);    
    wvm->callStackPointer = -1;

    wvm->operandStack = (struct Operand *)malloc(operandStackSize * sizeof(struct Operand));
    assert(wvm->operandStack != NULL);
    wvm->operandStackPointer = -1;

    wvm->gc = gcNew(gcMemorySize, gcLoadFactor);

    wvm->wcFile = wcFile;
    wvm->state = state;

    wvmExecute(wvm);

    for (int32_t i = 0; i <= wvm->callStackPointer; i++)
    {
        frameFree(wvm->callStack[i]);
    }
    
    free(wvm->callStack);
    free(wvm->operandStack);

    gcFree(wvm->gc);

    free(wvm);
}
