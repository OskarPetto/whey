#include "../Array.h"
#include "../Floating.h"
#include "../Gc.h"
#include "../Integer.h"
#include "../Map.h"
#include "../Object.h"
#include "../Pair.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


void testArrayNew()
{
    printf("testArrayNew: ");

    struct Object *array1 = arrayNew(NULL, 14);
    assert(array1->type == OBJECT_TYPE_ARRAY);
    assert(array1->mark == OBJECT_MARK_TRUE);
    assert(array1->value.array != NULL);
    assert(array1->value.array->objectCount == 14);
    assert(array1->value.array->slotCount == 22);
    array1->value.array->objects[0] = NULL;
    assert(array1->value.array->objects[0] == NULL);

    struct Object *array2 = arrayNew(NULL, 0);
    assert(array2->type == OBJECT_TYPE_ARRAY);
    assert(array2->mark == OBJECT_MARK_TRUE);
    assert(array2->value.array != NULL);
    assert(array2->value.array->objectCount == 0);
    assert(array2->value.array->slotCount == 1);

    array1->value.array->objects[13] = array2;
    assert(array1->value.array->objects[13] == array2);

    free(array1->value.array->objects);
    free(array2->value.array->objects);

    free(array1->value.array);
    free(array2->value.array);

    free(array1);
    free(array2);

    printf("OK\n");
}

void testArraySize()
{
    printf("testArraySize: ");
    struct Object *array1 = arrayNew(NULL, 14);
    assert(arraySize(array1->value.array) == 14);

    struct Object *array2 = arrayNew(NULL, 0);
    assert(arraySize(array2->value.array) == 0);

    free(array1->value.array->objects);
    free(array2->value.array->objects);

    free(array1->value.array);
    free(array2->value.array);

    free(array1);
    free(array2);

    printf("OK\n");
}

void testArrayGet()
{
    printf("testArrayGet: ");

    struct Object *array = arrayNew(NULL, 14);
    struct Object *integer = integerNew(NULL, -132);

    array->value.array->objects[10] = integer;

    assert(arrayGet(array->value.array, 10) == integer);

    free(array->value.array->objects);

    free(array->value.array);

    free(array);
    free(integer);

    printf("OK\n");
}

void testArraySet()
{
    printf("testArraySet: ");

    struct Object *array = arrayNew(NULL, 14);
    struct Object *integer = integerNew(NULL, -132);

    array->value.array->objects[10] = integer;

    assert(arraySet(array->value.array, 10, NULL) == integer);
    assert(arrayGet(array->value.array, 10) == NULL);

    free(array->value.array->objects);

    free(array->value.array);

    free(array);
    free(integer);

    printf("OK\n");
}

void testArrayInsert()
{
    printf("testArrayInsert: ");
    struct Object *array = arrayNew(NULL, 0);
    struct Object *integer1 = integerNew(NULL, 97);
    struct Object *integer2 = integerNew(NULL, 98);
    struct Object *integer3 = integerNew(NULL, 99);

    assert(array->value.array->objectCount == 0);
    assert(array->value.array->slotCount == 1);

    arrayInsert(array->value.array, 0, integer1);
    arrayInsert(array->value.array, 0, integer2);
    arrayInsert(array->value.array, 0, integer3);

    assert(array->value.array->objectCount == 3);
    assert(array->value.array->slotCount == 4);

    assert(array->value.array->objects[0] == integer3);
    assert(array->value.array->objects[1] == integer2);
    assert(array->value.array->objects[2] == integer1);

    arrayInsert(array->value.array, 0, integer1);
    arrayInsert(array->value.array, 1, integer2);
    arrayInsert(array->value.array, 2, integer3);

    assert(array->value.array->objectCount == 6);
    assert(array->value.array->slotCount == 8);

    assert(array->value.array->objects[0] == integer1);
    assert(array->value.array->objects[1] == integer2);
    assert(array->value.array->objects[2] == integer3);
    assert(array->value.array->objects[3] == integer3);
    assert(array->value.array->objects[4] == integer2);
    assert(array->value.array->objects[5] == integer1);

    arrayInsert(array->value.array, 6, integer2);

    assert(array->value.array->objectCount == 7);
    assert(array->value.array->slotCount == 8);
    assert(array->value.array->objects[6] == integer2);

    free(array->value.array->objects);
    free(array->value.array);
    free(array);

    free(integer1);
    free(integer2);
    free(integer3);

    printf("OK\n");
}

