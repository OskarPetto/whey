#ifndef OPCODE_H
#define OPCODE_H

#define OP_HALT                    0x00
#define OP_JMP                     0x01       
#define OP_JMPT                    0x02    
#define OP_JMPF                    0x03

#define OP_LOAD                    0x10 
#define OP_STORE                   0x11
#define OP_CALL                    0x12
#define OP_RETURN                  0x13

#define OP_CONST                   0x20  
#define OP_PRINT                   0x21
#define OP_POP                     0x22

#define OP_EQ                      0x30
#define OP_NEQ                     0x31
#define OP_GT                      0x32
#define OP_GTE                     0x33
#define OP_LT                      0x34
#define OP_LTE                     0x35

#define OP_ADD                     0x40
#define OP_SUB                     0x41
#define OP_MUL                     0x42
#define OP_DIV                     0x43
#define OP_NEG                     0x44
#define OP_INC                     0x45
#define OP_DEC                     0x46
#define OP_AND                     0x47
#define OP_OR                      0x48
#define OP_NOT                     0x49

#define OP_ONULL                   0x50
#define OP_OCOPY                   0x51
#define OP_OEQUALS                 0x52
#define OP_OHASH                   0x53
#define OP_OTOSTRING               0x54

#define OP_ANEW                    0x60
#define OP_ASIZE                   0x61
#define OP_AGET                    0x62
#define OP_ASET                    0x63
#define OP_AINSERT                 0x64
#define OP_AINSERTALL              0x65
#define OP_AREMOVE                 0x66
#define OP_AFOREACH                0x67

#define OP_MNEW                    0x70
#define OP_MSIZE                   0x71
#define OP_MGET                    0x72
#define OP_MPUT                    0x73
#define OP_MPUTALL                 0x74
#define OP_MREMOVE                 0x75
#define OP_MHASKEY                 0x76
#define OP_MENTRIES                0x77

#define OP_PNEW                    0x80
#define OP_PGETFST                 0x81
#define OP_PGETSND                 0x82
#define OP_PSETFST                 0x83
#define OP_PSETSND                 0x84

#define OP_SLENGTH                 0x90
#define OP_SFROMARRAY              0x91
#define OP_STOARRAY                0x92
#define OP_SCOMPARE                0x93
#define OP_SCONCAT                 0x94
#define OP_SSUBSTRING              0x95
#define OP_SINDEXOF                0x96
#define OP_SREPLACE                0x97

typedef void (*Instruction)(struct WheyVM *wvm);

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
void opStringCompare(struct WheyVM *wvm);
void opStringConcatenate(struct WheyVM *wvm);
void opStringSubstring(struct WheyVM *wvm);

#endif