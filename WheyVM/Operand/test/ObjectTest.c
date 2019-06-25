#include "../Array.h"
#include "../Double.h"
#include "../Gc.h"
#include "../Integer.h"
#include "../Map.h"
#include "../Object.h"
#include "../Pair.h"
#include "../String.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static struct Object *getComplexObject(struct Gc *gc)
{
    struct Object *mapNameToPersonWithAdresses = mapNew(gc);

    struct Object *nameKey1 = stringNewFromCString(gc, "Willi");
    struct Object *nameKey2 = stringNewFromCString(gc, "Otto");
    struct Object *nameKey3 = stringNewFromCString(gc, "Lisa");

    struct Object *personNameKey1 = stringNewFromCString(gc, "name");
    struct Object *personAgeKey1 = stringNewFromCString(gc, "age");
    struct Object *personAgeKey2 = stringNewFromCString(gc, "age");
    struct Object *personAgeKey3 = stringNewFromCString(gc, "age");
    struct Object *personHeightKey1 = stringNewFromCString(gc, "height");
    struct Object *personHeightKey2 = stringNewFromCString(gc, "height");
    struct Object *personHeightKey3 = stringNewFromCString(gc, "height");

    struct Object *person1 = mapNew(gc);
    struct Object *person1NameValue = stringNewFromCString(gc, "Willi");
    struct Object *person1AgeValue = integerNew(gc, 25);
    struct Object *person1HeightValue = doubleNew(gc, 1.81);
    mapPut(gc, person1->value.map, personNameKey1, person1NameValue);
    mapPut(gc, person1->value.map, personAgeKey1, person1AgeValue);
    mapPut(gc, person1->value.map, personHeightKey1, person1HeightValue);

    struct Object *person2 = mapNew(gc);
    struct Object *person2NameValue = stringNewFromCString(gc, "Otto");
    struct Object *person2AgeValue = integerNew(gc, 64);
    struct Object *person2HeightValue = doubleNew(gc, 1.65);
    mapPut(gc, person2->value.map, personNameKey1, person2NameValue);
    mapPut(gc, person2->value.map, personAgeKey2, person2AgeValue);
    mapPut(gc, person2->value.map, personHeightKey2, person2HeightValue);

    struct Object *person3 = mapNew(gc);
    struct Object *person3NameValue = stringNewFromCString(gc, "Lisa");
    struct Object *person3AgeValue = integerNew(gc, 33);
    struct Object *person3HeightValue = doubleNew(gc, 1.68);
    mapPut(gc, person3->value.map, personNameKey1, person3NameValue);
    mapPut(gc, person3->value.map, personAgeKey3, person3AgeValue);
    mapPut(gc, person3->value.map, personHeightKey3, person3HeightValue);

    struct Object *address1 = mapNew(gc);
    struct Object *address1StreetKey = stringNewFromCString(gc, "street");
    struct Object *address1NumberKey = stringNewFromCString(gc, "number");
    struct Object *address1StreetValue = stringNewFromCString(gc, "Hausdorf");
    struct Object *address1NumberValue = integerNew(gc, 121);
    mapPut(gc, address1->value.map, address1StreetKey, address1StreetValue);
    mapPut(gc, address1->value.map, address1NumberKey, address1NumberValue);

    struct Object *address2 = mapNew(gc);
    struct Object *address2StreetKey = stringNewFromCString(gc, "street");
    struct Object *address2NumberKey = stringNewFromCString(gc, "number");
    struct Object *address2StreetValue = stringNewFromCString(gc, "Hausdorf");
    struct Object *address2NumberValue = integerNew(gc, 122);
    mapPut(gc, address2->value.map, address2StreetKey, address2StreetValue);
    mapPut(gc, address2->value.map, address2NumberKey, address2NumberValue);

    struct Object *address3 = mapNew(gc);
    struct Object *address3StreetKey = stringNewFromCString(gc, "street");
    struct Object *address3NumberKey = stringNewFromCString(gc, "number");
    struct Object *address3StreetValue = stringNewFromCString(gc, "Siebenseiten");
    struct Object *address3NumberValue = integerNew(gc, 32);
    mapPut(gc, address3->value.map, address3StreetKey, address3StreetValue);
    mapPut(gc, address3->value.map, address3NumberKey, address3NumberValue);

    struct Object *person1AddressArray = arrayNew(gc, 2, 2);

    person1AddressArray->value.array->objects[0] = address1;
    person1AddressArray->value.array->objects[1] = address2;

    struct Object *person2AddressArray = arrayNew(gc, 1, 1);

    person2AddressArray->value.array->objects[0] = address3;

    struct Object *person3AddressArray = arrayNew(gc, 0, 0);

    struct Object *person1Pair = pairNew(gc, person1, person1AddressArray);
    struct Object *person2Pair = pairNew(gc, person2, person2AddressArray);
    struct Object *person3Pair = pairNew(gc, person3, person3AddressArray);

    mapPut(gc, mapNameToPersonWithAdresses->value.map, nameKey1, person1Pair);
    mapPut(gc, mapNameToPersonWithAdresses->value.map, nameKey2, person2Pair);
    mapPut(gc, mapNameToPersonWithAdresses->value.map, nameKey3, person3Pair);

    return mapNameToPersonWithAdresses;
}

void testArrayNew()
{
    printf("testArrayNew: ");

    struct Object *array1 = arrayNew(NULL, 14, 14);
    assert(array1->type == OBJECT_TYPE_ARRAY);
    assert(array1->mark == OBJECT_MARK_FALSE);
    assert(array1->value.array != NULL);
    assert(array1->value.array->objectCount == 14);
    assert(array1->value.array->slotCount == 14);
    array1->value.array->objects[0] = NULL;
    assert(array1->value.array->objects[0] == NULL);

    struct Object *array2 = arrayNew(NULL, 0, 0);
    assert(array2->type == OBJECT_TYPE_ARRAY);
    assert(array2->mark == OBJECT_MARK_FALSE);
    assert(array2->value.array != NULL);
    assert(array2->value.array->objectCount == 0);
    assert(array2->value.array->slotCount == 0);

    array1->value.array->objects[13] = array2;
    assert(array1->value.array->objects[13] == array2);

    objectFree(NULL, array1);
    objectFree(NULL, array2);

    printf("OK\n");
}

void testArraySet()
{
    printf("testArraySet: ");

    struct Object *array = arrayNew(NULL, 14, 14);
    struct Object *integer = integerNew(NULL, -132);

    array->value.array->objects[10] = integer;

    assert(arraySet(array->value.array, 10, NULL) == integer);
    assert(array->value.array->objects[10] == NULL);

    objectFree(NULL, array);
    objectFree(NULL, integer);

    printf("OK\n");
}

void testArrayInsert()
{
    printf("testArrayInsert: ");
    struct Object *array = arrayNew(NULL, 0, 0);
    struct Object *integer1 = integerNew(NULL, 97);
    struct Object *integer2 = integerNew(NULL, 98);
    struct Object *integer3 = integerNew(NULL, 99);

    assert(array->value.array->objectCount == 0);
    assert(array->value.array->slotCount == 0);

    arrayInsert(NULL, array->value.array, 0, integer1);
    arrayInsert(NULL, array->value.array, 0, integer2);
    arrayInsert(NULL, array->value.array, 0, integer3);

    assert(array->value.array->objectCount == 3);
    assert(array->value.array->slotCount == 5);

    assert(array->value.array->objects[0] == integer3);
    assert(array->value.array->objects[1] == integer2);
    assert(array->value.array->objects[2] == integer1);

    arrayInsert(NULL, array->value.array, 0, integer1);
    arrayInsert(NULL, array->value.array, 1, integer2);
    arrayInsert(NULL, array->value.array, 2, integer3);

    assert(array->value.array->objectCount == 6);
    assert(array->value.array->slotCount == 10);

    assert(array->value.array->objects[0] == integer1);
    assert(array->value.array->objects[1] == integer2);
    assert(array->value.array->objects[2] == integer3);
    assert(array->value.array->objects[3] == integer3);
    assert(array->value.array->objects[4] == integer2);
    assert(array->value.array->objects[5] == integer1);

    arrayInsert(NULL, array->value.array, 6, integer2);

    assert(array->value.array->objectCount == 7);
    assert(array->value.array->slotCount == 10);
    assert(array->value.array->objects[6] == integer2);

    objectFree(NULL, array);

    objectFree(NULL, integer1);
    objectFree(NULL, integer2);
    objectFree(NULL, integer3);

    printf("OK\n");
}

void testArrayInsertAll()
{
    printf("testArrayInsertAll: ");
    struct Object *array1 = arrayNew(NULL, 3, 3);
    struct Object *array2 = arrayNew(NULL, 2, 2);
    struct Object *array3 = arrayNew(NULL, 0, 0);
    struct Object *integer1 = integerNew(NULL, 97);
    struct Object *integer2 = integerNew(NULL, 98);
    struct Object *integer3 = integerNew(NULL, 99);

    array1->value.array->objects[0] = integer1;
    array1->value.array->objects[1] = integer2;
    array1->value.array->objects[2] = integer3;

    array2->value.array->objects[0] = integer3;
    array2->value.array->objects[1] = integer2;

    assert(array1->value.array->objectCount == 3);
    assert(array1->value.array->slotCount == 3);
    assert(array2->value.array->objectCount == 2);
    assert(array2->value.array->slotCount == 2);

    arrayInsertAll(NULL, array1->value.array, 0, array2->value.array);

    assert(array1->value.array->objectCount == 5);
    assert(array1->value.array->slotCount == 8);
    assert(array2->value.array->objectCount == 2);
    assert(array2->value.array->slotCount == 2);

    assert(array1->value.array->objects[0] == integer3);
    assert(array1->value.array->objects[1] == integer2);
    assert(array1->value.array->objects[2] == integer1);
    assert(array1->value.array->objects[3] == integer2);
    assert(array1->value.array->objects[4] == integer3);

    arrayInsertAll(NULL, array1->value.array, 3, array1->value.array);

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

    arrayInsertAll(NULL, array1->value.array, 1, array2->value.array);

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

    arrayInsertAll(NULL, array2->value.array, 2, array2->value.array);

    assert(array2->value.array->objectCount == 4);
    assert(array2->value.array->slotCount == 7);

    assert(array2->value.array->objects[0] == integer3);
    assert(array2->value.array->objects[1] == integer2);
    assert(array2->value.array->objects[2] == integer3);
    assert(array2->value.array->objects[3] == integer2);

    arrayInsertAll(NULL, array2->value.array, 2, array3->value.array);

    assert(array2->value.array->objectCount == 4);
    assert(array2->value.array->slotCount == 7);
    assert(array3->value.array->objectCount == 0);
    assert(array3->value.array->slotCount == 0);

    assert(array2->value.array->objects[0] == integer3);
    assert(array2->value.array->objects[1] == integer2);
    assert(array2->value.array->objects[2] == integer3);
    assert(array2->value.array->objects[3] == integer2);

    arrayInsertAll(NULL, array2->value.array, 4, array1->value.array);

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

    objectFree(NULL, array1);
    objectFree(NULL, array2);
    objectFree(NULL, array3);

    objectFree(NULL, integer1);
    objectFree(NULL, integer2);
    objectFree(NULL, integer3);

    printf("OK\n");
}