void testArrayInsertAll()
{
    printf("testArrayInsertAll: ");
    struct Object *array1 = arrayNew(NULL, 3);
    struct Object *array2 = arrayNew(NULL, 2);
    struct Object *array3 = arrayNew(NULL, 0);
    struct Object *integer1 = integerNew(NULL, 97);
    struct Object *integer2 = integerNew(NULL, 98);
    struct Object *integer3 = integerNew(NULL, 99);

    array1->value.array->objects[0] = integer1;
    array1->value.array->objects[1] = integer2;
    array1->value.array->objects[2] = integer3;

    array2->value.array->objects[0] = integer3;
    array2->value.array->objects[1] = integer2;

    assert(array1->value.array->objectCount == 3);
    assert(array1->value.array->slotCount == 5);
    assert(array2->value.array->objectCount == 2);
    assert(array2->value.array->slotCount == 4);

    arrayInsertAll(array1->value.array, 0, array2->value.array);

    assert(array1->value.array->objectCount == 5);
    assert(array1->value.array->slotCount == 5);
    assert(array2->value.array->objectCount == 2);
    assert(array2->value.array->slotCount == 4);

    assert(array1->value.array->objects[0] == integer3);
    assert(array1->value.array->objects[1] == integer2);
    assert(array1->value.array->objects[2] == integer1);
    assert(array1->value.array->objects[3] == integer2);
    assert(array1->value.array->objects[4] == integer3);

    arrayInsertAll(array1->value.array, 3, array1->value.array);

    assert(array1->value.array->objectCount == 10);
    assert(array1->value.array->slotCount == 16);
    
    assert(array1->value.array->objects[0] == integer3);
    assert(array1->value.array->objects[1] == integer2);
    assert(array1->value.array->objects[2] == integer1);
    assert(array1->value.array->objects[3] == integer3);
    assert(array1->value.array->objects[4] == integer2);
    assert(array1->value.array->objects[5] == integer1);
    assert(array1->value.array->objects[6] == integer2);
    assert(array1->value.array->objects[7] == integer3);
    assert(array1->value.array->objects[8] == integer2);
    assert(array1->value.array->objects[9] == integer3);

    arrayInsertAll(array1->value.array, 1, array2->value.array);

    assert(array1->value.array->objectCount == 12);
    assert(array1->value.array->slotCount == 16);
    
    assert(array1->value.array->objects[0] == integer3);
    assert(array1->value.array->objects[1] == integer3);
    assert(array1->value.array->objects[2] == integer2);
    assert(array1->value.array->objects[3] == integer2);
    assert(array1->value.array->objects[4] == integer1);
    assert(array1->value.array->objects[5] == integer3);
    assert(array1->value.array->objects[6] == integer2);
    assert(array1->value.array->objects[7] == integer1);
    assert(array1->value.array->objects[8] == integer2);
    assert(array1->value.array->objects[9] == integer3);
    assert(array1->value.array->objects[10] == integer2);
    assert(array1->value.array->objects[11] == integer3);

    arrayInsertAll(array2->value.array, 2, array2->value.array);

    assert(array2->value.array->objectCount == 4);
    assert(array2->value.array->slotCount == 4);

    assert(array2->value.array->objects[0] == integer3);
    assert(array2->value.array->objects[1] == integer2);
    assert(array2->value.array->objects[2] == integer3);
    assert(array2->value.array->objects[3] == integer2);

    arrayInsertAll(array2->value.array, 2, array3->value.array);

    assert(array2->value.array->objectCount == 4);
    assert(array2->value.array->slotCount == 4);
    assert(array3->value.array->objectCount == 0);
    assert(array3->value.array->slotCount == 1);

    assert(array2->value.array->objects[0] == integer3);
    assert(array2->value.array->objects[1] == integer2);
    assert(array2->value.array->objects[2] == integer3);
    assert(array2->value.array->objects[3] == integer2);

    arrayInsertAll(array2->value.array, 4, array1->value.array);

    assert(array2->value.array->objectCount == 16);
    assert(array2->value.array->slotCount == 25);
    
    assert(array2->value.array->objects[0] == integer3);
    assert(array2->value.array->objects[1] == integer2);
    assert(array2->value.array->objects[2] == integer3);
    assert(array2->value.array->objects[3] == integer2);
    assert(array2->value.array->objects[4] == integer3);
    assert(array2->value.array->objects[5] == integer3);
    assert(array2->value.array->objects[6] == integer2);
    assert(array2->value.array->objects[7] == integer2);
    assert(array2->value.array->objects[8] == integer1);
    assert(array2->value.array->objects[9] == integer3);
    assert(array2->value.array->objects[10] == integer2);
    assert(array2->value.array->objects[11] == integer1);
    assert(array2->value.array->objects[12] == integer2);
    assert(array2->value.array->objects[13] == integer3);
    assert(array2->value.array->objects[14] == integer2);
    assert(array2->value.array->objects[15] == integer3);

    free(array1->value.array->objects);
    free(array1->value.array);
    free(array1);

    free(array2->value.array->objects);
    free(array2->value.array);
    free(array2);

    free(array3->value.array->objects);
    free(array3->value.array);
    free(array3);

    free(integer1);
    free(integer2);
    free(integer3);

    printf("OK\n");
}

