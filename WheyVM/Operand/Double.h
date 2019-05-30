#ifndef DOUBLE_H
#define DOUBLE_H

#include "Types.h"

struct Object;
struct Gc;

struct Object *doubleNew(struct Gc *gc, Double value);
struct Object *doubleToString(struct Gc *gc, Double floating);

#endif