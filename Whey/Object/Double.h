#ifndef DOUBLE_H
#define DOUBLE_H

#include "../Types.h"

struct Object;
struct String;
struct Gc;

struct Object *doubleNew(struct Gc *gc, Double value);
struct Object *doubleToString(struct Gc *gc, struct Object *doble);

void doubleFree(struct Gc *gc, struct Object *doble);

uint32_t doubleStringCharacterCount(struct Object *doble);
void doubleWriteToString(struct Object *doble, struct Object *stringObject, uint32_t *index);

#endif