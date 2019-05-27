#include "../Array.h"
#include "../Double.h"
#include "../Gc.h"
#include "../Integer.h"
#include "../Map.h"
#include "../Object.h"
#include "../Pair.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static struct Object *getComplexObject(struct Gc *gc)
{
    struct Object *mapNameToPersonWithAdresses = mapNew(gc);

    struct Object *nameKey1 = stringNew(gc, "Willi");
    struct Object *nameKey2 = stringNew(gc, "Otto");
    struct Object *nameKey3 = stringNew(gc, "Lisa");

    struct Object *personNameKey = stringNew(gc, "name");
    struct Object *personAgeKey = stringNew(gc, "age");
    struct Object *personHeightKey = stringNew(gc, "height");

    struct Object *person1 = mapNew(gc);
    struct Object *person1NameValue = stringNew(gc, "Willi");
    struct Object *person1AgeValue = integerNew(gc, 25);
    struct Object *person1HeightValue = doubleNew(gc, 1.81);
    mapPut(person1->value.map, personNameKey, person1NameValue);
    mapPut(person1->value.map, personAgeKey, person1AgeValue);
    mapPut(person1->value.map, personHeightKey, person1HeightValue);

    struct Object *person2 = mapNew(gc);
    struct Object *person2NameValue = stringNew(gc, "Otto");
    struct Object *person2AgeValue = integerNew(gc, 64);
    struct Object *person2HeightValue = doubleNew(gc, 1.65);
    mapPut(person2->value.map, personNameKey, person2NameValue);
    mapPut(person2->value.map, personAgeKey, person2AgeValue);
    mapPut(person2->value.map, personHeightKey, person2HeightValue);

    struct Object *person3 = mapNew(gc);
    struct Object *person3NameValue = stringNew(gc, "Lisa");
    struct Object *person3AgeValue = integerNew(gc, 33);
    struct Object *person3HeightValue = doubleNew(gc, 1.68);
    mapPut(person3->value.map, personNameKey, person3NameValue);
    mapPut(person3->value.map, personAgeKey, person3AgeValue);
    mapPut(person3->value.map, personHeightKey, person3HeightValue);

    struct Object *address1 = mapNew(gc);
    struct Object *address1StreetKey = stringNew(gc, "street");
    struct Object *address1NumberKey = stringNew(gc, "number");
    struct Object *address1StreetValue = stringNew(gc, "Hausdorf");
    struct Object *address1NumberValue = integerNew(gc, 121);
    mapPut(address1->value.map, address1StreetKey, address1StreetValue);
    mapPut(address1->value.map, address1NumberKey, address1NumberValue);

    struct Object *address2 = mapNew(gc);
    struct Object *address2StreetKey = stringNew(gc, "street");
    struct Object *address2NumberKey = stringNew(gc, "number");
    struct Object *address2StreetValue = stringNew(gc, "Hausdorf");
    struct Object *address2NumberValue = integerNew(gc, 122);
    mapPut(address2->value.map, address2StreetKey, address2StreetValue);
    mapPut(address2->value.map, address2NumberKey, address2NumberValue);

    struct Object *address3 = mapNew(gc);
    struct Object *address3StreetKey = stringNew(gc, "street");
    struct Object *address3NumberKey = stringNew(gc, "number");
    struct Object *address3StreetValue = stringNew(gc, "Siebenseiten");
    struct Object *address3NumberValue = integerNew(gc, 32);
    mapPut(address3->value.map, address3StreetKey, address3StreetValue);
    mapPut(address3->value.map, address3NumberKey, address3NumberValue);

    struct Object *person1AddressArray = arrayNew(gc, 2);

    person1AddressArray->value.array->objects[0] = address1;
    person1AddressArray->value.array->objects[1] = address2;

    struct Object *person2AddressArray = arrayNew(gc, 1);

    person2AddressArray->value.array->objects[0] = address3;

    struct Object *person3AddressArray = arrayNew(gc, 0);

    struct Object *person1Pair = pairNew(gc, person1, person1AddressArray);
    struct Object *person2Pair = pairNew(gc, person2, person2AddressArray);
    struct Object *person3Pair = pairNew(gc, person3, person3AddressArray);

    mapPut(mapNameToPersonWithAdresses->value.map, nameKey1, person1Pair);
    mapPut(mapNameToPersonWithAdresses->value.map, nameKey2, person2Pair);
    mapPut(mapNameToPersonWithAdresses->value.map, nameKey3, person3Pair);

    return mapNameToPersonWithAdresses;
}

void testArrayNew()
{
    printf("testArrayNew: ");

    struct Object *array1 = arrayNew(NULL, 14);
    assert(array1->type == OBJECT_TYPE_ARRAY);
    assert(array1->mark == OBJECT_MARK_FALSE);
    assert(array1->value.array != NULL);
    assert(array1->value.array->objectCount == 14);
    assert(array1->value.array->slotCount == 22);
    array1->value.array->objects[0] = NULL;
    assert(array1->value.array->objects[0] == NULL);

    struct Object *array2 = arrayNew(NULL, 0);
    assert(array2->type == OBJECT_TYPE_ARRAY);
    assert(array2->mark == OBJECT_MARK_FALSE);
    assert(array2->value.array != NULL);
    assert(array2->value.array->objectCount == 0);
    assert(array2->value.array->slotCount == 1);

    array1->value.array->objects[13] = array2;
    assert(array1->value.array->objects[13] == array2);

    objectFree(array1);
    objectFree(array2);

    printf("OK\n");
}

void testArraySize()
{
    printf("testArraySize: ");
    struct Object *array1 = arrayNew(NULL, 14);
    assert(arraySize(array1->value.array) == 14);

    struct Object *array2 = arrayNew(NULL, 0);
    assert(arraySize(array2->value.array) == 0);

    objectFree(array1);
    objectFree(array2);

    printf("OK\n");
}

void testArrayGet()
{
    printf("testArrayGet: ");

    struct Object *array = arrayNew(NULL, 14);
    struct Object *integer = integerNew(NULL, -132);

    array->value.array->objects[10] = integer;

    assert(arrayGet(array->value.array, 10) == integer);

    objectFree(array);
    objectFree(integer);

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

    objectFree(array);
    objectFree(integer);

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

    objectFree(array);

    objectFree(integer1);
    objectFree(integer2);
    objectFree(integer3);

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

    objectFree(array1);
    objectFree(array2);
    objectFree(array3);

    objectFree(integer1);
    objectFree(integer2);
    objectFree(integer3);

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

    objectFree(array1);

    objectFree(integer1);
    objectFree(integer2);
    objectFree(integer3);

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
    assert(array2->value.array->objects[0]->value.integerValue == 97);
    assert(array2->value.array->objects[1]->value.integerValue == 98);
    assert(array2->value.array->objects[2]->value.integerValue == 99);

    integer1->value.integerValue = 55;
    assert(array2->value.array->objects[0]->value.integerValue == 97);

    objectFree(array2->value.array->objects[0]);
    objectFree(array2->value.array->objects[1]);
    objectFree(array2->value.array->objects[2]);

    objectFree(integer1);
    objectFree(integer2);
    objectFree(integer3);

    objectFree(array2);
    objectFree(array1);

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

    array2->value.array->objects[0]->value.integerValue = -1;

    assert(arrayEquals(array1->value.array, array2->value.array) == 0);

    array2->value.array->objects[0]->value.integerValue = 97;

    assert(arrayEquals(array1->value.array, array2->value.array) == 1);

    objectFree(array2->value.array->objects[0]);
    objectFree(array2->value.array->objects[1]);
    objectFree(array2->value.array->objects[2]);

    objectFree(integer1);
    objectFree(integer2);
    objectFree(integer3);

    objectFree(array2);
    objectFree(array1);

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

    objectFree(array2->value.array->objects[0]);
    objectFree(array2->value.array->objects[1]);
    objectFree(array2->value.array->objects[2]);

    objectFree(integer1);
    objectFree(integer2);
    objectFree(integer3);

    objectFree(array3);
    objectFree(array2);
    objectFree(array1);

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

    struct Object *string1 = arrayToString(NULL, array1->value.array);

    assert(string1->value.array->objectCount == 13);

    assert(string1->value.array->objects[0]->value.integerValue == '[');
    assert(string1->value.array->objects[1]->value.integerValue == '7');
    assert(string1->value.array->objects[2]->value.integerValue == ',');
    assert(string1->value.array->objects[3]->value.integerValue == '9');
    assert(string1->value.array->objects[4]->value.integerValue == '8');
    assert(string1->value.array->objects[5]->value.integerValue == ',');
    assert(string1->value.array->objects[6]->value.integerValue == '1');
    assert(string1->value.array->objects[7]->value.integerValue == '2');
    assert(string1->value.array->objects[8]->value.integerValue == '1');
    assert(string1->value.array->objects[9]->value.integerValue == '2');
    assert(string1->value.array->objects[10]->value.integerValue == '9');
    assert(string1->value.array->objects[11]->value.integerValue == '9');
    assert(string1->value.array->objects[12]->value.integerValue == ']');

    struct Object *array2 = arrayNew(NULL, 0);

    struct Object *string2 = arrayToString(NULL, array2->value.array);

    assert(string2->value.array->objectCount == 2);

    assert(string2->value.array->objects[0]->value.integerValue == '[');
    assert(string2->value.array->objects[1]->value.integerValue == ']');

    objectFree(string1);
    objectFree(string2);
    
    objectFree(integer1);
    objectFree(integer2);
    objectFree(integer3);

    objectFree(array1);
    objectFree(array2);

    printf("OK\n");
}

