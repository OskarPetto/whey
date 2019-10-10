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
    mapPut(gc, person1, personNameKey1, person1NameValue);
    mapPut(gc, person1, personAgeKey1, person1AgeValue);
    mapPut(gc, person1, personHeightKey1, person1HeightValue);

    struct Object *person2 = mapNew(gc);
    struct Object *person2NameValue = stringNewFromCString(gc, "Otto");
    struct Object *person2AgeValue = integerNew(gc, 64);
    struct Object *person2HeightValue = doubleNew(gc, 1.65);
    mapPut(gc, person2, personNameKey1, person2NameValue);
    mapPut(gc, person2, personAgeKey2, person2AgeValue);
    mapPut(gc, person2, personHeightKey2, person2HeightValue);

    struct Object *person3 = mapNew(gc);
    struct Object *person3NameValue = stringNewFromCString(gc, "Lisa");
    struct Object *person3AgeValue = integerNew(gc, 33);
    struct Object *person3HeightValue = doubleNew(gc, 1.68);
    mapPut(gc, person3, personNameKey1, person3NameValue);
    mapPut(gc, person3, personAgeKey3, person3AgeValue);
    mapPut(gc, person3, personHeightKey3, person3HeightValue);

    struct Object *address1 = mapNew(gc);
    struct Object *address1StreetKey = stringNewFromCString(gc, "street");
    struct Object *address1NumberKey = stringNewFromCString(gc, "number");
    struct Object *address1StreetValue = stringNewFromCString(gc, "Hausdorf");
    struct Object *address1NumberValue = integerNew(gc, 121);
    mapPut(gc,address1, address1StreetKey, address1StreetValue);
    mapPut(gc,address1, address1NumberKey, address1NumberValue);

    struct Object *address2 = mapNew(gc);
    struct Object *address2StreetKey = stringNewFromCString(gc, "street");
    struct Object *address2NumberKey = stringNewFromCString(gc, "number");
    struct Object *address2StreetValue = stringNewFromCString(gc, "Hausdorf");
    struct Object *address2NumberValue = integerNew(gc, 122);
    mapPut(gc, address2, address2StreetKey, address2StreetValue);
    mapPut(gc, address2, address2NumberKey, address2NumberValue);

    struct Object *address3 = mapNew(gc);
    struct Object *address3StreetKey = stringNewFromCString(gc, "street");
    struct Object *address3NumberKey = stringNewFromCString(gc, "number");
    struct Object *address3StreetValue = stringNewFromCString(gc, "Siebenseiten");
    struct Object *address3NumberValue = integerNew(gc, 32);
    mapPut(gc, address3, address3StreetKey, address3StreetValue);
    mapPut(gc, address3, address3NumberKey, address3NumberValue);

    struct Object *person1AddressArrayObject = arrayNew(gc, 2, 2);
    struct Array *person1AddressArray = person1AddressArrayObject->value.subObject;

    person1AddressArray->objects[0] = address1;
    person1AddressArray->objects[1] = address2;

    struct Object *person2AddressArrayObject = arrayNew(gc, 1, 1);
    struct Array *person2AddressArray = person2AddressArrayObject->value.subObject;

    person2AddressArray->objects[0] = address3;

    struct Object *person3AddressArrayObject = arrayNew(gc, 0, 0);

    struct Object *person1Pair = pairNew(gc, person1, person1AddressArrayObject);
    struct Object *person2Pair = pairNew(gc, person2, person2AddressArrayObject);
    struct Object *person3Pair = pairNew(gc, person3, person3AddressArrayObject);

    mapPut(gc, mapNameToPersonWithAdresses, nameKey1, person1Pair);
    mapPut(gc, mapNameToPersonWithAdresses, nameKey2, person2Pair);
    mapPut(gc, mapNameToPersonWithAdresses, nameKey3, person3Pair);

    return mapNameToPersonWithAdresses;
}

void testGcNew()
{
    printf("testGcNew: ");
    struct Gc *gc = gcNew(0, 0);

    assert(gc->size == 0);
    assert(gc->maxSize == 0);
    assert(gc->treshold == 0);
    assert(gc->sizeBeforeLastMarkAndSweep == 0);
    assert(gc->tolerance == 0);

    assert(gc->head == NULL);

    gcFree(gc);

    printf("OK\n");
}

void testGcObjectNew()
{
    printf("testGcObjectNew: ");
    struct Gc *gc = gcNew(190, 0);
    struct Object *arrayObject1 = arrayNew(gc, 3, 3);
    struct Object *integer1 = integerNew(gc, 7);
    struct Object *integer2 = integerNew(gc, 98);
    struct Object *integer3 = integerNew(gc, 121299);

    assert(gc->size == 4 * sizeof(struct Object) + sizeof(struct Array) + 3 * sizeof(struct Object *));

    struct Array *array = arrayObject1->value.subObject;

    array->objects[0] = integer1;
    array->objects[1] = integer2;
    array->objects[2] = integer3;

    struct Object *stringObject1 = stringNewFromCString(gc, "hallo1");

    assert(gc->size == 5 * sizeof(struct Object) + sizeof(struct Array) + 3 * sizeof(struct Object *) + sizeof(struct String) + 6);

    assert(gc->head == stringObject1);
    assert(gc->head->next == integer3);
    assert(gc->head->next->next == integer2);
    assert(gc->head->next->next->next == integer1);
    assert(gc->head->next->next->next->next == arrayObject1);
    assert(gc->head->next->next->next->next->next == NULL);

    assert(gc->size == 5 * sizeof(struct Object) + sizeof(struct Array) + 3 * sizeof(struct Object *) + sizeof(struct String) + 6);

    gcSweep(gc);

    gcFree(gc);

    printf("OK\n");
}

void testGcObjectNewMemoryFull1()
{
    printf("testGcObjectNewMemoryFull1: ");
    struct Gc *gc = gcNew(sizeof(struct Object) + sizeof(struct Array), GC_DEBUG_OVERFLOW);
    arrayNew(gc, 3, 3); 
    assert(gc->size == sizeof(struct Object) + sizeof(struct Array) + 3 * sizeof(struct Object *));
    assert(gc->size > gc->maxSize);

    gcSweep(gc);

    gcFree(gc);

    printf("OK\n");
}

void testGcObjectNewMemoryFull2()
{
    printf("testGcObjectNewMemoryFull2: ");
    struct Gc *gc = gcNew(2 * sizeof(struct Object), GC_DEBUG_OVERFLOW);
    integerNew(gc, 23);
    assert(gc->size == sizeof(struct Object));

    integerNew(gc, 13);
    assert(gc->size == 2 * sizeof(struct Object));

    integerNew(gc, 16); 
    assert(gc->size == 3 * sizeof(struct Object));
    assert(gc->size > gc->maxSize);

    gcSweep(gc);

    gcFree(gc);

    printf("OK\n");
}

void testGcMemoryMalloc()
{
    printf("testGcMemoryMalloc: ");
    struct Gc *gc = gcNew(1000, 0);
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

    mapPut(gc, map, integer1, double1);
    assert(gc->size == oldSize + sizeof(struct MapEntry));
    oldSize = gc->size;

    pairNew(gc, integer1, double1);
    assert(gc->size == oldSize + sizeof(struct Object) + sizeof(struct Pair));
    oldSize = gc->size;

    stringNewFromCString(gc, "double1");
    assert(gc->size == oldSize + sizeof(struct Object) + sizeof(struct String) + 7);
    oldSize = gc->size;

    gcSweep(gc);

    assert(gc->size == 0);

    gcFree(gc);

    printf("OK\n");
}

void testGcMemoryRealloc()
{
    printf("testGcMemoryRealloc: ");
    struct Gc *gc = gcNew(1000, 0);

    void *memory1 = gcMemoryMalloc(gc, NULL, 50);

    assert(gc->size == 50);

    memory1 = gcMemoryRealloc(gc, NULL, memory1, 50, 20);

    assert(gc->size == 20);

    free(memory1);

    gcFree(gc);

    printf("OK\n");
}

void testGcMemoryFree()
{
    printf("testGcMemoryFree: ");
    struct Gc *gc = gcNew(1000, 0);

    void *memory1 = gcMemoryMalloc(gc, NULL, 50);

    assert(gc->size == 50);

    memory1 = gcMemoryRealloc(gc, NULL, memory1, 50, 20);

    assert(gc->size == 20);

    gcMemoryFree(gc, NULL, memory1, 20);

    assert(gc->size == 0);

    gcFree(gc);

    printf("OK\n");
}

