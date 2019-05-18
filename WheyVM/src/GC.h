#ifndef GC_H
#define GC_H

#include "Object.h"

struct GC;

void gcRegisterObject(struct Object *object);

#endif