#ifndef FLOATING_H
#define FLOATING_H

#include "Types.h"

struct Object;
struct Gc;

struct Object *floatingNew(struct Gc *gc, Floating value);
struct Object *floatingToString(struct Gc *gc, Floating floating);

#endif