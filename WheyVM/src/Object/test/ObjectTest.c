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
    assert(array2->value.array->objects[0]->value.integer_value == 97);
    assert(array2->value.array->objects[1]->value.integer_value == 98);
    assert(array2->value.array->objects[2]->value.integer_value == 99);

    integer1->value.integer_value = 55;
    assert(array2->value.array->objects[0]->value.integer_value == 97);

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

    array2->value.array->objects[0]->value.integer_value = -1;

    assert(arrayEquals(array1->value.array, array2->value.array) == 0);

    array2->value.array->objects[0]->value.integer_value = 97;

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

    assert(string1->value.array->objects[0]->value.integer_value == '[');
    assert(string1->value.array->objects[1]->value.integer_value == '7');
    assert(string1->value.array->objects[2]->value.integer_value == ',');
    assert(string1->value.array->objects[3]->value.integer_value == '9');
    assert(string1->value.array->objects[4]->value.integer_value == '8');
    assert(string1->value.array->objects[5]->value.integer_value == ',');
    assert(string1->value.array->objects[6]->value.integer_value == '1');
    assert(string1->value.array->objects[7]->value.integer_value == '2');
    assert(string1->value.array->objects[8]->value.integer_value == '1');
    assert(string1->value.array->objects[9]->value.integer_value == '2');
    assert(string1->value.array->objects[10]->value.integer_value == '9');
    assert(string1->value.array->objects[11]->value.integer_value == '9');
    assert(string1->value.array->objects[12]->value.integer_value == ']');

    struct Object *array2 = arrayNew(NULL, 0);

    struct Object *string2 = arrayToString(NULL, array2->value.array);

    assert(string2->value.array->objectCount == 2);

    assert(string2->value.array->objects[0]->value.integer_value == '[');
    assert(string2->value.array->objects[1]->value.integer_value == ']');

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
    
    struct Object *string = stringNew(NULL, 3);
    assert(string != NULL);
    assert(string->value.array != NULL);
    assert(string->value.array->objects != NULL);
    assert(string->type == OBJECT_TYPE_STRING);
    assert(string->value.array->slotCount == 5);
    assert(string->value.array->objectCount == 3);

    objectFree(string);
    
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
    
    assert(string->value.array->objects[0]->value.integer_value == integer1->value.integer_value);
    assert(string->value.array->objects[1]->value.integer_value == integer2->value.integer_value);
    assert(string->value.array->objects[2]->value.integer_value == integer3->value.integer_value);
    assert(string->value.array->objects[3]->value.integer_value == integer4->value.integer_value);
    assert(string->value.array->objects[4]->value.integer_value == integer5->value.integer_value);

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
    struct Object *string1 = stringNew(NULL, 5);
    struct Object *integer1 = integerNew(NULL, 'h');
    struct Object *integer2 = integerNew(NULL, 'e');
    struct Object *integer3 = integerNew(NULL, 'l');
    struct Object *integer4 = integerNew(NULL, 'l');
    struct Object *integer5 = integerNew(NULL, 'o');

    string1->value.array->objects[0] = integer1;
    string1->value.array->objects[1] = integer2;
    string1->value.array->objects[2] = integer3;
    string1->value.array->objects[3] = integer4;
    string1->value.array->objects[4] = integer5;

    struct Object *array = stringToArray(NULL, string1->value.array);

    assert(array->type == OBJECT_TYPE_ARRAY);
    assert(array->value.array->objects[0] != integer1);
    assert(array->value.array->objects[1] != integer2);
    assert(array->value.array->objects[2] != integer3);
    assert(array->value.array->objects[3] != integer4);
    assert(array->value.array->objects[4] != integer5);
    
    assert(array->value.array->objects[0]->value.integer_value == integer1->value.integer_value);
    assert(array->value.array->objects[1]->value.integer_value == integer2->value.integer_value);
    assert(array->value.array->objects[2]->value.integer_value == integer3->value.integer_value);
    assert(array->value.array->objects[3]->value.integer_value == integer4->value.integer_value);
    assert(array->value.array->objects[4]->value.integer_value == integer5->value.integer_value);

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
    struct Object *string1 = stringNew(NULL, 6);
    struct Object *integer11 = integerNew(NULL, 'h');
    struct Object *integer12 = integerNew(NULL, 'a');
    struct Object *integer13 = integerNew(NULL, 'l');
    struct Object *integer14 = integerNew(NULL, 'l');
    struct Object *integer15 = integerNew(NULL, 'o');
    struct Object *integer16 = integerNew(NULL, '1');

    string1->value.array->objects[0] = integer11;
    string1->value.array->objects[1] = integer12;
    string1->value.array->objects[2] = integer13;
    string1->value.array->objects[3] = integer14;
    string1->value.array->objects[4] = integer15;
    string1->value.array->objects[5] = integer16;

    struct Object *string2 = stringNew(NULL, 5);
    struct Object *integer21 = integerNew(NULL, 'h');
    struct Object *integer22 = integerNew(NULL, 'a');
    struct Object *integer23 = integerNew(NULL, 'l');
    struct Object *integer24 = integerNew(NULL, 'l');
    struct Object *integer25 = integerNew(NULL, 'o');

    string2->value.array->objects[0] = integer21;
    string2->value.array->objects[1] = integer22;
    string2->value.array->objects[2] = integer23;
    string2->value.array->objects[3] = integer24;
    string2->value.array->objects[4] = integer25;

    struct Object *string3 = stringNew(NULL, 6);
    struct Object *integer31 = integerNew(NULL, 'b');
    struct Object *integer32 = integerNew(NULL, 'a');
    struct Object *integer33 = integerNew(NULL, 'n');
    struct Object *integer34 = integerNew(NULL, 'a');
    struct Object *integer35 = integerNew(NULL, 'n');
    struct Object *integer36 = integerNew(NULL, 'a');

    string3->value.array->objects[0] = integer31;
    string3->value.array->objects[1] = integer32;
    string3->value.array->objects[2] = integer33;
    string3->value.array->objects[3] = integer34;
    string3->value.array->objects[4] = integer35;
    string3->value.array->objects[5] = integer36;

    struct Object *string4 = stringNew(NULL, 0);

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
    struct Object *string1 = stringNew(NULL, 6);
    struct Object *integer11 = integerNew(NULL, 'h');
    struct Object *integer12 = integerNew(NULL, 'a');
    struct Object *integer13 = integerNew(NULL, 'l');
    struct Object *integer14 = integerNew(NULL, 'l');
    struct Object *integer15 = integerNew(NULL, 'o');
    struct Object *integer16 = integerNew(NULL, '1');

    string1->value.array->objects[0] = integer11;
    string1->value.array->objects[1] = integer12;
    string1->value.array->objects[2] = integer13;
    string1->value.array->objects[3] = integer14;
    string1->value.array->objects[4] = integer15;
    string1->value.array->objects[5] = integer16;

    struct Object *string2 = stringCopy(NULL, string1->value.array);

    assert(string2->type == OBJECT_TYPE_STRING);
    assert(string2->value.array->objects[0] != string1->value.array->objects[0]);
    assert(string2->value.array->objects[1] != string1->value.array->objects[1]);
    assert(string2->value.array->objects[2] != string1->value.array->objects[2]);
    assert(string2->value.array->objects[3] != string1->value.array->objects[3]);
    assert(string2->value.array->objects[4] != string1->value.array->objects[4]);
    assert(string2->value.array->objects[5] != string1->value.array->objects[5]);

    assert(string2->value.array->objects[0]->value.integer_value == string1->value.array->objects[0]->value.integer_value);
    assert(string2->value.array->objects[1]->value.integer_value == string1->value.array->objects[1]->value.integer_value);
    assert(string2->value.array->objects[2]->value.integer_value == string1->value.array->objects[2]->value.integer_value);
    assert(string2->value.array->objects[3]->value.integer_value == string1->value.array->objects[3]->value.integer_value);
    assert(string2->value.array->objects[4]->value.integer_value == string1->value.array->objects[4]->value.integer_value);
    assert(string2->value.array->objects[5]->value.integer_value == string1->value.array->objects[5]->value.integer_value);

    objectFree(string1);
    objectFree(string2);

    printf("OK\n");
}

