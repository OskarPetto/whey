#include "../Array.h"
#include "../Floating.h"
#include "../Gc.h"
#include "../Integer.h"
#include "../Map.h"
#include "../Object.h"
#include "../Pair.h"
#include "../String.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void testIntegerNew()
{
    struct Object *integer1 = integerNew(NULL, -5);
    assert(integer1 != NULL);
    assert(integer1->type == OBJECT_TYPE_INTEGER);
    assert(integer1->mark == OBJECT_MARK_TRUE);
    assert(integer1->value.integer_value == -5);
    free(integer1);
    printf("OK\n");
}


int main(int argc, char* argv[])
{
    testIntegerNew();
}