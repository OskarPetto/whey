#include "../Stack.h"
#include "../../Object/Integer.h"
#include "../../Object/String.h"
#include "../../Object/Gc.h"
#include "../../Object/Array.h"
#include "../../Object/Object.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void testStackNew()
{
    printf("testStackNew: ");
    struct Stack *stack = stackNew(100000);

    assert(stack->maxSize == 100000);
    assert(stack->size == 0);
    assert(stack->callStackPointer == NULL);

    stackFree(stack);
    printf("OK\n");
}

void testStackPush()
{
    printf("testStackPush: ");
    struct Gc *gc = gcNew(1000, 0);

    struct StringConstant stringConstant3;
    stringConstant3.characterCount = 6;
    stringConstant3.characters = "Class1";

    struct StringConstant stringConstant1;
    stringConstant1.characterCount = 7;
    stringConstant1.characters = "funMain";

    struct StringConstant stringConstant2;
    stringConstant2.characterCount = 4;
    stringConstant2.characters = "fun1";

    struct ConstantTable constantTable;
    constantTable.constantCount = 1;
    constantTable.constants = malloc(3 * sizeof(struct Constant));
    constantTable.constants[0].type = CONSTANT_TYPE_STRING;
    constantTable.constants[0].value.stringConstant = &stringConstant3;
    constantTable.constants[1].type = CONSTANT_TYPE_STRING;
    constantTable.constants[1].value.stringConstant = &stringConstant1;
    constantTable.constants[2].type = CONSTANT_TYPE_STRING;
    constantTable.constants[2].value.stringConstant = &stringConstant2;

    struct Stack *stack = stackNew(1000);

    struct Method methodMain;
    
    methodMain.nameIndex = 1;
    methodMain.argumentCount = 0;
    methodMain.localsCount = 2;
    methodMain.maxOperandCount = 3;
    
    size_t mainFrameSize = sizeof(struct Frame) + (methodMain.argumentCount + methodMain.localsCount + methodMain.maxOperandCount) * sizeof(struct Operand);

    stackPush(stack, &methodMain, &constantTable);

    struct Frame *mainFrame = stack->callStackPointer;

    assert(stack->size == mainFrameSize);
    assert(mainFrame == stack->callStack);
    assert(mainFrame == stack->callStackPointer);
    assert(mainFrame->prev == NULL);
    assert(mainFrame->constantTable == &constantTable);

    mainFrame->operandStack[0].type = OPERAND_TYPE_INTEGER;
    mainFrame->operandStack[0].value.integerValue = 87;

    mainFrame->operandStack[1].type = OPERAND_TYPE_REFERENCE;
    mainFrame->operandStack[1].value.reference = stringNewFromCString(gc, "hallo lol");
    
    mainFrame->operandStackPointer = mainFrame->operandStack + 2;

    struct Method methodFirst;

    methodFirst.nameIndex = 2;
    methodFirst.argumentCount = 2;
    methodFirst.localsCount = 0;
    methodFirst.maxOperandCount = 2;

    size_t firstFrameSize = sizeof(struct Frame) + (methodFirst.argumentCount + methodFirst.localsCount + methodFirst.maxOperandCount) * sizeof(struct Operand);

    stackPush(stack, &methodFirst, &constantTable);

    struct Frame *firstFrame = stack->callStackPointer;

    assert(firstFrame->arguments[0].type == OPERAND_TYPE_INTEGER);
    assert(firstFrame->arguments[1].type == OPERAND_TYPE_REFERENCE);
    assert(firstFrame == stack->callStackPointer);
    assert(firstFrame == (void *) stack->callStack + mainFrameSize);
    assert(firstFrame->prev == mainFrame);
    assert(firstFrame->arguments = mainFrame->operandStack);

    assert(stack->size == mainFrameSize + firstFrameSize);

    gcSweep(gc);

    stackFree(stack);

    free(constantTable.constants);
    gcFree(gc);
    printf("OK\n");
}

void testStackPushOverflow()
{
    printf("testStackPushOverflow: ");
    struct Stack *stack = stackNew(240);

    struct Method methodMain;
    
    methodMain.argumentCount = 0;
    methodMain.localsCount = 2;
    methodMain.maxOperandCount = 3;
    
    size_t mainFrameSize = sizeof(struct Frame) + (methodMain.localsCount + methodMain.maxOperandCount) * sizeof(struct Operand);

    stackPush(stack, &methodMain, NULL);

    struct Frame *mainFrame = stack->callStackPointer;

    assert(stack->size == mainFrameSize);
    assert(mainFrame == stack->callStack);
    assert(mainFrame == stack->callStackPointer);
    assert(mainFrame->prev == NULL);
    
    struct Method methodFirst;

    methodFirst.argumentCount = 2;
    methodFirst.localsCount = 0;
    methodFirst.maxOperandCount = 2;

    stackPush(stack, &methodFirst, NULL);

    assert(stack->size == stack->maxSize);

    stackFree(stack);
    printf("OK\n");
}

