#ifndef OPCODE_H
#define OPCODE_H

#define OP_HALT 0x00
#define OP_JMP 0x01
#define OP_JMPT 0x02
#define OP_JMPF 0x03

#define OP_LOAD 0x10
#define OP_STORE 0x11
#define OP_CALL 0x12
#define OP_RETURN 0x13

#define OP_CONST 0x20
#define OP_PRINT 0x21
#define OP_POP 0x22

#define OP_EQ 0x30
#define OP_NEQ 0x31
#define OP_GT 0x32
#define OP_GTE 0x33
#define OP_LT 0x34
#define OP_LTE 0x35

#define OP_ADD 0x40
#define OP_SUB 0x41
#define OP_MUL 0x42
#define OP_DIV 0x43
#define OP_NEG 0x44
#define OP_INC 0x45
#define OP_DEC 0x46
#define OP_AND 0x47
#define OP_OR 0x48
#define OP_NOT 0x49

#define OP_ONULL 0x50
#define OP_OCOPY 0x51
#define OP_OEQUALS 0x52
#define OP_OHASH 0x53
#define OP_OTOSTRING 0x54

#define OP_ANEW 0x60
#define OP_ASIZE 0x61
#define OP_AGET 0x62
#define OP_ASET 0x63
#define OP_AINSERT 0x64
#define OP_AINSERTALL 0x65
#define OP_AREMOVE 0x66
#define OP_AFOREACH 0x67

#define OP_MNEW 0x70
#define OP_MSIZE 0x71
#define OP_MGET 0x72
#define OP_MPUT 0x73
#define OP_MPUTALL 0x74
#define OP_MREMOVE 0x75
#define OP_MHASKEY 0x76
#define OP_MENTRIES 0x77

#define OP_PNEW 0x80
#define OP_PGETFST 0x81
#define OP_PGETSND 0x82
#define OP_PSETFST 0x83
#define OP_PSETSND 0x84

#define OP_SLENGTH 0x90
#define OP_SFROMARRAY 0x91
#define OP_STOARRAY 0x92
#define OP_SCOMPARE 0x93
#define OP_SCONCAT 0x94
#define OP_SSUBS 0x95
#define OP_SINDEXOF 0x96
#define OP_SREPLACE 0x97

struct WheyVM;

typedef void (*Instruction)(struct WheyVM *wvm);

void opUnknown(struct WheyVM *wvm);

void opHalt(struct WheyVM *wvm);
void opJump(struct WheyVM *wvm);
void opJumpTrue(struct WheyVM *wvm);
void opJumpFalse(struct WheyVM *wvm);
void opLoad(struct WheyVM *wvm);
void opStore(struct WheyVM *wvm);
void opCall(struct WheyVM *wvm);
void opReturn(struct WheyVM *wvm);
void opConstant(struct WheyVM *wvm);
void opPrint(struct WheyVM *wvm);
void opPop(struct WheyVM *wvm);
void opEqual(struct WheyVM *wvm);
void opNotEqual(struct WheyVM *wvm);
void opGreaterThan(struct WheyVM *wvm);
void opGreaterThanOrEqual(struct WheyVM *wvm);
void opLessThan(struct WheyVM *wvm);
void opLessThanOrEqual(struct WheyVM *wvm);
void opAdd(struct WheyVM *wvm);
void opSubtract(struct WheyVM *wvm);
void opMultiply(struct WheyVM *wvm);
void opDivide(struct WheyVM *wvm);
void opNegate(struct WheyVM *wvm);
void opIncrement(struct WheyVM *wvm);
void opDecrement(struct WheyVM *wvm);
void opAnd(struct WheyVM *wvm);
void opOr(struct WheyVM *wvm);
void opNot(struct WheyVM *wvm);
void opObjectNull(struct WheyVM *wvm);
void opObjectCopy(struct WheyVM *wvm);
void opObjectEquals(struct WheyVM *wvm);
void opObjectHash(struct WheyVM *wvm);
void opObjectToString(struct WheyVM *wvm);
void opArrayNew(struct WheyVM *wvm);
void opArraySize(struct WheyVM *wvm);
void opArrayGet(struct WheyVM *wvm);
void opArraySet(struct WheyVM *wvm);
void opArrayInsert(struct WheyVM *wvm);
void opArrayInsertAll(struct WheyVM *wvm);
void opArrayRemove(struct WheyVM *wvm);
void opArrayForEach(struct WheyVM *wvm);
void opMapNew(struct WheyVM *wvm);
void opMapSize(struct WheyVM *wvm);
void opMapGet(struct WheyVM *wvm);
void opMapPut(struct WheyVM *wvm);
void opMapPutAll(struct WheyVM *wvm);
void opMapRemove(struct WheyVM *wvm);
void opMapHasKey(struct WheyVM *wvm);
void opMapEntries(struct WheyVM *wvm);
void opPairNew(struct WheyVM *wvm);
void opPairGetFirst(struct WheyVM *wvm);
void opPairGetSecond(struct WheyVM *wvm);
void opPairSetFirst(struct WheyVM *wvm);
void opPairSetSecond(struct WheyVM *wvm);
void opStringLength(struct WheyVM *wvm);
void opStringFromArray(struct WheyVM *wvm);
void opStringToArray(struct WheyVM *wvm);
void opStringCompare(struct WheyVM *wvm);
void opStringConcatenate(struct WheyVM *wvm);
void opStringSubstring(struct WheyVM *wvm);
void opStringIndexOf(struct WheyVM *wvm);
void opStringReplace(struct WheyVM *wvm);

