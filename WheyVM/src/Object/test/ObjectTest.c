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


void testArrayNew()
{
    printf("testArrayNew: ");
    printf("OK\n");
}

void testArraySize()
{
    printf("testArraySize: ");
    printf("OK\n");
}

void testArrayGet()
{
    printf("testArrayGet: ");
    printf("OK\n");
}

void testArraySet()
{
    printf("testArraySet: ");
    printf("OK\n");
}

void testArrayInsert()
{
    printf("testArrayInsert: ");
    printf("OK\n");
}

void testArrayInsertAll()
{
    printf("testArrayInsertAll: ");
    printf("OK\n");
}

void testArrayRemove()
{
    printf("testArrayRemove: ");
    printf("OK\n");
}

void testArrayAppendInteger()
{
    printf("testArrayAppendInteger: ");
    printf("OK\n");
}

void testArrayCopy()
{
    printf("testArrayCopy: ");
    printf("OK\n");
}

void testArrayEquals()
{
    printf("testArrayEquals: ");
    printf("OK\n");
}

void testArrayHash()
{
    printf("testArrayHash: ");
    printf("OK\n");
}

void testArrayToString()
{
    printf("testArrayToString: ");
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
    assert(integer1 != NULL);
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

void testStringNew()
{
    printf("testStringNew: ");
    struct Object *string1 = stringNew(NULL, 10);
    assert(string1 != NULL);
    assert(string1->type == OBJECT_TYPE_STRING);
    assert(string1->mark == OBJECT_MARK_TRUE);
    assert(string1->value.string->characterCount == 10);
    string1->value.string->characters[0] = 'A';
    string1->value.string->characters[9] = 'B';
    free(string1->value.string->characters);
    free(string1->value.string);
    free(string1);
    printf("OK\n");
}

void testStringFromCharArray()
{
    printf("testStringFromCharArray: ");
    printf("OK\n");
}

void testStringToCharArray()
{
    printf("testStringToCharArray: ");
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

void testStringFree()
{
    printf("testStringFree: ");
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
    testArrayAppendInteger();
    testArrayCopy();
    testArrayEquals();
    testArrayHash();
    testArrayToString();
    testArrayMark();
    testArrayFree();
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
    testStringNew();
    testStringFromCharArray();
    testStringToCharArray();
    testStringCompare();
    testStringCopy();
    testStringEquals();
    testStringHash();
    testStringFree();
}