void testArrayRemove()
{
    printf("testArrayRemove: ");
    struct Object *array1 = arrayNew(NULL, 3, 3);
    struct Object *integer1 = integerNew(NULL, 97);
    struct Object *integer2 = integerNew(NULL, 98);
    struct Object *integer3 = integerNew(NULL, 99);

    array1->value.array->objects[0] = integer1;
    array1->value.array->objects[1] = integer2;
    array1->value.array->objects[2] = integer3;

    assert(arrayRemove(array1->value.array, 1) == integer2);

    assert(array1->value.array->objectCount == 2);
    assert(array1->value.array->slotCount == 3);

    assert(array1->value.array->objects[0] == integer1);
    assert(array1->value.array->objects[1] == integer3);

    assert(arrayRemove(array1->value.array, 0) == integer1);

    assert(array1->value.array->objectCount == 1);
    assert(array1->value.array->slotCount == 3);

    assert(array1->value.array->objects[0] == integer3);

    assert(arrayRemove(array1->value.array, 0) == integer3);

    assert(array1->value.array->objectCount == 0);
    assert(array1->value.array->slotCount == 3);

    objectFree(NULL, array1);

    objectFree(NULL, integer1);
    objectFree(NULL, integer2);
    objectFree(NULL, integer3);

    printf("OK\n");
}

void testArrayCopy()
{
    printf("testArrayCopy: ");
    struct Object *array1 = arrayNew(NULL, 3, 3);
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

    objectFree(NULL, array2->value.array->objects[0]);
    objectFree(NULL, array2->value.array->objects[1]);
    objectFree(NULL, array2->value.array->objects[2]);

    objectFree(NULL, integer1);
    objectFree(NULL, integer2);
    objectFree(NULL, integer3);

    objectFree(NULL, array2);
    objectFree(NULL, array1);

    printf("OK\n");
}

void testArrayEquals()
{
    printf("testArrayEquals: ");
    struct Object *array1 = arrayNew(NULL, 3, 3);
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

    objectFree(NULL, array2->value.array->objects[0]);
    objectFree(NULL, array2->value.array->objects[1]);
    objectFree(NULL, array2->value.array->objects[2]);

    objectFree(NULL, integer1);
    objectFree(NULL, integer2);
    objectFree(NULL, integer3);

    objectFree(NULL, array2);
    objectFree(NULL, array1);

    printf("OK\n");
}

void testArrayHash()
{
    printf("testArrayHash: ");
    struct Object *array1 = arrayNew(NULL, 3, 3);
    struct Object *integer1 = integerNew(NULL, 97);
    struct Object *integer2 = integerNew(NULL, 98);
    struct Object *integer3 = integerNew(NULL, 99);

    array1->value.array->objects[0] = integer1;
    array1->value.array->objects[1] = integer2;
    array1->value.array->objects[2] = integer3;

    assert(arrayHash(array1->value.array) == arrayHash(array1->value.array));

    struct Object *array2 = arrayCopy(NULL, array1->value.array);

    assert(arrayHash(array1->value.array) == arrayHash(array2->value.array));

    struct Object *array3 = arrayNew(NULL, 0, 0);

    assert(arrayHash(array3->value.array) == 1);

    objectFree(NULL, array2->value.array->objects[0]);
    objectFree(NULL, array2->value.array->objects[1]);
    objectFree(NULL, array2->value.array->objects[2]);

    objectFree(NULL, integer1);
    objectFree(NULL, integer2);
    objectFree(NULL, integer3);

    objectFree(NULL, array3);
    objectFree(NULL, array2);
    objectFree(NULL, array1);

    printf("OK\n");
}

void testArrayToString()
{
    printf("testArrayToString: ");
    struct Object *array1 = arrayNew(NULL, 3, 3);
    struct Object *integer1 = integerNew(NULL, 7);
    struct Object *integer2 = integerNew(NULL, 98);
    struct Object *integer3 = integerNew(NULL, 121299);

    array1->value.array->objects[0] = integer1;
    array1->value.array->objects[1] = integer2;
    array1->value.array->objects[2] = integer3;

    struct Object *string1 = arrayToString(NULL, array1->value.array);

    assert(string1->value.string->characterCount == 13);

    assert(string1->value.string->characters[0] == '[');
    assert(string1->value.string->characters[1] == '7');
    assert(string1->value.string->characters[2] == ',');
    assert(string1->value.string->characters[3] == '9');
    assert(string1->value.string->characters[4] == '8');
    assert(string1->value.string->characters[5] == ',');
    assert(string1->value.string->characters[6] == '1');
    assert(string1->value.string->characters[7] == '2');
    assert(string1->value.string->characters[8] == '1');
    assert(string1->value.string->characters[9] == '2');
    assert(string1->value.string->characters[10] == '9');
    assert(string1->value.string->characters[11] == '9');
    assert(string1->value.string->characters[12] == ']');

    struct Object *array2 = arrayNew(NULL, 0, 0);

    struct Object *string2 = arrayToString(NULL, array2->value.array);

    assert(string2->value.string->characterCount == 2);

    assert(string2->value.string->characters[0] == '[');
    assert(string2->value.string->characters[1] == ']');

    objectFree(NULL, string1);
    objectFree(NULL, string2);
    
    objectFree(NULL, integer1);
    objectFree(NULL, integer2);
    objectFree(NULL, integer3);

    objectFree(NULL, array1);
    objectFree(NULL, array2);

    printf("OK\n");
}

void testArrayMark()
{
    printf("testArrayMark: ");
    struct Object *array1 = arrayNew(NULL, 3, 3);
    struct Object *array2 = arrayNew(NULL, 0, 0);
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

    objectFree(NULL, integer1);
    objectFree(NULL, integer2);
    objectFree(NULL, integer3);

    objectFree(NULL, array1);
    objectFree(NULL, array2);

    printf("OK\n");
}

void testArrayFree()
{
    printf("testArrayFree: ");
    struct Object *array1 = arrayNew(NULL, 3, 3);
    assert(array1->type == OBJECT_TYPE_ARRAY);
    objectFree(NULL, array1);

    printf("OK\n");
}

void testStringNew()
{
    printf("testStringNew: ");
    
    struct Object *string = stringNewFromCString(NULL, "Aha");
    assert(string != NULL);
    assert(string->value.string != NULL);
    assert(string->value.string->characters != NULL);
    assert(string->type == OBJECT_TYPE_STRING);
    assert(string->value.string->characterCount == 3);
    assert(string->value.string->characters[0] == 'A');
    assert(string->value.string->characters[1] == 'h');
    assert(string->value.string->characters[2] == 'a');

    struct Object *string2 = stringNewFromCString(NULL, "");
    assert(string2 != NULL);
    assert(string2->value.string != NULL);
    assert(string2->value.string->characters != NULL);
    assert(string2->type == OBJECT_TYPE_STRING);
    assert(string2->value.string->characterCount == 0);

    objectFree(NULL, string);
    objectFree(NULL, string2);
    
    printf("OK\n");
}

void testStringFromArray()
{
    printf("testStringFromArray: ");
    struct Object *array1 = arrayNew(NULL, 5, 5);
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
    assert(string->value.string->characterCount == 5);

    assert(string->value.string->characters[0] == (char) integer1->value.integerValue);
    assert(string->value.string->characters[1] == (char) integer2->value.integerValue);
    assert(string->value.string->characters[2] == (char) integer3->value.integerValue);
    assert(string->value.string->characters[3] == (char) integer4->value.integerValue);
    assert(string->value.string->characters[4] == (char) integer5->value.integerValue);

    objectFree(NULL, array1);

    objectFree(NULL, string);

    objectFree(NULL, integer1);
    objectFree(NULL, integer2);
    objectFree(NULL, integer3);
    objectFree(NULL, integer4);
    objectFree(NULL, integer5);

    printf("OK\n");
}

void testStringToArray()
{
    printf("testStringToArray: ");
    struct Object *string1 = stringNewFromCString(NULL, "hello");

    struct Object *array = stringToArray(NULL, string1->value.string);

    assert(array->type == OBJECT_TYPE_ARRAY);
    
    assert(array->value.array->objects[0]->value.integerValue == 'h');
    assert(array->value.array->objects[1]->value.integerValue == 'e');
    assert(array->value.array->objects[2]->value.integerValue == 'l');
    assert(array->value.array->objects[3]->value.integerValue == 'l');
    assert(array->value.array->objects[4]->value.integerValue == 'o');

    objectFree(NULL, string1);

    objectFree(NULL, array->value.array->objects[0]);
    objectFree(NULL, array->value.array->objects[1]);
    objectFree(NULL, array->value.array->objects[2]);
    objectFree(NULL, array->value.array->objects[3]);
    objectFree(NULL, array->value.array->objects[4]);

    objectFree(NULL, array);

    printf("OK\n");
}

