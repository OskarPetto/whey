#include "../WheyVM.h"
#include "../InstructionSet.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 

Instruction instructionSet[256] =
    {
        /* 0x00 */ &opHalt,
        /* 0x01 */ &opJump,
        /* 0x02 */ &opJumpTrue,
        /* 0x03 */ &opJumpFalse,
        /* 0x04 */ &opUnknown,
        /* 0x05 */ &opUnknown,
        /* 0x06 */ &opUnknown,
        /* 0x07 */ &opUnknown,
        /* 0x08 */ &opUnknown,
        /* 0x09 */ &opUnknown,
        /* 0x0A */ &opUnknown,
        /* 0x0B */ &opUnknown,
        /* 0x0C */ &opUnknown,
        /* 0x0D */ &opUnknown,
        /* 0x0E */ &opUnknown,
        /* 0x0F */ &opUnknown,
        /* 0x10 */ &opLoad,
        /* 0x11 */ &opStore,
        /* 0x12 */ &opCall,
        /* 0x13 */ &opReturn,
        /* 0x14 */ &opConstant,
        /* 0x15 */ &opPrint,
        /* 0x16 */ &opPop,
        /* 0x17 */ &opUnknown,
        /* 0x18 */ &opUnknown,
        /* 0x19 */ &opUnknown,
        /* 0x1A */ &opUnknown,
        /* 0x1B */ &opUnknown,
        /* 0x1C */ &opUnknown,
        /* 0x1D */ &opUnknown,
        /* 0x1E */ &opUnknown,
        /* 0x1F */ &opUnknown,
        /* 0x20 */ &opEqual,
        /* 0x21 */ &opNotEqual,
        /* 0x22 */ &opGreaterThan,
        /* 0x23 */ &opGreaterThanOrEqual,
        /* 0x24 */ &opLessThan,
        /* 0x25 */ &opLessThanOrEqual,
        /* 0x26 */ &opUnknown,
        /* 0x27 */ &opUnknown,
        /* 0x28 */ &opUnknown,
        /* 0x29 */ &opUnknown,
        /* 0x2A */ &opUnknown,
        /* 0x2B */ &opUnknown,
        /* 0x2C */ &opUnknown,
        /* 0x2D */ &opUnknown,
        /* 0x2E */ &opUnknown,
        /* 0x2F */ &opUnknown,
        /* 0x30 */ &opAdd,
        /* 0x31 */ &opSubtract,
        /* 0x32 */ &opMultiply,
        /* 0x33 */ &opDivide,
        /* 0x34 */ &opPower,
        /* 0x35 */ &opNegate,
        /* 0x36 */ &opUnknown,
        /* 0x37 */ &opUnknown,
        /* 0x38 */ &opUnknown,
        /* 0x39 */ &opUnknown,
        /* 0x3A */ &opUnknown,
        /* 0x3B */ &opUnknown,
        /* 0x3C */ &opUnknown,
        /* 0x3D */ &opUnknown,
        /* 0x3E */ &opUnknown,
        /* 0x3F */ &opUnknown,
        /* 0x40 */ &opIntegerToDouble,
        /* 0x41 */ &opIntegerIncrement,
        /* 0x42 */ &opIntegerDecrement,
        /* 0x43 */ &opIntegerModulo,
        /* 0x44 */ &opIntegerAnd,
        /* 0x45 */ &opIntegerOr,
        /* 0x46 */ &opIntegerNot,
        /* 0x47 */ &opUnknown,
        /* 0x48 */ &opUnknown,
        /* 0x49 */ &opUnknown,
        /* 0x4A */ &opUnknown,
        /* 0x4B */ &opUnknown,
        /* 0x4C */ &opUnknown,
        /* 0x4D */ &opUnknown,
        /* 0x4E */ &opUnknown,
        /* 0x4F */ &opUnknown,
        /* 0x50 */ &opDoubleToInteger,
        /* 0x51 */ &opDoubleCeil,
        /* 0x52 */ &opDoubleFloor,
        /* 0x53 */ &opUnknown,
        /* 0x54 */ &opUnknown,
        /* 0x55 */ &opUnknown,
        /* 0x56 */ &opUnknown,
        /* 0x57 */ &opUnknown,
        /* 0x58 */ &opUnknown,
        /* 0x59 */ &opUnknown,
        /* 0x5A */ &opUnknown,
        /* 0x5B */ &opUnknown,
        /* 0x5C */ &opUnknown,
        /* 0x5D */ &opUnknown,
        /* 0x5E */ &opUnknown,
        /* 0x5F */ &opUnknown,
        /* 0x60 */ &opObjectNull,
        /* 0x61 */ &opObjectCopy,
        /* 0x62 */ &opObjectEquals,
        /* 0x63 */ &opObjectHash,
        /* 0x64 */ &opObjectToString,
        /* 0x65 */ &opObjectBox,
        /* 0x66 */ &opObjectUnbox,
        /* 0x67 */ &opUnknown,
        /* 0x68 */ &opUnknown,
        /* 0x69 */ &opUnknown,
        /* 0x6A */ &opUnknown,
        /* 0x6B */ &opUnknown,
        /* 0x6C */ &opUnknown,
        /* 0x6D */ &opUnknown,
        /* 0x6E */ &opUnknown,
        /* 0x6F */ &opUnknown,
        /* 0x70 */ &opArrayNew,
        /* 0x71 */ &opArraySize,
        /* 0x72 */ &opArrayGet,
        /* 0x73 */ &opArraySet,
        /* 0x74 */ &opArrayInsert,
        /* 0x75 */ &opArrayInsertAll,
        /* 0x76 */ &opArrayRemove,
        /* 0x77 */ &opArrayForEach,
        /* 0x78 */ &opUnknown,
        /* 0x79 */ &opUnknown,
        /* 0x7A */ &opUnknown,
        /* 0x7B */ &opUnknown,
        /* 0x7C */ &opUnknown,
        /* 0x7D */ &opUnknown,
        /* 0x7E */ &opUnknown,
        /* 0x7F */ &opUnknown,
        /* 0x80 */ &opMapNew,
        /* 0x81 */ &opMapSize,
        /* 0x82 */ &opMapGet,
        /* 0x83 */ &opMapPut,
        /* 0x84 */ &opMapPutAll,
        /* 0x85 */ &opMapRemove,
        /* 0x86 */ &opMapHasKey,
        /* 0x87 */ &opMapEntries,
        /* 0x88 */ &opUnknown,
        /* 0x89 */ &opUnknown,
        /* 0x8A */ &opUnknown,
        /* 0x8B */ &opUnknown,
        /* 0x8C */ &opUnknown,
        /* 0x8D */ &opUnknown,
        /* 0x8E */ &opUnknown,
        /* 0x8F */ &opUnknown,
        /* 0x90 */ &opPairNew,
        /* 0x91 */ &opPairGetFirst,
        /* 0x92 */ &opPairGetSecond,
        /* 0x93 */ &opPairSetFirst,
        /* 0x94 */ &opPairSetSecond,
        /* 0x95 */ &opUnknown,
        /* 0x96 */ &opUnknown,
        /* 0x97 */ &opUnknown,
        /* 0x98 */ &opUnknown,
        /* 0x99 */ &opUnknown,
        /* 0x9A */ &opUnknown,
        /* 0x9B */ &opUnknown,
        /* 0x9C */ &opUnknown,
        /* 0x9D */ &opUnknown,
        /* 0x9E */ &opUnknown,
        /* 0x9F */ &opUnknown,
        /* 0xA0 */ &opStringLength,
        /* 0xA1 */ &opStringFromArray,
        /* 0xA2 */ &opStringToArray,
        /* 0xA3 */ &opStringCompare,
        /* 0xA4 */ &opStringConcatenate,
        /* 0xA5 */ &opStringSubstring,
        /* 0xA6 */ &opStringIndexOf,
        /* 0xA7 */ &opStringReplace,
        /* 0xA8 */ &opStringSplit,
        /* 0xA9 */ &opUnknown,
        /* 0xAA */ &opUnknown,
        /* 0xAB */ &opUnknown,
        /* 0xAC */ &opUnknown,
        /* 0xAD */ &opUnknown,
        /* 0xAE */ &opUnknown,
        /* 0xAF */ &opUnknown,
        /* 0xB0 */ &opUnknown,
        /* 0xB1 */ &opUnknown,
        /* 0xB2 */ &opUnknown,
        /* 0xB3 */ &opUnknown,
        /* 0xB4 */ &opUnknown,
        /* 0xB5 */ &opUnknown,
        /* 0xB6 */ &opUnknown,
        /* 0xB7 */ &opUnknown,
        /* 0xB8 */ &opUnknown,
        /* 0xB9 */ &opUnknown,
        /* 0xBA */ &opUnknown,
        /* 0xBB */ &opUnknown,
        /* 0xBC */ &opUnknown,
        /* 0xBD */ &opUnknown,
        /* 0xBE */ &opUnknown,
        /* 0xBF */ &opUnknown,
        /* 0xC0 */ &opUnknown,
        /* 0xC1 */ &opUnknown,
        /* 0xC2 */ &opUnknown,
        /* 0xC3 */ &opUnknown,
        /* 0xC4 */ &opUnknown,
        /* 0xC5 */ &opUnknown,
        /* 0xC6 */ &opUnknown,
        /* 0xC7 */ &opUnknown,
        /* 0xC8 */ &opUnknown,
        /* 0xC9 */ &opUnknown,
        /* 0xCA */ &opUnknown,
        /* 0xCB */ &opUnknown,
        /* 0xCC */ &opUnknown,
        /* 0xCD */ &opUnknown,
        /* 0xCE */ &opUnknown,
        /* 0xCF */ &opUnknown,
        /* 0xD0 */ &opUnknown,
        /* 0xD1 */ &opUnknown,
        /* 0xD2 */ &opUnknown,
        /* 0xD3 */ &opUnknown,
        /* 0xD4 */ &opUnknown,
        /* 0xD5 */ &opUnknown,
        /* 0xD6 */ &opUnknown,
        /* 0xD7 */ &opUnknown,
        /* 0xD8 */ &opUnknown,
        /* 0xD9 */ &opUnknown,
        /* 0xDA */ &opUnknown,
        /* 0xDB */ &opUnknown,
        /* 0xDC */ &opUnknown,
        /* 0xDD */ &opUnknown,
        /* 0xDE */ &opUnknown,
        /* 0xDF */ &opUnknown,
        /* 0xE0 */ &opUnknown,
        /* 0xE1 */ &opUnknown,
        /* 0xE2 */ &opUnknown,
        /* 0xE3 */ &opUnknown,
        /* 0xE4 */ &opUnknown,
        /* 0xE5 */ &opUnknown,
        /* 0xE6 */ &opUnknown,
        /* 0xE7 */ &opUnknown,
        /* 0xE8 */ &opUnknown,
        /* 0xE9 */ &opUnknown,
        /* 0xEA */ &opUnknown,
        /* 0xEB */ &opUnknown,
        /* 0xEC */ &opUnknown,
        /* 0xED */ &opUnknown,
        /* 0xEE */ &opUnknown,
        /* 0xEF */ &opUnknown,
        /* 0xF0 */ &opUnknown,
        /* 0xF1 */ &opUnknown,
        /* 0xF2 */ &opUnknown,
        /* 0xF3 */ &opUnknown,
        /* 0xF4 */ &opUnknown,
        /* 0xF5 */ &opUnknown,
        /* 0xF6 */ &opUnknown,
        /* 0xF7 */ &opUnknown,
        /* 0xF8 */ &opUnknown,
        /* 0xF9 */ &opUnknown,
        /* 0xFA */ &opUnknown,
        /* 0xFB */ &opUnknown,
        /* 0xFC */ &opUnknown,
        /* 0xFD */ &opUnknown,
        /* 0xFE */ &opUnknown,
        /* 0xFF */ &opUnknown};