void testGcShouldMarkAndSweep()
{
    printf("testGcShouldMarkAndSweep: ");
    struct Gc *gc = gcNew(3 * sizeof(struct Object), 0);
    integerNew(gc, 23);
    assert(gcShouldMarkAndSweep(gc) == 0);
    assert(gc->size == sizeof(struct Object));

    integerNew(gc, 13);
    assert(gcShouldMarkAndSweep(gc) == 1);
    assert(gc->size == 2 * sizeof(struct Object));

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testGcSweep()
{
    printf("testGcSweep: ");
    struct Gc *gc = gcNew(300, 0);
    struct Object *arrayObject1 = arrayNew(gc, 3, 3);
    struct Object *integer1 = integerNew(gc, 7);
    struct Object *integer2 = integerNew(gc, 98);
    struct Object *integer3 = integerNew(gc, 121299);

    struct Array *array1 = arrayObject1->value.subObject;

    array1->objects[0] = integer1;
    array1->objects[1] = integer2;
    array1->objects[2] = integer3;

    struct Object *string = stringNewFromCString(gc, "hallo1");

    assert(gc->size == 5 * sizeof(struct Object) + sizeof(struct Array) + 3 * sizeof(struct Object *) + sizeof(struct String) + 6);

    integer1->type |= OBJECT_MARK;
    string->type |= OBJECT_MARK;

    gcSweep(gc);

    assert(gc->objectCount == 2);
    assert(gc->head == string);
    assert(gc->head->next == integer1);
    assert(gc->head->next->next == NULL);
    assert(gc->size == 2 * sizeof(struct Object) + sizeof(struct String) + 6);

    integer1->type |= OBJECT_MARK;

    gcSweep(gc);

    assert(gc->objectCount == 1);
    assert(gc->head == integer1);
    assert(gc->head->next == NULL);
    assert(gc->size == sizeof(struct Object));

    gcSweep(gc);

    assert(gc->objectCount == 0);
    assert(gc->head == NULL);
    assert(gc->size == 0);

    struct Object *arrayString1 = stringNewFromCString(gc, "");
    struct Object *arrayString2 = arrayToString(gc, stringToArray(gc, arrayString1));
    
    arrayToString(gc, stringToArray(gc, arrayString2));

    // assert((arrayString3->value.subObject)->objectCount == 7);

    gcSweep(gc);

    assert(gc->head == NULL);
    assert(gc->size == 0);

    gcFree(gc);

    printf("OK\n");
}

void testGcDebug()
{
    printf("testGcDebug: ");
    struct Gc *gc = gcNew(1000, GC_DEBUG_SWEEP | GC_DEBUG_OBJECT);

    struct Object *double1 = doubleNew(gc, 13);

    struct Object *integer1 = integerNew(gc, 16);
    struct Object *integer2 = integerNew(gc, 17);
    struct Object *integer3 = integerNew(gc, 18);
    struct Object *integer4 = integerNew(gc, 19);
    struct Object *integer5 = integerNew(gc, 20);

    struct Object *pair = pairNew(gc, integer1, double1);

    struct Object *string = stringNewFromCString(gc, "extremly long string with a lot of characters. believe me"); // 57

    struct Object *map = mapNew(gc);

    mapPut(gc, map, integer1, double1);
    mapPut(gc, map, integer2, double1);
    mapPut(gc, map, integer3, double1);
    mapPut(gc, map, integer4, double1);
    mapPut(gc, map, integer5, double1);
    mapPut(gc, map, string, pair);

    mapRemove(gc, map, integer1);
    mapRemove(gc, map, integer2);
    mapRemove(gc, map, integer3);
    mapRemove(gc, map, integer4);
    mapRemove(gc, map, integer5);

    struct Object *array = arrayNew(gc, 0, 1);

    arrayPush(gc, array, integer1);
    arrayPush(gc, array, integer1);
    arrayPush(gc, array, integer1);
    arrayPush(gc, array, integer1);
    arrayPush(gc, array, integer1);

    gcSweep(gc);

    gcFree(gc);

    printf("OK\n");
}

void testGcFree()
{
    printf("testGcFree: ");
    struct Gc *gc = gcNew(100, 0);
    gcFree(gc);
    printf("OK\n");
}

void testDoubleNew()
{
    printf("testDoubleNew: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *double1 = doubleNew(gc, 0.001);
    assert(double1->type == OBJECT_TYPE_DOUBLE);
    assert(double1->value.doubleValue == 0.001);

    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testDoubleStringCharacterCount()
{
    printf("testDoubleStringCharacterCount: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *double1 = doubleNew(gc, 0.03);

    assert(doubleStringCharacterCount(double1) == 12);

    struct Object *double2 = doubleNew(gc, 5121.2321);

    assert(doubleStringCharacterCount(double2) == 12);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testDoubleWriteToString()
{
    printf("testDoubleWriteToString: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *double1 = doubleNew(gc, 0.001);

    uint32_t charCount = doubleStringCharacterCount(double1);

    struct Object *stringObject = stringNew(gc, charCount);

    uint32_t index = 0;

    doubleWriteToString(double1, stringObject, &index);

    struct String *string = stringObject->value.subObject;

    assert(string->characterCount == charCount);
    assert(string->characters[0] == '1');
    assert(string->characters[1] == '.');
    assert(string->characters[2] == '0');
    assert(string->characters[3] == '0');
    assert(string->characters[4] == '0');
    assert(string->characters[5] == '0');
    assert(string->characters[6] == '0');
    assert(string->characters[7] == '0');
    assert(string->characters[8] == 'e');
    assert(string->characters[9] == '-');
    assert(string->characters[10] == '0');
    assert(string->characters[11] == '3');

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testDoubleToString()
{
    printf("testDoubleToString: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *double1 = doubleNew(gc, 0.0010105);

    struct Object *stringObject = doubleToString(gc, double1);
    struct String *string = stringObject->value.subObject;

    assert(stringObject->type == OBJECT_TYPE_STRING);

    assert(string->characterCount == 12);
    assert(string->characters[0] == '1');
    assert(string->characters[1] == '.');
    assert(string->characters[2] == '0');
    assert(string->characters[3] == '1');
    assert(string->characters[4] == '0');
    assert(string->characters[5] == '5');
    assert(string->characters[6] == '0');
    assert(string->characters[7] == '0');
    assert(string->characters[8] == 'e');
    assert(string->characters[9] == '-');
    assert(string->characters[10] == '0');
    assert(string->characters[11] == '3');
    
    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testIntegerNew()
{
    printf("testIntegerNew: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *integer = integerNew(gc, 1231212);

    assert(integer->type == OBJECT_TYPE_INTEGER);
    assert(integer->value.integerValue == 1231212);

    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}


void testIntegerStringCharacterCount()
{
    printf("testIntegerStringCharacterCount: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *integer1 = integerNew(gc, 1231212);

    assert(integerStringCharacterCount(integer1) == 7);

    struct Object *integer2 = integerNew(gc, -76453);

    assert(integerStringCharacterCount(integer2) == 6);

    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testIntegerWriteToString()
{
    printf("testIntegerWriteToString: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *integer1 = integerNew(gc, -76453);

    uint32_t charCount = integerStringCharacterCount(integer1);
    struct Object *stringObject = stringNew(gc, charCount);
    struct String *string = stringObject->value.subObject;

    uint32_t index = 0;

    integerWriteToString(integer1, stringObject, &index);

    assert(string->characters[0] == '-');
    assert(string->characters[1] == '7');
    assert(string->characters[2] == '6');
    assert(string->characters[3] == '4');
    assert(string->characters[4] == '5');
    assert(string->characters[5] == '3');

    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testIntegerToString()
{
    printf("testIntegerToString: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *integer1 = integerNew(gc, 10105);

    struct Object *stringObject = integerToString(gc, integer1);
    struct String *string = stringObject->value.subObject;

    assert(stringObject->type == OBJECT_TYPE_STRING);

    assert(string->characterCount == 5);
    assert(string->characters[0] == '1');
    assert(string->characters[1] == '0');
    assert(string->characters[2] == '1');
    assert(string->characters[3] == '0');
    assert(string->characters[4] == '5');
    
    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testStringNew()
{
    printf("testStringNew: ");
    struct Gc *gc = gcNew(1000, 0);
    
    struct Object *stringObject = stringNewFromCString(gc, "Aha");
    assert(stringObject != NULL);
    assert(stringObject->type == OBJECT_TYPE_STRING);

    struct String *string = stringObject->value.subObject;

    assert(string != NULL);
    assert(string->characters != NULL);
    assert(string->characterCount == 3);
    assert(string->characters[0] == 'A');
    assert(string->characters[1] == 'h');
    assert(string->characters[2] == 'a');

    struct Object *stringObject2 = stringNewFromCString(gc, "");
    assert(stringObject2 != NULL);
    assert(stringObject2->type == OBJECT_TYPE_STRING);

    struct String *string2 = stringObject2->value.subObject;

    assert(string2 != NULL);
    assert(string2->characters != NULL);
    assert(string2->characterCount == 0);

    uint64_t oldSize = gc->size;

    stringNew(gc, 10);

    assert(gc->size == oldSize + sizeof(struct Object) + sizeof(struct String) + 10);

    gcSweep(gc);
    gcFree(gc);
    
    printf("OK\n");
}

void testStringFromArray()
{
    printf("testStringFromArray: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *arrayObject1 = arrayNew(gc, 5, 5);
    struct Object *integer1 = integerNew(gc, 'h');
    struct Object *integer2 = integerNew(gc, 'e');
    struct Object *integer3 = integerNew(gc, 'l');
    struct Object *integer4 = integerNew(gc, 'l');
    struct Object *integer5 = integerNew(gc, 'o');

    struct Array *array1 = arrayObject1->value.subObject;

    array1->objects[0] = integer1;
    array1->objects[1] = integer2;
    array1->objects[2] = integer3;
    array1->objects[3] = integer4;
    array1->objects[4] = integer5;

    struct Object *stringObject = stringFromArray(gc, arrayObject1); 
    struct String *string = stringObject->value.subObject;

    assert(stringObject->type == OBJECT_TYPE_STRING);
    assert(string->characterCount == 5);

    assert(string->characters[0] == (char) integer1->value.integerValue);
    assert(string->characters[1] == (char) integer2->value.integerValue);
    assert(string->characters[2] == (char) integer3->value.integerValue);
    assert(string->characters[3] == (char) integer4->value.integerValue);
    assert(string->characters[4] == (char) integer5->value.integerValue);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testStringToArray()
{
    printf("testStringToArray: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *stringObject1 = stringNewFromCString(gc, "hello");

    struct Object *arrayObject = stringToArray(gc, stringObject1);
    struct Array *array = arrayObject->value.subObject;

    assert(arrayObject->type == OBJECT_TYPE_ARRAY);
    
    assert(array->objects[0]->value.integerValue == 'h');
    assert(array->objects[1]->value.integerValue == 'e');
    assert(array->objects[2]->value.integerValue == 'l');
    assert(array->objects[3]->value.integerValue == 'l');
    assert(array->objects[4]->value.integerValue == 'o');

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testStringCompare()
{
    printf("testStringCompare: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *stringObject1 = stringNewFromCString(gc, "hallo1");

    struct Object *stringObject2 = stringNewFromCString(gc, "hallo");

    struct Object *stringObject3 = stringNewFromCString(gc, "banana");

    struct Object *stringObject4 = stringNewFromCString(gc, "");

    assert(stringCompare(stringObject1, stringObject1) == 0);
    assert(stringCompare(stringObject1, stringObject2) > 0);
    assert(stringCompare(stringObject1, stringObject3) > 0);
    assert(stringCompare(stringObject1, stringObject4) > 0);
    assert(stringCompare(stringObject2, stringObject1) < 0);
    assert(stringCompare(stringObject2, stringObject2) == 0);
    assert(stringCompare(stringObject2, stringObject3) > 0);
    assert(stringCompare(stringObject2, stringObject4) > 0);
    assert(stringCompare(stringObject3, stringObject1) < 0);
    assert(stringCompare(stringObject3, stringObject2) < 0);
    assert(stringCompare(stringObject3, stringObject3) == 0);
    assert(stringCompare(stringObject3, stringObject4) > 0);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testStringConcatenate()
{
    printf("testStringConcatenate: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *stringObject1 = stringNewFromCString(gc, "hallo1");

    struct Object *stringObject2 = stringNewFromCString(gc, "hallo");

    struct Object *stringObject3 = stringNewFromCString(gc, "");

    struct Object *stringConcatObject1 = stringConcatenate(gc, stringObject1, stringObject2);
    struct String *stringConcat1 = stringConcatObject1->value.subObject;

    assert(stringConcat1->characterCount == 11);
    assert(stringConcat1->characters[0] == 'h');
    assert(stringConcat1->characters[1] == 'a');
    assert(stringConcat1->characters[2] == 'l');
    assert(stringConcat1->characters[3] == 'l');
    assert(stringConcat1->characters[4] == 'o');
    assert(stringConcat1->characters[5] == '1');
    assert(stringConcat1->characters[6] == 'h');
    assert(stringConcat1->characters[7] == 'a');
    assert(stringConcat1->characters[8] == 'l');
    assert(stringConcat1->characters[9] == 'l');
    assert(stringConcat1->characters[10] == 'o');

    struct Object *stringConcatObject2 = stringConcatenate(gc, stringObject1, stringObject3);
    struct String *stringConcat2 = stringConcatObject2->value.subObject;

    assert(stringConcat2->characterCount == 6);
    assert(stringConcat2->characters[0] == 'h');
    assert(stringConcat2->characters[1] == 'a');
    assert(stringConcat2->characters[2] == 'l');
    assert(stringConcat2->characters[3] == 'l');
    assert(stringConcat2->characters[4] == 'o');
    assert(stringConcat2->characters[5] == '1');

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testStringSubstring()
{
    printf("testStringSubstring: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *stringObject1 = stringNewFromCString(gc, "hallo1");

    struct Object *stringObject2 = stringNewFromCString(gc, "");

    struct Object *subStringObject1 = stringSubstring(gc, stringObject1, 0, 6);
    struct String *subString1 = subStringObject1->value.subObject;

    assert(subString1->characterCount == 6);
    assert(subString1->characters[0] == 'h');
    assert(subString1->characters[1] == 'a');
    assert(subString1->characters[2] == 'l');
    assert(subString1->characters[3] == 'l');
    assert(subString1->characters[4] == 'o');
    assert(subString1->characters[5] == '1');

    struct Object *subStringObject2 = stringSubstring(gc, stringObject1, 0, 2);
    struct String *subString2 = subStringObject2->value.subObject;

    assert(subString2->characterCount == 2);
    assert(subString2->characters[0] == 'h');
    assert(subString2->characters[1] == 'a');

    struct Object *subStringObject3 = stringSubstring(gc, stringObject1, 4, 5);
    struct String *subString3 = subStringObject3->value.subObject;

    assert(subString3->characterCount == 1);
    assert(subString3->characters[0] == 'o');

    struct Object *subStringObject4 = stringSubstring(gc, stringObject2, 0, 0);
    struct String *subString4 = subStringObject4->value.subObject;

    assert(subString4->characterCount == 0);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testStringIndexOf()
{
    printf("testStringIndexOf: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *stringObject1 = stringNewFromCString(gc, "hallo1");

    struct Object *stringObject2 = stringNewFromCString(gc, "l");

    assert(stringIndexOf(stringObject1, stringObject2, 0) == 2);
    assert(stringIndexOf(stringObject1, stringObject2, 2) == 2);
    assert(stringIndexOf(stringObject1, stringObject2, 3) == 3);
    assert(stringIndexOf(stringObject1, stringObject2, 4) == -1);

    struct Object *stringObject3 = stringNewFromCString(gc, "lo1");

    assert(stringIndexOf(stringObject1, stringObject3, 0) == 3);
    assert(stringIndexOf(stringObject1, stringObject3, 3) == 3);
    assert(stringIndexOf(stringObject1, stringObject3, 4) == -1);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testStringReplace()
{
    printf("testStringReplace: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *stringObject1 = stringNewFromCString(gc, "hallo1");
    struct Object *stringObject2 = stringNewFromCString(gc, "l");
    struct Object *stringObject3 = stringNewFromCString(gc, "x");
    struct Object *stringObject4 = stringNewFromCString(gc, "lo1");
    struct Object *stringObject5 = stringNewFromCString(gc, "");

    struct Object *replacementStringObject1 = stringReplace(gc, stringObject1, stringObject2, stringObject3);
    struct String *replacementString1 = replacementStringObject1->value.subObject;

    assert(replacementString1->characterCount == 6);
    assert(replacementString1->characters[0] == 'h');
    assert(replacementString1->characters[1] == 'a');
    assert(replacementString1->characters[2] == 'x');
    assert(replacementString1->characters[3] == 'x');
    assert(replacementString1->characters[4] == 'o');
    assert(replacementString1->characters[5] == '1');

    struct Object *replacementStringObject2 = stringReplace(gc, stringObject1, stringObject2, stringObject4);
    struct String *replacementString2 = replacementStringObject2->value.subObject;

    assert(replacementString2->characterCount == 10);
    assert(replacementString2->characters[0] == 'h');
    assert(replacementString2->characters[1] == 'a');
    assert(replacementString2->characters[2] == 'l');
    assert(replacementString2->characters[3] == 'o');
    assert(replacementString2->characters[4] == '1');
    assert(replacementString2->characters[5] == 'l');
    assert(replacementString2->characters[6] == 'o');
    assert(replacementString2->characters[7] == '1');
    assert(replacementString2->characters[8] == 'o');
    assert(replacementString2->characters[9] == '1');

    struct Object *replacementStringObject3 = stringReplace(gc, stringObject1, stringObject4, stringObject3);
    struct String *replacementString3 = replacementStringObject3->value.subObject;

    assert(replacementString3->characterCount == 4);
    assert(replacementString3->characters[0] == 'h');
    assert(replacementString3->characters[1] == 'a');
    assert(replacementString3->characters[2] == 'l');
    assert(replacementString3->characters[3] == 'x');

    struct Object *replacementStringObject4 = stringReplace(gc, stringObject1, stringObject4, stringObject5);
    struct String *replacementString4 = replacementStringObject4->value.subObject;

    assert(replacementString4->characterCount == 3);
    assert(replacementString4->characters[0] == 'h');
    assert(replacementString4->characters[1] == 'a');
    assert(replacementString4->characters[2] == 'l');

    struct Object *replacementStringObject5 = stringReplace(gc, stringObject1, stringObject1, stringObject5);
    struct String *replacementString5 = replacementStringObject5->value.subObject;

    assert(replacementString5->characterCount == 0);

    struct Object *replacementStringObject6 = stringReplace(gc, stringObject1, stringObject1, stringObject1);
    struct String *replacementString6 = replacementStringObject6->value.subObject;

    assert(replacementString6->characterCount == 6);
    assert(replacementString6->characters[0] == 'h');
    assert(replacementString6->characters[1] == 'a');
    assert(replacementString6->characters[2] == 'l');
    assert(replacementString6->characters[3] == 'l');
    assert(replacementString6->characters[4] == 'o');
    assert(replacementString6->characters[5] == '1');

    struct Object *replacementStringObject7 = stringReplace(gc, stringObject3, stringObject4, stringObject1);
    struct String *replacementString7 = replacementStringObject7->value.subObject;

    assert(replacementString7->characterCount == 1);
    assert(replacementString7->characters[0] == 'x');

    struct Object *replacementStringObject8 = stringReplace(gc, stringObject4, stringObject5, stringObject1);
    struct String *replacementString8 = replacementStringObject8->value.subObject;

    assert(replacementString8->characterCount == 3);
    assert(replacementString8->characters[0] == 'l');
    assert(replacementString8->characters[1] == 'o');
    assert(replacementString8->characters[2] == '1');

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testStringSplit()
{
    printf("testStringSplit: ");
    struct Gc *gc = gcNew(10000, 0);

    struct Object *stringObject1 = stringNewFromCString(gc, "hallo ich heisse oskar");
    struct String *string1 = stringObject1->value.subObject;

    struct Object *stringObject2 = stringNewFromCString(gc, " ");

    struct Object *stringObjectNotFound = stringNewFromCString(gc, "lol");

    struct Object *arrayObject = stringSplit(gc, stringObject1, stringObject2);
    struct Array *array = arrayObject->value.subObject;

    struct String *splitPart;

    assert(array->objectCount == 4);
    assert(array->objects[0]->type == OBJECT_TYPE_STRING);
    splitPart = array->objects[0]->value.subObject;
    assert(splitPart->characterCount == 5);

    assert(array->objects[1]->type == OBJECT_TYPE_STRING);
    splitPart = array->objects[1]->value.subObject;
    assert(splitPart->characterCount == 3);

    assert(array->objects[2]->type == OBJECT_TYPE_STRING);
    splitPart = array->objects[2]->value.subObject;
    assert(splitPart->characterCount == 6);

    assert(array->objects[3]->type == OBJECT_TYPE_STRING);
    splitPart = array->objects[3]->value.subObject;
    assert(splitPart->characterCount == 5);

    struct Object *arrayOneObject = stringSplit(gc, stringObject1, stringObjectNotFound);
    struct Array *arrayOne = arrayOneObject->value.subObject;

    assert(arrayOne->objectCount == 1);
    splitPart = arrayOne->objects[0]->value.subObject;
    assert(splitPart->characterCount == string1->characterCount);

    struct Object *stringObject3 = stringNewFromCString(gc, "mann o mann o mann o mann o");
    struct Object *stringObject4 = stringNewFromCString(gc, "o");
    struct Object *stringObject5 = stringNewFromCString(gc, "mann");

    struct Object *arrayObject1 = stringSplit(gc, stringObject3, stringObject4);

    struct Array *array1 = arrayObject1->value.subObject;

    assert(array1->objectCount == 5);
    assert(array1->objects[0]->type == OBJECT_TYPE_STRING);
    splitPart = array1->objects[0]->value.subObject;
    assert(splitPart->characterCount == 5);

    assert(array1->objects[1]->type == OBJECT_TYPE_STRING);
    splitPart = array1->objects[1]->value.subObject;
    assert(splitPart->characterCount == 6);

    assert(array1->objects[2]->type == OBJECT_TYPE_STRING);
    splitPart = array1->objects[2]->value.subObject;
    assert(splitPart->characterCount == 6);

    assert(array1->objects[3]->type == OBJECT_TYPE_STRING);
    splitPart = array1->objects[3]->value.subObject;
    assert(splitPart->characterCount == 6);

    assert(array1->objects[4]->type == OBJECT_TYPE_STRING);
    splitPart = array1->objects[4]->value.subObject;
    assert(splitPart->characterCount == 0);

    struct Object *arrayObject2 = stringSplit(gc, stringObject3, stringObject5);
    struct Array *array2 = arrayObject2->value.subObject;

    assert(array2->objectCount == 5);
    assert(array2->objects[0]->type == OBJECT_TYPE_STRING);
    splitPart = array2->objects[0]->value.subObject;
    assert(splitPart->characterCount == 0);

    assert(array2->objects[1]->type == OBJECT_TYPE_STRING);
    splitPart = array2->objects[1]->value.subObject;
    assert(splitPart->characterCount == 3);

    assert(array2->objects[2]->type == OBJECT_TYPE_STRING);
    splitPart = array2->objects[2]->value.subObject;
    assert(splitPart->characterCount == 3);

    assert(array2->objects[3]->type == OBJECT_TYPE_STRING);
    splitPart = array2->objects[3]->value.subObject;
    assert(splitPart->characterCount == 3);

    assert(array2->objects[4]->type == OBJECT_TYPE_STRING);
    splitPart = array2->objects[4]->value.subObject;
    assert(splitPart->characterCount == 2);

    gcSweep(gc);

    gcFree(gc);

    printf("OK\n");
}

void testStringCopy()
{
    printf("testStringCopy: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *stringObject1 = stringNewFromCString(gc, "hallo1");
    struct String *string1 = stringObject1->value.subObject;

    struct Object *stringObject2 = stringCopy(gc, stringObject1);
    struct String *string2 = stringObject2->value.subObject;

    assert(stringObject2->type == OBJECT_TYPE_STRING);
    assert(string2->characterCount == string1->characterCount);
    assert(string2->characters[0] == string1->characters[0]);
    assert(string2->characters[1] == string1->characters[1]);
    assert(string2->characters[2] == string1->characters[2]);
    assert(string2->characters[3] == string1->characters[3]);
    assert(string2->characters[4] == string1->characters[4]);
    assert(string2->characters[5] == string1->characters[5]);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testStringEquals()
{
    printf("testStringEquals: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *string1 = stringNewFromCString(gc, "hallo1");

    struct Object *string2 = stringCopy(gc, string1);

    struct Object *string3 = stringNewFromCString(gc, "ban");

    struct Object *string4 = stringNewFromCString(gc, "");

    assert(stringEquals(string1, string1) == BOOLEAN_TRUE);
    assert(stringEquals(string1, string2) == BOOLEAN_TRUE);
    assert(stringEquals(string1, string3) == BOOLEAN_FALSE);
    assert(stringEquals(string1, string4) == BOOLEAN_FALSE);
    assert(stringEquals(string2, string1) == BOOLEAN_TRUE);
    assert(stringEquals(string2, string2) == BOOLEAN_TRUE);
    assert(stringEquals(string2, string3) == BOOLEAN_FALSE);
    assert(stringEquals(string2, string4) == BOOLEAN_FALSE);
    assert(stringEquals(string3, string1) == BOOLEAN_FALSE);
    assert(stringEquals(string3, string2) == BOOLEAN_FALSE);
    assert(stringEquals(string3, string3) == BOOLEAN_TRUE);
    assert(stringEquals(string3, string4) == BOOLEAN_FALSE);
    assert(stringEquals(string4, string1) == BOOLEAN_FALSE);
    assert(stringEquals(string4, string2) == BOOLEAN_FALSE);
    assert(stringEquals(string4, string3) == BOOLEAN_FALSE);
    assert(stringEquals(string4, string4) == BOOLEAN_TRUE);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testStringHash()
{
    printf("testStringHash: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *string1 = stringNewFromCString(gc, "hallo1");

    struct Object *string2 = stringCopy(gc, string1);

    struct Object *string3 = stringNewFromCString(gc, "");

    struct Object *string4 = stringNewFromCString(gc, "");

    assert(stringHash(string1) == stringHash(string2));
    assert(stringHash(string3) == stringHash(string4));

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testStringFree()
{
    printf("testStringFree: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *stringObject1 = stringNewFromCString(gc, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    objectFree(gc, stringObject1);
    gcFree(gc);

    printf("OK\n");
}

void testArrayNew()
{
    printf("testArrayNew: ");
    struct Gc *gc = gcNew(1000, 0);
    struct Object *arrayObject1 = arrayNew(gc, 14, 14);
    assert(arrayObject1->type == OBJECT_TYPE_ARRAY);
    
    struct Array *array1 = arrayObject1->value.subObject;
    
    assert(array1 != NULL);
    assert(array1->objectCount == 14);
    assert(array1->slotCount == 14);
    array1->objects[0] = NULL;
    assert(array1->objects[0] == NULL);

    struct Object *arrayObject2 = arrayNew(gc, 0, 0);
    assert(arrayObject2->type == OBJECT_TYPE_ARRAY);
    
    struct Array *array2 = arrayObject2->value.subObject;
    
    assert(array2 != NULL);
    assert(array2->objectCount == 0);
    assert(array2->slotCount == 0);

    array1->objects[13] = arrayObject2;
    assert(array1->objects[13] == arrayObject2);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testArraySet()
{
    printf("testArraySet: ");
    struct Gc *gc = gcNew(1000, 0);
    struct Object *arrayObject = arrayNew(gc, 14, 14);
    struct Object *integer = integerNew(gc, -132);

    struct Array *array = arrayObject->value.subObject;

    array->objects[10] = integer;

    assert(arraySet(arrayObject, 10, NULL) == integer);
    assert(array->objects[10] == NULL);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testArrayInsert()
{
    printf("testArrayInsert: ");
    struct Gc *gc = gcNew(1000, 0);
    struct Object *arrayObject = arrayNew(gc, 0, 0);
    struct Object *integer1 = integerNew(gc, 97);
    struct Object *integer2 = integerNew(gc, 98);
    struct Object *integer3 = integerNew(gc, 99);

    struct Array *array = arrayObject->value.subObject;

    assert(array->objectCount == 0);
    assert(array->slotCount == 0);

    arrayPush(gc, arrayObject, integer1);
    arrayInsert(gc, arrayObject, 0, integer2);
    arrayInsert(gc, arrayObject, 0, integer3);

    assert(array->objectCount == 3);
    assert(array->slotCount == 5);

    assert(array->objects[0] == integer3);
    assert(array->objects[1] == integer2);
    assert(array->objects[2] == integer1);

    arrayInsert(gc, arrayObject, 0, integer1);
    arrayInsert(gc, arrayObject, 1, integer2);
    arrayInsert(gc, arrayObject, 2, integer3);

    assert(array->objectCount == 6);
    assert(array->slotCount == 10);

    assert(array->objects[0] == integer1);
    assert(array->objects[1] == integer2);
    assert(array->objects[2] == integer3);
    assert(array->objects[3] == integer3);
    assert(array->objects[4] == integer2);
    assert(array->objects[5] == integer1);

    arrayPush(gc, arrayObject, integer2);

    assert(array->objectCount == 7);
    assert(array->slotCount == 10);
    assert(array->objects[6] == integer2);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testArrayInsertAll()
{
    printf("testArrayInsertAll: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *arrayObject1 = arrayNew(gc, 3, 3);
    struct Object *arrayObject2 = arrayNew(gc, 2, 2);
    struct Object *arrayObject3 = arrayNew(gc, 0, 0);
    struct Object *integer1 = integerNew(gc, 97);
    struct Object *integer2 = integerNew(gc, 98);
    struct Object *integer3 = integerNew(gc, 99);

    struct Array *array1 = arrayObject1->value.subObject;
    struct Array *array2 = arrayObject2->value.subObject;
    struct Array *array3 = arrayObject3->value.subObject;

    array1->objects[0] = integer1;
    array1->objects[1] = integer2;
    array1->objects[2] = integer3;

    array2->objects[0] = integer3;
    array2->objects[1] = integer2;

    assert(array1->objectCount == 3);
    assert(array1->slotCount == 3);
    assert(array2->objectCount == 2);
    assert(array2->slotCount == 2);

    arrayInsertAll(gc, arrayObject1, 0, arrayObject2);

    assert(array1->objectCount == 5);
    assert(array1->slotCount == 8);
    assert(array2->objectCount == 2);
    assert(array2->slotCount == 2);

    assert(array1->objects[0] == integer3);
    assert(array1->objects[1] == integer2);
    assert(array1->objects[2] == integer1);
    assert(array1->objects[3] == integer2);
    assert(array1->objects[4] == integer3);

    arrayInsertAll(gc, arrayObject1, 3, arrayObject1);

    assert(array1->objectCount == 10);
    assert(array1->slotCount == 16);
    
    assert(array1->objects[0] == integer3);
    assert(array1->objects[1] == integer2);
    assert(array1->objects[2] == integer1);
    assert(array1->objects[3] == integer3);
    assert(array1->objects[4] == integer2);
    assert(array1->objects[5] == integer1);
    assert(array1->objects[6] == integer2);
    assert(array1->objects[7] == integer3);
    assert(array1->objects[8] == integer2);
    assert(array1->objects[9] == integer3);

    arrayInsertAll(gc, arrayObject1, 1, arrayObject2);

    assert(array1->objectCount == 12);
    assert(array1->slotCount == 16);
    
    assert(array1->objects[0] == integer3);
    assert(array1->objects[1] == integer3);
    assert(array1->objects[2] == integer2);
    assert(array1->objects[3] == integer2);
    assert(array1->objects[4] == integer1);
    assert(array1->objects[5] == integer3);
    assert(array1->objects[6] == integer2);
    assert(array1->objects[7] == integer1);
    assert(array1->objects[8] == integer2);
    assert(array1->objects[9] == integer3);
    assert(array1->objects[10] == integer2);
    assert(array1->objects[11] == integer3);

    arrayPushAll(gc, arrayObject2, arrayObject2);

    assert(array2->objectCount == 4);
    assert(array2->slotCount == 7);

    assert(array2->objects[0] == integer3);
    assert(array2->objects[1] == integer2);
    assert(array2->objects[2] == integer3);
    assert(array2->objects[3] == integer2);

    arrayInsertAll(gc, arrayObject2, 2, arrayObject3);

    assert(array2->objectCount == 4);
    assert(array2->slotCount == 7);
    assert(array3->objectCount == 0);
    assert(array3->slotCount == 0);

    assert(array2->objects[0] == integer3);
    assert(array2->objects[1] == integer2);
    assert(array2->objects[2] == integer3);
    assert(array2->objects[3] == integer2);

    arrayPushAll(gc, arrayObject2, arrayObject1);

    assert(array2->objectCount == 16);
    assert(array2->slotCount == 25);
    
    assert(array2->objects[0] == integer3);
    assert(array2->objects[1] == integer2);
    assert(array2->objects[2] == integer3);
    assert(array2->objects[3] == integer2);
    assert(array2->objects[4] == integer3);
    assert(array2->objects[5] == integer3);
    assert(array2->objects[6] == integer2);
    assert(array2->objects[7] == integer2);
    assert(array2->objects[8] == integer1);
    assert(array2->objects[9] == integer3);
    assert(array2->objects[10] == integer2);
    assert(array2->objects[11] == integer1);
    assert(array2->objects[12] == integer2);
    assert(array2->objects[13] == integer3);
    assert(array2->objects[14] == integer2);
    assert(array2->objects[15] == integer3);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testArrayRemove()
{
    printf("testArrayRemove: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *array1 = arrayNew(gc, 3, 3);
    struct Object *integer1 = integerNew(gc, 97);
    struct Object *integer2 = integerNew(gc, 98);
    struct Object *integer3 = integerNew(gc, 99);

    struct Array *pureArray1 = array1->value.subObject;

    arraySet(array1, 0, integer1);
    arraySet(array1, 1, integer2);
    arraySet(array1, 2, integer3);

    assert(arrayRemove(array1, 1) == integer2);

    assert(pureArray1->objectCount == 2);
    assert(pureArray1->slotCount == 3);

    assert(pureArray1->objects[0] == integer1);
    assert(pureArray1->objects[1] == integer3);

    assert(arrayRemove(array1, 0) == integer1);

    assert(pureArray1->objectCount == 1);
    assert(pureArray1->slotCount == 3);

    assert(pureArray1->objects[0] == integer3);

    assert(arrayRemove(array1, 0) == integer3);

    assert(pureArray1->objectCount == 0);
    assert(pureArray1->slotCount == 3);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testArraySwap()
{
    printf("testArraySwap: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *array1 = arrayNew(gc, 3, 3);
    struct Object *integer1 = integerNew(gc, 97);
    struct Object *integer2 = integerNew(gc, 98);
    struct Object *integer3 = integerNew(gc, 99);

    arraySet(array1, 0, integer1);
    arraySet(array1, 1, integer2);
    arraySet(array1, 2, integer3);

    arraySwap(array1, 0, 2);

    assert(arrayGet(array1, 0) == integer3);
    assert(arrayGet(array1, 2) == integer1);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testArrayCopy()
{
    printf("testArrayCopy: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *array1 = arrayNew(gc, 3, 3);
    struct Object *integer1 = integerNew(gc, 97);
    struct Object *integer2 = integerNew(gc, 98);
    struct Object *integer3 = integerNew(gc, 99);

    arraySet(array1, 0, integer1);
    arraySet(array1, 1, integer2);
    arraySet(array1, 2, integer3);

    struct Object *array2 = arrayCopy(gc, array1);

    assert(arraySize(array2) == arraySize(array1));
    assert(arrayGet(array2, 0) != arrayGet(array1, 0));
    assert(arrayGet(array2, 1) != arrayGet(array1, 1));
    assert(arrayGet(array2, 2) != arrayGet(array1, 2));
    assert(arrayGet(array2, 0)->type == OBJECT_TYPE_INTEGER);
    assert(arrayGet(array2, 1)->type == OBJECT_TYPE_INTEGER);
    assert(arrayGet(array2, 2)->type == OBJECT_TYPE_INTEGER);
    assert(arrayGet(array2, 0)->value.integerValue == 97);
    assert(arrayGet(array2, 1)->value.integerValue == 98);
    assert(arrayGet(array2, 2)->value.integerValue == 99);

    integer1->value.integerValue = 55;
    assert(arrayGet(array2, 0)->value.integerValue == 97);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testArrayEquals()
{
    printf("testArrayEquals: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *array1 = arrayNew(gc, 3, 3);
    struct Object *integer1 = integerNew(gc, 97);
    struct Object *integer2 = integerNew(gc, 98);
    struct Object *integer3 = integerNew(gc, 99);

    arraySet(array1, 0, integer1);
    arraySet(array1, 1, integer2);
    arraySet(array1, 2, integer3);

    assert(arrayEquals(array1, array1) == 1);

    struct Object *array2 = arrayCopy(gc, array1);
    
    assert(arrayEquals(array1, array2) == 1);

    arrayGet(array2, 0)->value.integerValue = -1;

    assert(arrayEquals(array1, array2) == 0);

    arrayGet(array2, 0)->value.integerValue = 97;

    assert(arrayEquals(array1, array2) == 1);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testArrayHash()
{
    printf("testArrayHash: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *array1 = arrayNew(gc, 3, 3);
    struct Object *integer1 = integerNew(gc, 97);
    struct Object *integer2 = integerNew(gc, 98);
    struct Object *integer3 = integerNew(gc, 99);

    arraySet(array1, 0, integer1);
    arraySet(array1, 1, integer2);
    arraySet(array1, 2, integer3);

    assert(arrayHash(array1) == arrayHash(array1));

    struct Object *array2 = arrayCopy(gc, array1);

    assert(arrayHash(array1) == arrayHash(array2));

    struct Object *array3 = arrayNew(gc, 0, 0);

    assert(arrayHash(array3) == 1);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testArrayStringCharacterCount()
{
    printf("testArrayStringCharacterCount: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *array1 = arrayNew(gc, 3, 3);
    struct Object *array2 = arrayNew(gc, 0, 3);
    struct Object *integer1 = integerNew(gc, 97);
    struct Object *integer2 = integerNew(gc, 8);
    struct Object *integer3 = integerNew(gc, 199);

    arraySet(array1, 0, integer1);
    arraySet(array1, 1, integer2);
    arraySet(array1, 2, integer3);

    assert(arrayStringCharacterCount(array1) == 10);

    integer1->value.integerValue = 912;

    assert(arrayStringCharacterCount(array1) == 11);

    assert(arrayStringCharacterCount(array2) == 2);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testArrayWriteToString()
{
    printf("testArrayWriteToString: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *array1 = arrayNew(gc, 3, 3);
    struct Object *array2 = arrayNew(gc, 0, 3);
    struct Object *integer1 = integerNew(gc, 97);
    struct Object *integer2 = integerNew(gc, 8);
    struct Object *integer3 = integerNew(gc, 199);

    arraySet(array1, 0, integer1);
    arraySet(array1, 1, integer2);
    arraySet(array1, 2, integer3);

    struct Object *stringObject1 = stringNew(gc, arrayStringCharacterCount(array1));
    struct Object *stringObject2 = stringNew(gc, arrayStringCharacterCount(array2));

    uint32_t index = 0;

    arrayWriteToString(array1, stringObject1, &index);

    struct String *string1 = stringObject1->value.subObject;

    assert(string1->characterCount == 10);
    assert(string1->characters[0] == '[');
    assert(string1->characters[1] == '9');
    assert(string1->characters[2] == '7');
    assert(string1->characters[3] == ',');
    assert(string1->characters[4] == '8');
    assert(string1->characters[5] == ',');
    assert(string1->characters[6] == '1');
    assert(string1->characters[7] == '9');
    assert(string1->characters[8] == '9');
    assert(string1->characters[9] == ']');

    index = 0;

    arrayWriteToString(array2, stringObject2, &index);

    struct String *string2 = stringObject2->value.subObject;

    assert(string2->characterCount == 2);
    assert(string2->characters[0] == '[');
    assert(string2->characters[1] == ']');

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testArrayToString()
{
    printf("testArrayToString: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *array1 = arrayNew(gc, 3, 3);
    struct Object *integer1 = integerNew(gc, 7);
    struct Object *integer2 = integerNew(gc, 98);
    struct Object *integer3 = integerNew(gc, 121299);

    arraySet(array1, 0, integer1);
    arraySet(array1, 1, integer2);
    arraySet(array1, 2, integer3);

    struct Object *stringObject1 = arrayToString(gc, array1);
    struct String *string1 = stringObject1->value.subObject;

    assert(string1->characterCount == 13);

    assert(string1->characters[0] == '[');
    assert(string1->characters[1] == '7');
    assert(string1->characters[2] == ',');
    assert(string1->characters[3] == '9');
    assert(string1->characters[4] == '8');
    assert(string1->characters[5] == ',');
    assert(string1->characters[6] == '1');
    assert(string1->characters[7] == '2');
    assert(string1->characters[8] == '1');
    assert(string1->characters[9] == '2');
    assert(string1->characters[10] == '9');
    assert(string1->characters[11] == '9');
    assert(string1->characters[12] == ']');

    struct Object *array2 = arrayNew(gc, 0, 0);

    struct Object *stringObject2 = arrayToString(gc, array2);
    struct String *string2 = stringObject2->value.subObject;

    assert(string2->characterCount == 2);

    assert(string2->characters[0] == '[');
    assert(string2->characters[1] == ']');

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testArrayMark()
{
    printf("testArrayMark: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *arrayObject1 = arrayNew(gc, 3, 3);
    struct Object *arrayObject2 = arrayNew(gc, 0, 0);
    struct Object *integer1 = integerNew(gc, 7);
    struct Object *integer2 = integerNew(gc, 98);
    struct Object *integer3 = integerNew(gc, 121299);

    struct Array *array1 = arrayObject1->value.subObject;

    array1->objects[0] = integer1;
    array1->objects[1] = integer2;
    array1->objects[2] = integer3;

    objectMark(arrayObject1);

    assert(arrayObject1->type & OBJECT_MARK);
    assert(integer1->type & OBJECT_MARK);
    assert(integer2->type & OBJECT_MARK);
    assert(integer3->type & OBJECT_MARK);
    assert(integer3->type & OBJECT_MARK);

    integer2->type = OBJECT_TYPE_INTEGER; // unmark

    objectMark(arrayObject1);

    assert(arrayObject1->type & OBJECT_MARK);
    assert(integer1->type & OBJECT_MARK);
    assert(!(integer2->type & OBJECT_MARK));
    assert(integer3->type & OBJECT_MARK);
    assert(integer3->type & OBJECT_MARK);

    objectMark(arrayObject2);
    
    assert(arrayObject2->type & OBJECT_MARK);

    gcSweep(gc);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testArrayFree()
{
    printf("testArrayFree: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *arrayObject1 = arrayNew(gc, 3, 3);
    assert(arrayObject1->type == OBJECT_TYPE_ARRAY);
    objectFree(gc, arrayObject1);

    gcFree(gc);

    printf("OK\n");
}

void testMapNew()
{
    printf("testMapNew: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *mapObject1 = mapNew(gc);
    struct Map *map1 = mapObject1->value.subObject;

    assert(mapObject1->type == OBJECT_TYPE_MAP);

    assert(map1->bucketCount == 8);

    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testMapGet()
{
    printf("testMapGet: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *map1 = mapNew(gc);
    struct Object *integer1 = integerNew(gc, 1212);

    struct Object *string1 = stringNewFromCString(gc, "hallo1");

    assert(mapGet(map1, integer1) == NULL);
    assert(mapGet(map1, string1) == NULL);
    assert(mapGet(map1, map1) == NULL);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testMapPut()
{
    printf("testMapPut: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *map1 = mapNew(gc);
    struct Map *realMap1 = map1->value.subObject;
    
    struct Object *integer1 = integerNew(gc, 1);
    struct Object *integer2 = integerNew(gc, 17);
    struct Object *integer3 = integerNew(gc, 82);
    struct Object *integer4 = integerNew(gc, 43);
    struct Object *integer5 = integerNew(gc, 17);

    struct Object *integer6 = integerNew(gc, 121);
    struct Object *integer7 = integerNew(gc, 441);
    struct Object *integer8 = integerNew(gc, 566);
    struct Object *integer9 = integerNew(gc, 874);
    struct Object *integer10 = integerNew(gc, 236);

    assert(mapPut(gc, map1, integer1, integer6) == NULL);
    assert(mapSize(map1) == 1);
    assert(realMap1->bucketCount == 8);

    assert(mapPut(gc, map1, integer2, integer7) == NULL);
    assert(mapSize(map1) == 2);
    assert(realMap1->bucketCount == 8);

    assert(mapPut(gc, map1, integer3, integer8) == NULL);
    assert(mapSize(map1) == 3);
    assert(realMap1->bucketCount == 8);

    assert(mapPut(gc, map1, integer4, integer9) == NULL);
    assert(mapSize(map1) == 4);
    assert(realMap1->bucketCount == 8);
    
    assert(mapPut(gc, map1, integer5, integer10) == integer7);
    assert(mapGet(map1, integer5) == integer10);
    assert(mapSize(map1) == 4);
    assert(realMap1->bucketCount == 8);

    assert(mapPut(gc, map1, integer6, integer5) == NULL);
    assert(mapGet(map1, integer6) == integer5);
    assert(mapSize(map1) == 5);
    assert(realMap1->bucketCount == 8);

    assert(mapPut(gc, map1, integer7, integer4) == NULL);
    assert(mapGet(map1, integer7) == integer4);
    assert(mapSize(map1) == 6);
    assert(realMap1->bucketCount == 8);

    assert(mapPut(gc, map1, integer8, integer3) == NULL);
    assert(mapGet(map1, integer8) == integer3);
    assert(mapSize(map1) == 7);
    assert(realMap1->bucketCount == 16);

    assert(mapPut(gc, map1, integer9, integer2) == NULL);
    assert(mapGet(map1, integer9) == integer2);
    assert(mapSize(map1) == 8);
    assert(realMap1->bucketCount == 16);

    assert(mapPut(gc, map1, NULL, integer1) == NULL);
    assert(mapGet(map1, NULL) == integer1);
    assert(mapSize(map1) == 9);
    assert(realMap1->bucketCount == 16);

    assert(mapPut(gc, map1, NULL, NULL) == integer1);
    assert(mapGet(map1, NULL) == NULL);
    assert(mapSize(map1) == 9);
    assert(realMap1->bucketCount == 16);

    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testMapPutAll()
{
    printf("testMapPutAll: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *map1 = mapNew(gc);
    struct Object *map2 = mapNew(gc);
    struct Object *map3 = mapNew(gc);

    struct Map *pureMap1 = map1->value.subObject;
    struct Map *pureMap2 = map2->value.subObject;

    struct Object *integer1 = integerNew(gc, 1);
    struct Object *integer2 = integerNew(gc, 17);
    struct Object *integer3 = integerNew(gc, 82);
    struct Object *integer4 = integerNew(gc, 43);
    struct Object *integer5 = integerNew(gc, 17);

    struct Object *integer6 = integerNew(gc, 121);
    struct Object *integer7 = integerNew(gc, 441);
    struct Object *integer8 = integerNew(gc, 566);
    struct Object *integer9 = integerNew(gc, 874);
    struct Object *integer10 = integerNew(gc, 236);

    mapPut(gc, map1, integer1, integer6);
    mapPut(gc, map1, integer2, integer7);
    mapPut(gc, map1, integer3, integer8);
    mapPut(gc, map1, integer4, integer9);

    mapPut(gc, map2, integer5, integer10);
    mapPut(gc, map2, integer7, integer1);

    mapPutAll(gc, map1, map2);

    assert(mapSize(map1) == 5);
    assert(pureMap1->bucketCount == 8);
    assert(mapGet(map1, integer1) == integer6);
    assert(mapGet(map1, integer2) == integer10);
    assert(mapGet(map1, integer3) == integer8);
    assert(mapGet(map1, integer4) == integer9);
    assert(mapGet(map1, integer5) == integer10);
    assert(mapGet(map1, integer7) == integer1);

    mapPutAll(gc, map2, map3);

    assert(mapSize(map2) == 2);
    assert(pureMap2->bucketCount == 8);
    assert(mapGet(map2, integer5) == integer10);
    assert(mapGet(map2, integer7) == integer1);

    mapPutAll(gc, map2, map2);

    assert(mapSize(map2) == 2);
    assert(pureMap2->bucketCount == 8);
    assert(mapGet(map2, integer5) == integer10);
    assert(mapGet(map2, integer7) == integer1);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testMapRemove()
{
    printf("testMapRemove: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *map1 = mapNew(gc);
    
    struct Object *integer1 = integerNew(gc, 1);
    struct Object *integer2 = integerNew(gc, 17);
    struct Object *integer3 = integerNew(gc, 82);
    struct Object *integer4 = integerNew(gc, 43);
    struct Object *integer5 = integerNew(gc, 17);

    struct Object *integer6 = integerNew(gc, 121);
    struct Object *integer7 = integerNew(gc, 441);
    struct Object *integer8 = integerNew(gc, 566);
    struct Object *integer9 = integerNew(gc, 874);
    struct Object *integer10 = integerNew(gc, 236);

    assert(mapRemove(gc, map1, integer10) == NULL);

    assert(mapSize(map1) == 0);

    mapPut(gc, map1, integer1, integer6);
    mapPut(gc, map1, integer2, integer7);
    mapPut(gc, map1, integer3, integer8);
    mapPut(gc, map1, integer4, integer9);
    mapPut(gc, map1, integer5, integer10);

    assert(mapSize(map1) == 4);

    assert(mapRemove(gc, map1, integer2) == integer10);
    assert(mapSize(map1) == 3);
    assert(mapGet(map1, integer2) == NULL);

    assert(mapRemove(gc, map1, integer2) == NULL);
    assert(mapSize(map1) == 3);

    assert(mapRemove(gc, map1, integer4) == integer9);
    assert(mapSize(map1) == 2);
    assert(mapGet(map1, integer4) == NULL);

    assert(mapRemove(gc, map1, integer3) == integer8);
    assert(mapSize(map1) == 1);
    assert(mapGet(map1, integer3) == NULL);

    assert(mapRemove(gc, map1, integer1) == integer6);
    assert(mapSize(map1) == 0);
    assert(mapGet(map1, integer1) == NULL);

    assert(mapRemove(gc, map1, NULL) == NULL);
    assert(mapSize(map1) == 0);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testMapHasKey()
{
    printf("testMapHasKey: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *map1 = mapNew(gc);

    struct Object *integer1 = integerNew(gc, 1);

    assert(mapHasKey(map1, integer1) == BOOLEAN_FALSE);
    assert(mapHasKey(map1, NULL) == BOOLEAN_FALSE);

    mapPut(gc, map1, integer1, NULL);

    assert(mapHasKey(map1, integer1) == BOOLEAN_TRUE);

    mapRemove(gc, map1, integer1);

    assert(mapHasKey(map1, integer1) == BOOLEAN_FALSE);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testMapEntries()
{
    printf("testMapEntries: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *map1 = mapNew(gc);
    struct Object *map2 = mapNew(gc);
    
    struct Object *integer1 = integerNew(gc, 1);
    struct Object *integer2 = integerNew(gc, 17);
    struct Object *integer3 = integerNew(gc, 82);
    struct Object *integer4 = integerNew(gc, 43);
    struct Object *integer5 = integerNew(gc, 18);

    struct Object *integer6 = integerNew(gc, 121);
    struct Object *integer7 = integerNew(gc, 441);
    struct Object *integer8 = integerNew(gc, 566);
    struct Object *integer9 = integerNew(gc, 874);
    struct Object *integer10 = integerNew(gc, 236);

    mapPut(gc, map1, integer1, integer6);
    mapPut(gc, map1, integer2, integer7);
    mapPut(gc, map1, integer3, integer8);
    mapPut(gc, map1, integer4, integer9);
    mapPut(gc, map1, integer5, integer10);

    struct Object *emptyArrayObject = mapEntries(gc, map2);
    struct Array *emptyArray = emptyArrayObject->value.subObject;

    assert(emptyArray->objectCount == 0);

    struct Object *arrayObject = mapEntries(gc, map1);
    struct Array *array = arrayObject->value.subObject;

    assert(arrayObject->type == OBJECT_TYPE_ARRAY);
    assert(array->objectCount == 5);
    assert(array->slotCount == 5);

    assert(array->objects[0]->type == OBJECT_TYPE_PAIR);
    assert(array->objects[1]->type == OBJECT_TYPE_PAIR);
    assert(array->objects[2]->type == OBJECT_TYPE_PAIR);
    assert(array->objects[3]->type == OBJECT_TYPE_PAIR);
    assert(array->objects[4]->type == OBJECT_TYPE_PAIR);

    struct Pair *p1 = (struct Pair *) array->objects[0]->value.subObject;
    struct Pair *p2 = (struct Pair *) array->objects[1]->value.subObject;
    struct Pair *p3 = (struct Pair *) array->objects[2]->value.subObject;
    struct Pair *p4 = (struct Pair *) array->objects[3]->value.subObject;
    struct Pair *p5 = (struct Pair *) array->objects[4]->value.subObject;

    struct Object *f1 = p1->first;
    struct Object *f2 = p2->first;
    struct Object *f3 = p3->first;
    struct Object *f4 = p4->first;
    struct Object *f5 = p5->first;

    assert(f1 == integer1 || f2 == integer1 || f3 == integer1 || f4 == integer1 || f5 == integer1);
    assert(f1 == integer2 || f2 == integer2 || f3 == integer2 || f4 == integer2 || f5 == integer2);
    assert(f1 == integer3 || f2 == integer3 || f3 == integer3 || f4 == integer3 || f5 == integer3);
    assert(f1 == integer4 || f2 == integer4 || f3 == integer4 || f4 == integer4 || f5 == integer4);
    assert(f1 == integer5 || f2 == integer5 || f3 == integer5 || f4 == integer5 || f5 == integer5);

    struct Object *s1 = p1->second;
    struct Object *s2 = p2->second;
    struct Object *s3 = p3->second;
    struct Object *s4 = p4->second;
    struct Object *s5 = p5->second;

    assert(s1 == integer6 || s2 == integer6 || s3 == integer6 || s4 == integer6 || s5 == integer6);
    assert(s1 == integer7 || s2 == integer7 || s3 == integer7 || s4 == integer7 || s5 == integer7);
    assert(s1 == integer8 || s2 == integer8 || s3 == integer8 || s4 == integer8 || s5 == integer8);
    assert(s1 == integer9 || s2 == integer9 || s3 == integer9 || s4 == integer9 || s5 == integer9);
    assert(s1 == integer10 || s2 == integer10 || s3 == integer10 || s4 == integer10 || s5 == integer10);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testMapKeys()
{
    printf("testMapKeys: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *map1 = mapNew(gc);
    struct Object *map2 = mapNew(gc);
    
    struct Object *integer1 = integerNew(gc, 1);
    struct Object *integer2 = integerNew(gc, 17);
    struct Object *integer3 = integerNew(gc, 82);
    struct Object *integer4 = integerNew(gc, 43);
    struct Object *integer5 = integerNew(gc, 18);

    struct Object *integer6 = integerNew(gc, 121);
    struct Object *integer7 = integerNew(gc, 441);
    struct Object *integer8 = integerNew(gc, 566);
    struct Object *integer9 = integerNew(gc, 874);
    struct Object *integer10 = integerNew(gc, 236);

    mapPut(gc, map1, integer1, integer6);
    mapPut(gc, map1, integer2, integer7);
    mapPut(gc, map1, integer3, integer8);
    mapPut(gc, map1, integer4, integer9);
    mapPut(gc, map1, integer5, integer10);

    struct Object *emptyArrayObject = mapKeys(gc, map2);
    struct Array *emptyArray = emptyArrayObject->value.subObject;

    assert(emptyArray->objectCount == 0);

    struct Object *arrayObject = mapKeys(gc, map1);
    struct Array *array = arrayObject->value.subObject;

    assert(arrayObject->type == OBJECT_TYPE_ARRAY);
    assert(array->objectCount == 5);
    assert(array->slotCount == 5);

    assert(array->objects[0]->type == OBJECT_TYPE_INTEGER);
    assert(array->objects[1]->type == OBJECT_TYPE_INTEGER);
    assert(array->objects[2]->type == OBJECT_TYPE_INTEGER);
    assert(array->objects[3]->type == OBJECT_TYPE_INTEGER);
    assert(array->objects[4]->type == OBJECT_TYPE_INTEGER);

    struct Object *i1 = array->objects[0];
    struct Object *i2 = array->objects[1];
    struct Object *i3 = array->objects[2];
    struct Object *i4 = array->objects[3];
    struct Object *i5 = array->objects[4];

    assert(i1 == integer1 || i2 == integer1 || i3 == integer1 || i4 == integer1 || i5 == integer1);
    assert(i1 == integer2 || i2 == integer2 || i3 == integer2 || i4 == integer2 || i5 == integer2);
    assert(i1 == integer3 || i2 == integer3 || i3 == integer3 || i4 == integer3 || i5 == integer3);
    assert(i1 == integer4 || i2 == integer4 || i3 == integer4 || i4 == integer4 || i5 == integer4);
    assert(i1 == integer5 || i2 == integer5 || i3 == integer5 || i4 == integer5 || i5 == integer5);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testMapValues()
{
    printf("testMapValues: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *map1 = mapNew(gc);
    struct Object *map2 = mapNew(gc);
    
    struct Object *integer1 = integerNew(gc, 1);
    struct Object *integer2 = integerNew(gc, 17);
    struct Object *integer3 = integerNew(gc, 82);
    struct Object *integer4 = integerNew(gc, 43);
    struct Object *integer5 = integerNew(gc, 18);

    struct Object *integer6 = integerNew(gc, 121);
    struct Object *integer7 = integerNew(gc, 441);
    struct Object *integer8 = integerNew(gc, 566);
    struct Object *integer9 = integerNew(gc, 874);
    struct Object *integer10 = integerNew(gc, 236);

    mapPut(gc, map1, integer1, integer6);
    mapPut(gc, map1, integer2, integer7);
    mapPut(gc, map1, integer3, integer8);
    mapPut(gc, map1, integer4, integer9);
    mapPut(gc, map1, integer5, integer10);

    struct Object *emptyArrayObject = mapValues(gc, map2);
    struct Array *emptyArray = emptyArrayObject->value.subObject;

    assert(emptyArray->objectCount == 0);

    struct Object *arrayObject = mapValues(gc, map1);
    struct Array *array = arrayObject->value.subObject;

    assert(arrayObject->type == OBJECT_TYPE_ARRAY);
    assert(array->objectCount == 5);
    assert(array->slotCount == 5);

    assert(array->objects[0]->type == OBJECT_TYPE_INTEGER);
    assert(array->objects[1]->type == OBJECT_TYPE_INTEGER);
    assert(array->objects[2]->type == OBJECT_TYPE_INTEGER);
    assert(array->objects[3]->type == OBJECT_TYPE_INTEGER);
    assert(array->objects[4]->type == OBJECT_TYPE_INTEGER);

    struct Object *i1 = array->objects[0];
    struct Object *i2 = array->objects[1];
    struct Object *i3 = array->objects[2];
    struct Object *i4 = array->objects[3];
    struct Object *i5 = array->objects[4];

    assert(i1 == integer6 || i2 == integer6 || i3 == integer6 || i4 == integer6 || i5 == integer6);
    assert(i1 == integer7 || i2 == integer7 || i3 == integer7 || i4 == integer7 || i5 == integer7);
    assert(i1 == integer8 || i2 == integer8 || i3 == integer8 || i4 == integer8 || i5 == integer8);
    assert(i1 == integer9 || i2 == integer9 || i3 == integer9 || i4 == integer9 || i5 == integer9);
    assert(i1 == integer10 || i2 == integer10 || i3 == integer10 || i4 == integer10 || i5 == integer10);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testMapSwap()
{
    printf("testMapSwap: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *map1 = mapNew(gc);
    
    struct Object *integer1 = integerNew(gc, 1);
    struct Object *integer2 = integerNew(gc, 17);
    struct Object *integer3 = integerNew(gc, 82);
    struct Object *integer4 = integerNew(gc, 43);
    struct Object *integer5 = integerNew(gc, 18);

    struct Object *integer6 = integerNew(gc, 121);
    struct Object *integer7 = integerNew(gc, 441);
    struct Object *integer8 = integerNew(gc, 566);
    struct Object *integer9 = integerNew(gc, 874);
    struct Object *integer10 = integerNew(gc, 236);

    mapPut(gc, map1, integer1, integer6);
    mapPut(gc, map1, integer2, integer7);
    mapPut(gc, map1, integer3, integer8);
    mapPut(gc, map1, integer4, integer9);
    mapPut(gc, map1, integer5, integer10);

    assert(mapSize(map1) == 5);

    mapSwap(map1, integer1, integer2);

    assert(mapGet(map1, integer1) == integer7);
    assert(mapGet(map1, integer2) == integer6);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testMapCopy()
{
    printf("testMapCopy: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *map1 = mapNew(gc);

    struct Object *stringObject1 = stringNewFromCString(gc, "hier");
    struct Object *stringObject2 = stringNewFromCString(gc, "dort");
    struct Object *stringObject3 = stringNewFromCString(gc, "nah");
    struct Object *stringObject4 = stringNewFromCString(gc, "fern");
    struct Object *integer1 = integerNew(gc, 2);

    mapPut(gc, map1, stringObject1, stringObject2);
    mapPut(gc, map1, stringObject3, stringObject4);
    mapPut(gc, map1, integer1, NULL);
    mapPut(gc, map1, NULL, integer1);

    struct Object *map2 = mapCopy(gc, map1);

    assert(mapSize(map2) == 4);
    assert(mapGet(map2, stringObject1) != stringObject2);
    assert(mapGet(map2, stringObject3) != stringObject4);
    assert(mapGet(map2, integer1) == NULL);
    assert(mapGet(map2, NULL) != integer1);

    assert(objectEquals(mapGet(map2, stringObject1), stringObject2) == BOOLEAN_TRUE);
    assert(objectEquals(mapGet(map2, stringObject3), stringObject4) == BOOLEAN_TRUE);
    assert(objectEquals(mapGet(map2, NULL), integer1) == BOOLEAN_TRUE);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testMapEquals()
{
    printf("testMapEquals: ");
    struct Gc *gc = gcNew(1500, 0);
    struct Object *map1 = mapNew(gc);
    struct Object *map2 = mapNew(gc);

    struct Object *stringObject1 = stringNewFromCString(gc, "hier");
    struct Object *stringObject2 = stringNewFromCString(gc, "dort");
    struct Object *stringObject3 = stringNewFromCString(gc, "nah");
    struct Object *stringObject4 = stringNewFromCString(gc, "fern");
    struct Object *integer1 = integerNew(gc, 2);

    mapPut(gc, map1, stringObject1, stringObject2);
    mapPut(gc, map1, stringObject3, stringObject4);
    mapPut(gc, map1, integer1, NULL);
    mapPut(gc, map1, NULL, integer1);

    mapPut(gc, map2, stringObject1, stringObject2);

    assert(mapEquals(map1, map2) == BOOLEAN_FALSE);
    assert(mapEquals(map2, map1) == BOOLEAN_FALSE);

    struct Object *mapCopy1 = mapCopy(gc, map1);

    assert(mapEquals(map1, map1) == BOOLEAN_TRUE);
    assert(mapEquals(map1, mapCopy1) == BOOLEAN_TRUE);
    
    mapRemove(gc, mapCopy1, integer1);
    
    assert(mapEquals(map1, mapCopy1) == BOOLEAN_FALSE);

    mapPut(gc, mapCopy1, integer1, integer1);

    assert(mapEquals(map1, mapCopy1) == BOOLEAN_FALSE);

    mapPut(gc, mapCopy1, integer1, NULL);

    assert(mapEquals(map1, mapCopy1) == BOOLEAN_TRUE);

    gcSweep(gc);

    assert(gc->head == NULL);
    assert(gc->size == 0);

    gcFree(gc);
    printf("OK\n");
}

void testMapHash()
{
    printf("testMapHash: ");
    struct Gc *gc = gcNew(1000, 0);
    struct Object *map1 = mapNew(gc);

    struct Object *stringObject1 = stringNewFromCString(gc, "hier");
    struct Object *stringObject2 = stringNewFromCString(gc, "dort");
    struct Object *stringObject3 = stringNewFromCString(gc, "nah");
    struct Object *stringObject4 = stringNewFromCString(gc, "fern");
    struct Object *integer1 = integerNew(gc, 2);

    mapPut(gc, map1, stringObject1, stringObject2);
    mapPut(gc, map1, stringObject3, stringObject4);
    mapPut(gc, map1, integer1, NULL);
    mapPut(gc, map1, NULL, integer1);

    struct Object *map2 = mapCopy(gc, map1);

    assert(mapHash(map1) == mapHash(map1));
    assert(mapHash(map1) == mapHash(map2));
    
    mapRemove(gc, map2, integer1);
    mapPut(gc, map2, integer1, integer1);
    mapPut(gc, map2, integer1, NULL);

    assert(mapHash(map1) == mapHash(map2));

    gcSweep(gc);

    assert(gc->head == NULL);
    assert(gc->size == 0);

    gcFree(gc);
    printf("OK\n");
}

void testMapStringCharacterCount()
{
    printf("testMapStringCharacterCount: ");
    struct Gc *gc = gcNew(1000, 0);
    struct Object *map1 = mapNew(gc);

    struct Object *stringObject1 = stringNewFromCString(gc, "hier");
    struct Object *stringObject2 = stringNewFromCString(gc, "dort");
    struct Object *stringObject3 = stringNewFromCString(gc, "nah");
    struct Object *stringObject4 = stringNewFromCString(gc, "fern");
    struct Object *integer1 = integerNew(gc, 2);

    mapPut(gc, map1, stringObject1, stringObject2);
    mapPut(gc, map1, stringObject3, stringObject4);
    mapPut(gc, map1, integer1, NULL);
    mapPut(gc, map1, NULL, integer1);

    assert(mapStringCharacterCount(map1) == 34);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}
    
void testMapWriteToString()
{
    printf("testMapWriteToString: ");
    struct Gc *gc = gcNew(1000, 0);
    struct Object *map1 = mapNew(gc);

    struct Object *stringObject1 = stringNewFromCString(gc, "hier");
    struct Object *stringObject2 = stringNewFromCString(gc, "dort");
    struct Object *stringObject3 = stringNewFromCString(gc, "nah");
    struct Object *stringObject4 = stringNewFromCString(gc, "fern");
    struct Object *integer1 = integerNew(gc, 2);

    mapPut(gc, map1, stringObject1, stringObject2);
    mapPut(gc, map1, stringObject3, stringObject4);
    mapPut(gc, map1, integer1, NULL);
    mapPut(gc, map1, NULL, integer1);

    struct Object *mapStringObject = stringNew(gc, mapStringCharacterCount(map1));

    uint32_t index = 0;

    mapWriteToString(map1, mapStringObject, &index);

    stringPrint(mapStringObject);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testMapToString()
{
    printf("testMapToString: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *map1 = mapNew(gc);

    struct Object *stringObject1 = stringNewFromCString(gc, "hier");
    struct Object *stringObject2 = stringNewFromCString(gc, "dort");
    struct Object *stringObject3 = stringNewFromCString(gc, "nah");
    struct Object *stringObject4 = stringNewFromCString(gc, "fern");
    struct Object *integer1 = integerNew(gc, 2);

    mapPut(gc, map1, stringObject1, stringObject2);
    mapPut(gc, map1, stringObject3, stringObject4);
    mapPut(gc, map1, integer1, NULL);
    mapPut(gc, map1, NULL, integer1);

    struct Object *mapStringObject1 = mapToString(gc, map1);
    struct String *mapString1 = mapStringObject1->value.subObject;

    assert(mapStringObject1->type == OBJECT_TYPE_STRING);
    assert(mapString1->characterCount == 34);

    stringPrint(mapStringObject1);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testMapMark()
{
    printf("testMapMark: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *map1 = mapNew(gc);

    struct Object *stringObject1 = stringNewFromCString(gc, "hier");
    struct Object *stringObject2 = stringNewFromCString(gc, "dort");
    struct Object *stringObject3 = stringNewFromCString(gc, "nah");
    struct Object *stringObject4 = stringNewFromCString(gc, "fern");
    struct Object *integer1 = integerNew(gc, 2);

    mapPut(gc, map1, stringObject1, stringObject2);
    mapPut(gc, map1, stringObject3, stringObject4);
    mapPut(gc, map1, integer1, NULL);
    mapPut(gc, map1, NULL, integer1);

    assert(map1->type == OBJECT_TYPE_MAP); // mark false
    assert(stringObject1->type == OBJECT_TYPE_STRING); // mark false
    assert(stringObject2->type == OBJECT_TYPE_STRING); // mark false
    assert(stringObject3->type == OBJECT_TYPE_STRING); // mark false
    assert(stringObject4->type == OBJECT_TYPE_STRING); // mark false
    assert(integer1->type == OBJECT_TYPE_INTEGER); // mark false

    objectMark(map1);

    assert(map1->type & OBJECT_MARK);
    assert(stringObject1->type & OBJECT_MARK);
    assert(stringObject2->type & OBJECT_MARK);
    assert(stringObject3->type & OBJECT_MARK);
    assert(stringObject4->type & OBJECT_MARK);
    assert(integer1->type & OBJECT_MARK);

    gcSweep(gc);
    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testMapFree()
{
    printf("testMapFree: ");
    struct Gc *gc = gcNew(1000, 0);
    struct Object *map = mapNew(gc);
    objectFree(gc, map);
    gcFree(gc);

    printf("OK\n");
}


void testPairNew()
{
    printf("testPairNew: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *integer1 = integerNew(gc, 1231);
    struct Object *pairObject = pairNew(gc, NULL, integer1);

    struct Pair *pair = (struct Pair *) pairObject->value.subObject;

    assert(pair->first == NULL);
    assert(pair->second == integer1);

    gcSweep(gc);
    gcFree(gc);

    printf("OK\n");
}

void testPairSetFirst()
{
    printf("testPairSetFirst: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *integer1 = integerNew(gc, 1231);
    struct Object *pair = pairNew(gc, NULL, integer1);

    assert(pairSetFirst(pair, integer1) == NULL);
    assert(pairGetFirst(pair) == integer1);

    assert(pairSetFirst(pair, NULL) == integer1);
    assert(pairGetFirst(pair) == NULL);

    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testPairSetSecond()
{
    printf("testPairSetSecond: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *integer1 = integerNew(gc, 1231);
    struct Object *pair = pairNew(gc, NULL, integer1);

    assert(pairSetSecond(pair, NULL) == integer1);
    assert(pairGetSecond(pair) == NULL);

    assert(pairSetSecond(pair, integer1) == NULL);
    assert(pairGetSecond(pair) == integer1);

    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testPairSwap()
{
    printf("testPairSwap: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *integer1 = integerNew(gc, 1231);
    struct Object *pair = pairNew(gc, NULL, integer1);

    pairSwap(pair);

    assert(pairGetFirst(pair) == integer1);
    assert(pairGetSecond(pair) == NULL);

    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testPairCopy()
{
    printf("testPairCopy: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *integer1 = integerNew(gc, 1231);
    struct Object *string1 = stringNewFromCString(gc, "1233123");
    struct Object *pair = pairNew(gc, string1, integer1);

    struct Object *copy = pairCopy(gc, pair);

    assert(copy != pair);
    assert(pairGetFirst(copy) != pairGetFirst(pair));
    assert(pairGetSecond(copy) != pairGetSecond(pair));

    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testPairEquals()
{
    printf("testPairEquals: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *integer1 = integerNew(gc, 1231);
    struct Object *string1 = stringNewFromCString(gc, "1233123");
    struct Object *pair = pairNew(gc, string1, integer1);

    struct Object *copy = pairCopy(gc, pair);

    assert(pairEquals(pair, pair) == BOOLEAN_TRUE);
    assert(pairEquals(copy, pair) == BOOLEAN_TRUE);

    pairSetFirst(pair, NULL);
    assert(pairEquals(copy, pair) == BOOLEAN_FALSE);

    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testPairHash()
{
    printf("testPairHash: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *integer1 = integerNew(gc, 1231);
    struct Object *string1 = stringNewFromCString(gc, "1233123");
    struct Object *pair = pairNew(gc, string1, integer1);

    struct Object *copy = pairCopy(gc, pair);

    assert(pairHash(pair) == pairHash(pair));
    assert(pairHash(copy) == pairHash(pair));

    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testPairStringCharacterCount()
{
    printf("testPairStringCharacterCount: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *integer1 = integerNew(gc, 1231);
    struct Object *string1 = stringNewFromCString(gc, "1233123");
    struct Object *pair = pairNew(gc, string1, integer1);

    assert(pairStringCharacterCount(pair) == 14);

    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testPairWriteToString()
{
    printf("testPairWriteToString: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *integer1 = integerNew(gc, 1231);
    struct Object *string1 = stringNewFromCString(gc, "1233123");
    struct Object *pair = pairNew(gc, string1, integer1);

    uint32_t charCount = pairStringCharacterCount(pair);

    struct Object *stringObject = stringNew(gc, charCount);

    uint32_t index = 0;

    pairWriteToString(pair, stringObject, &index);

    struct String *string = stringObject->value.subObject;

    assert(string->characters[0] == '(');
    assert(string->characters[1] == '1');
    assert(string->characters[2] == '2');
    assert(string->characters[3] == '3');
    assert(string->characters[4] == '3');
    assert(string->characters[5] == '1');
    assert(string->characters[6] == '2');
    assert(string->characters[7] == '3');
    assert(string->characters[8] == ',');
    assert(string->characters[9] == '1');
    assert(string->characters[10] == '2');
    assert(string->characters[11] == '3');
    assert(string->characters[12] == '1');
    assert(string->characters[13] == ')');

    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testPairToString()
{
    printf("testPairToString: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *integer1 = integerNew(gc, 1231);
    struct Object *string1 = stringNewFromCString(gc, "1233123");
    struct Object *pair = pairNew(gc, string1, integer1);

    struct Object *pairStringObject = pairToString(gc, pair);
    
    struct String *pairString = pairStringObject->value.subObject;

    assert(pairStringObject->type == OBJECT_TYPE_STRING);
    assert(pairString->characterCount == 14);
    assert(pairString->characters[0] == '(');
    assert(pairString->characters[1] == '1');
    assert(pairString->characters[2] == '2');
    assert(pairString->characters[3] == '3');
    assert(pairString->characters[4] == '3');
    assert(pairString->characters[5] == '1');
    assert(pairString->characters[6] == '2');
    assert(pairString->characters[7] == '3');
    assert(pairString->characters[8] == ',');
    assert(pairString->characters[9] == '1');
    assert(pairString->characters[10] == '2');
    assert(pairString->characters[11] == '3');
    assert(pairString->characters[12] == '1');
    assert(pairString->characters[13] == ')');

    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testPairMark()
{
    printf("testPairMark: ");
    struct Gc *gc = gcNew(1000, 0);

    struct Object *integer1 = integerNew(gc, 1231);
    struct Object *string1 = stringNewFromCString(gc, "1233123");
    struct Object *pairObject = pairNew(gc, string1, integer1);

    objectMark(pairObject);

    assert(integer1->type & OBJECT_MARK);
    assert(string1->type & OBJECT_MARK);
    assert(pairObject->type & OBJECT_MARK);

    gcSweep(gc);

    gcSweep(gc);
    gcFree(gc);
    printf("OK\n");
}

void testObjectCopy()
{
    printf("testObjectCopy: ");
    struct Gc *gc = gcNew(10000, 0);

    struct Object *mapObject = getComplexObject(gc);

    uint32_t oldSize = gc->size;

    struct Object *copyMap = objectCopy(gc, mapObject);
    
    // if object is in container multiple times copy is called multiple times on said object 
    assert(gc->size >= oldSize * 2);

    assert(copyMap != mapObject);

    struct Object *williPair = mapGet(mapObject, stringNewFromCString(gc, "Willi"));
    struct Object *ottoPair = mapGet(mapObject, stringNewFromCString(gc, "Otto"));
    struct Object *lisaPair = mapGet(mapObject, stringNewFromCString(gc, "Lisa"));

    struct Object *williPairCopy = mapGet(copyMap, stringNewFromCString(gc, "Willi"));
    struct Object *ottoPairCopy = mapGet(copyMap, stringNewFromCString(gc, "Otto"));
    struct Object *lisaPairCopy = mapGet(copyMap, stringNewFromCString(gc, "Lisa"));

    assert(williPair != williPairCopy);
    assert(ottoPair != ottoPairCopy);
    assert(lisaPair != lisaPairCopy);

    struct Object *williPairMap = pairGetFirst(williPair);
    struct Object *williPairCopyMap = pairGetFirst(williPairCopy);
    
    struct Object *ottoPairMap = pairGetFirst(ottoPair);
    struct Object *ottoPairCopyMap = pairGetFirst(ottoPairCopy);

    struct Object *lisaPairMap = pairGetFirst(lisaPair);
    struct Object *lisaPairCopyMap = pairGetFirst(lisaPairCopy);

    assert(williPairMap != williPairCopyMap);
    assert(ottoPairMap != ottoPairCopyMap);
    assert(lisaPairMap != lisaPairCopyMap);

    assert(mapGet(williPairMap, stringNewFromCString(gc, "name")) 
        != mapGet(williPairCopyMap, stringNewFromCString(gc, "name")));
    
    assert(mapGet(ottoPairMap, stringNewFromCString(gc, "name"))  
        != mapGet(ottoPairCopyMap, stringNewFromCString(gc, "name")));
    
    assert(mapGet(lisaPairMap, stringNewFromCString(gc, "name"))  
        != mapGet(lisaPairCopyMap, stringNewFromCString(gc, "name")));

    assert(mapGet(williPairMap, stringNewFromCString(gc, "age")) 
        != mapGet(williPairCopyMap, stringNewFromCString(gc, "age")));
    
    assert(mapGet(ottoPairMap, stringNewFromCString(gc, "age"))  
        != mapGet(ottoPairCopyMap, stringNewFromCString(gc, "age")));
    
    assert(mapGet(lisaPairMap, stringNewFromCString(gc, "age"))  
        != mapGet(lisaPairCopyMap, stringNewFromCString(gc, "age")));

    assert(mapGet(williPairMap, stringNewFromCString(gc, "height")) 
        != mapGet(williPairCopyMap, stringNewFromCString(gc, "height")));
    
    assert(mapGet(ottoPairMap, stringNewFromCString(gc, "height"))  
        != mapGet(ottoPairCopyMap, stringNewFromCString(gc, "height")));
    
    assert(mapGet(lisaPairMap, stringNewFromCString(gc, "height"))  
        != mapGet(lisaPairCopyMap, stringNewFromCString(gc, "height")));

    struct Object *williPairArray = pairGetSecond(williPair);
    struct Object *williPairArrayCopy = pairGetSecond(williPairCopy);
    struct Object *ottoPairArray = pairGetSecond(ottoPair);
    struct Object *ottoPairArrayCopy = pairGetSecond(ottoPairCopy);
    struct Object *lisaPairArray = pairGetSecond(lisaPair);
    struct Object *lisaPairArrayCopy = pairGetSecond(lisaPairCopy);

    assert(williPairArray != williPairArrayCopy);
    assert(ottoPairArray != ottoPairArrayCopy);
    assert(lisaPairArray != lisaPairArrayCopy);

    struct Object *williPairArrayMap0 = arrayGet(williPairArray, 0);
    struct Object *williPairArrayCopyMap0 = arrayGet(williPairArrayCopy, 0);
    struct Object *williPairArrayMap1 = arrayGet(williPairArray, 1);
    struct Object *williPairArrayCopyMap1 = arrayGet(williPairArrayCopy, 1);
    struct Object *ottoPairArrayMap0 = arrayGet(ottoPairArray, 0);
    struct Object *ottoPairArrayCopyMap0 = arrayGet(ottoPairArrayCopy, 0);

    assert(williPairArrayMap0 
        != williPairArrayCopyMap0);
    
    assert(williPairArrayMap1 
        != williPairArrayCopyMap1);

    assert(ottoPairArrayMap0
        != ottoPairArrayCopyMap0);

    assert(mapGet(williPairArrayMap0, stringNewFromCString(gc, "street")) 
        != mapGet(williPairArrayCopyMap0, stringNewFromCString(gc, "street")));

    assert(mapGet(williPairArrayMap0, stringNewFromCString(gc, "number")) 
        != mapGet(williPairArrayCopyMap0, stringNewFromCString(gc, "number")));
    
    assert(mapGet(williPairArrayMap1, stringNewFromCString(gc, "street")) 
        != mapGet(williPairArrayCopyMap1, stringNewFromCString(gc, "street")));

    assert(mapGet(williPairArrayMap1, stringNewFromCString(gc, "number")) 
        != mapGet(williPairArrayCopyMap1, stringNewFromCString(gc, "number")));

    assert(mapGet(ottoPairArrayMap0, stringNewFromCString(gc, "street")) 
        != mapGet(ottoPairArrayCopyMap0, stringNewFromCString(gc, "street")));

    assert(mapGet(ottoPairArrayMap0, stringNewFromCString(gc, "number")) 
        != mapGet(ottoPairArrayCopyMap0, stringNewFromCString(gc, "number")));

    gcSweep(gc);
    assert(gc->size == 0);
    gcFree(gc);
    printf("OK\n");
}

void testObjectEquals()
{
    printf("testObjectEquals: ");
    struct Gc *gc = gcNew(10000, 0);
    struct Object *object = getComplexObject(gc);
    
    struct Object *copyMap = objectCopy(gc, object);

    assert(objectEquals(object, copyMap) == BOOLEAN_TRUE);

    struct Object *ottoPairCopy = mapGet(copyMap, stringNewFromCString(gc, "Otto"));
    struct Object *ottoPairArrayCopy = pairGetSecond(ottoPairCopy);
    struct Object *ottoPairArrayCopyMap = arrayGet(ottoPairArrayCopy, 0);

    // copy changes address
    mapGet(ottoPairArrayCopyMap, stringNewFromCString(gc, "number"))->value.integerValue = 12;
    
    assert(objectEquals(object, copyMap) == BOOLEAN_FALSE);

    // copy changes address back
    mapPut(gc, ottoPairArrayCopyMap, stringNewFromCString(gc, "number"), integerNew(gc, 32));
    
    assert(objectEquals(object, copyMap) == BOOLEAN_TRUE);

    gcSweep(gc);
    assert(gc->size == 0);
    gcFree(gc);
    printf("OK\n");
}

void testObjectHash()
{
    printf("testObjectHash: ");
    struct Gc *gc = gcNew(10000, 0);
    struct Object *object = getComplexObject(gc);
    
    struct Object *copyMap = objectCopy(gc, object);

    assert(objectHash(object) == objectHash(copyMap));

    struct Object *ottoPairCopy = mapGet(copyMap, stringNewFromCString(gc, "Otto"));
    struct Object *ottoPairArrayCopy = pairGetSecond(ottoPairCopy);
    struct Object *ottoPairArrayCopyMap = arrayGet(ottoPairArrayCopy, 0);

    // copy changes address
    mapGet(ottoPairArrayCopyMap, stringNewFromCString(gc, "number"))->value.integerValue = 12;
    
    // copy changes address back
    mapPut(gc, ottoPairArrayCopyMap, stringNewFromCString(gc, "number"), integerNew(gc, 32));
    
    assert(objectHash(object) == objectHash(copyMap));

    gcSweep(gc);
    assert(gc->size == 0);
    gcFree(gc);
    printf("OK\n");
}

void testObjectStringCharacterCount()
{
    printf("testObjectStringCharacterCount: ");
    struct Gc *gc = gcNew(10000, 0);
    struct Object *object = NULL;
    
    assert(objectStringCharacterCount(object) == 4);

    struct Object *stringObject1 = stringNewFromCString(gc, "11");

    assert(objectStringCharacterCount(stringObject1) == 2);

    struct Object *stringObject2 = stringNewFromCString(gc, "");

    assert(objectStringCharacterCount(stringObject2) == 0);

    struct Object *complexObject = getComplexObject(gc);

    assert(objectStringCharacterCount(complexObject) > 50);

    gcSweep(gc);
    assert(gc->size == 0);
    gcFree(gc);
    printf("OK\n");
}

void testObjectWriteToString()
{
    printf("testObjectWriteToString: ");
    struct Gc *gc = gcNew(10000, 0);
    struct Object *object = NULL;
    struct Object *stringObject1 = stringNewFromCString(gc, "21");

    struct Object *stringObject3 = stringNew(gc, 4);
    struct Object *stringObject4 = stringNew(gc, 2);

    struct String *string1 = stringObject3->value.subObject;
    struct String *string2 = stringObject4->value.subObject;
    
    uint32_t index = 0;

    objectWriteToString(object, stringObject3, &index);

    assert(string1->characters[0] = 'n');
    assert(string1->characters[1] = 'u');
    assert(string1->characters[2] = 'l');
    assert(string1->characters[3] = 'l');

    index = 0;

    objectWriteToString(stringObject1, stringObject4, &index);

    assert(string2->characters[0] = '2');
    assert(string2->characters[1] = '1');

    gcSweep(gc);
    assert(gc->size == 0);
    gcFree(gc);
    printf("OK\n");
}

void testObjectToString()
{
    printf("testObjectToString: ");
    struct Gc *gc = gcNew(10000, 0);
    struct Object *object = getComplexObject(gc);
    
    struct Object *stringObject = objectToString(gc, object);

    stringPrint(stringObject);

    gcSweep(gc);
    assert(gc->size == 0);
    gcFree(gc);
    printf("OK\n");
}

void testObjectMark()
{
    printf("testObjectMark: ");
    struct Gc *gc = gcNew(10000, 0);
    struct Object *object = getComplexObject(gc);

    uint32_t oldSize = gc->size;

    objectMark(object);

    gcSweep(gc);

    assert(gc->size == oldSize);

    gcSweep(gc);
    assert(gc->size == 0);
    gcFree(gc);

    printf("OK\n");
}

void testObjectFree()
{
    printf("testObjectFree: ");
    struct Gc *gc = gcNew(10000, 0);
    getComplexObject(gc);

    gcSweep(gc);

    gcFree(gc);

    printf("OK\n");
}

int main(int argc, char* argv[])
{
    testGcNew();
    testGcObjectNew();
    testGcObjectNewMemoryFull1();
    testGcObjectNewMemoryFull2();
    testGcMemoryMalloc();
    testGcMemoryRealloc();
    testGcMemoryFree();
    testGcShouldMarkAndSweep();
    testGcSweep();
    testGcFree();
    testGcDebug();
    testDoubleNew();
    testDoubleStringCharacterCount();
    testDoubleWriteToString();
    testDoubleToString();
    testIntegerNew();
    testIntegerStringCharacterCount();
    testIntegerWriteToString();
    testIntegerToString();
    testStringNew();
    testStringFromArray();
    testStringToArray();
    testStringCompare();
    testStringConcatenate();
    testStringSubstring();
    testStringIndexOf();
    testStringReplace();
    testStringSplit();
    testStringCopy();
    testStringEquals();
    testStringHash();
    testArrayNew();
    testArraySet();
    testArrayInsert();
    testArrayInsertAll();
    testArrayRemove();
    testArraySwap();
    testArrayCopy();
    testArrayEquals();
    testArrayHash();
    testArrayStringCharacterCount();
    testArrayWriteToString();
    testArrayToString();
    testArrayMark();
    testArrayFree();
    testMapNew();
    testMapGet();
    testMapPut();
    //testMapPutMany();
    testMapPutAll();
    testMapRemove();
    testMapHasKey();
    testMapEntries();
    testMapKeys();
    testMapValues();
    testMapSwap();
    testMapCopy();
    testMapEquals();
    testMapHash();
    testMapStringCharacterCount();
    testMapWriteToString();
    testMapToString();
    testMapMark();
    testMapFree();
    testPairNew();
    testPairSetFirst();
    testPairSetSecond();
    testPairSwap();
    testPairCopy();
    testPairEquals();
    testPairHash();
    testPairStringCharacterCount();
    testPairWriteToString();
    testPairToString();
    testPairMark();
    testObjectCopy();
    testObjectEquals();
    testObjectHash();
    testObjectStringCharacterCount();
    testObjectWriteToString();
    testObjectToString();
    testObjectMark();
    testObjectFree();
    printf("All tests passed.\n");

    return 0;
}