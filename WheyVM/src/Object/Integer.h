#ifndef INTEGER_H
#define INTEGER_H

#include "Object.h"
#include "Gc.h"

struct Object *integerNew(struct Gc *gc, Integer value);
struct Object *integerToString(struct Gc *gc, Integer integer);

#endif