#ifndef UFILE_H
#define UFILE_H

#include "Constant.h"
#include "Prototype.h"

struct UFile
{
    uint16_t constantCount;
    struct Constant *constants;

    uint16_t exportPrototypeIndex;

    uint16_t prototypeCount;
    struct Prototype *prototypes;
    
};

#endif