void testStringEquals()
{
    printf("testStringEquals: ");

    struct Object *string1 = stringNew(NULL, 6);
    struct Object *integer11 = integerNew(NULL, 'h');
    struct Object *integer12 = integerNew(NULL, 'a');
    struct Object *integer13 = integerNew(NULL, 'l');
    struct Object *integer14 = integerNew(NULL, 'l');
    struct Object *integer15 = integerNew(NULL, 'o');
    struct Object *integer16 = integerNew(NULL, '1');

    string1->value.array->objects[0] = integer11;
    string1->value.array->objects[1] = integer12;
    string1->value.array->objects[2] = integer13;
    string1->value.array->objects[3] = integer14;
    string1->value.array->objects[4] = integer15;
    string1->value.array->objects[5] = integer16;

    struct Object *string2 = stringCopy(NULL, string1->value.array);

    struct Object *string3 = stringNew(NULL, 3);
    struct Object *integer31 = integerNew(NULL, 'b');
    struct Object *integer32 = integerNew(NULL, 'a');
    struct Object *integer33 = integerNew(NULL, 'n');

    string3->value.array->objects[0] = integer31;
    string3->value.array->objects[1] = integer32;
    string3->value.array->objects[2] = integer33;

    struct Object *string4 = stringNew(NULL, 0);

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

    struct Object *string1 = stringNew(NULL, 6);
    struct Object *integer11 = integerNew(NULL, 'h');
    struct Object *integer12 = integerNew(NULL, 'a');
    struct Object *integer13 = integerNew(NULL, 'l');
    struct Object *integer14 = integerNew(NULL, 'l');
    struct Object *integer15 = integerNew(NULL, 'o');
    struct Object *integer16 = integerNew(NULL, '1');

    string1->value.array->objects[0] = integer11;
    string1->value.array->objects[1] = integer12;
    string1->value.array->objects[2] = integer13;
    string1->value.array->objects[3] = integer14;
    string1->value.array->objects[4] = integer15;
    string1->value.array->objects[5] = integer16;

    struct Object *string2 = stringCopy(NULL, string1->value.array);

    struct Object *string3 = stringNew(NULL, 0);
    struct Object *string4 = stringNew(NULL, 0);

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
    struct Object *string1 = stringNew(NULL, 6);
    struct Object *integer11 = integerNew(NULL, 'h');
    struct Object *integer12 = integerNew(NULL, 'a');
    struct Object *integer13 = integerNew(NULL, 'l');
    struct Object *integer14 = integerNew(NULL, 'l');
    struct Object *integer15 = integerNew(NULL, 'o');
    struct Object *integer16 = integerNew(NULL, '1');

    string1->value.array->objects[0] = integer11;
    string1->value.array->objects[1] = integer12;
    string1->value.array->objects[2] = integer13;
    string1->value.array->objects[3] = integer14;
    string1->value.array->objects[4] = integer15;
    string1->value.array->objects[5] = integer16;

    struct Object *string2 = stringNew(NULL, 0);
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
    struct Object *string1 = stringNew(NULL, 6);
    objectFree(string1);

    printf("OK\n");
}

