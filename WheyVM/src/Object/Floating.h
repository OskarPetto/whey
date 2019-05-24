#ifndef FLOATING_H
#define FLOATING_H

#include "Object.h"
#include "Gc.h"

struct Object *floatingNew(struct Gc *gc, Floating value);
struct Object *floatingToString(struct Gc *gc, Floating floating);

#endif