void testArrayMark()
{
    printf("testArrayMark: ");
    struct Object *array1 = arrayNew(NULL, 3);
    struct Object *array2 = arrayNew(NULL, 0);
    struct Object *integer1 = integerNew(NULL, 7);
    struct Object *integer2 = integerNew(NULL, 98);
    struct Object *integer3 = integerNew(NULL, 121299);

    array1->value.array->objects[0] = integer1;
    array1->value.array->objects[1] = integer2;
    array1->value.array->objects[2] = integer3;

    objectMark(array1);

    assert(array1->mark == OBJECT_MARK_TRUE);
    assert(integer1->mark == OBJECT_MARK_TRUE);
    assert(integer2->mark == OBJECT_MARK_TRUE);
    assert(integer3->mark == OBJECT_MARK_TRUE);
    assert(integer3->mark == OBJECT_MARK_TRUE);

    integer2->mark = OBJECT_MARK_FALSE;

    objectMark(array1);

    assert(array1->mark == OBJECT_MARK_TRUE);
    assert(integer1->mark == OBJECT_MARK_TRUE);
    assert(integer2->mark == OBJECT_MARK_FALSE);
    assert(integer3->mark == OBJECT_MARK_TRUE);
    assert(integer3->mark == OBJECT_MARK_TRUE);

    objectMark(array2);
    
    assert(array2->mark == OBJECT_MARK_TRUE);

    objectFree(integer1);
    objectFree(integer2);
    objectFree(integer3);

    objectFree(array1);
    objectFree(array2);

    printf("OK\n");
}

void testArrayFree()
{
    printf("testArrayFree: ");
    struct Object *array1 = arrayNew(NULL, 3);
    assert(array1->type == OBJECT_TYPE_ARRAY);
    objectFree(array1);

    printf("OK\n");
}

void testStringNew()
{
    printf("testStringNew: ");
    
    struct Object *string = stringNew(NULL, "Aha");
    assert(string != NULL);
    assert(string->value.array != NULL);
    assert(string->value.array->objects != NULL);
    assert(string->type == OBJECT_TYPE_STRING);
    assert(string->value.array->slotCount == 5);
    assert(string->value.array->objectCount == 3);
    assert(string->value.array->objects[0]->value.integerValue == 'A');
    assert(string->value.array->objects[1]->value.integerValue == 'h');
    assert(string->value.array->objects[2]->value.integerValue == 'a');

    struct Object *string2 = stringNew(NULL, "");
    assert(string2 != NULL);
    assert(string2->value.array != NULL);
    assert(string2->value.array->objects != NULL);
    assert(string2->type == OBJECT_TYPE_STRING);
    assert(string2->value.array->slotCount == 1);
    assert(string2->value.array->objectCount == 0);

    objectFree(string);
    objectFree(string2);
    
    printf("OK\n");
}

void testStringFromArray()
{
    printf("testStringFromArray: ");
    struct Object *array1 = arrayNew(NULL, 5);
    struct Object *integer1 = integerNew(NULL, 'h');
    struct Object *integer2 = integerNew(NULL, 'e');
    struct Object *integer3 = integerNew(NULL, 'l');
    struct Object *integer4 = integerNew(NULL, 'l');
    struct Object *integer5 = integerNew(NULL, 'o');

    array1->value.array->objects[0] = integer1;
    array1->value.array->objects[1] = integer2;
    array1->value.array->objects[2] = integer3;
    array1->value.array->objects[3] = integer4;
    array1->value.array->objects[4] = integer5;

    struct Object *string = stringFromArray(NULL, array1->value.array); 

    assert(string->type == OBJECT_TYPE_STRING);
    assert(string->value.array->objectCount == 5);
    assert(string->value.array->slotCount == 8);

    assert(string->value.array->objects[0] != integer1);
    assert(string->value.array->objects[1] != integer2);
    assert(string->value.array->objects[2] != integer3);
    assert(string->value.array->objects[3] != integer4);
    assert(string->value.array->objects[4] != integer5);
    
    assert(string->value.array->objects[0]->value.integerValue == integer1->value.integerValue);
    assert(string->value.array->objects[1]->value.integerValue == integer2->value.integerValue);
    assert(string->value.array->objects[2]->value.integerValue == integer3->value.integerValue);
    assert(string->value.array->objects[3]->value.integerValue == integer4->value.integerValue);
    assert(string->value.array->objects[4]->value.integerValue == integer5->value.integerValue);

    objectFree(array1);

    objectFree(string);

    objectFree(integer1);
    objectFree(integer2);
    objectFree(integer3);
    objectFree(integer4);
    objectFree(integer5);


    printf("OK\n");
}

void testStringToArray()
{
    printf("testStringToArray: ");
    struct Object *string1 = stringNew(NULL, "hello");

    struct Object *array = stringToArray(NULL, string1->value.array);

    assert(array->type == OBJECT_TYPE_ARRAY);
    
    assert(array->value.array->objects[0]->value.integerValue == 'h');
    assert(array->value.array->objects[1]->value.integerValue == 'e');
    assert(array->value.array->objects[2]->value.integerValue == 'l');
    assert(array->value.array->objects[3]->value.integerValue == 'l');
    assert(array->value.array->objects[4]->value.integerValue == 'o');

    objectFree(string1);

    objectFree(array->value.array->objects[0]);
    objectFree(array->value.array->objects[1]);
    objectFree(array->value.array->objects[2]);
    objectFree(array->value.array->objects[3]);
    objectFree(array->value.array->objects[4]);

    objectFree(array);

    printf("OK\n");
}

void testStringCompare()
{
    printf("testStringCompare: ");
    struct Object *string1 = stringNew(NULL, "hallo1");

    struct Object *string2 = stringNew(NULL, "hallo");

    struct Object *string3 = stringNew(NULL, "banana");

    struct Object *string4 = stringNew(NULL, "");

    assert(stringCompare(string1->value.array, string1->value.array) == 0);
    assert(stringCompare(string1->value.array, string2->value.array) > 0);
    assert(stringCompare(string1->value.array, string3->value.array) > 0);
    assert(stringCompare(string2->value.array, string1->value.array) < 0);
    assert(stringCompare(string2->value.array, string2->value.array) == 0);
    assert(stringCompare(string2->value.array, string3->value.array) > 0);
    assert(stringCompare(string3->value.array, string1->value.array) < 0);
    assert(stringCompare(string3->value.array, string2->value.array) < 0);
    assert(stringCompare(string3->value.array, string3->value.array) == 0);

    objectFree(string1);
    objectFree(string2);
    objectFree(string3);
    objectFree(string4);

    printf("OK\n");
}

