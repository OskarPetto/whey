#ifndef WHEY_H
#define WHEY_H

#define OP_HALT                    0x00
        
#define OP_JMP                     0x01       
#define OP_JMPT                    0x02    
#define OP_JMPF                    0x03

#define OP_POP                     0x30
#define OP_DUP                     0x31
#define OP_LOAD                    0x32 
#define OP_STORE                   0x33
#define OP_RETURN                  0x34

#define OP_BNEW                    0x40
#define OP_BAND                    0x41
#define OP_BOR                     0x42
#define OP_BNOT                    0x43
#define OP_BEQ                     0x44
#define OP_POP                     0x30
#define OP_BXOR                    0x45
        
#define OP_INEW                    0x50
#define OP_IADD                    0x51
#define OP_ISUB                    0x52
#define OP_IMUL                    0x53
#define OP_IDIV                    0x54
#define OP_INEG                    0x55
#define OP_IINC                    0x56
#define OP_IDEC                    0x57
#define OP_IMOD                    0x58
#define OP_IPOW                    0x59
#define OP_IEQ                     0x5A
#define OP_INEQ                    0x5B
#define OP_IGT                     0x5C
#define OP_IGTE                    0x5D
#define OP_ILT                     0x5E
#define OP_ILTE                    0x5F

#define OP_FNEW                    0x60
#define OP_FADD                    0x61
#define OP_FSUB                    0x62
#define OP_FMUL                    0x63
#define OP_FDIV                    0x64
#define OP_FNEG                    0x65
#define OP_FEQ                     0x66
#define OP_FNEQ                    0x67
#define OP_FGT                     0x68
#define OP_FGTE                    0x69
#define OP_FLT                     0x6A
#define OP_FLTE                    0x6B    

#define OP_CNEW                    0x80
#define OP_CCALL                   0x81
#define OP_CTAILCALL               0x82

#define OP_ANEW                    0x90
#define OP_ASIZE                   0x91
#define OP_ACONTAINS               0x92
#define OP_AADD                    0x93
#define OP_AREMOVE                 0x94
#define OP_AGET                    0x95
#define OP_ASET                    0x96

#define OP_MNEW                    0xA0
#define OP_MSIZE                   0xA1
#define OP_MKEYS                   0xA2
#define OP_MVALUES                 0xA3
#define OP_MADD                    0xA4
#define OP_MREMOVE                 0xA5
#define OP_MGET                    0xA6
#define OP_MSET                    0xA7

#endif