char *instructionStrings[256] =
    {
        /* 0x00 */ "opHalt",
        /* 0x01 */ "opJump",
        /* 0x02 */ "opJumpTrue",
        /* 0x03 */ "opJumpFalse",
        /* 0x04 */ "opUnknown",
        /* 0x05 */ "opUnknown",
        /* 0x06 */ "opUnknown",
        /* 0x07 */ "opUnknown",
        /* 0x08 */ "opUnknown",
        /* 0x09 */ "opUnknown",
        /* 0x0A */ "opUnknown",
        /* 0x0B */ "opUnknown",
        /* 0x0C */ "opUnknown",
        /* 0x0D */ "opUnknown",
        /* 0x0E */ "opUnknown",
        /* 0x0F */ "opUnknown",
        /* 0x10 */ "opLoad",
        /* 0x11 */ "opStore",
        /* 0x12 */ "opCall",
        /* 0x13 */ "opReturn",
        /* 0x14 */ "opConstant",
        /* 0x15 */ "opPrint",
        /* 0x16 */ "opPop",
        /* 0x17 */ "opUnknown",
        /* 0x18 */ "opUnknown",
        /* 0x19 */ "opUnknown",
        /* 0x1A */ "opUnknown",
        /* 0x1B */ "opUnknown",
        /* 0x1C */ "opUnknown",
        /* 0x1D */ "opUnknown",
        /* 0x1E */ "opUnknown",
        /* 0x1F */ "opUnknown",
        /* 0x20 */ "opEqual",
        /* 0x21 */ "opNotEqual",
        /* 0x22 */ "opGreaterThan",
        /* 0x23 */ "opGreaterThanOrEqual",
        /* 0x24 */ "opLessThan",
        /* 0x25 */ "opLessThanOrEqual",
        /* 0x26 */ "opUnknown",
        /* 0x27 */ "opUnknown",
        /* 0x28 */ "opUnknown",
        /* 0x29 */ "opUnknown",
        /* 0x2A */ "opUnknown",
        /* 0x2B */ "opUnknown",
        /* 0x2C */ "opUnknown",
        /* 0x2D */ "opUnknown",
        /* 0x2E */ "opUnknown",
        /* 0x2F */ "opUnknown",
        /* 0x30 */ "opAdd",
        /* 0x31 */ "opSubtract",
        /* 0x32 */ "opMultiply",
        /* 0x33 */ "opDivide",
        /* 0x34 */ "opPower",
        /* 0x35 */ "opNegate",
        /* 0x36 */ "opUnknown",
        /* 0x37 */ "opUnknown",
        /* 0x38 */ "opUnknown",
        /* 0x39 */ "opUnknown",
        /* 0x3A */ "opUnknown",
        /* 0x3B */ "opUnknown",
        /* 0x3C */ "opUnknown",
        /* 0x3D */ "opUnknown",
        /* 0x3E */ "opUnknown",
        /* 0x3F */ "opUnknown",
        /* 0x40 */ "opIntegerToDouble",
        /* 0x41 */ "opIntegerIncrement",
        /* 0x42 */ "opIntegerDecrement",
        /* 0x43 */ "opIntegerModulo",
        /* 0x44 */ "opIntegerAnd",
        /* 0x45 */ "opIntegerOr",
        /* 0x46 */ "opIntegerNot",
        /* 0x47 */ "opUnknown",
        /* 0x48 */ "opUnknown",
        /* 0x49 */ "opUnknown",
        /* 0x4A */ "opUnknown",
        /* 0x4B */ "opUnknown",
        /* 0x4C */ "opUnknown",
        /* 0x4D */ "opUnknown",
        /* 0x4E */ "opUnknown",
        /* 0x4F */ "opUnknown",
        /* 0x50 */ "opDoubleToInteger",
        /* 0x51 */ "opDoubleCeil",
        /* 0x52 */ "opDoubleFloor",
        /* 0x53 */ "opUnknown",
        /* 0x54 */ "opUnknown",
        /* 0x55 */ "opUnknown",
        /* 0x56 */ "opUnknown",
        /* 0x57 */ "opUnknown",
        /* 0x58 */ "opUnknown",
        /* 0x59 */ "opUnknown",
        /* 0x5A */ "opUnknown",
        /* 0x5B */ "opUnknown",
        /* 0x5C */ "opUnknown",
        /* 0x5D */ "opUnknown",
        /* 0x5E */ "opUnknown",
        /* 0x5F */ "opUnknown",
        /* 0x60 */ "opObjectNull",
        /* 0x61 */ "opObjectCopy",
        /* 0x62 */ "opObjectEquals",
        /* 0x63 */ "opObjectHash",
        /* 0x64 */ "opObjectToString",
        /* 0x65 */ "opObjectBox",
        /* 0x66 */ "opObjectUnbox",
        /* 0x67 */ "opUnknown",
        /* 0x68 */ "opUnknown",
        /* 0x69 */ "opUnknown",
        /* 0x6A */ "opUnknown",
        /* 0x6B */ "opUnknown",
        /* 0x6C */ "opUnknown",
        /* 0x6D */ "opUnknown",
        /* 0x6E */ "opUnknown",
        /* 0x6F */ "opUnknown",
        /* 0x70 */ "opArrayNew",
        /* 0x71 */ "opArraySize",
        /* 0x72 */ "opArrayGet",
        /* 0x73 */ "opArraySet",
        /* 0x74 */ "opArrayInsert",
        /* 0x75 */ "opArrayInsertAll",
        /* 0x76 */ "opArrayRemove",
        /* 0x77 */ "opArrayForEach",
        /* 0x78 */ "opUnknown",
        /* 0x79 */ "opUnknown",
        /* 0x7A */ "opUnknown",
        /* 0x7B */ "opUnknown",
        /* 0x7C */ "opUnknown",
        /* 0x7D */ "opUnknown",
        /* 0x7E */ "opUnknown",
        /* 0x7F */ "opUnknown",
        /* 0x80 */ "opMapNew",
        /* 0x81 */ "opMapSize",
        /* 0x82 */ "opMapGet",
        /* 0x83 */ "opMapPut",
        /* 0x84 */ "opMapPutAll",
        /* 0x85 */ "opMapRemove",
        /* 0x86 */ "opMapHasKey",
        /* 0x87 */ "opMapEntries",
        /* 0x88 */ "opUnknown",
        /* 0x89 */ "opUnknown",
        /* 0x8A */ "opUnknown",
        /* 0x8B */ "opUnknown",
        /* 0x8C */ "opUnknown",
        /* 0x8D */ "opUnknown",
        /* 0x8E */ "opUnknown",
        /* 0x8F */ "opUnknown",
        /* 0x90 */ "opPairNew",
        /* 0x91 */ "opPairGetFirst",
        /* 0x92 */ "opPairGetSecond",
        /* 0x93 */ "opPairSetFirst",
        /* 0x94 */ "opPairSetSecond",
        /* 0x95 */ "opUnknown",
        /* 0x96 */ "opUnknown",
        /* 0x97 */ "opUnknown",
        /* 0x98 */ "opUnknown",
        /* 0x99 */ "opUnknown",
        /* 0x9A */ "opUnknown",
        /* 0x9B */ "opUnknown",
        /* 0x9C */ "opUnknown",
        /* 0x9D */ "opUnknown",
        /* 0x9E */ "opUnknown",
        /* 0x9F */ "opUnknown",
        /* 0xA0 */ "opStringLength",
        /* 0xA1 */ "opStringFromArray",
        /* 0xA2 */ "opStringToArray",
        /* 0xA3 */ "opStringCompare",
        /* 0xA4 */ "opStringConcatenate",
        /* 0xA5 */ "opStringSubstring",
        /* 0xA6 */ "opStringIndexOf",
        /* 0xA7 */ "opStringReplace",
        /* 0xA8 */ "opStringSplit",
        /* 0xA9 */ "opUnknown",
        /* 0xAA */ "opUnknown",
        /* 0xAB */ "opUnknown",
        /* 0xAC */ "opUnknown",
        /* 0xAD */ "opUnknown",
        /* 0xAE */ "opUnknown",
        /* 0xAF */ "opUnknown",
        /* 0xB0 */ "opUnknown",
        /* 0xB1 */ "opUnknown",
        /* 0xB2 */ "opUnknown",
        /* 0xB3 */ "opUnknown",
        /* 0xB4 */ "opUnknown",
        /* 0xB5 */ "opUnknown",
        /* 0xB6 */ "opUnknown",
        /* 0xB7 */ "opUnknown",
        /* 0xB8 */ "opUnknown",
        /* 0xB9 */ "opUnknown",
        /* 0xBA */ "opUnknown",
        /* 0xBB */ "opUnknown",
        /* 0xBC */ "opUnknown",
        /* 0xBD */ "opUnknown",
        /* 0xBE */ "opUnknown",
        /* 0xBF */ "opUnknown",
        /* 0xC0 */ "opUnknown",
        /* 0xC1 */ "opUnknown",
        /* 0xC2 */ "opUnknown",
        /* 0xC3 */ "opUnknown",
        /* 0xC4 */ "opUnknown",
        /* 0xC5 */ "opUnknown",
        /* 0xC6 */ "opUnknown",
        /* 0xC7 */ "opUnknown",
        /* 0xC8 */ "opUnknown",
        /* 0xC9 */ "opUnknown",
        /* 0xCA */ "opUnknown",
        /* 0xCB */ "opUnknown",
        /* 0xCC */ "opUnknown",
        /* 0xCD */ "opUnknown",
        /* 0xCE */ "opUnknown",
        /* 0xCF */ "opUnknown",
        /* 0xD0 */ "opUnknown",
        /* 0xD1 */ "opUnknown",
        /* 0xD2 */ "opUnknown",
        /* 0xD3 */ "opUnknown",
        /* 0xD4 */ "opUnknown",
        /* 0xD5 */ "opUnknown",
        /* 0xD6 */ "opUnknown",
        /* 0xD7 */ "opUnknown",
        /* 0xD8 */ "opUnknown",
        /* 0xD9 */ "opUnknown",
        /* 0xDA */ "opUnknown",
        /* 0xDB */ "opUnknown",
        /* 0xDC */ "opUnknown",
        /* 0xDD */ "opUnknown",
        /* 0xDE */ "opUnknown",
        /* 0xDF */ "opUnknown",
        /* 0xE0 */ "opUnknown",
        /* 0xE1 */ "opUnknown",
        /* 0xE2 */ "opUnknown",
        /* 0xE3 */ "opUnknown",
        /* 0xE4 */ "opUnknown",
        /* 0xE5 */ "opUnknown",
        /* 0xE6 */ "opUnknown",
        /* 0xE7 */ "opUnknown",
        /* 0xE8 */ "opUnknown",
        /* 0xE9 */ "opUnknown",
        /* 0xEA */ "opUnknown",
        /* 0xEB */ "opUnknown",
        /* 0xEC */ "opUnknown",
        /* 0xED */ "opUnknown",
        /* 0xEE */ "opUnknown",
        /* 0xEF */ "opUnknown",
        /* 0xF0 */ "opUnknown",
        /* 0xF1 */ "opUnknown",
        /* 0xF2 */ "opUnknown",
        /* 0xF3 */ "opUnknown",
        /* 0xF4 */ "opUnknown",
        /* 0xF5 */ "opUnknown",
        /* 0xF6 */ "opUnknown",
        /* 0xF7 */ "opUnknown",
        /* 0xF8 */ "opUnknown",
        /* 0xF9 */ "opUnknown",
        /* 0xFA */ "opUnknown",
        /* 0xFB */ "opUnknown",
        /* 0xFC */ "opUnknown",
        /* 0xFD */ "opUnknown",
        /* 0xFE */ "opUnknown",
        /* 0xFF */ "opUnknown"};