void testStringCompare()
{
    printf("testStringCompare: ");
    struct Object *string1 = stringNewFromCString(NULL, "hallo1");

    struct Object *string2 = stringNewFromCString(NULL, "hallo");

    struct Object *string3 = stringNewFromCString(NULL, "banana");

    struct Object *string4 = stringNewFromCString(NULL, "");

    assert(stringCompare(string1->value.string, string1->value.string) == 0);
    assert(stringCompare(string1->value.string, string2->value.string) > 0);
    assert(stringCompare(string1->value.string, string3->value.string) > 0);
    assert(stringCompare(string2->value.string, string1->value.string) < 0);
    assert(stringCompare(string2->value.string, string2->value.string) == 0);
    assert(stringCompare(string2->value.string, string3->value.string) > 0);
    assert(stringCompare(string3->value.string, string1->value.string) < 0);
    assert(stringCompare(string3->value.string, string2->value.string) < 0);
    assert(stringCompare(string3->value.string, string3->value.string) == 0);

    objectFree(NULL, string1);
    objectFree(NULL, string2);
    objectFree(NULL, string3);
    objectFree(NULL, string4);

    printf("OK\n");
}

void testStringConcatenate()
{
    printf("testStringConcatenate: ");
    struct Object *string1 = stringNewFromCString(NULL, "hallo1");

    struct Object *string2 = stringNewFromCString(NULL, "hallo");

    struct Object *string3 = stringNewFromCString(NULL, "");

    struct Object *stringConcat1 = stringConcatenate(NULL, string1->value.string, string2->value.string);

    assert(stringConcat1->value.string->characterCount == 11);
    assert(stringConcat1->value.string->characters[0] == 'h');
    assert(stringConcat1->value.string->characters[1] == 'a');
    assert(stringConcat1->value.string->characters[2] == 'l');
    assert(stringConcat1->value.string->characters[3] == 'l');
    assert(stringConcat1->value.string->characters[4] == 'o');
    assert(stringConcat1->value.string->characters[5] == '1');
    assert(stringConcat1->value.string->characters[6] == 'h');
    assert(stringConcat1->value.string->characters[7] == 'a');
    assert(stringConcat1->value.string->characters[8] == 'l');
    assert(stringConcat1->value.string->characters[9] == 'l');
    assert(stringConcat1->value.string->characters[10] == 'o');

    struct Object *stringConcat2 = stringConcatenate(NULL, string1->value.string, string3->value.string);

    assert(stringConcat2->value.string->characterCount == 6);
    assert(stringConcat2->value.string->characters[0] == 'h');
    assert(stringConcat2->value.string->characters[1] == 'a');
    assert(stringConcat2->value.string->characters[2] == 'l');
    assert(stringConcat2->value.string->characters[3] == 'l');
    assert(stringConcat2->value.string->characters[4] == 'o');
    assert(stringConcat2->value.string->characters[5] == '1');

    objectFree(NULL, string1);
    objectFree(NULL, string2);
    objectFree(NULL, string3);
    objectFree(NULL, stringConcat1);
    objectFree(NULL, stringConcat2);

    printf("OK\n");
}

void testStringSubstring()
{
    printf("testStringSubstring: ");
    struct Object *string1 = stringNewFromCString(NULL, "hallo1");

    struct Object *string2 = stringNewFromCString(NULL, "");

    struct Object *subString1 = stringSubstring(NULL, string1->value.string, 0, 6);

    assert(subString1->value.string->characterCount == 6);
    assert(subString1->value.string->characters[0] == 'h');
    assert(subString1->value.string->characters[1] == 'a');
    assert(subString1->value.string->characters[2] == 'l');
    assert(subString1->value.string->characters[3] == 'l');
    assert(subString1->value.string->characters[4] == 'o');
    assert(subString1->value.string->characters[5] == '1');

    struct Object *subString2 = stringSubstring(NULL, string1->value.string, 0, 2);

    assert(subString2->value.string->characterCount == 2);
    assert(subString2->value.string->characters[0] == 'h');
    assert(subString2->value.string->characters[1] == 'a');

    struct Object *subString3 = stringSubstring(NULL, string1->value.string, 4, 5);

    assert(subString3->value.string->characterCount == 1);
    assert(subString3->value.string->characters[0] == 'o');

    struct Object *subString4 = stringSubstring(NULL, string2->value.string, 0, 0);

    assert(subString4->value.string->characterCount == 0);

    objectFree(NULL, string1);
    objectFree(NULL, string2);

    objectFree(NULL, subString1);
    objectFree(NULL, subString2);
    objectFree(NULL, subString3);
    objectFree(NULL, subString4);

    printf("OK\n");
}

void testStringIndexOf()
{
    printf("testStringIndexOf: ");
    struct Object *string1 = stringNewFromCString(NULL, "hallo1");

    struct Object *string2 = stringNewFromCString(NULL, "l");

    assert(stringIndexOf(string1->value.string, string2->value.string, 0) == 2);
    assert(stringIndexOf(string1->value.string, string2->value.string, 2) == 2);
    assert(stringIndexOf(string1->value.string, string2->value.string, 3) == 3);
    assert(stringIndexOf(string1->value.string, string2->value.string, 4) == -1);

    struct Object *string3 = stringNewFromCString(NULL, "lo1");

    assert(stringIndexOf(string1->value.string, string3->value.string, 0) == 3);
    assert(stringIndexOf(string1->value.string, string3->value.string, 3) == 3);
    assert(stringIndexOf(string1->value.string, string3->value.string, 4) == -1);

    objectFree(NULL, string1);
    objectFree(NULL, string2);
    objectFree(NULL, string3);

    printf("OK\n");
}

void testStringReplace()
{
    printf("testStringReplace: ");

    struct Object *string1 = stringNewFromCString(NULL, "hallo1");
    struct Object *string2 = stringNewFromCString(NULL, "l");
    struct Object *string3 = stringNewFromCString(NULL, "x");
    struct Object *string4 = stringNewFromCString(NULL, "lo1");
    struct Object *string5 = stringNewFromCString(NULL, "");

    struct Object *replacementString1 = stringReplace(NULL, string1->value.string, string2->value.string, string3->value.string);

    assert(replacementString1->value.string->characterCount == 6);
    assert(replacementString1->value.string->characters[0] == 'h');
    assert(replacementString1->value.string->characters[1] == 'a');
    assert(replacementString1->value.string->characters[2] == 'x');
    assert(replacementString1->value.string->characters[3] == 'x');
    assert(replacementString1->value.string->characters[4] == 'o');
    assert(replacementString1->value.string->characters[5] == '1');

    struct Object *replacementString2 = stringReplace(NULL, string1->value.string, string2->value.string, string4->value.string);

    assert(replacementString2->value.string->characterCount == 10);
    assert(replacementString2->value.string->characters[0] == 'h');
    assert(replacementString2->value.string->characters[1] == 'a');
    assert(replacementString2->value.string->characters[2] == 'l');
    assert(replacementString2->value.string->characters[3] == 'o');
    assert(replacementString2->value.string->characters[4] == '1');
    assert(replacementString2->value.string->characters[5] == 'l');
    assert(replacementString2->value.string->characters[6] == 'o');
    assert(replacementString2->value.string->characters[7] == '1');
    assert(replacementString2->value.string->characters[8] == 'o');
    assert(replacementString2->value.string->characters[9] == '1');

    struct Object *replacementString3 = stringReplace(NULL, string1->value.string, string4->value.string, string3->value.string);

    assert(replacementString3->value.string->characterCount == 4);
    assert(replacementString3->value.string->characters[0] == 'h');
    assert(replacementString3->value.string->characters[1] == 'a');
    assert(replacementString3->value.string->characters[2] == 'l');
    assert(replacementString3->value.string->characters[3] == 'x');

    struct Object *replacementString4 = stringReplace(NULL, string1->value.string, string4->value.string, string5->value.string);

    assert(replacementString4->value.string->characterCount == 3);
    assert(replacementString4->value.string->characters[0] == 'h');
    assert(replacementString4->value.string->characters[1] == 'a');
    assert(replacementString4->value.string->characters[2] == 'l');

    struct Object *replacementString5 = stringReplace(NULL, string1->value.string, string1->value.string, string5->value.string);

    assert(replacementString5->value.string->characterCount == 0);

    struct Object *replacementString6 = stringReplace(NULL, string1->value.string, string1->value.string, string1->value.string);

    assert(replacementString6->value.string->characterCount == 6);
    assert(replacementString6->value.string->characters[0] == 'h');
    assert(replacementString6->value.string->characters[1] == 'a');
    assert(replacementString6->value.string->characters[2] == 'l');
    assert(replacementString6->value.string->characters[3] == 'l');
    assert(replacementString6->value.string->characters[4] == 'o');
    assert(replacementString6->value.string->characters[5] == '1');

    struct Object *replacementString7 = stringReplace(NULL, string3->value.string, string4->value.string, string1->value.string);

    assert(replacementString7->value.string->characterCount == 1);
    assert(replacementString7->value.string->characters[0] == 'x');


    struct Object *replacementString8 = stringReplace(NULL, string4->value.string, string5->value.string, string1->value.string);

    assert(replacementString8->value.string->characterCount == 3);
    assert(replacementString8->value.string->characters[0] == 'l');
    assert(replacementString8->value.string->characters[1] == 'o');
    assert(replacementString8->value.string->characters[2] == '1');

    objectFree(NULL, string1);
    objectFree(NULL, string2);
    objectFree(NULL, string3);
    objectFree(NULL, string4);
    objectFree(NULL, string5);
    objectFree(NULL, replacementString1);
    objectFree(NULL, replacementString2);
    objectFree(NULL, replacementString3);
    objectFree(NULL, replacementString4);
    objectFree(NULL, replacementString5);
    objectFree(NULL, replacementString6);
    objectFree(NULL, replacementString7);
    objectFree(NULL, replacementString8);
    printf("OK\n");
}

