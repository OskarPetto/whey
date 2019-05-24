#ifndef INTEGER_H
#define INTEGER_H

#include "Types.h"

struct Object;
struct Gc;

struct Object *integerNew(struct Gc *gc, Integer value);
struct Object *integerToString(struct Gc *gc, Integer integer);

#endif