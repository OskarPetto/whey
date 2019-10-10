#ifndef INTEGER_H
#define INTEGER_H

#include "../Types.h"

struct Object;
struct Gc;
struct String;

struct Object *integerNew(struct Gc *gc, Integer value);
struct Object *integerToString(struct Gc *gc, struct Object *integer);

void integerFree(struct Gc *gc, struct Object *integer);

uint32_t integerStringCharacterCount(struct Object *integer);
void integerWriteToString(struct Object *integer, struct Object *stringObject, uint32_t *index);

#endif