void testStringCopy()
{
    printf("testStringCopy: ");
    struct Object *string1 = stringNewFromCString(NULL, "hallo1");
    struct Object *string2 = stringCopy(NULL, string1->value.string);

    assert(string2->type == OBJECT_TYPE_STRING);
    assert(string2->value.string->characterCount == string1->value.string->characterCount);
    assert(string2->value.string->characters[0] == string1->value.string->characters[0]);
    assert(string2->value.string->characters[1] == string1->value.string->characters[1]);
    assert(string2->value.string->characters[2] == string1->value.string->characters[2]);
    assert(string2->value.string->characters[3] == string1->value.string->characters[3]);
    assert(string2->value.string->characters[4] == string1->value.string->characters[4]);
    assert(string2->value.string->characters[5] == string1->value.string->characters[5]);

    objectFree(NULL, string1);
    objectFree(NULL, string2);

    printf("OK\n");
}

void testStringEquals()
{
    printf("testStringEquals: ");

    struct Object *string1 = stringNewFromCString(NULL, "hallo1");

    struct Object *string2 = stringCopy(NULL, string1->value.string);

    struct Object *string3 = stringNewFromCString(NULL, "ban");

    struct Object *string4 = stringNewFromCString(NULL, "");

    assert(stringEquals(string1->value.string, string1->value.string) == BOOLEAN_TRUE);
    assert(stringEquals(string1->value.string, string2->value.string) == BOOLEAN_TRUE);
    assert(stringEquals(string1->value.string, string3->value.string) == BOOLEAN_FALSE);
    assert(stringEquals(string1->value.string, string4->value.string) == BOOLEAN_FALSE);
    assert(stringEquals(string2->value.string, string1->value.string) == BOOLEAN_TRUE);
    assert(stringEquals(string2->value.string, string2->value.string) == BOOLEAN_TRUE);
    assert(stringEquals(string2->value.string, string3->value.string) == BOOLEAN_FALSE);
    assert(stringEquals(string2->value.string, string4->value.string) == BOOLEAN_FALSE);
    assert(stringEquals(string3->value.string, string1->value.string) == BOOLEAN_FALSE);
    assert(stringEquals(string3->value.string, string2->value.string) == BOOLEAN_FALSE);
    assert(stringEquals(string3->value.string, string3->value.string) == BOOLEAN_TRUE);
    assert(stringEquals(string3->value.string, string4->value.string) == BOOLEAN_FALSE);
    assert(stringEquals(string4->value.string, string1->value.string) == BOOLEAN_FALSE);
    assert(stringEquals(string4->value.string, string2->value.string) == BOOLEAN_FALSE);
    assert(stringEquals(string4->value.string, string3->value.string) == BOOLEAN_FALSE);
    assert(stringEquals(string4->value.string, string4->value.string) == BOOLEAN_TRUE);

    objectFree(NULL, string1);
    objectFree(NULL, string2);
    objectFree(NULL, string3);
    objectFree(NULL, string4);

    printf("OK\n");
}

void testStringHash()
{
    printf("testStringHash: ");

    struct Object *string1 = stringNewFromCString(NULL, "hallo1");

    struct Object *string2 = stringCopy(NULL, string1->value.string);

    struct Object *string3 = stringNewFromCString(NULL, "");
    struct Object *string4 = stringNewFromCString(NULL, "");

    assert(stringHash(string1->value.string) == stringHash(string2->value.string));
    assert(stringHash(string3->value.string) == stringHash(string4->value.string));

    objectFree(NULL, string1);
    objectFree(NULL, string2);
    objectFree(NULL, string3);
    objectFree(NULL, string4);

    printf("OK\n");
}

void testStringAppendCharacter()
{
    printf("testStringAppendCharacter: ");
    struct Object *string1 = stringNewFromCString(NULL, "hallo1");

    struct Object *string2 = stringNewFromCString(NULL, "");

    stringAppendCharacter(string2->value.string, 'h');
    stringAppendCharacter(string2->value.string, 'a');
    stringAppendCharacter(string2->value.string, 'l');
    stringAppendCharacter(string2->value.string, 'l');
    stringAppendCharacter(string2->value.string, 'o');
    stringAppendCharacter(string2->value.string, '1');

    assert(stringEquals(string1->value.string, string2->value.string) == BOOLEAN_TRUE);

    objectFree(NULL, string1);
    objectFree(NULL, string2);

    printf("OK\n");
}

