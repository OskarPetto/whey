#ifndef WFILE_H
#define WFILE_H

#include "Constant.h"
#include "Function.h"

struct WFile
{
    uint8_t constantCount;
    struct Constant *constants;

    uint8_t mainFunctionIndex;

    uint8_t functionCount;
    struct Function *functions;
    
};

#endif