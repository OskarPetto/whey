#ifndef WHEY_H
#define WHEY_H

#define OP_HALT                    0x00
        
#define OP_JMP                     0x01       
#define OP_JMPT                    0x02    
#define OP_JMPF                    0x03
#define OP_RETURN                  0x04

#define OP_POP                     0x10

#define OP_ONEW                    0x20 
#define OP_OCONST                  0x21 
#define OP_OCOPY                   0x22
#define OP_OEQ                     0x23
#define OP_OHASH                   0x24
#define OP_OTOSTRING               0x25

#define OP_BAND                    0x30
#define OP_BOR                     0x31
#define OP_BNOT                    0x32
#define OP_BXOR                    0x33

#define OP_IADD                    0x40
#define OP_ISUB                    0x41
#define OP_IMUL                    0x42
#define OP_IDIV                    0x43
#define OP_INEG                    0x44
#define OP_IINC                    0x45
#define OP_IDEC                    0x46
#define OP_IMOD                    0x47
#define OP_IPOW                    0x48
#define OP_IGT                     0x49
#define OP_IGTE                    0x4A
#define OP_ILT                     0x4B
#define OP_ILTE                    0x4C

#define OP_FADD                    0x50
#define OP_FSUB                    0x51
#define OP_FMUL                    0x52
#define OP_FDIV                    0x53
#define OP_FNEG                    0x54
#define OP_FGT                     0x55
#define OP_FGTE                    0x56
#define OP_FLT                     0x57
#define OP_FLTE                    0x58    

#define OP_LLOAD                   0x60 
#define OP_LSTORE                  0x61
#define OP_LAPPLY                  0x62
#define OP_LTAILAPPLY              0x63
#define OP_LBEFORE                 0x64
#define OP_LAFTER                  0x65

#define OP_ASIZE                   0x70
#define OP_AGET                    0x71
#define OP_ASET                    0x72
#define OP_AINSERT                 0x73
#define OP_AREMOVE                 0x74
#define OP_AINSERTALL              0x75
#define OP_AFOREACH                0x76
#define OP_AMAP                    0x77
#define OP_AFILTER                 0x78
#define OP_AREDUCE                 0x79

#define OP_MSIZE                   0x80
#define OP_MGET                    0x81
#define OP_MPUT                    0x82
#define OP_MREMOVE                 0x83
#define OP_MPUTALL                 0x84
#define OP_MHASKEY                 0x85
#define OP_MENTRIES                0x86

#define OP_PGETFST                 0x90
#define OP_PGETSND                 0x91
#define OP_PSETFST                 0x92
#define OP_PSETSND                 0x93


#endif