void testStringFree()
{
    printf("testStringFree: ");
    struct Object *string1 = stringNewFromCString(NULL, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    objectFree(NULL, string1);

    printf("OK\n");
}

void testDoubleNew()
{
    printf("testDoubleNew: ");
    struct Object *double1 = doubleNew(NULL, 0.001);
    assert(double1->type == OBJECT_TYPE_DOUBLE);
    assert(double1->mark == OBJECT_MARK_FALSE);
    assert(double1->value.doubleValue == 0.001);
    objectFree(NULL, double1);
    printf("OK\n");
}

void testDoubleToString()
{
    printf("testDoubleToString: ");
    struct Object *double1 = doubleNew(NULL, 0.0010105);

    struct Object *string = doubleToString(NULL, double1->value.doubleValue);

    assert(string->type == OBJECT_TYPE_STRING);

    assert(string->value.string->characterCount == 16);
    assert(string->value.string->characters[0] == '1');
    assert(string->value.string->characters[1] == '.');
    assert(string->value.string->characters[2] == '0');
    assert(string->value.string->characters[3] == '1');
    assert(string->value.string->characters[4] == '0');
    assert(string->value.string->characters[5] == '5');
    assert(string->value.string->characters[6] == '0');
    assert(string->value.string->characters[7] == '0');
    assert(string->value.string->characters[8] == '0');
    assert(string->value.string->characters[9] == '0');
    assert(string->value.string->characters[10] == '0');
    assert(string->value.string->characters[11] == '0');
    assert(string->value.string->characters[12] == 'e');
    assert(string->value.string->characters[13] == '-');
    assert(string->value.string->characters[14] == '0');
    assert(string->value.string->characters[15] == '3');
    
    objectFree(NULL, string);
    objectFree(NULL, double1);
    printf("OK\n");
}

void testGcNew()
{
    printf("testGcNew: ");
    struct Gc *gc = gcNew(1, 0.5, 0);

    assert(gc->freeCount == 0);
    assert(gc->newCount == 0);
    assert(gc->head == NULL);

    gcFree(gc);

    printf("OK\n");
}

void testGcRegisterObject()
{
    printf("testGcRegisterObject: ");
    struct Gc *gc = gcNew(150, 0.4, 0);
    struct Object *array1 = arrayNew(gc, 3, 3);
    struct Object *integer1 = integerNew(gc, 7);
    struct Object *integer2 = integerNew(gc, 98);
    struct Object *integer3 = integerNew(gc, 121299);
    assert(gc->size == 4 * sizeof(struct Object) + sizeof(struct Array) + 3 * sizeof(struct Object *));

    array1->value.array->objects[0] = integer1;
    array1->value.array->objects[1] = integer2;
    array1->value.array->objects[2] = integer3;

    struct Object *string1 = stringNewFromCString(gc, "hallo1");

    assert(gc->newCount == 5);
    assert(gc->freeCount == 0);
    assert(gc->head->object == string1);
    assert(gc->head->next->object == integer3);
    assert(gc->head->next->next->object == integer2);
    assert(gc->head->next->next->next->object == integer1);
    assert(gc->head->next->next->next->next->object == array1);
    assert(gc->head->next->next->next->next->next == NULL);

    assert(gc->outOfMemory == 0);
    assert(gc->size == 5 * sizeof(struct Object) + sizeof(struct Array) + 3 * sizeof(struct Object *) + sizeof(struct String) + 6 * sizeof(Char));

    gcFree(gc);

    printf("OK\n");
}

void testGcRegisterObjectFull1()
{
    printf("testGcRegisterObjectFull1: ");
    struct Gc *gc = gcNew(sizeof(struct Object) + sizeof(struct Array), 0.5, 0);
    arrayNew(gc, 3, 3);
    assert(gc->outOfMemory == 1);
    assert(gc->size == sizeof(struct Object) + sizeof(struct Array) + 3 * sizeof(struct Object *));

    gcFree(gc);

    printf("OK\n");
}

void testGcRegisterObjectFull2()
{
    printf("testGcRegisterObjectFull2: ");
    struct Gc *gc = gcNew(2 * sizeof(struct Object), 0.5, 0);
    integerNew(gc, 23);
    assert(gc->outOfMemory == 0);
    assert(gc->size == sizeof(struct Object));

    integerNew(gc, 13);
    assert(gc->outOfMemory == 0);
    assert(gc->size == 2 * sizeof(struct Object));

    integerNew(gc, 16);
    assert(gc->outOfMemory == 1);
    assert(gc->size == 3 * sizeof(struct Object));

    gcFree(gc);

    printf("OK\n");
}

void testGcRequestMemory()
{
    printf("testGcRequestMemory: ");
    struct Gc *gc = gcNew(1000, 0.5, 0);
    arrayNew(gc, 23, 23);
    assert(gc->size == sizeof(struct Object) + sizeof(struct Array) + 23 * sizeof(struct Object *));
    uint32_t oldSize = gc->size;

    struct Object *double1 = doubleNew(gc, 13);
    assert(gc->size == oldSize + sizeof(struct Object));
    oldSize = gc->size;

    struct Object *integer1 = integerNew(gc, 16);
    assert(gc->size == oldSize + sizeof(struct Object));
    oldSize = gc->size;

    struct Object *map = mapNew(gc);
    assert(gc->size == oldSize + sizeof(struct Object) + sizeof(struct Map) + 8 * sizeof(struct MapEntry *));
    oldSize = gc->size;

    mapPut(gc, map->value.map, integer1, double1);
    assert(gc->size == oldSize + sizeof(struct MapEntry));
    oldSize = gc->size;

    pairNew(gc, integer1, double1);
    assert(gc->size == oldSize + sizeof(struct Object) + sizeof(struct Pair));
    oldSize = gc->size;

    stringNewFromCString(gc, "double1");
    assert(gc->size == oldSize + sizeof(struct Object) + sizeof(struct String) + 7 * sizeof(Char));
    oldSize = gc->size;

    gcSweep(gc);

    assert(gc->size == 0);

    gcFree(gc);

    printf("OK\n");
}

void testGcReleaseMemory()
{
    printf("testGcReleaseMemory: ");
    struct Gc *gc = gcNew(1000, 0.5, 0);
    struct Object *array = arrayNew(gc, 4, 4);
    assert(gc->size == sizeof(struct Object) + sizeof(struct Array) + 4 * sizeof(struct Object *));
    uint32_t oldSize = gc->size;

    struct Object *double1 = doubleNew(gc, 13);
    assert(gc->size == oldSize + sizeof(struct Object));
    oldSize = gc->size;

    struct Object *integer1 = integerNew(gc, 16);
    assert(gc->size == oldSize + sizeof(struct Object));
    oldSize = gc->size;

    arraySet(array->value.array, 0, double1);
    arraySet(array->value.array, 1, integer1);

    struct Object *map = mapNew(gc);
    assert(gc->size == oldSize + sizeof(struct Object) + sizeof(struct Map) + 8 * sizeof(struct MapEntry *));
    oldSize = gc->size;

    mapPut(gc, map->value.map, integer1, double1);
    assert(gc->size == oldSize + sizeof(struct MapEntry));
    oldSize = gc->size;

    mapPut(gc, map->value.map, array, double1);
    assert(gc->size == oldSize + sizeof(struct MapEntry));
    oldSize = gc->size;

    struct Object *pair = pairNew(gc, integer1, double1);
    assert(gc->size == oldSize + sizeof(struct Object) + sizeof(struct Pair));
    oldSize = gc->size;

    struct Object *string = stringNewFromCString(gc, "double1");
    assert(gc->size == oldSize + sizeof(struct Object) + sizeof(struct String) + 7 * sizeof(Char));
    oldSize = gc->size;

    arraySet(array->value.array, 2, string);

    pairNew(gc, pair, array);
    assert(gc->size == oldSize + sizeof(struct Object) + sizeof(struct Pair));
    oldSize = gc->size;

    pairNew(gc, string, map);
    assert(gc->size == oldSize + sizeof(struct Object) + sizeof(struct Pair));
    oldSize = gc->size;

    gcSweep(gc);

    assert(gc->size == 0);

    gcFree(gc);

    printf("OK\n");
}

void testGcShouldMarkAndSweep()
{
    printf("testGcShouldMarkAndSweep: ");
    struct Gc *gc = gcNew(3 * sizeof(struct Object), 0.5, 0);
    integerNew(gc, 23);
    assert(gcShouldMarkAndSweep(gc) == 0);
    assert(gc->size == sizeof(struct Object));

    integerNew(gc, 13);
    assert(gcShouldMarkAndSweep(gc) == 1);
    assert(gc->outOfMemory == 0);
    assert(gc->size == 2 * sizeof(struct Object));

    gcFree(gc);

    printf("OK\n");
}

void testGcSweep()
{
    printf("testGcSweep: ");
    struct Gc *gc = gcNew(250, 0.6, 0);
    struct Object *array1 = arrayNew(gc, 3, 3);
    struct Object *integer1 = integerNew(gc, 7);
    struct Object *integer2 = integerNew(gc, 98);
    struct Object *integer3 = integerNew(gc, 121299);

    array1->value.array->objects[0] = integer1;
    array1->value.array->objects[1] = integer2;
    array1->value.array->objects[2] = integer3;

    struct Object *string = stringNewFromCString(gc, "hallo1");

    assert(gc->newCount == 5);
    assert(gc->size == 5 * sizeof(struct Object) + sizeof(struct Array) + 3 * sizeof(struct Object *) + sizeof(struct String) + 6 * sizeof(Char));

    integer1->mark = OBJECT_MARK_TRUE;
    string->mark = OBJECT_MARK_TRUE;

    gcSweep(gc);

    assert(gc->freeCount == 3);
    assert(gc->head->object == string);
    assert(gc->head->next->object == integer1);
    assert(gc->head->next->next == NULL);
    assert(gc->size == 2 * sizeof(struct Object) + sizeof(struct String) + 6 * sizeof(Char));

    integer1->mark = OBJECT_MARK_TRUE;

    gcSweep(gc);

    assert(gc->freeCount == 4);
    assert(gc->head->object == integer1);
    assert(gc->head->next == NULL);
    assert(gc->size == sizeof(struct Object));

    gcSweep(gc);

    assert(gc->freeCount == 5);
    assert(gc->head == NULL);
    assert(gc->size == 0);

    struct Object *arrayString1 = stringNewFromCString(gc, "");
    struct Object *arrayString2 = arrayToString(gc, stringToArray(gc, arrayString1->value.string)->value.array);
    struct Object *arrayString3 = arrayToString(gc, stringToArray(gc, arrayString2->value.string)->value.array);

    assert(arrayString3->value.array->objectCount == 7);

    gcSweep(gc);

    assert(gc->freeCount == 12);
    assert(gc->freeCount == gc->newCount);
    assert(gc->head == NULL);
    assert(gc->size == 0);

    gcFree(gc);

    printf("OK\n");
}

void testGcFree()
{
    printf("testGcFree: ");
    struct Gc *gc = gcNew(100, 0.6, 0);
    gcFree(gc);
    printf("OK\n");
}

void testIntegerNew()
{
    printf("testIntegerNew: ");
    struct Object *integer = integerNew(NULL, 1231212);

    assert(integer->type == OBJECT_TYPE_INTEGER);
    assert(integer->value.integerValue == 1231212);

    objectFree(NULL, integer);
    printf("OK\n");
}

void testIntegerToString()
{
    printf("testIntegerToString: ");
    struct Object *integer1 = integerNew(NULL, 10105);

    struct Object *string = integerToString(NULL, integer1->value.integerValue);

    assert(string->type == OBJECT_TYPE_STRING);

    assert(string->value.string->characterCount == 5);
    assert(string->value.string->characters[0] == '1');
    assert(string->value.string->characters[1] == '0');
    assert(string->value.string->characters[2] == '1');
    assert(string->value.string->characters[3] == '0');
    assert(string->value.string->characters[4] == '5');
    
    objectFree(NULL, string);
    objectFree(NULL, integer1);
    printf("OK\n");
}

void testMapNew()
{
    printf("testMapNew: ");
    struct Object *map1 = mapNew(NULL);

    assert(map1->type == OBJECT_TYPE_MAP);

    assert(map1->value.map->bucketCount == 8);

    objectFree(NULL, map1);

    printf("OK\n");
}

void testMapGet()
{
    printf("testMapGet: ");
    struct Object *map1 = mapNew(NULL);
    struct Object *integer1 = integerNew(NULL, 1212);

    struct Object *string1 = stringNewFromCString(NULL, "hallo1");

    assert(mapGet(map1->value.map, integer1) == NULL);
    assert(mapGet(map1->value.map, string1) == NULL);
    assert(mapGet(map1->value.map, map1) == NULL);

    objectFree(NULL, map1);
    objectFree(NULL, integer1);
    objectFree(NULL, string1);

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

    assert(mapPut(NULL, map1->value.map, integer1, integer6) == NULL);
    assert(map1->value.map->entryCount == 1);
    assert(map1->value.map->bucketCount == 8);

    assert(mapPut(NULL, map1->value.map, integer2, integer7) == NULL);
    assert(map1->value.map->entryCount == 2);
    assert(map1->value.map->bucketCount == 8);

    assert(mapPut(NULL, map1->value.map, integer3, integer8) == NULL);
    assert(map1->value.map->entryCount == 3);
    assert(map1->value.map->bucketCount == 8);

    assert(mapPut(NULL, map1->value.map, integer4, integer9) == NULL);
    assert(map1->value.map->entryCount == 4);
    assert(map1->value.map->bucketCount == 8);
    
    assert(mapPut(NULL, map1->value.map, integer5, integer10) == integer7);
    assert(mapGet(map1->value.map, integer5) == integer10);
    assert(map1->value.map->entryCount == 4);
    assert(map1->value.map->bucketCount == 8);

    assert(mapPut(NULL, map1->value.map, integer6, integer5) == NULL);
    assert(mapGet(map1->value.map, integer6) == integer5);
    assert(map1->value.map->entryCount == 5);
    assert(map1->value.map->bucketCount == 8);

    assert(mapPut(NULL, map1->value.map, integer7, integer4) == NULL);
    assert(mapGet(map1->value.map, integer7) == integer4);
    assert(map1->value.map->entryCount == 6);
    assert(map1->value.map->bucketCount == 8);

    assert(mapPut(NULL, map1->value.map, integer8, integer3) == NULL);
    assert(mapGet(map1->value.map, integer8) == integer3);
    assert(map1->value.map->entryCount == 7);
    assert(map1->value.map->bucketCount == 16);

    assert(mapPut(NULL, map1->value.map, integer9, integer2) == NULL);
    assert(mapGet(map1->value.map, integer9) == integer2);
    assert(map1->value.map->entryCount == 8);
    assert(map1->value.map->bucketCount == 16);

    assert(mapPut(NULL, map1->value.map, NULL, integer1) == NULL);
    assert(mapGet(map1->value.map, NULL) == integer1);
    assert(map1->value.map->entryCount == 9);
    assert(map1->value.map->bucketCount == 16);

    assert(mapPut(NULL, map1->value.map, NULL, NULL) == integer1);
    assert(mapGet(map1->value.map, NULL) == NULL);
    assert(map1->value.map->entryCount == 9);
    assert(map1->value.map->bucketCount == 16);

    objectFree(NULL, map1);
    objectFree(NULL, integer1);
    objectFree(NULL, integer2);
    objectFree(NULL, integer3);
    objectFree(NULL, integer4);
    objectFree(NULL, integer5);
    objectFree(NULL, integer6);
    objectFree(NULL, integer7);
    objectFree(NULL, integer8);
    objectFree(NULL, integer9);
    objectFree(NULL, integer10);

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
        assert(mapPut(NULL, map->value.map, objects[i], objects[i]) == NULL);
    }
    
    for (int i = 0; i < largeNum; i++)
    {
        assert(mapGet(map->value.map, objects[i]) == objects[i]);
        free(objects[i]);
    }

    free(objects);
    objectFree(NULL, map);

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

    mapPut(NULL, map1->value.map, integer1, integer6);
    mapPut(NULL, map1->value.map, integer2, integer7);
    mapPut(NULL, map1->value.map, integer3, integer8);
    mapPut(NULL, map1->value.map, integer4, integer9);

    mapPut(NULL, map2->value.map, integer5, integer10);
    mapPut(NULL, map2->value.map, integer7, integer1);

    mapPutAll(NULL, map1->value.map, map2->value.map);

    assert(map1->value.map->entryCount == 5);
    assert(map1->value.map->bucketCount == 8);
    assert(mapGet(map1->value.map, integer1) == integer6);
    assert(mapGet(map1->value.map, integer2) == integer10);
    assert(mapGet(map1->value.map, integer3) == integer8);
    assert(mapGet(map1->value.map, integer4) == integer9);
    assert(mapGet(map1->value.map, integer5) == integer10);
    assert(mapGet(map1->value.map, integer7) == integer1);

    mapPutAll(NULL, map2->value.map, map3->value.map);

    assert(map2->value.map->entryCount == 2);
    assert(map2->value.map->bucketCount == 8);
    assert(mapGet(map2->value.map, integer5) == integer10);
    assert(mapGet(map2->value.map, integer7) == integer1);

    mapPutAll(NULL, map2->value.map, map2->value.map);

    assert(map2->value.map->entryCount == 2);
    assert(map2->value.map->bucketCount == 8);
    assert(mapGet(map2->value.map, integer5) == integer10);
    assert(mapGet(map2->value.map, integer7) == integer1);

    objectFree(NULL, map1);
    objectFree(NULL, map2);
    objectFree(NULL, map3);

    objectFree(NULL, integer1);
    objectFree(NULL, integer2);
    objectFree(NULL, integer3);
    objectFree(NULL, integer4);
    objectFree(NULL, integer5);
    objectFree(NULL, integer6);
    objectFree(NULL, integer7);
    objectFree(NULL, integer8);
    objectFree(NULL, integer9);
    objectFree(NULL, integer10);

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

    mapPut(NULL, map1->value.map, integer1, integer6);
    mapPut(NULL, map1->value.map, integer2, integer7);
    mapPut(NULL, map1->value.map, integer3, integer8);
    mapPut(NULL, map1->value.map, integer4, integer9);

    assert(mapRemove(NULL, map1->value.map, integer2) == integer7);
    assert(map1->value.map->entryCount == 3);
    assert(mapGet(map1->value.map, integer2) == NULL);

    assert(mapRemove(NULL, map1->value.map, integer2) == NULL);
    assert(map1->value.map->entryCount == 3);

    assert(mapRemove(NULL, map1->value.map, integer4) == integer9);
    assert(map1->value.map->entryCount == 2);
    assert(mapGet(map1->value.map, integer4) == NULL);

    assert(mapRemove(NULL, map1->value.map, integer3) == integer8);
    assert(map1->value.map->entryCount == 1);
    assert(mapGet(map1->value.map, integer3) == NULL);

    assert(mapRemove(NULL, map1->value.map, integer1) == integer6);
    assert(map1->value.map->entryCount == 0);
    assert(mapGet(map1->value.map, integer1) == NULL);

    assert(mapRemove(NULL, map1->value.map, NULL) == NULL);
    assert(map1->value.map->entryCount == 0);

    objectFree(NULL, map1);

    objectFree(NULL, integer1);
    objectFree(NULL, integer2);
    objectFree(NULL, integer3);
    objectFree(NULL, integer4);
    objectFree(NULL, integer5);
    objectFree(NULL, integer6);
    objectFree(NULL, integer7);
    objectFree(NULL, integer8);
    objectFree(NULL, integer9);
    objectFree(NULL, integer10);

    printf("OK\n");
}