Instruction const instructionSet[256] =
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
        /* 0x14 */ &opUnknown,
        /* 0x15 */ &opUnknown,
        /* 0x16 */ &opUnknown,
        /* 0x17 */ &opUnknown,
        /* 0x18 */ &opUnknown,
        /* 0x19 */ &opUnknown,
        /* 0x1A */ &opUnknown,
        /* 0x1B */ &opUnknown,
        /* 0x1C */ &opUnknown,
        /* 0x1D */ &opUnknown,
        /* 0x1E */ &opUnknown,
        /* 0x1F */ &opUnknown,
        /* 0x20 */ &opConstant,
        /* 0x21 */ &opPrint,
        /* 0x22 */ &opPop,
        /* 0x23 */ &opUnknown,
        /* 0x24 */ &opUnknown,
        /* 0x25 */ &opUnknown,
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
        /* 0x30 */ &opEqual,
        /* 0x31 */ &opNotEqual,
        /* 0x32 */ &opGreaterThan,
        /* 0x33 */ &opGreaterThanOrEqual,
        /* 0x34 */ &opLessThan,
        /* 0x35 */ &opLessThanOrEqual,
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
        /* 0x40 */ &opAdd,
        /* 0x41 */ &opSubtract,
        /* 0x42 */ &opMultiply,
        /* 0x43 */ &opDivide,
        /* 0x44 */ &opNegate,
        /* 0x45 */ &opIncrement,
        /* 0x46 */ &opDecrement,
        /* 0x47 */ &opAnd,
        /* 0x48 */ &opOr,
        /* 0x49 */ &opNot,
        /* 0x4A */ &opUnknown,
        /* 0x4B */ &opUnknown,
        /* 0x4C */ &opUnknown,
        /* 0x4D */ &opUnknown,
        /* 0x4E */ &opUnknown,
        /* 0x4F */ &opUnknown,
        /* 0x50 */ &opObjectNull,
        /* 0x51 */ &opObjectCopy,
        /* 0x52 */ &opObjectEquals,
        /* 0x53 */ &opObjectHash,
        /* 0x54 */ &opObjectToString,
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
        /* 0x60 */ &opArrayNew,
        /* 0x61 */ &opArraySize,
        /* 0x62 */ &opArrayGet,
        /* 0x63 */ &opArraySet,
        /* 0x64 */ &opArrayInsert,
        /* 0x65 */ &opArrayInsertAll,
        /* 0x66 */ &opArrayRemove,
        /* 0x67 */ &opArrayForEach,
        /* 0x68 */ &opUnknown,
        /* 0x69 */ &opUnknown,
        /* 0x6A */ &opUnknown,
        /* 0x6B */ &opUnknown,
        /* 0x6C */ &opUnknown,
        /* 0x6D */ &opUnknown,
        /* 0x6E */ &opUnknown,
        /* 0x6F */ &opUnknown,
        /* 0x70 */ &opMapNew,
        /* 0x71 */ &opMapSize,
        /* 0x72 */ &opMapGet,
        /* 0x73 */ &opMapPut,
        /* 0x74 */ &opMapPutAll,
        /* 0x75 */ &opMapRemove,
        /* 0x76 */ &opMapHasKey,
        /* 0x77 */ &opMapEntries,
        /* 0x78 */ &opUnknown,
        /* 0x79 */ &opUnknown,
        /* 0x7A */ &opUnknown,
        /* 0x7B */ &opUnknown,
        /* 0x7C */ &opUnknown,
        /* 0x7D */ &opUnknown,
        /* 0x7E */ &opUnknown,
        /* 0x7F */ &opUnknown,
        /* 0x80 */ &opPairNew,
        /* 0x81 */ &opPairGetFirst,
        /* 0x82 */ &opPairGetSecond,
        /* 0x83 */ &opPairSetFirst,
        /* 0x84 */ &opPairSetSecond,
        /* 0x85 */ &opUnknown,
        /* 0x86 */ &opUnknown,
        /* 0x87 */ &opUnknown,
        /* 0x88 */ &opUnknown,
        /* 0x89 */ &opUnknown,
        /* 0x8A */ &opUnknown,
        /* 0x8B */ &opUnknown,
        /* 0x8C */ &opUnknown,
        /* 0x8D */ &opUnknown,
        /* 0x8E */ &opUnknown,
        /* 0x8F */ &opUnknown,
        /* 0x90 */ &opStringLength,
        /* 0x91 */ &opStringFromArray,
        /* 0x92 */ &opStringToArray,
        /* 0x93 */ &opStringCompare,
        /* 0x94 */ &opStringConcatenate,
        /* 0x95 */ &opStringSubstring,
        /* 0x96 */ &opStringIndexOf,
        /* 0x97 */ &opStringReplace,
        /* 0x98 */ &opUnknown,
        /* 0x99 */ &opUnknown,
        /* 0x9A */ &opUnknown,
        /* 0x9B */ &opUnknown,
        /* 0x9C */ &opUnknown,
        /* 0x9D */ &opUnknown,
        /* 0x9E */ &opUnknown,
        /* 0x9F */ &opUnknown,
        /* 0xA0 */ &opUnknown,
        /* 0xA1 */ &opUnknown,
        /* 0xA2 */ &opUnknown,
        /* 0xA3 */ &opUnknown,
        /* 0xA4 */ &opUnknown,
        /* 0xA5 */ &opUnknown,
        /* 0xA6 */ &opUnknown,
        /* 0xA7 */ &opUnknown,
        /* 0xA8 */ &opUnknown,
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
        /* 0xFF */ &opUnknown
};

#endif