static uint32_t wvmMark(struct WheyVM *wvm)
{
    uint32_t count = 0;

    for (int32_t i = 0; i <= wvm->callStackPointer; i++)
    {
        count += frameMark(wvm->callStack[i]);
    }

    for (int32_t i = 0; i <= wvm->operandStackPointer; i++)
    {
        struct Operand operand = wvm->operandStack[i];
        if (operand.type == OPERAND_TYPE_REFERENCE)
        {
            count += objectMark(operand.value.reference);
        }
    }

    return count;
}

static int wvmExecute(struct WheyVM *wvm)
{
    struct Function *mainFunction = wcFileGetFunction(wvm->wcFile, 0);

    wvm->callStack[++wvm->callStackPointer] = frameNew(mainFunction);

    //Performance timings

#ifdef INSTRUCTION_TIMING
    int instructionCount[256];
    clock_t instructionTimings[256];
    for(int i = 0; i < 256; ++i)
    {
        instructionCount[i] = 0;
        instructionTimings[i] = 0;
    }
#endif



    //Invariants go here, to avoid constant wvm-> lookups
    int32_t const operandStackSize = wvm->operandStackSize;
    int32_t const callStackSize = wvm->callStackSize;

    while (!(wvm->state & WHEYVM_STATE_STOPPED))
    {
        int32_t const stack = wvm->callStackPointer;
        struct Frame* const currentFrame = wvm->callStack[stack];
        struct Function* const currentFunction = currentFrame->function;
        uint16_t const codePointer = currentFrame->codePointer;

        if (stack < 0)
        {
            fprintf(stderr, "Call stack pointer is negative.\n");
            return 1;
        }

        if (codePointer >= currentFunction->codeSize) 
        {
            fprintf(stderr, "No return reached.\n");
            return 1;
        }          

        if (wvm->operandStackPointer >= operandStackSize)
        {
            fprintf(stderr, "Operand stack overflow.\n");
            return 1;
        }

        if (stack >= callStackSize)
        {
            fprintf(stderr, "Call stack overflow.\n");
            return 1;
        }

        unsigned char const instruction = currentFunction->byteCode[codePointer];

        //printf("%s: %d \n", instructionStrings[instruction], wvm->operandStackPointer);

#ifdef INSTRUCTION_TIMING
        clock_t begin = clock();
#endif
        instructionSet[instruction](wvm,currentFrame);

#ifdef INSTRUCTION_TIMING
        clock_t end = clock();
        instructionTimings[instruction] += (end - begin);
        instructionCount[instruction] += 1;
#endif

        ++wvm->executedInstructions;

        if (gcShouldMarkAndSweep(wvm->gc))
        {
            uint32_t count = wvmMark(wvm);

            gcSweep(wvm->gc);

            if (wvm->state & WHEYVM_STATE_DEBUG)
            {
                printf("instruction %lu: %d objects marked with %d bytes used.\n", wvm->executedInstructions, count, wvm->gc->size);
                printf("instruction %lu: garbage collected %lu objects with %lu bytes.\n", wvm->executedInstructions, wvm->gc->freeCount, wvm->gc->claimedSize);
            }
        }

    }

#ifdef INSTRUCTION_TIMING
    printf("Instruction time\n");
    for(int i = 0; i < 256; ++i)
    {
        if(instructionTimings[i] == 0) continue;
        printf("instructionTimings %s took %f seconds, was called %d times \n", instructionStrings[i], ((double) (instructionTimings[i]))/CLOCKS_PER_SEC,instructionCount[i]);
    }
#endif

    return 0;
}