void testMapHasKey()
{
    printf("testMapHasKey: ");

    struct Object *map1 = mapNew(NULL);
    struct Object *integer1 = integerNew(NULL, 1);

    assert(mapHasKey(map1->value.map, integer1) == BOOLEAN_FALSE);
    assert(mapHasKey(map1->value.map, NULL) == BOOLEAN_FALSE);

    mapPut(NULL, map1->value.map, integer1, NULL);

    assert(mapHasKey(map1->value.map, integer1) == BOOLEAN_TRUE);

    mapRemove(NULL, map1->value.map, integer1);

    assert(mapHasKey(map1->value.map, integer1) == BOOLEAN_FALSE);

    objectFree(NULL, map1);
    objectFree(NULL, integer1);

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

    mapPut(NULL, map1->value.map, integer1, integer6);
    mapPut(NULL, map1->value.map, integer2, integer7);
    mapPut(NULL, map1->value.map, integer3, integer8);
    mapPut(NULL, map1->value.map, integer4, integer9);
    mapPut(NULL, map1->value.map, integer5, integer10);

    struct Object *emptyArray = mapEntries(NULL, map2->value.map);
    assert(emptyArray->value.array->objectCount == 0);

    struct Object *array = mapEntries(NULL, map1->value.map);

    assert(array->type == OBJECT_TYPE_ARRAY);
    assert(array->value.array->objectCount == 5);
    assert(array->value.array->slotCount == 5);

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

    objectFree(NULL, array->value.array->objects[0]);
    objectFree(NULL, array->value.array->objects[1]);
    objectFree(NULL, array->value.array->objects[2]);
    objectFree(NULL, array->value.array->objects[3]);
    objectFree(NULL, array->value.array->objects[4]);

    objectFree(NULL, array);
    objectFree(NULL, emptyArray);
    objectFree(NULL, map1);
    objectFree(NULL, map2);

    objectFree(NULL, integer1);
    objectFree(NULL, integer2);
    objectFree(NULL, integer3);
    objectFree(NULL, integer4);
    objectFree(NULL, integer5);
    objectFree(NULL, integer6);
    objectFree(NULL, integer7);
    objectFree(NULL, integer8);
    objectFree(NULL, integer9);
    objectFree(NULL, integer10);
    printf("OK\n");
}

void testMapCopy()
{
    printf("testMapCopy: ");
    struct Object *map1 = mapNew(NULL);

    struct Object *string1 = stringNewFromCString(NULL, "hier");
    struct Object *string2 = stringNewFromCString(NULL, "dort");
    struct Object *string3 = stringNewFromCString(NULL, "nah");
    struct Object *string4 = stringNewFromCString(NULL, "fern");
    struct Object *integer1 = integerNew(NULL, 2);

    mapPut(NULL, map1->value.map, string1, string2);
    mapPut(NULL, map1->value.map, string3, string4);
    mapPut(NULL, map1->value.map, integer1, NULL);
    mapPut(NULL, map1->value.map, NULL, integer1);

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
            objectFree(NULL, currEntry->key);
            objectFree(NULL, currEntry->value);

            currEntry = currEntry->next;
        }
    }

    objectFree(NULL, integer1);
    objectFree(NULL, string1);
    objectFree(NULL, string2);
    objectFree(NULL, string3);
    objectFree(NULL, string4);
    objectFree(NULL, map1);
    objectFree(NULL, map2);
    printf("OK\n");
}

void testMapEquals()
{
    printf("testMapEquals: ");
    struct Gc *gc = gcNew(1000, 0.9, 0);
    struct Object *map1 = mapNew(gc);
    struct Object *map2 = mapNew(gc);

    struct Object *string1 = stringNewFromCString(gc, "hier");
    struct Object *string2 = stringNewFromCString(gc, "dort");
    struct Object *string3 = stringNewFromCString(gc, "nah");
    struct Object *string4 = stringNewFromCString(gc, "fern");
    struct Object *integer1 = integerNew(gc, 2);

    mapPut(gc, map1->value.map, string1, string2);
    mapPut(gc, map1->value.map, string3, string4);
    mapPut(gc, map1->value.map, integer1, NULL);
    mapPut(gc, map1->value.map, NULL, integer1);

    mapPut(gc, map2->value.map, string1, string2);

    assert(mapEquals(map1->value.map, map2->value.map) == BOOLEAN_FALSE);
    assert(mapEquals(map2->value.map, map1->value.map) == BOOLEAN_FALSE);

    struct Object *mapCopy1 = mapCopy(gc, map1->value.map);

    assert(mapEquals(map1->value.map, map1->value.map) == BOOLEAN_TRUE);
    assert(mapEquals(map1->value.map, mapCopy1->value.map) == BOOLEAN_TRUE);
    
    mapRemove(gc, mapCopy1->value.map, integer1);
    
    assert(mapEquals(map1->value.map, mapCopy1->value.map) == BOOLEAN_FALSE);

    mapPut(gc, mapCopy1->value.map, integer1, integer1);

    assert(mapEquals(map1->value.map, mapCopy1->value.map) == BOOLEAN_FALSE);

    mapPut(gc, mapCopy1->value.map, integer1, NULL);

    assert(mapEquals(map1->value.map, mapCopy1->value.map) == BOOLEAN_TRUE);

    gcSweep(gc);

    assert(gc->freeCount == 14);
    assert(gc->head == NULL);
    assert(gc->size == 0);

    gcFree(gc);
    printf("OK\n");
}