void testArrayRemove()
{
    printf("testArrayRemove: ");
    struct Object *array1 = arrayNew(NULL, 3);
    struct Object *integer1 = integerNew(NULL, 97);
    struct Object *integer2 = integerNew(NULL, 98);
    struct Object *integer3 = integerNew(NULL, 99);

    array1->value.array->objects[0] = integer1;
    array1->value.array->objects[1] = integer2;
    array1->value.array->objects[2] = integer3;

    assert(arrayRemove(array1->value.array, 1) == integer2);

    assert(array1->value.array->objectCount == 2);
    assert(array1->value.array->slotCount == 5);

    assert(array1->value.array->objects[0] == integer1);
    assert(array1->value.array->objects[1] == integer3);

    assert(arrayRemove(array1->value.array, 0) == integer1);

    assert(array1->value.array->objectCount == 1);
    assert(array1->value.array->slotCount == 5);

    assert(array1->value.array->objects[0] == integer3);

    assert(arrayRemove(array1->value.array, 0) == integer3);

    assert(array1->value.array->objectCount == 0);
    assert(array1->value.array->slotCount == 5);

    free(array1->value.array->objects);
    free(array1->value.array);
    free(array1);

    free(integer1);
    free(integer2);
    free(integer3);

    printf("OK\n");
}

void testArrayCopy()
{
    printf("testArrayCopy: ");
    struct Object *array1 = arrayNew(NULL, 3);
    struct Object *integer1 = integerNew(NULL, 97);
    struct Object *integer2 = integerNew(NULL, 98);
    struct Object *integer3 = integerNew(NULL, 99);

    array1->value.array->objects[0] = integer1;
    array1->value.array->objects[1] = integer2;
    array1->value.array->objects[2] = integer3;

    struct Object *array2 = arrayCopy(NULL, array1->value.array);

    assert(array2->value.array->objectCount == array1->value.array->objectCount);
    assert(array2->value.array->objects[0] != array1->value.array->objects[0]);
    assert(array2->value.array->objects[1] != array1->value.array->objects[1]);
    assert(array2->value.array->objects[2] != array1->value.array->objects[2]);
    assert(array2->value.array->objects[0]->type == OBJECT_TYPE_INTEGER);
    assert(array2->value.array->objects[1]->type == OBJECT_TYPE_INTEGER);
    assert(array2->value.array->objects[2]->type == OBJECT_TYPE_INTEGER);
    assert(array2->value.array->objects[0]->value.integer_value == 97);
    assert(array2->value.array->objects[1]->value.integer_value == 98);
    assert(array2->value.array->objects[2]->value.integer_value == 99);

    integer1->value.integer_value = 55;
    assert(array2->value.array->objects[0]->value.integer_value == 97);

    free(array2->value.array->objects[0]);
    free(array2->value.array->objects[1]);
    free(array2->value.array->objects[2]);

    free(integer1);
    free(integer2);
    free(integer3);

    free(array2->value.array->objects);
    free(array2->value.array);
    free(array2);

    free(array1->value.array->objects);
    free(array1->value.array);
    free(array1);

    printf("OK\n");
}

