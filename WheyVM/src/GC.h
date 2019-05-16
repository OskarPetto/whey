#ifndef GC_H
#define GC_H

#include "Object.h"

struct GC;

void gcAddObject(struct Object *object);

#endif