void testMapHash()
{
    printf("testMapHash: ");
    struct Gc *gc = gcNew(1000, 0.9, 0);
    struct Object *map1 = mapNew(gc);

    struct Object *string1 = stringNewFromCString(gc, "hier");
    struct Object *string2 = stringNewFromCString(gc, "dort");
    struct Object *string3 = stringNewFromCString(gc, "nah");
    struct Object *string4 = stringNewFromCString(gc, "fern");
    struct Object *integer1 = integerNew(gc, 2);

    mapPut(gc, map1->value.map, string1, string2);
    mapPut(gc, map1->value.map, string3, string4);
    mapPut(gc, map1->value.map, integer1, NULL);
    mapPut(gc, map1->value.map, NULL, integer1);

    struct Object *map2 = mapCopy(gc, map1->value.map);

    assert(mapHash(map1->value.map) == mapHash(map1->value.map));
    assert(mapHash(map1->value.map) == mapHash(map2->value.map));
    
    mapRemove(gc, map2->value.map, integer1);
    mapPut(gc, map2->value.map, integer1, integer1);
    mapPut(gc, map2->value.map, integer1, NULL);

    assert(mapHash(map1->value.map) == mapHash(map2->value.map));

    gcSweep(gc);

    assert(gc->freeCount == 13);
    assert(gc->head == NULL);
    assert(gc->size == 0);

    gcFree(gc);
    printf("OK\n");
}

void testMapToString()
{
    printf("testMapToString: ");
    struct Object *map1 = mapNew(NULL);

    struct Object *string1 = stringNewFromCString(NULL, "hier");
    struct Object *string2 = stringNewFromCString(NULL, "dort");
    struct Object *string3 = stringNewFromCString(NULL, "nah");
    struct Object *string4 = stringNewFromCString(NULL, "fern");
    struct Object *integer1 = integerNew(NULL, 2);

    mapPut(NULL, map1->value.map, string1, string2);
    mapPut(NULL, map1->value.map, string3, string4);
    mapPut(NULL, map1->value.map, integer1, NULL);
    mapPut(NULL, map1->value.map, NULL, integer1);

    struct Object *mapString1 = mapToString(NULL, map1->value.map);

    assert(mapString1->type == OBJECT_TYPE_STRING);
    assert(mapString1->value.string->characterCount == 34);

    objectFree(NULL, map1);
    objectFree(NULL, string1);
    objectFree(NULL, string2);
    objectFree(NULL, string3);
    objectFree(NULL, string4);
    objectFree(NULL, integer1);
    objectFree(NULL, mapString1);

    printf("OK\n");
}

void testMapMark()
{
    printf("testMapMark: ");
    struct Object *map1 = mapNew(NULL);

    struct Object *string1 = stringNewFromCString(NULL, "hier");
    struct Object *string2 = stringNewFromCString(NULL, "dort");
    struct Object *string3 = stringNewFromCString(NULL, "nah");
    struct Object *string4 = stringNewFromCString(NULL, "fern");
    struct Object *integer1 = integerNew(NULL, 2);

    mapPut(NULL, map1->value.map, string1, string2);
    mapPut(NULL, map1->value.map, string3, string4);
    mapPut(NULL, map1->value.map, integer1, NULL);
    mapPut(NULL, map1->value.map, NULL, integer1);

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

    objectFree(NULL, map1);
    objectFree(NULL, string1);
    objectFree(NULL, string2);
    objectFree(NULL, string3);
    objectFree(NULL, string4);
    objectFree(NULL, integer1);

    printf("OK\n");
}

void testMapFree()
{
    printf("testMapFree: ");
    struct Object *map = mapNew(NULL);
    objectFree(NULL, map);
    printf("OK\n");
}