void testArrayEquals()
{
    printf("testArrayEquals: ");
    struct Object *array1 = arrayNew(NULL, 3);
    struct Object *integer1 = integerNew(NULL, 97);
    struct Object *integer2 = integerNew(NULL, 98);
    struct Object *integer3 = integerNew(NULL, 99);

    array1->value.array->objects[0] = integer1;
    array1->value.array->objects[1] = integer2;
    array1->value.array->objects[2] = integer3;

    assert(arrayEquals(array1->value.array, array1->value.array) == 1);

    struct Object *array2 = arrayCopy(NULL, array1->value.array);
    
    assert(arrayEquals(array1->value.array, array2->value.array) == 1);

    array2->value.array->objects[0]->value.integer_value = -1;

    assert(arrayEquals(array1->value.array, array2->value.array) == 0);

    array2->value.array->objects[0]->value.integer_value = 97;

    assert(arrayEquals(array1->value.array, array2->value.array) == 1);

    free(array2->value.array->objects[0]);
    free(array2->value.array->objects[1]);
    free(array2->value.array->objects[2]);

    free(integer1);
    free(integer2);
    free(integer3);

    free(array2->value.array->objects);
    free(array2->value.array);
    free(array2);

    free(array1->value.array->objects);
    free(array1->value.array);
    free(array1);

    printf("OK\n");
}

void testArrayHash()
{
    printf("testArrayHash: ");
    struct Object *array1 = arrayNew(NULL, 3);
    struct Object *integer1 = integerNew(NULL, 97);
    struct Object *integer2 = integerNew(NULL, 98);
    struct Object *integer3 = integerNew(NULL, 99);

    array1->value.array->objects[0] = integer1;
    array1->value.array->objects[1] = integer2;
    array1->value.array->objects[2] = integer3;

    assert(arrayHash(array1->value.array) == arrayHash(array1->value.array));

    struct Object *array2 = arrayCopy(NULL, array1->value.array);
    
    assert(arrayHash(array1->value.array) == arrayHash(array2->value.array));

    struct Object *array3 = arrayNew(NULL, 0);

    assert(arrayHash(array3->value.array) == 1);

    free(array2->value.array->objects[0]);
    free(array2->value.array->objects[1]);
    free(array2->value.array->objects[2]);

    free(integer1);
    free(integer2);
    free(integer3);

    free(array3->value.array->objects);
    free(array3->value.array);
    free(array3);

    free(array2->value.array->objects);
    free(array2->value.array);
    free(array2);

    free(array1->value.array->objects);
    free(array1->value.array);
    free(array1);
    printf("OK\n");
}

void testArrayToString()
{
    printf("testArrayToString: ");
    struct Object *array1 = arrayNew(NULL, 3);
    struct Object *integer1 = integerNew(NULL, 7);
    struct Object *integer2 = integerNew(NULL, 98);
    struct Object *integer3 = integerNew(NULL, 121299);

    array1->value.array->objects[0] = integer1;
    array1->value.array->objects[1] = integer2;
    array1->value.array->objects[2] = integer3;

    struct Object *string = arrayToString(NULL, array1->value.array);

    assert(string->value.array->objectCount == 13);

    assert(string->value.array->objects[0]->value.integer_value == '[');
    assert(string->value.array->objects[1]->value.integer_value == '7');
    assert(string->value.array->objects[2]->value.integer_value == ',');
    assert(string->value.array->objects[3]->value.integer_value == '9');
    assert(string->value.array->objects[4]->value.integer_value == '8');
    assert(string->value.array->objects[5]->value.integer_value == ',');
    assert(string->value.array->objects[6]->value.integer_value == '1');
    assert(string->value.array->objects[7]->value.integer_value == '2');
    assert(string->value.array->objects[8]->value.integer_value == '1');
    assert(string->value.array->objects[9]->value.integer_value == '2');
    assert(string->value.array->objects[10]->value.integer_value == '9');
    assert(string->value.array->objects[11]->value.integer_value == '9');
    assert(string->value.array->objects[12]->value.integer_value == ']');


    free(string->value.array->objects[0]);
    free(string->value.array->objects[1]);
    free(string->value.array->objects[2]);

    free(integer1);
    free(integer2);
    free(integer3);

    free(array1->value.array->objects);
    free(array1->value.array);
    free(array1);

    free(string->value.array->objects);
    free(string->value.array);
    free(string);

    printf("OK\n");
}