void testStringCopy()
{
    printf("testStringCopy: ");
    struct Object *string1 = stringNew(NULL, "hallo1");
    struct Object *string2 = stringCopy(NULL, string1->value.array);

    assert(string2->type == OBJECT_TYPE_STRING);
    assert(string2->value.array->objects[0] != string1->value.array->objects[0]);
    assert(string2->value.array->objects[1] != string1->value.array->objects[1]);
    assert(string2->value.array->objects[2] != string1->value.array->objects[2]);
    assert(string2->value.array->objects[3] != string1->value.array->objects[3]);
    assert(string2->value.array->objects[4] != string1->value.array->objects[4]);
    assert(string2->value.array->objects[5] != string1->value.array->objects[5]);

    assert(string2->value.array->objects[0]->value.integerValue == string1->value.array->objects[0]->value.integerValue);
    assert(string2->value.array->objects[1]->value.integerValue == string1->value.array->objects[1]->value.integerValue);
    assert(string2->value.array->objects[2]->value.integerValue == string1->value.array->objects[2]->value.integerValue);
    assert(string2->value.array->objects[3]->value.integerValue == string1->value.array->objects[3]->value.integerValue);
    assert(string2->value.array->objects[4]->value.integerValue == string1->value.array->objects[4]->value.integerValue);
    assert(string2->value.array->objects[5]->value.integerValue == string1->value.array->objects[5]->value.integerValue);

    objectFree(string1);
    objectFree(string2);

    printf("OK\n");
}

void testStringEquals()
{
    printf("testStringEquals: ");

    struct Object *string1 = stringNew(NULL, "hallo1");

    struct Object *string2 = stringCopy(NULL, string1->value.array);

    struct Object *string3 = stringNew(NULL, "ban");

    struct Object *string4 = stringNew(NULL, "");

    assert(stringEquals(string1->value.array, string1->value.array) == BOOLEAN_TRUE);
    assert(stringEquals(string1->value.array, string2->value.array) == BOOLEAN_TRUE);
    assert(stringEquals(string1->value.array, string3->value.array) == BOOLEAN_FALSE);
    assert(stringEquals(string1->value.array, string4->value.array) == BOOLEAN_FALSE);
    assert(stringEquals(string2->value.array, string1->value.array) == BOOLEAN_TRUE);
    assert(stringEquals(string2->value.array, string2->value.array) == BOOLEAN_TRUE);
    assert(stringEquals(string2->value.array, string3->value.array) == BOOLEAN_FALSE);
    assert(stringEquals(string2->value.array, string4->value.array) == BOOLEAN_FALSE);
    assert(stringEquals(string3->value.array, string1->value.array) == BOOLEAN_FALSE);
    assert(stringEquals(string3->value.array, string2->value.array) == BOOLEAN_FALSE);
    assert(stringEquals(string3->value.array, string3->value.array) == BOOLEAN_TRUE);
    assert(stringEquals(string3->value.array, string4->value.array) == BOOLEAN_FALSE);
    assert(stringEquals(string4->value.array, string1->value.array) == BOOLEAN_FALSE);
    assert(stringEquals(string4->value.array, string2->value.array) == BOOLEAN_FALSE);
    assert(stringEquals(string4->value.array, string3->value.array) == BOOLEAN_FALSE);
    assert(stringEquals(string4->value.array, string4->value.array) == BOOLEAN_TRUE);

    objectFree(string1);
    objectFree(string2);
    objectFree(string3);
    objectFree(string4);

    printf("OK\n");
}

void testStringHash()
{
    printf("testStringHash: ");

    struct Object *string1 = stringNew(NULL, "hallo1");

    struct Object *string2 = stringCopy(NULL, string1->value.array);

    struct Object *string3 = stringNew(NULL, "");
    struct Object *string4 = stringNew(NULL, "");

    assert(stringHash(string1->value.array) == stringHash(string2->value.array));
    assert(stringHash(string3->value.array) == stringHash(string4->value.array));

    objectFree(string1);
    objectFree(string2);
    objectFree(string3);
    objectFree(string4);

    printf("OK\n");
}

void testStringAppendCharacter()
{
    printf("testStringAppendCharacter: ");
    struct Object *string1 = stringNew(NULL, "hallo1");

    struct Object *string2 = stringNew(NULL, "");

    stringAppendCharacter(string2->value.array, 'h');
    stringAppendCharacter(string2->value.array, 'a');
    stringAppendCharacter(string2->value.array, 'l');
    stringAppendCharacter(string2->value.array, 'l');
    stringAppendCharacter(string2->value.array, 'o');
    stringAppendCharacter(string2->value.array, '1');

    assert(stringEquals(string1->value.array, string2->value.array) == BOOLEAN_TRUE);

    objectFree(string1);
    objectFree(string2);

    printf("OK\n");
}

