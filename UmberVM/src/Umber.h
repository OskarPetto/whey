#ifndef UMBER_H
#define UMBER_H

#define UMBER_VERSION_MAJOR "0"
#define UMBER_VERSION_MINOR "2"

#define UMBER_VERSION "Umber " UMBER_VERSION_MAJOR "." UMBER_VERSION_MINOR

#define UMBER_CONSTANT_BOOLEAN          0
#define UMBER_CONSTANT_INTEGER          1
#define UMBER_CONSTANT_FLOATING_POINT   2
#define UMBER_CONSTANT_UTF8             3 
#define UMBER_CONSTANT_PROTOTYPE        4
#define UMBER_CONSTANT_ARRAY            5

#define UMBER_OBJECT_NULL               0
#define UMBER_OBJECT_BOOLEAN            1
#define UMBER_OBJECT_INTEGER            2
#define UMBER_OBJECT_FLOATING_POINT     3
#define UMBER_OBJECT_STRING             4
#define UMBER_OBJECT_CLOSURE            5
#define UMBER_OBJECT_VECTOR             6

#define UMBER_OP_HALT                   0
        
#define UMBER_OP_JMP                    1       
#define UMBER_OP_JMPT                   2    
#define UMBER_OP_JMPF                   3
        
#define UMBER_OP_CALL                   10
#define UMBER_OP_TAILCALL               11
#define UMBER_OP_RETURN                 12

#define UMBER_OP_INTEGER                20
#define UMBER_OP_FLOATING_POINT         21
#define UMBER_OP_UTF8                   22
#define UMBER_OP_PROTOTYPE              23
#define UMBER_OP_ARRAY                  24

#define UMBER_OP_POP                    30
#define UMBER_OP_LOAD                   31 
#define UMBER_OP_STORE                  32
        
#define UMBER_OP_IADD                   40
#define UMBER_OP_ISUB                   41
#define UMBER_OP_IMUL                   42
#define UMBER_OP_IDIV                   43
#define UMBER_OP_INEG                   44
#define UMBER_OP_IINC                   45
#define UMBER_OP_IDEC                   46
#define UMBER_OP_IMOD                   47
#define UMBER_OP_IPOW                   48
        
#define UMBER_OP_IEQ                    50
#define UMBER_OP_INEQ                   51
#define UMBER_OP_IGT                    52
#define UMBER_OP_IGTE                   53
#define UMBER_OP_ILT                    54
#define UMBER_OP_ILTE                   55
        
#define UMBER_OP_BAND                   60
#define UMBER_OP_BOR                    61
#define UMBER_OP_BNOT                   62
#define UMBER_OP_BXOR                   63

#endif