void testArrayMark()
{
    printf("testArrayMark: ");
    printf("OK\n");
}

void testArrayFree()
{
    printf("testArrayFree: ");
    printf("OK\n");
}

void testStringNew()
{
    printf("testStringNew: ");
    printf("OK\n");
}

void testStringFromArray()
{
    printf("testStringFromArray: ");
    printf("OK\n");
}

void testStringToArray()
{
    printf("testStringToArray: ");
    printf("OK\n");
}

void testStringCompare()
{
    printf("testStringCompare: ");
    printf("OK\n");
}

void testStringCopy()
{
    printf("testStringCopy: ");
    printf("OK\n");
}

void testStringEquals()
{
    printf("testStringEquals: ");
    printf("OK\n");
}

void testStringHash()
{
    printf("testStringHash: ");
    printf("OK\n");
}

void testStringAppendCharacter()
{
    printf("testStringAppendCharacter: ");
    struct Object *array1 = arrayNew(NULL, 0);
    Integer integer1 = 97;
    Integer integer2 = 98;
    Integer integer3 = 99;

    stringAppendCharacter(array1->value.array, integer2);

    assert(array1->value.array->objectCount == 1);
    assert(array1->value.array->slotCount == 1);

    assert(array1->value.array->objects[0]->value.integer_value == integer2);

    stringAppendCharacter(array1->value.array, integer1);
    stringAppendCharacter(array1->value.array, integer3);

    assert(array1->value.array->objectCount == 3);
    assert(array1->value.array->slotCount == 4);

    assert(array1->value.array->objects[1]->value.integer_value == integer1);
    assert(array1->value.array->objects[2]->value.integer_value == integer3);

    free(array1->value.array->objects[0]);
    free(array1->value.array->objects[1]);
    free(array1->value.array->objects[2]);

    free(array1->value.array->objects);
    free(array1->value.array);
    free(array1);

    printf("OK\n");
}

void testStringFree()
{
    printf("testStringFree: ");
    printf("OK\n");
}

void testFloatingNew()
{
    printf("testFloatingNew: ");
    printf("OK\n");
}

void testFloatingToString()
{
    printf("testFloatingToString: ");
    printf("OK\n");
}

void testGcNew()
{
    printf("testGcNew: ");
    printf("OK\n");
}

void testGcRegisterObject()
{
    printf("testGcRegisterObject: ");
    printf("OK\n");
}

void testGcSweep()
{
    printf("testGcSweep: ");
    printf("OK\n");
}

void testGcFree()
{
    printf("testGcFree: ");
    printf("OK\n");
}

void testIntegerNew()
{
    printf("testIntegerNew: ");
    struct Object *integer1 = integerNew(NULL, -5);
    assert(integer1->type == OBJECT_TYPE_INTEGER);
    assert(integer1->mark == OBJECT_MARK_TRUE);
    assert(integer1->value.integer_value == -5);
    free(integer1);
    printf("OK\n");
}

void testIntegerToString()
{
    printf("testIntegerToString: ");
    printf("OK\n");
}

void testMapNew()
{
    printf("testMapNew: ");
    printf("OK\n");
}

void testMapSize()
{
    printf("testMapSize: ");
    printf("OK\n");
}

void testMapGet()
{
    printf("testMapGet: ");
    printf("OK\n");
}