void testDoubleNew()
{
    printf("testDoubleNew: ");
    struct Object *double1 = doubleNew(NULL, 0.001);
    assert(double1->type == OBJECT_TYPE_FLOATING);
    assert(double1->mark == OBJECT_MARK_FALSE);
    assert(double1->value.double_value == 0.001);
    objectFree(double1);
    printf("OK\n");
}

void testDoubleToString()
{
    printf("testDoubleToString: ");
    struct Object *double1 = doubleNew(NULL, 0.0010105);

    struct Object *string = doubleToString(NULL, double1->value.double_value);

    assert(string->type == OBJECT_TYPE_STRING);

    assert(string->value.array->objectCount == 16);
    assert(string->value.array->objects[0]->value.integer_value == '1');
    assert(string->value.array->objects[1]->value.integer_value == '.');
    assert(string->value.array->objects[2]->value.integer_value == '0');
    assert(string->value.array->objects[3]->value.integer_value == '1');
    assert(string->value.array->objects[4]->value.integer_value == '0');
    assert(string->value.array->objects[5]->value.integer_value == '5');
    assert(string->value.array->objects[6]->value.integer_value == '0');
    assert(string->value.array->objects[7]->value.integer_value == '0');
    assert(string->value.array->objects[8]->value.integer_value == '0');
    assert(string->value.array->objects[9]->value.integer_value == '0');
    assert(string->value.array->objects[10]->value.integer_value == '0');
    assert(string->value.array->objects[11]->value.integer_value == '0');
    assert(string->value.array->objects[12]->value.integer_value == 'e');
    assert(string->value.array->objects[13]->value.integer_value == '-');
    assert(string->value.array->objects[14]->value.integer_value == '0');
    assert(string->value.array->objects[15]->value.integer_value == '3');
    
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

    struct Object *string1 = stringNew(gc, 6);
    struct Object *integer11 = integerNew(NULL, 'h');
    struct Object *integer12 = integerNew(NULL, 'a');
    struct Object *integer13 = integerNew(NULL, 'l');
    struct Object *integer14 = integerNew(NULL, 'l');
    struct Object *integer15 = integerNew(NULL, 'o');
    struct Object *integer16 = integerNew(NULL, '1');

    string1->value.array->objects[0] = integer11;
    string1->value.array->objects[1] = integer12;
    string1->value.array->objects[2] = integer13;
    string1->value.array->objects[3] = integer14;
    string1->value.array->objects[4] = integer15;
    string1->value.array->objects[5] = integer16;

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

    struct Object *string1 = stringNew(gc, 6);
    struct Object *integer11 = integerNew(NULL, 'h');
    struct Object *integer12 = integerNew(NULL, 'a');
    struct Object *integer13 = integerNew(NULL, 'l');
    struct Object *integer14 = integerNew(NULL, 'l');
    struct Object *integer15 = integerNew(NULL, 'o');
    struct Object *integer16 = integerNew(NULL, '1');

    string1->value.array->objects[0] = integer11;
    string1->value.array->objects[1] = integer12;
    string1->value.array->objects[2] = integer13;
    string1->value.array->objects[3] = integer14;
    string1->value.array->objects[4] = integer15;
    string1->value.array->objects[5] = integer16;

    assert(gc->newCount == 5);

    integer1->mark = OBJECT_MARK_TRUE;
    string1->mark = OBJECT_MARK_TRUE;

    gcSweep(gc);

    assert(gc->freeCount == 3);
    assert(gc->head->object == string1);
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
    assert(integer->value.integer_value == 1231212);

    objectFree(integer);
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