void testStackPop()
{
    printf("testStackPop: ");
    struct Gc *gc = gcNew(1000, 0);

    struct StringConstant stringConstant3;
    stringConstant3.characterCount = 6;
    stringConstant3.characters = "Class1";

    struct StringConstant stringConstant1;
    stringConstant1.characterCount = 7;
    stringConstant1.characters = "funMain";

    struct StringConstant stringConstant2;
    stringConstant2.characterCount = 4;
    stringConstant2.characters = "fun1";

    struct ConstantTable constantTable;
    constantTable.constantCount = 1;
    constantTable.constants = malloc(3 * sizeof(struct Constant));
    constantTable.constants[0].type = CONSTANT_TYPE_STRING;
    constantTable.constants[0].value.stringConstant = &stringConstant3;
    constantTable.constants[1].type = CONSTANT_TYPE_STRING;
    constantTable.constants[1].value.stringConstant = &stringConstant1;
    constantTable.constants[2].type = CONSTANT_TYPE_STRING;
    constantTable.constants[2].value.stringConstant = &stringConstant2;

    struct Stack *stack = stackNew(1000);

    struct Method methodMain;
    
    methodMain.nameIndex = 1;
    methodMain.argumentCount = 0;
    methodMain.localsCount = 2;
    methodMain.returnsSomething = 0;
    methodMain.maxOperandCount = 3;
    
    size_t mainFrameSize = sizeof(struct Frame) + (methodMain.argumentCount + methodMain.localsCount + methodMain.maxOperandCount) * sizeof(struct Operand);

    stackPush(stack, &methodMain, &constantTable);

    struct Frame *mainFrame = stack->callStackPointer;

    assert(mainFrame->operandStackPointer != NULL);
    
    struct Method methodFirst;

    methodFirst.nameIndex = 2;
    methodFirst.returnsSomething = 1;
    methodFirst.argumentCount = 2;
    methodFirst.localsCount = 0;
    methodFirst.maxOperandCount = 2;

    stackPush(stack, &methodFirst, &constantTable);

    struct Frame *firstFrame = stack->callStackPointer;

    firstFrame->operandStack[0].type = OPERAND_TYPE_REFERENCE;
    firstFrame->operandStack[0].value.reference = arrayNew(gc, 0, 10);

    firstFrame->operandStackPointer = firstFrame->operandStack + 1;

    stackPop(stack);

    struct Frame *alsoMainFrame = stack->callStackPointer;
    assert(mainFrame == alsoMainFrame);

    struct Operand *topOfStack = mainFrame->operandStackPointer - 1;
    struct Operand *returnValue = firstFrame->operandStack;

    assert(topOfStack->type == returnValue->type);
    assert(topOfStack->value.reference == returnValue->value.reference);

    assert(stack->size == mainFrameSize);

    stackPop(stack);

    assert(stack->size == 0);
    free(constantTable.constants);
    gcSweep(gc);
    stackFree(stack);
    gcFree(gc);
    printf("OK\n");
}

void testStackMark()
{
    printf("testStackMark: ");
    struct Gc *gc = gcNew(1000, 0);
    struct Stack *stack = stackNew(1000);

    struct StringConstant stringConstant3;
    stringConstant3.characterCount = 6;
    stringConstant3.characters = "Class1";

    struct StringConstant stringConstant1;
    stringConstant1.characterCount = 7;
    stringConstant1.characters = "funMain";

    struct StringConstant stringConstant2;
    stringConstant2.characterCount = 4;
    stringConstant2.characters = "fun1";

    struct ConstantTable constantTable;
    constantTable.constantCount = 1;
    constantTable.constants = malloc(3 * sizeof(struct Constant));
    constantTable.constants[0].type = CONSTANT_TYPE_STRING;
    constantTable.constants[0].value.stringConstant = &stringConstant3;
    constantTable.constants[1].type = CONSTANT_TYPE_STRING;
    constantTable.constants[1].value.stringConstant = &stringConstant1;
    constantTable.constants[2].type = CONSTANT_TYPE_STRING;
    constantTable.constants[2].value.stringConstant = &stringConstant2;

    struct Method methodMain;
    
    methodMain.returnsSomething = 1;
    methodMain.nameIndex = 1;
    methodMain.argumentCount = 0;
    methodMain.localsCount = 0;
    methodMain.maxOperandCount = 2;
    
    stackPush(stack, &methodMain, &constantTable);
    
    struct Frame *mainFrame = stack->callStackPointer;

    mainFrame->operandStack[0].type = OPERAND_TYPE_REFERENCE;
    mainFrame->operandStack[0].value.reference = integerNew(gc, 121);

    mainFrame->operandStack[1].type = OPERAND_TYPE_REFERENCE;
    mainFrame->operandStack[1].value.reference = integerNew(gc, 543);

    mainFrame->operandStackPointer = mainFrame->operandStack + 2;

    struct Method methodFirst;

    methodFirst.returnsSomething = 0;
    methodFirst.nameIndex = 2;
    methodFirst.argumentCount = 2;
    methodFirst.localsCount = 1;
    methodFirst.maxOperandCount = 2;

    stackPush(stack, &methodFirst, &constantTable);

    struct Frame *firstFrame = stack->callStackPointer;

    assert(firstFrame->arguments->type == mainFrame->operandStack->type);
    assert(firstFrame->arguments->value.reference == mainFrame->operandStack->value.reference);

    firstFrame->locals[0].type = OPERAND_TYPE_REFERENCE;
    firstFrame->locals[0].value.reference = arrayNew(gc, 1, 1);

    struct Array *array = firstFrame->locals[0].value.reference->value.subObject;
    
    array->objects[0] = mainFrame->operandStack[1].value.reference;

    firstFrame->operandStack[0].type = OPERAND_TYPE_REFERENCE;
    firstFrame->operandStack[0].value.reference = firstFrame->locals[0].value.reference;

    firstFrame->operandStack[1].type = OPERAND_TYPE_REFERENCE;
    firstFrame->operandStack[1].value.reference = mainFrame->operandStack[0].value.reference;

    firstFrame->operandStackPointer = firstFrame->operandStack + 1;

    stackMark(stack);

    uint32_t oldObjectCount = gc->objectCount;

    gcSweep(gc);

    assert(gc->objectCount == oldObjectCount);

    gcSweep(gc);
    gcFree(gc);
    stackFree(stack);
    free(constantTable.constants);
    printf("OK\n");
}