void testObjectCopy()
{
    printf("testObjectCopy: ");
    struct Gc *gc = gcNew(10000, 0.9, 0);

    struct Object *object = getComplexObject(gc);

    uint32_t oldSize = gc->size;
    uint32_t oldNewCount = gc->newCount;

    struct Object *copy = objectCopy(gc, object);
    
    // if object is in container multiple times copy is called multiple times on said object 
    assert(gc->newCount >= oldNewCount * 2); 
    assert(gc->size >= oldSize * 2);

    assert(copy != object);

    assert(mapGet(object->value.map, stringNewFromCString(gc, "Willi")) != mapGet(copy->value.map, stringNewFromCString(gc, "Willi")));
    assert(mapGet(object->value.map, stringNewFromCString(gc, "Otto")) != mapGet(copy->value.map, stringNewFromCString(gc, "Otto")));
    assert(mapGet(object->value.map, stringNewFromCString(gc, "Lisa")) != mapGet(copy->value.map, stringNewFromCString(gc, "Lisa")));

    assert(mapGet(object->value.map, stringNewFromCString(gc, "Willi"))->value.pair->first != mapGet(copy->value.map, stringNewFromCString(gc, "Willi"))->value.pair->first);
    assert(mapGet(object->value.map, stringNewFromCString(gc, "Otto"))->value.pair->first != mapGet(copy->value.map, stringNewFromCString(gc, "Otto"))->value.pair->first);
    assert(mapGet(object->value.map, stringNewFromCString(gc, "Lisa"))->value.pair->first != mapGet(copy->value.map, stringNewFromCString(gc, "Lisa"))->value.pair->first);

    assert(mapGet(mapGet(object->value.map, stringNewFromCString(gc, "Willi"))->value.pair->first->value.map, stringNewFromCString(gc, "name")) 
        != mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Willi"))->value.pair->first->value.map, stringNewFromCString(gc, "name")));
    
    assert(mapGet(mapGet(object->value.map, stringNewFromCString(gc, "Otto"))->value.pair->first->value.map, stringNewFromCString(gc, "name"))  
        != mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Otto"))->value.pair->first->value.map, stringNewFromCString(gc, "name")));
    
    assert(mapGet(mapGet(object->value.map, stringNewFromCString(gc, "Lisa"))->value.pair->first->value.map, stringNewFromCString(gc, "name"))  
        != mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Lisa"))->value.pair->first->value.map, stringNewFromCString(gc, "name")));

    assert(mapGet(mapGet(object->value.map, stringNewFromCString(gc, "Willi"))->value.pair->first->value.map, stringNewFromCString(gc, "age")) 
        != mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Willi"))->value.pair->first->value.map, stringNewFromCString(gc, "age")));
    
    assert(mapGet(mapGet(object->value.map, stringNewFromCString(gc, "Otto"))->value.pair->first->value.map, stringNewFromCString(gc, "age"))  
        != mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Otto"))->value.pair->first->value.map, stringNewFromCString(gc, "age")));
    
    assert(mapGet(mapGet(object->value.map, stringNewFromCString(gc, "Lisa"))->value.pair->first->value.map, stringNewFromCString(gc, "age"))  
        != mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Lisa"))->value.pair->first->value.map, stringNewFromCString(gc, "age")));

    assert(mapGet(mapGet(object->value.map, stringNewFromCString(gc, "Willi"))->value.pair->first->value.map, stringNewFromCString(gc, "height")) 
        != mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Willi"))->value.pair->first->value.map, stringNewFromCString(gc, "height")));
    
    assert(mapGet(mapGet(object->value.map, stringNewFromCString(gc, "Otto"))->value.pair->first->value.map, stringNewFromCString(gc, "height"))  
        != mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Otto"))->value.pair->first->value.map, stringNewFromCString(gc, "height")));
    
    assert(mapGet(mapGet(object->value.map, stringNewFromCString(gc, "Lisa"))->value.pair->first->value.map, stringNewFromCString(gc, "height"))  
        != mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Lisa"))->value.pair->first->value.map, stringNewFromCString(gc, "height")));

    assert(mapGet(object->value.map, stringNewFromCString(gc, "Willi"))->value.pair->second != mapGet(copy->value.map, stringNewFromCString(gc, "Willi"))->value.pair->second);
    assert(mapGet(object->value.map, stringNewFromCString(gc, "Otto"))->value.pair->second != mapGet(copy->value.map, stringNewFromCString(gc, "Otto"))->value.pair->second);
    assert(mapGet(object->value.map, stringNewFromCString(gc, "Lisa"))->value.pair->second != mapGet(copy->value.map, stringNewFromCString(gc, "Lisa"))->value.pair->second);

    assert(mapGet(object->value.map, stringNewFromCString(gc, "Willi"))->value.pair->second->value.array->objects[0] 
        != mapGet(copy->value.map, stringNewFromCString(gc, "Willi"))->value.pair->second->value.array->objects[0]);
    
    assert(mapGet(object->value.map, stringNewFromCString(gc, "Willi"))->value.pair->second->value.array->objects[1] 
        != mapGet(copy->value.map, stringNewFromCString(gc, "Willi"))->value.pair->second->value.array->objects[1]);

    assert(mapGet(object->value.map, stringNewFromCString(gc, "Otto"))->value.pair->second->value.array->objects[0] 
        != mapGet(copy->value.map, stringNewFromCString(gc, "Otto"))->value.pair->second->value.array->objects[0]);

    assert(mapGet(mapGet(object->value.map, stringNewFromCString(gc, "Willi"))->value.pair->second->value.array->objects[0]->value.map, stringNewFromCString(gc, "street")) 
        != mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Willi"))->value.pair->second->value.array->objects[0]->value.map, stringNewFromCString(gc, "street")));

    assert(mapGet(mapGet(object->value.map, stringNewFromCString(gc, "Willi"))->value.pair->second->value.array->objects[0]->value.map, stringNewFromCString(gc, "number")) 
        != mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Willi"))->value.pair->second->value.array->objects[0]->value.map, stringNewFromCString(gc, "number")));
    
    assert(mapGet(mapGet(object->value.map, stringNewFromCString(gc, "Willi"))->value.pair->second->value.array->objects[1]->value.map, stringNewFromCString(gc, "street")) 
        != mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Willi"))->value.pair->second->value.array->objects[1]->value.map, stringNewFromCString(gc, "street")));

    assert(mapGet(mapGet(object->value.map, stringNewFromCString(gc, "Willi"))->value.pair->second->value.array->objects[1]->value.map, stringNewFromCString(gc, "number")) 
        != mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Willi"))->value.pair->second->value.array->objects[1]->value.map, stringNewFromCString(gc, "number")));

    assert(mapGet(mapGet(object->value.map, stringNewFromCString(gc, "Otto"))->value.pair->second->value.array->objects[0]->value.map, stringNewFromCString(gc, "street")) 
        != mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Otto"))->value.pair->second->value.array->objects[0]->value.map, stringNewFromCString(gc, "street")));

    assert(mapGet(mapGet(object->value.map, stringNewFromCString(gc, "Otto"))->value.pair->second->value.array->objects[0]->value.map, stringNewFromCString(gc, "number")) 
        != mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Otto"))->value.pair->second->value.array->objects[0]->value.map, stringNewFromCString(gc, "number")));


    gcSweep(gc);
    assert(gc->freeCount == gc->newCount);
    assert(gc->size == 0);
    gcFree(gc);
    printf("OK\n");
}

void testObjectEquals()
{
    printf("testObjectEquals: ");
    struct Gc *gc = gcNew(10000, 0.9, 0);
    struct Object *object = getComplexObject(gc);
    
    struct Object *copy = objectCopy(gc, object);

    assert(objectEquals(object, copy) == BOOLEAN_TRUE);

    // copy changes address
    mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Otto"))->value.pair->second->value.array->objects[0]->value.map, stringNewFromCString(gc, "number"))->value.integerValue = 12;
    
    assert(objectEquals(object, copy) == BOOLEAN_FALSE);

    // copy changes address back
    mapPut(gc, mapGet(copy->value.map, stringNewFromCString(gc, "Otto"))->value.pair->second->value.array->objects[0]->value.map, stringNewFromCString(gc, "number"), integerNew(gc, 32));
    
    assert(objectEquals(object, copy) == BOOLEAN_TRUE);

    gcSweep(gc);
    assert(gc->freeCount == gc->newCount);
    assert(gc->size == 0);
    gcFree(gc);
    printf("OK\n");
}

void testObjectHash()
{
    printf("testObjectHash: ");
    struct Gc *gc = gcNew(10000, 0.7, 0);
    struct Object *object = getComplexObject(gc);
    
    struct Object *copy = objectCopy(gc, object);

    assert(objectHash(object) == objectHash(copy));

    // copy changes address
    mapGet(mapGet(copy->value.map, stringNewFromCString(gc, "Otto"))->value.pair->second->value.array->objects[0]->value.map, stringNewFromCString(gc, "number"))->value.integerValue = 12;
    
    // copy changes address back
    mapPut(gc, mapGet(copy->value.map, stringNewFromCString(gc, "Otto"))->value.pair->second->value.array->objects[0]->value.map, stringNewFromCString(gc, "number"), integerNew(gc, 32));
    
    assert(objectHash(object) == objectHash(copy));

    gcSweep(gc);
    assert(gc->freeCount == gc->newCount);
    assert(gc->size == 0);
    gcFree(gc);
    printf("OK\n");
}

void testObjectToString()
{
    printf("testObjectToString: ");
    struct Gc *gc = gcNew(10000, 0.7, 0);
    struct Object *object = getComplexObject(gc);
    
    struct Object *string = objectToString(gc, object);

    stringPrint(string->value.string);

    gcSweep(gc);
    assert(gc->freeCount == gc->newCount);
    assert(gc->size == 0);
    gcFree(gc);
    printf("OK\n");
}

void testObjectNew()
{
    printf("testObjectNew: ");
    struct Gc *gc = gcNew(16, 0.7, 0);
    
    objectNew(gc, 200);

    assert(gc->size == sizeof(struct Object));

    gcSweep(gc);

    assert(gc->freeCount == gc->newCount);
    assert(gc->size == 0);
    assert(gc->freeCount == 1);
    assert(gc->head == NULL);

    gcFree(gc);

    printf("OK\n");
}

void testObjectMark()
{
    printf("testObjectMark: ");
    struct Gc *gc = gcNew(10000, 0.7, 0);
    struct Object *object = getComplexObject(gc);

    uint32_t oldSize = gc->size;

    objectMark(object);

    gcSweep(gc);

    assert(gc->freeCount == 0);
    assert(gc->size == oldSize);

    gcSweep(gc);
    assert(gc->freeCount == gc->newCount);
    assert(gc->size == 0);
    gcFree(gc);

    printf("OK\n");
}

void testObjectFree()
{
    printf("testObjectFree: ");
    struct Gc *gc = gcNew(10000, 0.7, 0);
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

    objectFree(NULL, integer1);
    objectFree(NULL, pair);

    printf("OK\n");
}

void testPairSetFirst()
{
    printf("testPairSetFirst: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *pair = pairNew(NULL, NULL, integer1);

    assert(pairSetFirst(pair->value.pair, integer1) == NULL);
    assert(pair->value.pair->first == integer1);

    assert(pairSetFirst(pair->value.pair, NULL) == integer1);
    assert(pair->value.pair->first == NULL);

    objectFree(NULL, integer1);
    objectFree(NULL, pair);
    printf("OK\n");
}

void testPairSetSecond()
{
    printf("testPairSetSecond: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *pair = pairNew(NULL, NULL, integer1);

    assert(pairSetSecond(pair->value.pair, NULL) == integer1);
    assert(pair->value.pair->second == NULL);

    assert(pairSetSecond(pair->value.pair, integer1) == NULL);
    assert(pair->value.pair->second == integer1);

    objectFree(NULL, integer1);
    objectFree(NULL, pair);
    printf("OK\n");
}

void testPairCopy()
{
    printf("testPairCopy: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *string1 = stringNewFromCString(NULL, "1233123");
    struct Object *pair = pairNew(NULL, string1, integer1);

    struct Object *copy = pairCopy(NULL, pair->value.pair);

    assert(copy != pair);
    assert(copy->value.pair->first != pair->value.pair->first);
    assert(copy->value.pair->second != pair->value.pair->second);

    objectFree(NULL, integer1);
    objectFree(NULL, string1);
    objectFree(NULL, pair);
    objectFree(NULL, copy->value.pair->first);
    objectFree(NULL, copy->value.pair->second);
    objectFree(NULL, copy);
    printf("OK\n");
}

void testPairEquals()
{
    printf("testPairEquals: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *string1 = stringNewFromCString(NULL, "1233123");
    struct Object *pair = pairNew(NULL, string1, integer1);

    struct Object *copy = pairCopy(NULL, pair->value.pair);

    assert(pairEquals(pair->value.pair, pair->value.pair) == BOOLEAN_TRUE);
    assert(pairEquals(copy->value.pair, pair->value.pair) == BOOLEAN_TRUE);

    pairSetFirst(pair->value.pair, NULL);
    assert(pairEquals(copy->value.pair, pair->value.pair) == BOOLEAN_FALSE);

    objectFree(NULL, integer1);
    objectFree(NULL, string1);
    objectFree(NULL, pair);
    objectFree(NULL, copy->value.pair->first);
    objectFree(NULL, copy->value.pair->second);
    objectFree(NULL, copy);
    printf("OK\n");
}

void testPairHash()
{
    printf("testPairHash: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *string1 = stringNewFromCString(NULL, "1233123");
    struct Object *pair = pairNew(NULL, string1, integer1);

    struct Object *copy = pairCopy(NULL, pair->value.pair);

    assert(pairHash(pair->value.pair) == pairHash(pair->value.pair));
    assert(pairHash(copy->value.pair) == pairHash(pair->value.pair));

    objectFree(NULL, integer1);
    objectFree(NULL, string1);
    objectFree(NULL, pair);
    objectFree(NULL, copy->value.pair->first);
    objectFree(NULL, copy->value.pair->second);
    objectFree(NULL, copy);
    printf("OK\n");
}

void testPairToString()
{
    printf("testPairToString: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *string1 = stringNewFromCString(NULL, "1233123");
    struct Object *pair = pairNew(NULL, string1, integer1);

    struct Object *pairString = pairToString(NULL, pair->value.pair);
    
    assert(pairString->type == OBJECT_TYPE_STRING);
    assert(pairString->value.string->characterCount == 14);
    assert(pairString->value.string->characters[0] == '(');
    assert(pairString->value.string->characters[1] == '1');
    assert(pairString->value.string->characters[2] == '2');
    assert(pairString->value.string->characters[3] == '3');
    assert(pairString->value.string->characters[4] == '3');
    assert(pairString->value.string->characters[5] == '1');
    assert(pairString->value.string->characters[6] == '2');
    assert(pairString->value.string->characters[7] == '3');
    assert(pairString->value.string->characters[8] == ',');
    assert(pairString->value.string->characters[9] == '1');
    assert(pairString->value.string->characters[10] == '2');
    assert(pairString->value.string->characters[11] == '3');
    assert(pairString->value.string->characters[12] == '1');
    assert(pairString->value.string->characters[13] == ')');

    objectFree(NULL, pairString);
    objectFree(NULL, integer1);
    objectFree(NULL, string1);
    objectFree(NULL, pair);
    printf("OK\n");
}

void testPairMark()
{
    printf("testPairMark: ");
    struct Object *integer1 = integerNew(NULL, 1231);
    struct Object *string1 = stringNewFromCString(NULL, "1233123");
    struct Object *pair = pairNew(NULL, string1, integer1);

    objectMark(pair);

    assert(integer1->mark == OBJECT_MARK_TRUE);
    assert(string1->mark == OBJECT_MARK_TRUE);
    assert(pair->mark == OBJECT_MARK_TRUE);

    objectFree(NULL, integer1);
    objectFree(NULL, string1);
    objectFree(NULL, pair);
    printf("OK\n");
}

int main(int argc, char* argv[])
{
    testArrayNew();
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
    testStringConcatenate();
    testStringSubstring();
    testStringIndexOf();
    testStringReplace();
    testStringCopy();
    testStringEquals();
    testStringHash();
    testStringAppendCharacter();
    testStringFree();
    testDoubleNew();
    testDoubleToString();
    testGcNew();
    testGcRegisterObject();
    testGcRegisterObjectFull1();
    testGcRegisterObjectFull2();
    testGcRequestMemory();
    testGcReleaseMemory();
    testGcShouldMarkAndSweep();
    testGcSweep();
    testGcFree();
    testIntegerNew();
    testIntegerToString();
    testMapNew();
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