int wvmRun(struct WcFile *wcFile, uint16_t callStackSize, uint16_t operandStackSize, uint64_t gcMemorySize, double gcLoadFactor, uint16_t coolDown, uint8_t state)
{
    struct WheyVM *wvm = (struct WheyVM *)malloc(sizeof(struct WheyVM));
    assert(wvm != NULL);
    
    wvm->callStackSize = callStackSize;
    wvm->callStack = (struct Frame **)malloc(callStackSize * sizeof(struct Frame *));
    assert(wvm->callStack != NULL);
    wvm->callStackPointer = -1;
    wvm->executedInstructions = 0;

    wvm->operandStackSize = operandStackSize;
    wvm->operandStack = (struct Operand *)malloc(operandStackSize * sizeof(struct Operand));
    assert(wvm->operandStack != NULL);
    wvm->operandStackPointer = -1;

    wvm->gc = gcNew(gcMemorySize, gcLoadFactor, coolDown);

    wvm->wcFile = wcFile;
    wvm->state = state;

    clock_t begin = clock();

    int returnStatus = wvmExecute(wvm);

    clock_t end = clock();

    printf("instruction %lu: finished program execution in %f seconds.\n", wvm->executedInstructions, ((double) (end - begin))/CLOCKS_PER_SEC);

    for (int32_t i = 0; i <= wvm->callStackPointer; i++)
    {
        frameFree(wvm->callStack[i]);
    }

    free(wvm->callStack);
    free(wvm->operandStack);

    gcSweep(wvm->gc);
    gcFree(wvm->gc);

    free(wvm);

    return returnStatus;
}
