#ifndef BYTE_CODE_H
#define BYTE_CODE_H

#include <stdint.h>
#include "Constant.h"
#include "Function.h"

struct WcFile
{
    uint32_t byteCount;

    uint16_t constantCount;
    struct Constant **constants;

    uint16_t functionCount;
    struct Function **functions;
};

struct WcFile *wcFileNew(char *fileName);

struct Constant *wcFileGetConstant(struct WcFile *wcFile, uint16_t constantIndex);

struct Function *wcFileGetFunction(struct WcFile *wcFile, uint16_t functionIndex);

void wcFileFree(struct WcFile *wcFile);

#endif