void testMapPut()
{
    printf("testMapPut: ");
    printf("OK\n");
}

void testMapPutAll()
{
    printf("testMapPutAll: ");
    printf("OK\n");
}

void testMapRemove()
{
    printf("testMapRemove: ");
    printf("OK\n");
}

void testMapHasKey()
{
    printf("testMapHasKey: ");
    printf("OK\n");
}

void testMapEntries()
{
    printf("testMapEntries: ");
    printf("OK\n");
}

void testMapCopy()
{
    printf("testMapCopy: ");
    printf("OK\n");
}

void testMapEquals()
{
    printf("testMapEquals: ");
    printf("OK\n");
}

void testMapHash()
{
    printf("testMapHash: ");
    printf("OK\n");
}

void testMapToString()
{
    printf("testMapToString: ");
    printf("OK\n");
}

void testMapMark()
{
    printf("testMapMark: ");
    printf("OK\n");
}

void testMapFree()
{
    printf("testMapFree: ");
    printf("OK\n");
}

void testObjectCopy()
{
    printf("testObjectCopy: ");
    printf("OK\n");
}

void testObjectEquals()
{
    printf("testObjectEquals: ");
    printf("OK\n");
}

void testObjectHash()
{
    printf("testObjectHash: ");
    printf("OK\n");
}

void testObjectToString()
{
    printf("testObjectToString: ");
    printf("OK\n");
}

void testObjectNew()
{
    printf("testObjectNew: ");
    printf("OK\n");
}

void testObjectMark()
{
    printf("testObjectMark: ");
    printf("OK\n");
}

void testObjectFree()
{
    printf("testObjectFree: ");
    printf("OK\n");
}

void testPairNew()
{
    printf("testPairNew: ");
    printf("OK\n");
}

void testPairGetFirst()
{
    printf("testPairGetFirst: ");
    printf("OK\n");
}

void testPairGetSecond()
{
    printf("testPairGetSecond: ");
    printf("OK\n");
}

void testPairSetFirst()
{
    printf("testPairSetFirst: ");
    printf("OK\n");
}

void testPairSetSecond()
{
    printf("testPairSetSecond: ");
    printf("OK\n");
}

void testPairCopy()
{
    printf("testPairCopy: ");
    printf("OK\n");
}

void testPairEquals()
{
    printf("testPairEquals: ");
    printf("OK\n");
}

void testPairHash()
{
    printf("testPairHash: ");
    printf("OK\n");
}

void testPairToString()
{
    printf("testPairToString: ");
    printf("OK\n");
}

void testPairMark()
{
    printf("testPairMark: ");
    printf("OK\n");
}

int main(int argc, char* argv[])
{
    testArrayNew();
    testArraySize();
    testArrayGet();
    testArraySet();
    testArrayInsert();
    testArrayInsertAll();
    testArrayRemove();
    testArrayCopy();
    testArrayEquals();
    testArrayHash();
    testArrayToString();
    testArrayMark();
    testArrayFree();
    testStringNew();
    testStringFromArray();
    testStringToArray();
    testStringCompare();
    testStringCopy();
    testStringEquals();
    testStringHash();
    testStringAppendCharacter();
    testStringFree();
    testFloatingNew();
    testFloatingToString();
    testGcNew();
    testGcRegisterObject();
    testGcSweep();
    testGcFree();
    testIntegerNew();
    testIntegerToString();
    testMapNew();
    testMapSize();
    testMapGet();
    testMapPut();
    testMapPutAll();
    testMapRemove();
    testMapHasKey();
    testMapEntries();
    testMapCopy();
    testMapEquals();
    testMapHash();
    testMapToString();
    testMapMark();
    testMapFree();
    testObjectCopy();
    testObjectEquals();
    testObjectHash();
    testObjectToString();
    testObjectNew();
    testObjectMark();
    testObjectFree();
    testPairNew();
    testPairGetFirst();
    testPairGetSecond();
    testPairSetFirst();
    testPairSetSecond();
    testPairCopy();
    testPairEquals();
    testPairHash();
    testPairToString();
    testPairMark();
    printf("All tests passed.\n");
}