void testStackPrint()
{
    printf("testStackPrint: ");
    struct Gc *gc = gcNew(1000, 0);
    struct Stack *stack = stackNew(1000);

    struct StringConstant stringConstant3;
    stringConstant3.characterCount = 6;
    stringConstant3.characters = "Class1";

    struct StringConstant stringConstant1;
    stringConstant1.characterCount = 7;
    stringConstant1.characters = "funMain";

    struct StringConstant stringConstant2;
    stringConstant2.characterCount = 4;
    stringConstant2.characters = "fun1";

    struct ConstantTable constantTable;
    constantTable.constantCount = 1;
    constantTable.constants = malloc(3 * sizeof(struct Constant));
    constantTable.constants[0].type = CONSTANT_TYPE_STRING;
    constantTable.constants[0].value.stringConstant = &stringConstant3;
    constantTable.constants[1].type = CONSTANT_TYPE_STRING;
    constantTable.constants[1].value.stringConstant = &stringConstant1;
    constantTable.constants[2].type = CONSTANT_TYPE_STRING;
    constantTable.constants[2].value.stringConstant = &stringConstant2;

    struct Method methodMain;
    
    methodMain.returnsSomething = 1;
    methodMain.nameIndex = 1;
    methodMain.argumentCount = 0;
    methodMain.localsCount = 0;
    methodMain.maxOperandCount = 2;
    methodMain.codeSize = 2;
    methodMain.byteCode = malloc(2);
    
    stackPush(stack, &methodMain, &constantTable);
    
    struct Frame *mainFrame = stack->callStackPointer;

    mainFrame->operandStack[0].type = OPERAND_TYPE_REFERENCE;
    mainFrame->operandStack[0].value.reference = integerNew(gc, 121);

    mainFrame->operandStack[1].type = OPERAND_TYPE_REFERENCE;
    mainFrame->operandStack[1].value.reference = integerNew(gc, 543);

    mainFrame->operandStackPointer = mainFrame->operandStack + 2;

    struct Method methodFirst;

    methodFirst.returnsSomething = 0;
    methodFirst.nameIndex = 2;
    methodFirst.argumentCount = 2;
    methodFirst.localsCount = 1;
    methodFirst.maxOperandCount = 2;
    methodFirst.codeSize = 20;
    methodFirst.byteCode = malloc(20);

    stackPush(stack, &methodFirst, &constantTable);

    struct Frame *firstFrame = stack->callStackPointer;

    firstFrame->locals[0].type = OPERAND_TYPE_REFERENCE;
    firstFrame->locals[0].value.reference = arrayNew(gc, 1, 1);

    struct Array *array = firstFrame->locals[0].value.reference->value.subObject;
    
    array->objects[0] = mainFrame->operandStack[1].value.reference;

    firstFrame->operandStack[0].type = OPERAND_TYPE_REFERENCE;
    firstFrame->operandStack[0].value.reference = firstFrame->locals[0].value.reference;

    firstFrame->operandStack[1].type = OPERAND_TYPE_REFERENCE;
    firstFrame->operandStack[1].value.reference = mainFrame->operandStack[0].value.reference;

    firstFrame->operandStackPointer = firstFrame->operandStack + 1;

    stackPrint(stack);

    gcSweep(gc);
    gcFree(gc);
    stackFree(stack);
    free(constantTable.constants);
    free(methodMain.byteCode);
    free(methodFirst.byteCode);
    printf("OK\n");
}

int main(int argc, char* argv[])
{
    testStackNew();
    testStackPush();
    // testStackPushOverflow();
    testStackPop();
    testStackMark();
    testStackPrint();
    printf("All tests passed.\n");
    return 0;
}