void testStringFree()
{
    printf("testStringFree: ");
    struct Object *string1 = stringNew(NULL, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    objectFree(string1);

    printf("OK\n");
}

void testDoubleNew()
{
    printf("testDoubleNew: ");
    struct Object *double1 = doubleNew(NULL, 0.001);
    assert(double1->type == OBJECT_TYPE_DOUBLE);
    assert(double1->mark == OBJECT_MARK_FALSE);
    assert(double1->value.doubleValue == 0.001);
    objectFree(double1);
    printf("OK\n");
}

void testDoubleToString()
{
    printf("testDoubleToString: ");
    struct Object *double1 = doubleNew(NULL, 0.0010105);

    struct Object *string = doubleToString(NULL, double1->value.doubleValue);

    assert(string->type == OBJECT_TYPE_STRING);

    assert(string->value.array->objectCount == 16);
    assert(string->value.array->objects[0]->value.integerValue == '1');
    assert(string->value.array->objects[1]->value.integerValue == '.');
    assert(string->value.array->objects[2]->value.integerValue == '0');
    assert(string->value.array->objects[3]->value.integerValue == '1');
    assert(string->value.array->objects[4]->value.integerValue == '0');
    assert(string->value.array->objects[5]->value.integerValue == '5');
    assert(string->value.array->objects[6]->value.integerValue == '0');
    assert(string->value.array->objects[7]->value.integerValue == '0');
    assert(string->value.array->objects[8]->value.integerValue == '0');
    assert(string->value.array->objects[9]->value.integerValue == '0');
    assert(string->value.array->objects[10]->value.integerValue == '0');
    assert(string->value.array->objects[11]->value.integerValue == '0');
    assert(string->value.array->objects[12]->value.integerValue == 'e');
    assert(string->value.array->objects[13]->value.integerValue == '-');
    assert(string->value.array->objects[14]->value.integerValue == '0');
    assert(string->value.array->objects[15]->value.integerValue == '3');
    
    objectFree(string);
    objectFree(double1);
    printf("OK\n");
}

void testGcNew()
{
    printf("testGcNew: ");
    struct Gc *gc = gcNew();

    assert(gc->freeCount == 0);
    assert(gc->newCount == 0);
    assert(gc->head == NULL);

    gcFree(gc);

    printf("OK\n");
}

void testGcRegisterObject()
{
    printf("testGcRegisterObject: ");
    struct Gc *gc = gcNew();
    struct Object *array1 = arrayNew(gc, 3);
    struct Object *integer1 = integerNew(gc, 7);
    struct Object *integer2 = integerNew(gc, 98);
    struct Object *integer3 = integerNew(gc, 121299);

    array1->value.array->objects[0] = integer1;
    array1->value.array->objects[1] = integer2;
    array1->value.array->objects[2] = integer3;

    struct Object *string1 = stringNew(gc, "hallo1");

    assert(gc->newCount == 5);
    assert(gc->freeCount == 0);
    assert(gc->head->object == string1);
    assert(gc->head->next->object == integer3);
    assert(gc->head->next->next->object == integer2);
    assert(gc->head->next->next->next->object == integer1);
    assert(gc->head->next->next->next->next->object == array1);
    assert(gc->head->next->next->next->next->next == NULL);

    gcFree(gc);

    printf("OK\n");
}

void testGcSweep()
{
    printf("testGcSweep: ");
    struct Gc *gc = gcNew();
    struct Object *array1 = arrayNew(gc, 3);
    struct Object *integer1 = integerNew(gc, 7);
    struct Object *integer2 = integerNew(gc, 98);
    struct Object *integer3 = integerNew(gc, 121299);

    array1->value.array->objects[0] = integer1;
    array1->value.array->objects[1] = integer2;
    array1->value.array->objects[2] = integer3;

    struct Object *string = stringNew(gc, "hallo1");

    assert(gc->newCount == 5);

    integer1->mark = OBJECT_MARK_TRUE;
    string->mark = OBJECT_MARK_TRUE;

    gcSweep(gc);

    assert(gc->freeCount == 3);
    assert(gc->head->object == string);
    assert(gc->head->next->object == integer1);
    assert(gc->head->next->next == NULL);

    integer1->mark = OBJECT_MARK_TRUE;

    gcSweep(gc);

    assert(gc->freeCount == 4);
    assert(gc->head->object == integer1);
    assert(gc->head->next == NULL);

    gcSweep(gc);

    assert(gc->freeCount == 5);
    assert(gc->head == NULL);

    struct Object *arrayString1 = stringNew(gc, "");
    struct Object *arrayString2 = arrayToString(gc, stringToArray(gc, arrayString1->value.array)->value.array);
    struct Object *arrayString3 = arrayToString(gc, stringToArray(gc, arrayString2->value.array)->value.array);

    assert(arrayString3->value.array->objectCount == 7);

    gcSweep(gc);

    assert(gc->freeCount == 12);
    assert(gc->head == NULL);

    gcFree(gc);

    printf("OK\n");
}

void testGcFree()
{
    printf("testGcFree: ");
    struct Gc *gc = gcNew();
    gcFree(gc);
    printf("OK\n");
}

void testIntegerNew()
{
    printf("testIntegerNew: ");
    struct Object *integer = integerNew(NULL, 1231212);

    assert(integer->type == OBJECT_TYPE_INTEGER);
    assert(integer->value.integerValue == 1231212);

    objectFree(integer);
    printf("OK\n");
}

void testIntegerToString()
{
    printf("testIntegerToString: ");
    struct Object *integer1 = integerNew(NULL, 10105);

    struct Object *string = integerToString(NULL, integer1->value.integerValue);

    assert(string->type == OBJECT_TYPE_STRING);

    assert(string->value.array->objectCount == 5);
    assert(string->value.array->objects[0]->value.integerValue == '1');
    assert(string->value.array->objects[1]->value.integerValue == '0');
    assert(string->value.array->objects[2]->value.integerValue == '1');
    assert(string->value.array->objects[3]->value.integerValue == '0');
    assert(string->value.array->objects[4]->value.integerValue == '5');
    
    objectFree(string);
    objectFree(integer1);
    printf("OK\n");
}

void testMapNew()
{
    printf("testMapNew: ");
    struct Object *map1 = mapNew(NULL);

    assert(map1->type == OBJECT_TYPE_MAP);

    assert(map1->value.map->bucketCount == 8);

    objectFree(map1);

    printf("OK\n");
}

void testMapSize()
{
    printf("testMapSize: ");
    struct Object *map1 = mapNew(NULL);

    assert(map1->type == OBJECT_TYPE_MAP);

    assert(map1->value.map->bucketCount == 8);

    assert(mapSize(map1->value.map) == 0);

    objectFree(map1);
    printf("OK\n");
}

void testMapGet()
{
    printf("testMapGet: ");
    struct Object *map1 = mapNew(NULL);
    struct Object *integer1 = integerNew(NULL, 1212);

    struct Object *string1 = stringNew(NULL, "hallo1");

    assert(mapGet(map1->value.map, integer1) == NULL);
    assert(mapGet(map1->value.map, string1) == NULL);
    assert(mapGet(map1->value.map, map1) == NULL);

    objectFree(map1);
    objectFree(integer1);
    objectFree(string1);

    printf("OK\n");
}

void testMapPut()
{
    printf("testMapPut: ");
    struct Object *map1 = mapNew(NULL);
    
    struct Object *integer1 = integerNew(NULL, 1);
    struct Object *integer2 = integerNew(NULL, 17);
    struct Object *integer3 = integerNew(NULL, 82);
    struct Object *integer4 = integerNew(NULL, 43);
    struct Object *integer5 = integerNew(NULL, 17);

    struct Object *integer6 = integerNew(NULL, 121);
    struct Object *integer7 = integerNew(NULL, 441);
    struct Object *integer8 = integerNew(NULL, 566);
    struct Object *integer9 = integerNew(NULL, 874);
    struct Object *integer10 = integerNew(NULL, 236);

    assert(mapPut(map1->value.map, integer1, integer6) == NULL);
    assert(mapSize(map1->value.map) == 1);
    assert(map1->value.map->bucketCount == 8);

    assert(mapPut(map1->value.map, integer2, integer7) == NULL);
    assert(mapSize(map1->value.map) == 2);
    assert(map1->value.map->bucketCount == 8);

    assert(mapPut(map1->value.map, integer3, integer8) == NULL);
    assert(mapSize(map1->value.map) == 3);
    assert(map1->value.map->bucketCount == 8);

    assert(mapPut(map1->value.map, integer4, integer9) == NULL);
    assert(mapSize(map1->value.map) == 4);
    assert(map1->value.map->bucketCount == 8);
    
    assert(mapPut(map1->value.map, integer5, integer10) == integer7);
    assert(mapGet(map1->value.map, integer5) == integer10);
    assert(mapSize(map1->value.map) == 4);
    assert(map1->value.map->bucketCount == 8);

    assert(mapPut(map1->value.map, integer6, integer5) == NULL);
    assert(mapGet(map1->value.map, integer6) == integer5);
    assert(mapSize(map1->value.map) == 5);
    assert(map1->value.map->bucketCount == 8);

    assert(mapPut(map1->value.map, integer7, integer4) == NULL);
    assert(mapGet(map1->value.map, integer7) == integer4);
    assert(mapSize(map1->value.map) == 6);
    assert(map1->value.map->bucketCount == 8);

    assert(mapPut(map1->value.map, integer8, integer3) == NULL);
    assert(mapGet(map1->value.map, integer8) == integer3);
    assert(mapSize(map1->value.map) == 7);
    assert(map1->value.map->bucketCount == 16);

    assert(mapPut(map1->value.map, integer9, integer2) == NULL);
    assert(mapGet(map1->value.map, integer9) == integer2);
    assert(mapSize(map1->value.map) == 8);
    assert(map1->value.map->bucketCount == 16);

    assert(mapPut(map1->value.map, NULL, integer1) == NULL);
    assert(mapGet(map1->value.map, NULL) == integer1);
    assert(mapSize(map1->value.map) == 9);
    assert(map1->value.map->bucketCount == 16);

    assert(mapPut(map1->value.map, NULL, NULL) == integer1);
    assert(mapGet(map1->value.map, NULL) == NULL);
    assert(mapSize(map1->value.map) == 9);
    assert(map1->value.map->bucketCount == 16);

    objectFree(map1);
    objectFree(integer1);
    objectFree(integer2);
    objectFree(integer3);
    objectFree(integer4);
    objectFree(integer5);
    objectFree(integer6);
    objectFree(integer7);
    objectFree(integer8);
    objectFree(integer9);
    objectFree(integer10);

    printf("OK\n");
}

void testMapPutMany()
{
    printf("testMapPutMany: ");
 
    int largeNum = 200000;

    struct Object *map = mapNew(NULL);
    struct Object **objects = (struct Object **) malloc(largeNum * sizeof(struct Object *));

    for (int i = 0; i < largeNum; i++)
    {
        objects[i] = integerNew(NULL, i);
        assert(mapPut(map->value.map, objects[i], objects[i]) == NULL);
    }
    
    for (int i = 0; i < largeNum; i++)
    {
        assert(mapGet(map->value.map, objects[i]) == objects[i]);
        free(objects[i]);
    }

    free(objects);
    objectFree(map);

    printf("OK\n");
}

void testMapPutAll()
{
    printf("testMapPutAll: ");
    struct Object *map1 = mapNew(NULL);
    struct Object *map2 = mapNew(NULL);
    struct Object *map3 = mapNew(NULL);
    
    struct Object *integer1 = integerNew(NULL, 1);
    struct Object *integer2 = integerNew(NULL, 17);
    struct Object *integer3 = integerNew(NULL, 82);
    struct Object *integer4 = integerNew(NULL, 43);
    struct Object *integer5 = integerNew(NULL, 17);

    struct Object *integer6 = integerNew(NULL, 121);
    struct Object *integer7 = integerNew(NULL, 441);
    struct Object *integer8 = integerNew(NULL, 566);
    struct Object *integer9 = integerNew(NULL, 874);
    struct Object *integer10 = integerNew(NULL, 236);

    mapPut(map1->value.map, integer1, integer6);
    mapPut(map1->value.map, integer2, integer7);
    mapPut(map1->value.map, integer3, integer8);
    mapPut(map1->value.map, integer4, integer9);

    mapPut(map2->value.map, integer5, integer10);
    mapPut(map2->value.map, integer7, integer1);

    mapPutAll(map1->value.map, map2->value.map);

    assert(map1->value.map->entryCount == 5);
    assert(map1->value.map->bucketCount == 8);
    assert(mapGet(map1->value.map, integer1) == integer6);
    assert(mapGet(map1->value.map, integer2) == integer10);
    assert(mapGet(map1->value.map, integer3) == integer8);
    assert(mapGet(map1->value.map, integer4) == integer9);
    assert(mapGet(map1->value.map, integer5) == integer10);
    assert(mapGet(map1->value.map, integer7) == integer1);

    mapPutAll(map2->value.map, map3->value.map);

    assert(map2->value.map->entryCount == 2);
    assert(map2->value.map->bucketCount == 8);
    assert(mapGet(map2->value.map, integer5) == integer10);
    assert(mapGet(map2->value.map, integer7) == integer1);

    mapPutAll(map2->value.map, map2->value.map);

    assert(map2->value.map->entryCount == 2);
    assert(map2->value.map->bucketCount == 8);
    assert(mapGet(map2->value.map, integer5) == integer10);
    assert(mapGet(map2->value.map, integer7) == integer1);

    objectFree(map1);
    objectFree(map2);
    objectFree(map3);

    objectFree(integer1);
    objectFree(integer2);
    objectFree(integer3);
    objectFree(integer4);
    objectFree(integer5);
    objectFree(integer6);
    objectFree(integer7);
    objectFree(integer8);
    objectFree(integer9);
    objectFree(integer10);

    printf("OK\n");
}

void testMapRemove()
{
    printf("testMapRemove: ");
    struct Object *map1 = mapNew(NULL);
    
    struct Object *integer1 = integerNew(NULL, 1);
    struct Object *integer2 = integerNew(NULL, 17);
    struct Object *integer3 = integerNew(NULL, 82);
    struct Object *integer4 = integerNew(NULL, 43);
    struct Object *integer5 = integerNew(NULL, 17);

    struct Object *integer6 = integerNew(NULL, 121);
    struct Object *integer7 = integerNew(NULL, 441);
    struct Object *integer8 = integerNew(NULL, 566);
    struct Object *integer9 = integerNew(NULL, 874);
    struct Object *integer10 = integerNew(NULL, 236);

    mapPut(map1->value.map, integer1, integer6);
    mapPut(map1->value.map, integer2, integer7);
    mapPut(map1->value.map, integer3, integer8);
    mapPut(map1->value.map, integer4, integer9);

    assert(mapRemove(map1->value.map, integer2) == integer7);
    assert(map1->value.map->entryCount == 3);
    assert(mapGet(map1->value.map, integer2) == NULL);

    assert(mapRemove(map1->value.map, integer2) == NULL);
    assert(map1->value.map->entryCount == 3);

    assert(mapRemove(map1->value.map, integer4) == integer9);
    assert(map1->value.map->entryCount == 2);
    assert(mapGet(map1->value.map, integer4) == NULL);

    assert(mapRemove(map1->value.map, integer3) == integer8);
    assert(map1->value.map->entryCount == 1);
    assert(mapGet(map1->value.map, integer3) == NULL);

    assert(mapRemove(map1->value.map, integer1) == integer6);
    assert(map1->value.map->entryCount == 0);
    assert(mapGet(map1->value.map, integer1) == NULL);

    assert(mapRemove(map1->value.map, NULL) == NULL);
    assert(map1->value.map->entryCount == 0);

    objectFree(map1);

    objectFree(integer1);
    objectFree(integer2);
    objectFree(integer3);
    objectFree(integer4);
    objectFree(integer5);
    objectFree(integer6);
    objectFree(integer7);
    objectFree(integer8);
    objectFree(integer9);
    objectFree(integer10);

    printf("OK\n");
}

void testMapHasKey()
{
    printf("testMapHasKey: ");

    struct Object *map1 = mapNew(NULL);
    struct Object *integer1 = integerNew(NULL, 1);

    assert(mapHasKey(map1->value.map, integer1) == BOOLEAN_FALSE);
    assert(mapHasKey(map1->value.map, NULL) == BOOLEAN_FALSE);

    mapPut(map1->value.map, integer1, NULL);

    assert(mapHasKey(map1->value.map, integer1) == BOOLEAN_TRUE);

    mapRemove(map1->value.map, integer1);

    assert(mapHasKey(map1->value.map, integer1) == BOOLEAN_FALSE);

    objectFree(map1);
    objectFree(integer1);

    printf("OK\n");
}

void testMapEntries()
{
    printf("testMapEntries: ");

    struct Object *map1 = mapNew(NULL);
    struct Object *map2 = mapNew(NULL);
    
    struct Object *integer1 = integerNew(NULL, 1);
    struct Object *integer2 = integerNew(NULL, 17);
    struct Object *integer3 = integerNew(NULL, 82);
    struct Object *integer4 = integerNew(NULL, 43);
    struct Object *integer5 = integerNew(NULL, 18);

    struct Object *integer6 = integerNew(NULL, 121);
    struct Object *integer7 = integerNew(NULL, 441);
    struct Object *integer8 = integerNew(NULL, 566);
    struct Object *integer9 = integerNew(NULL, 874);
    struct Object *integer10 = integerNew(NULL, 236);

    mapPut(map1->value.map, integer1, integer6);
    mapPut(map1->value.map, integer2, integer7);
    mapPut(map1->value.map, integer3, integer8);
    mapPut(map1->value.map, integer4, integer9);
    mapPut(map1->value.map, integer5, integer10);

    struct Object *emptyArray = mapEntries(NULL, map2->value.map);
    assert(emptyArray->value.array->objectCount == 0);

    struct Object *array = mapEntries(NULL, map1->value.map);

    assert(array->type == OBJECT_TYPE_ARRAY);
    assert(array->value.array->objectCount == 5);
    assert(array->value.array->slotCount == 8);

    assert(array->value.array->objects[0]->type == OBJECT_TYPE_PAIR);
    assert(array->value.array->objects[1]->type == OBJECT_TYPE_PAIR);
    assert(array->value.array->objects[2]->type == OBJECT_TYPE_PAIR);
    assert(array->value.array->objects[3]->type == OBJECT_TYPE_PAIR);
    assert(array->value.array->objects[4]->type == OBJECT_TYPE_PAIR);

    struct Object *f1 = array->value.array->objects[0]->value.pair->first;
    struct Object *f2 = array->value.array->objects[1]->value.pair->first;
    struct Object *f3 = array->value.array->objects[2]->value.pair->first;
    struct Object *f4 = array->value.array->objects[3]->value.pair->first;
    struct Object *f5 = array->value.array->objects[4]->value.pair->first;

    assert(f1 == integer1 || f2 == integer1 || f3 == integer1 || f4 == integer1 || f5 == integer1);
    assert(f1 == integer2 || f2 == integer2 || f3 == integer2 || f4 == integer2 || f5 == integer2);
    assert(f1 == integer3 || f2 == integer3 || f3 == integer3 || f4 == integer3 || f5 == integer3);
    assert(f1 == integer4 || f2 == integer4 || f3 == integer4 || f4 == integer4 || f5 == integer4);
    assert(f1 == integer5 || f2 == integer5 || f3 == integer5 || f4 == integer5 || f5 == integer5);

    struct Object *s1 = array->value.array->objects[0]->value.pair->second;
    struct Object *s2 = array->value.array->objects[1]->value.pair->second;
    struct Object *s3 = array->value.array->objects[2]->value.pair->second;
    struct Object *s4 = array->value.array->objects[3]->value.pair->second;
    struct Object *s5 = array->value.array->objects[4]->value.pair->second;

    assert(s1 == integer6 || s2 == integer6 || s3 == integer6 || s4 == integer6 || s5 == integer6);
    assert(s1 == integer7 || s2 == integer7 || s3 == integer7 || s4 == integer7 || s5 == integer7);
    assert(s1 == integer8 || s2 == integer8 || s3 == integer8 || s4 == integer8 || s5 == integer8);
    assert(s1 == integer9 || s2 == integer9 || s3 == integer9 || s4 == integer9 || s5 == integer9);
    assert(s1 == integer10 || s2 == integer10 || s3 == integer10 || s4 == integer10 || s5 == integer10);

    objectFree(array->value.array->objects[0]);
    objectFree(array->value.array->objects[1]);
    objectFree(array->value.array->objects[2]);
    objectFree(array->value.array->objects[3]);
    objectFree(array->value.array->objects[4]);

    objectFree(array);
    objectFree(emptyArray);
    objectFree(map1);
    objectFree(map2);

    objectFree(integer1);
    objectFree(integer2);
    objectFree(integer3);
    objectFree(integer4);
    objectFree(integer5);
    objectFree(integer6);
    objectFree(integer7);
    objectFree(integer8);
    objectFree(integer9);
    objectFree(integer10);
    printf("OK\n");
}

void testMapCopy()
{
    printf("testMapCopy: ");
    struct Object *map1 = mapNew(NULL);

    struct Object *string1 = stringNew(NULL, "hier");
    struct Object *string2 = stringNew(NULL, "dort");
    struct Object *string3 = stringNew(NULL, "nah");
    struct Object *string4 = stringNew(NULL, "fern");
    struct Object *integer1 = integerNew(NULL, 2);

    mapPut(map1->value.map, string1, string2);
    mapPut(map1->value.map, string3, string4);
    mapPut(map1->value.map, integer1, NULL);
    mapPut(map1->value.map, NULL, integer1);

    struct Object *map2 = mapCopy(NULL, map1->value.map);

    assert(map2->value.map->entryCount == 4);
    assert(mapGet(map2->value.map, string1) != string2);
    assert(mapGet(map2->value.map, string3) != string4);
    assert(mapGet(map2->value.map, integer1) == NULL);
    assert(mapGet(map2->value.map, NULL) != integer1);

    assert(objectEquals(mapGet(map2->value.map, string1), string2) == BOOLEAN_TRUE);
    assert(objectEquals(mapGet(map2->value.map, string3), string4) == BOOLEAN_TRUE);
    assert(objectEquals(mapGet(map2->value.map, NULL), integer1) == BOOLEAN_TRUE);

    for (Integer i = 0; i < map2->value.map->bucketCount; i++)
    {
        struct MapEntry *currEntry = map2->value.map->buckets[i];

        while (currEntry != NULL)
        {
            objectFree(currEntry->key);
            objectFree(currEntry->value);

            currEntry = currEntry->next;
        }
    }

    objectFree(integer1);
    objectFree(string1);
    objectFree(string2);
    objectFree(string3);
    objectFree(string4);
    objectFree(map1);
    objectFree(map2);
    printf("OK\n");
}

void testMapEquals()
{
    printf("testMapEquals: ");
    struct Gc *gc = gcNew();
    struct Object *map1 = mapNew(gc);
    struct Object *map2 = mapNew(gc);

    struct Object *string1 = stringNew(gc, "hier");
    struct Object *string2 = stringNew(gc, "dort");
    struct Object *string3 = stringNew(gc, "nah");
    struct Object *string4 = stringNew(gc, "fern");
    struct Object *integer1 = integerNew(gc, 2);

    mapPut(map1->value.map, string1, string2);
    mapPut(map1->value.map, string3, string4);
    mapPut(map1->value.map, integer1, NULL);
    mapPut(map1->value.map, NULL, integer1);

    mapPut(map2->value.map, string1, string2);

    assert(mapEquals(map1->value.map, map2->value.map) == BOOLEAN_FALSE);
    assert(mapEquals(map2->value.map, map1->value.map) == BOOLEAN_FALSE);

    struct Object *mapCopy1 = mapCopy(gc, map1->value.map);

    assert(mapEquals(map1->value.map, map1->value.map) == BOOLEAN_TRUE);
    assert(mapEquals(map1->value.map, mapCopy1->value.map) == BOOLEAN_TRUE);
    
    mapRemove(mapCopy1->value.map, integer1);
    
    assert(mapEquals(map1->value.map, mapCopy1->value.map) == BOOLEAN_FALSE);

    mapPut(mapCopy1->value.map, integer1, integer1);

    assert(mapEquals(map1->value.map, mapCopy1->value.map) == BOOLEAN_FALSE);

    mapPut(mapCopy1->value.map, integer1, NULL);

    assert(mapEquals(map1->value.map, mapCopy1->value.map) == BOOLEAN_TRUE);

    gcSweep(gc);

    assert(gc->freeCount == 14);
    assert(gc->head == NULL);

    gcFree(gc);
    printf("OK\n");
}

void testMapHash()
{
    printf("testMapHash: ");
    struct Gc *gc = gcNew();
    struct Object *map1 = mapNew(gc);

    struct Object *string1 = stringNew(gc, "hier");
    struct Object *string2 = stringNew(gc, "dort");
    struct Object *string3 = stringNew(gc, "nah");
    struct Object *string4 = stringNew(gc, "fern");
    struct Object *integer1 = integerNew(gc, 2);

    mapPut(map1->value.map, string1, string2);
    mapPut(map1->value.map, string3, string4);
    mapPut(map1->value.map, integer1, NULL);
    mapPut(map1->value.map, NULL, integer1);

    struct Object *map2 = mapCopy(gc, map1->value.map);

    assert(mapHash(map1->value.map) == mapHash(map1->value.map));
    assert(mapHash(map1->value.map) == mapHash(map2->value.map));
    
    mapRemove(map2->value.map, integer1);
    mapPut(map2->value.map, integer1, integer1);
    mapPut(map2->value.map, integer1, NULL);

    assert(mapHash(map1->value.map) == mapHash(map2->value.map));

    gcSweep(gc);

    assert(gc->freeCount == 13);
    assert(gc->head == NULL);

    gcFree(gc);
    printf("OK\n");
}

void testMapToString()
{
    printf("testMapToString: ");
    struct Object *map1 = mapNew(NULL);

    struct Object *string1 = stringNew(NULL, "hier");
    struct Object *string2 = stringNew(NULL, "dort");
    struct Object *string3 = stringNew(NULL, "nah");
    struct Object *string4 = stringNew(NULL, "fern");
    struct Object *integer1 = integerNew(NULL, 2);

    mapPut(map1->value.map, string1, string2);
    mapPut(map1->value.map, string3, string4);
    mapPut(map1->value.map, integer1, NULL);
    mapPut(map1->value.map, NULL, integer1);

    struct Object *mapString1 = mapToString(NULL, map1->value.map);

    assert(mapString1->type == OBJECT_TYPE_STRING);
    assert(mapString1->value.array->objectCount == 34);

    objectFree(map1);
    objectFree(string1);
    objectFree(string2);
    objectFree(string3);
    objectFree(string4);
    objectFree(integer1);
    objectFree(mapString1);

    printf("OK\n");
}

void testMapMark()
{
    printf("testMapMark: ");
    struct Object *map1 = mapNew(NULL);

    struct Object *string1 = stringNew(NULL, "hier");
    struct Object *string2 = stringNew(NULL, "dort");
    struct Object *string3 = stringNew(NULL, "nah");
    struct Object *string4 = stringNew(NULL, "fern");
    struct Object *integer1 = integerNew(NULL, 2);

    mapPut(map1->value.map, string1, string2);
    mapPut(map1->value.map, string3, string4);
    mapPut(map1->value.map, integer1, NULL);
    mapPut(map1->value.map, NULL, integer1);

    assert(map1->mark == OBJECT_MARK_FALSE);
    assert(string1->mark == OBJECT_MARK_FALSE);
    assert(string2->mark == OBJECT_MARK_FALSE);
    assert(string3->mark == OBJECT_MARK_FALSE);
    assert(string4->mark == OBJECT_MARK_FALSE);
    assert(integer1->mark == OBJECT_MARK_FALSE);

    objectMark(map1);

    assert(map1->mark == OBJECT_MARK_TRUE);
    assert(string1->mark == OBJECT_MARK_TRUE);
    assert(string2->mark == OBJECT_MARK_TRUE);
    assert(string3->mark == OBJECT_MARK_TRUE);
    assert(string4->mark == OBJECT_MARK_TRUE);
    assert(integer1->mark == OBJECT_MARK_TRUE);

    objectFree(map1);
    objectFree(string1);
    objectFree(string2);
    objectFree(string3);
    objectFree(string4);
    objectFree(integer1);

    printf("OK\n");
}

void testMapFree()
{
    printf("testMapFree: ");
    struct Object *map = mapNew(NULL);
    objectFree(map);
    printf("OK\n");
}

void testObjectCopy()
{
    printf("testObjectCopy: ");
    struct Gc *gc = gcNew();
    struct Object *object = getComplexObject(gc);
    
    struct Object *copy = objectCopy(gc, object);
    
    assert(copy != object);

    assert(mapGet(object->value.map, stringNew(gc, "Willi")) != mapGet(copy->value.map, stringNew(gc, "Willi")));
    assert(mapGet(object->value.map, stringNew(gc, "Otto")) != mapGet(copy->value.map, stringNew(gc, "Otto")));
    assert(mapGet(object->value.map, stringNew(gc, "Lisa")) != mapGet(copy->value.map, stringNew(gc, "Lisa")));

    assert(mapGet(object->value.map, stringNew(gc, "Willi"))->value.pair->first != mapGet(copy->value.map, stringNew(gc, "Willi"))->value.pair->first);
    assert(mapGet(object->value.map, stringNew(gc, "Otto"))->value.pair->first != mapGet(copy->value.map, stringNew(gc, "Otto"))->value.pair->first);
    assert(mapGet(object->value.map, stringNew(gc, "Lisa"))->value.pair->first != mapGet(copy->value.map, stringNew(gc, "Lisa"))->value.pair->first);

    assert(mapGet(mapGet(object->value.map, stringNew(gc, "Willi"))->value.pair->first->value.map, stringNew(gc, "name")) 
        != mapGet(mapGet(copy->value.map, stringNew(gc, "Willi"))->value.pair->first->value.map, stringNew(gc, "name")));
    
    assert(mapGet(mapGet(object->value.map, stringNew(gc, "Otto"))->value.pair->first->value.map, stringNew(gc, "name"))  
        != mapGet(mapGet(copy->value.map, stringNew(gc, "Otto"))->value.pair->first->value.map, stringNew(gc, "name")));
    
    assert(mapGet(mapGet(object->value.map, stringNew(gc, "Lisa"))->value.pair->first->value.map, stringNew(gc, "name"))  
        != mapGet(mapGet(copy->value.map, stringNew(gc, "Lisa"))->value.pair->first->value.map, stringNew(gc, "name")));

    assert(mapGet(mapGet(object->value.map, stringNew(gc, "Willi"))->value.pair->first->value.map, stringNew(gc, "age")) 
        != mapGet(mapGet(copy->value.map, stringNew(gc, "Willi"))->value.pair->first->value.map, stringNew(gc, "age")));
    
    assert(mapGet(mapGet(object->value.map, stringNew(gc, "Otto"))->value.pair->first->value.map, stringNew(gc, "age"))  
        != mapGet(mapGet(copy->value.map, stringNew(gc, "Otto"))->value.pair->first->value.map, stringNew(gc, "age")));
    
    assert(mapGet(mapGet(object->value.map, stringNew(gc, "Lisa"))->value.pair->first->value.map, stringNew(gc, "age"))  
        != mapGet(mapGet(copy->value.map, stringNew(gc, "Lisa"))->value.pair->first->value.map, stringNew(gc, "age")));

    assert(mapGet(mapGet(object->value.map, stringNew(gc, "Willi"))->value.pair->first->value.map, stringNew(gc, "height")) 
        != mapGet(mapGet(copy->value.map, stringNew(gc, "Willi"))->value.pair->first->value.map, stringNew(gc, "height")));
    
    assert(mapGet(mapGet(object->value.map, stringNew(gc, "Otto"))->value.pair->first->value.map, stringNew(gc, "height"))  
        != mapGet(mapGet(copy->value.map, stringNew(gc, "Otto"))->value.pair->first->value.map, stringNew(gc, "height")));
    
    assert(mapGet(mapGet(object->value.map, stringNew(gc, "Lisa"))->value.pair->first->value.map, stringNew(gc, "height"))  
        != mapGet(mapGet(copy->value.map, stringNew(gc, "Lisa"))->value.pair->first->value.map, stringNew(gc, "height")));

    assert(mapGet(object->value.map, stringNew(gc, "Willi"))->value.pair->second != mapGet(copy->value.map, stringNew(gc, "Willi"))->value.pair->second);
    assert(mapGet(object->value.map, stringNew(gc, "Otto"))->value.pair->second != mapGet(copy->value.map, stringNew(gc, "Otto"))->value.pair->second);
    assert(mapGet(object->value.map, stringNew(gc, "Lisa"))->value.pair->second != mapGet(copy->value.map, stringNew(gc, "Lisa"))->value.pair->second);

    assert(mapGet(object->value.map, stringNew(gc, "Willi"))->value.pair->second->value.array->objects[0] 
        != mapGet(copy->value.map, stringNew(gc, "Willi"))->value.pair->second->value.array->objects[0]);
    
    assert(mapGet(object->value.map, stringNew(gc, "Willi"))->value.pair->second->value.array->objects[1] 
        != mapGet(copy->value.map, stringNew(gc, "Willi"))->value.pair->second->value.array->objects[1]);

    assert(mapGet(object->value.map, stringNew(gc, "Otto"))->value.pair->second->value.array->objects[0] 
        != mapGet(copy->value.map, stringNew(gc, "Otto"))->value.pair->second->value.array->objects[0]);

    assert(mapGet(mapGet(object->value.map, stringNew(gc, "Willi"))->value.pair->second->value.array->objects[0]->value.map, stringNew(gc, "street")) 
        != mapGet(mapGet(copy->value.map, stringNew(gc, "Willi"))->value.pair->second->value.array->objects[0]->value.map, stringNew(gc, "street")));

    assert(mapGet(mapGet(object->value.map, stringNew(gc, "Willi"))->value.pair->second->value.array->objects[0]->value.map, stringNew(gc, "number")) 
        != mapGet(mapGet(copy->value.map, stringNew(gc, "Willi"))->value.pair->second->value.array->objects[0]->value.map, stringNew(gc, "number")));
    
    assert(mapGet(mapGet(object->value.map, stringNew(gc, "Willi"))->value.pair->second->value.array->objects[1]->value.map, stringNew(gc, "street")) 
        != mapGet(mapGet(copy->value.map, stringNew(gc, "Willi"))->value.pair->second->value.array->objects[1]->value.map, stringNew(gc, "street")));

    assert(mapGet(mapGet(object->value.map, stringNew(gc, "Willi"))->value.pair->second->value.array->objects[1]->value.map, stringNew(gc, "number")) 
        != mapGet(mapGet(copy->value.map, stringNew(gc, "Willi"))->value.pair->second->value.array->objects[1]->value.map, stringNew(gc, "number")));

    assert(mapGet(mapGet(object->value.map, stringNew(gc, "Otto"))->value.pair->second->value.array->objects[0]->value.map, stringNew(gc, "street")) 
        != mapGet(mapGet(copy->value.map, stringNew(gc, "Otto"))->value.pair->second->value.array->objects[0]->value.map, stringNew(gc, "street")));

    assert(mapGet(mapGet(object->value.map, stringNew(gc, "Otto"))->value.pair->second->value.array->objects[0]->value.map, stringNew(gc, "number")) 
        != mapGet(mapGet(copy->value.map, stringNew(gc, "Otto"))->value.pair->second->value.array->objects[0]->value.map, stringNew(gc, "number")));

    gcSweep(gc);
    assert(gc->freeCount == gc->newCount);
    gcFree(gc);
    printf("OK\n");
}

void testObjectEquals()
{
    printf("testObjectEquals: ");
    struct Gc *gc = gcNew();
    struct Object *object = getComplexObject(gc);
    
    struct Object *copy = objectCopy(gc, object);

    assert(objectEquals(object, copy) == BOOLEAN_TRUE);

    // copy changes address
    mapGet(mapGet(copy->value.map, stringNew(gc, "Otto"))->value.pair->second->value.array->objects[0]->value.map, stringNew(gc, "number"))->value.integerValue = 12;
    
    assert(objectEquals(object, copy) == BOOLEAN_FALSE);

    // copy changes address back
    mapPut(mapGet(copy->value.map, stringNew(gc, "Otto"))->value.pair->second->value.array->objects[0]->value.map, stringNew(gc, "number"), integerNew(gc, 32));
    
    assert(objectEquals(object, copy) == BOOLEAN_TRUE);

    gcSweep(gc);
    assert(gc->freeCount == gc->newCount);
    gcFree(gc);
    printf("OK\n");
}

void testObjectHash()
{
    printf("testObjectHash: ");
    struct Gc *gc = gcNew();
    struct Object *object = getComplexObject(gc);
    
    struct Object *copy = objectCopy(gc, object);

    assert(objectHash(object) == objectHash(copy));

    // copy changes address
    mapGet(mapGet(copy->value.map, stringNew(gc, "Otto"))->value.pair->second->value.array->objects[0]->value.map, stringNew(gc, "number"))->value.integerValue = 12;
    
    // copy changes address back
    mapPut(mapGet(copy->value.map, stringNew(gc, "Otto"))->value.pair->second->value.array->objects[0]->value.map, stringNew(gc, "number"), integerNew(gc, 32));
    
    assert(objectHash(object) == objectHash(copy));

    gcSweep(gc);
    assert(gc->freeCount == gc->newCount);
    gcFree(gc);
    printf("OK\n");
}

void testObjectToString()
{
    printf("testObjectToString: ");
    struct Gc *gc = gcNew();
    struct Object *object = getComplexObject(gc);

    struct Object *string = objectToString(gc, object);

    stringPrint(string->value.array);

    gcSweep(gc);
    assert(gc->freeCount == gc->newCount);
    gcFree(gc);
    printf("OK\n");
}

void testObjectNew()
{
    printf("testObjectNew: ");
    struct Gc *gc = gcNew();
    
    objectNew(gc, 200);

    gcSweep(gc);

    assert(gc->freeCount == gc->newCount);
    assert(gc->freeCount == 1);
    assert(gc->head == NULL);

    gcFree(gc);

    printf("OK\n");
}

void testObjectMark()
{
    printf("testObjectMark: ");
    struct Gc *gc = gcNew();
    struct Object *object = getComplexObject(gc);

    objectMark(object);

    gcSweep(gc);

    assert(gc->freeCount == 0);

    gcSweep(gc);
    assert(gc->freeCount == gc->newCount);
    gcFree(gc);

    printf("OK\n");
}

void testObjectFree()
{
    printf("testObjectFree: ");
    struct Gc *gc = gcNew();
    getComplexObject(gc);
    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testPairNew()
{
    printf("testPairNew: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *pair = pairNew(NULL, NULL, integer1);

    assert(pair->value.pair->first == NULL);
    assert(pair->value.pair->second == integer1);

    objectFree(integer1);
    objectFree(pair);

    printf("OK\n");
}

void testPairGetFirst()
{
    printf("testPairGetFirst: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *pair = pairNew(NULL, NULL, integer1);

    assert(pairGetFirst(pair->value.pair) == NULL);
    pair->value.pair->first = integer1;
    assert(pairGetFirst(pair->value.pair) == integer1);

    objectFree(integer1);
    objectFree(pair);
    printf("OK\n");
}

void testPairGetSecond()
{
    printf("testPairGetSecond: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *pair = pairNew(NULL, NULL, integer1);

    assert(pairGetSecond(pair->value.pair) == integer1);
    pair->value.pair->second = NULL;
    assert(pairGetSecond(pair->value.pair) == NULL);

    objectFree(integer1);
    objectFree(pair);
    printf("OK\n");
}

void testPairSetFirst()
{
    printf("testPairSetFirst: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *pair = pairNew(NULL, NULL, integer1);

    assert(pairSetFirst(pair->value.pair, integer1) == NULL);
    assert(pairGetFirst(pair->value.pair) == integer1);

    assert(pairSetFirst(pair->value.pair, NULL) == integer1);
    assert(pairGetFirst(pair->value.pair) == NULL);

    objectFree(integer1);
    objectFree(pair);
    printf("OK\n");
}

void testPairSetSecond()
{
    printf("testPairSetSecond: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *pair = pairNew(NULL, NULL, integer1);

    assert(pairSetSecond(pair->value.pair, NULL) == integer1);
    assert(pairGetSecond(pair->value.pair) == NULL);

    assert(pairSetSecond(pair->value.pair, integer1) == NULL);
    assert(pairGetSecond(pair->value.pair) == integer1);

    objectFree(integer1);
    objectFree(pair);
    printf("OK\n");
}

void testPairCopy()
{
    printf("testPairCopy: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *string1 = stringNew(NULL, "1233123");
    struct Object *pair = pairNew(NULL, string1, integer1);

    struct Object *copy = pairCopy(NULL, pair->value.pair);

    assert(copy != pair);
    assert(copy->value.pair->first != pair->value.pair->first);
    assert(copy->value.pair->second != pair->value.pair->second);

    objectFree(integer1);
    objectFree(string1);
    objectFree(pair);
    objectFree(copy->value.pair->first);
    objectFree(copy->value.pair->second);
    objectFree(copy);
    printf("OK\n");
}

void testPairEquals()
{
    printf("testPairEquals: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *string1 = stringNew(NULL, "1233123");
    struct Object *pair = pairNew(NULL, string1, integer1);

    struct Object *copy = pairCopy(NULL, pair->value.pair);

    assert(pairEquals(pair->value.pair, pair->value.pair) == BOOLEAN_TRUE);
    assert(pairEquals(copy->value.pair, pair->value.pair) == BOOLEAN_TRUE);

    pairSetFirst(pair->value.pair, NULL);
    assert(pairEquals(copy->value.pair, pair->value.pair) == BOOLEAN_FALSE);

    objectFree(integer1);
    objectFree(string1);
    objectFree(pair);
    objectFree(copy->value.pair->first);
    objectFree(copy->value.pair->second);
    objectFree(copy);
    printf("OK\n");
}

void testPairHash()
{
    printf("testPairHash: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *string1 = stringNew(NULL, "1233123");
    struct Object *pair = pairNew(NULL, string1, integer1);

    struct Object *copy = pairCopy(NULL, pair->value.pair);

    assert(pairHash(pair->value.pair) == pairHash(pair->value.pair));
    assert(pairHash(copy->value.pair) == pairHash(pair->value.pair));

    objectFree(integer1);
    objectFree(string1);
    objectFree(pair);
    objectFree(copy->value.pair->first);
    objectFree(copy->value.pair->second);
    objectFree(copy);
    printf("OK\n");
}

void testPairToString()
{
    printf("testPairToString: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *string1 = stringNew(NULL, "1233123");
    struct Object *pair = pairNew(NULL, string1, integer1);

    struct Object *pairString = pairToString(NULL, pair->value.pair);
    
    assert(pairString->type == OBJECT_TYPE_STRING);
    assert(pairString->value.array->objectCount == 14);
    assert(pairString->value.array->objects[0]->value.integerValue == '(');
    assert(pairString->value.array->objects[1]->value.integerValue == '1');
    assert(pairString->value.array->objects[2]->value.integerValue == '2');
    assert(pairString->value.array->objects[3]->value.integerValue == '3');
    assert(pairString->value.array->objects[4]->value.integerValue == '3');
    assert(pairString->value.array->objects[5]->value.integerValue == '1');
    assert(pairString->value.array->objects[6]->value.integerValue == '2');
    assert(pairString->value.array->objects[7]->value.integerValue == '3');
    assert(pairString->value.array->objects[8]->value.integerValue == ',');
    assert(pairString->value.array->objects[9]->value.integerValue == '1');
    assert(pairString->value.array->objects[10]->value.integerValue == '2');
    assert(pairString->value.array->objects[11]->value.integerValue == '3');
    assert(pairString->value.array->objects[12]->value.integerValue == '1');
    assert(pairString->value.array->objects[13]->value.integerValue == ')');

    objectFree(pairString);
    objectFree(integer1);
    objectFree(string1);
    objectFree(pair);
    printf("OK\n");
}

void testPairMark()
{
    printf("testPairMark: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *string1 = stringNew(NULL, "1233123");
    struct Object *pair = pairNew(NULL, string1, integer1);

    objectMark(pair);

    assert(integer1->mark == OBJECT_MARK_TRUE);
    assert(string1->mark == OBJECT_MARK_TRUE);
    assert(pair->mark == OBJECT_MARK_TRUE);

    objectFree(integer1);
    objectFree(string1);
    objectFree(pair);
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
    testDoubleNew();
    testDoubleToString();
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
    //testMapPutMany();
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

    return 0;
}