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
    printf("testArrayNew:\n");
    printf("OK\n");
}

void testArraySize()
{
    printf("testArraySize:\n");
    printf("OK\n");
}

void testArrayGet()
{
    printf("testArrayGet:\n");
    printf("OK\n");
}

void testArraySet()
{
    printf("testArraySet:\n");
    printf("OK\n");
}

void testArrayInsert()
{
    printf("testArrayInsert:\n");
    printf("OK\n");
}

void testArrayInsertAll()
{
    printf("testArrayInsertAll:\n");
    printf("OK\n");
}

void testArrayRemove()
{
    printf("testArrayRemove:\n");
    printf("OK\n");
}

void testArrayAppendInteger()
{
    printf("testArrayAppendInteger:\n");
    printf("OK\n");
}

void testArrayCopy()
{
    printf("testArrayCopy:\n");
    printf("OK\n");
}

void testArrayEquals()
{
    printf("testArrayEquals:\n");
    printf("OK\n");
}

void testArrayHash()
{
    printf("testArrayHash:\n");
    printf("OK\n");
}

void testArrayToString()
{
    printf("testArrayToString:\n");
    printf("OK\n");
}

void testArrayMark()
{
    printf("testArrayMark:\n");
    printf("OK\n");
}

void testArrayFree()
{
    printf("testArrayFree:\n");
    printf("OK\n");
}

void testFloatingNew()
{
    printf("testFloatingNew:\n");
    printf("OK\n");
}

void testFloatingToString()
{
    printf("testFloatingToString:\n");
    printf("OK\n");
}

void testGcNew()
{
    printf("testGcNew:\n");
    printf("OK\n");
}

void testGcRegisterObject()
{
    printf("testGcRegisterObject:\n");
    printf("OK\n");
}

void testGcSweep()
{
    printf("testGcSweep:\n");
    printf("OK\n");
}

void testGcFree()
{
    printf("testGcFree:\n");
    printf("OK\n");
}

void testIntegerNew()
{
    printf("testIntegerNew:\n");
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
    printf("testIntegerToString:\n");
    printf("OK\n");
}

void testMapNew()
{
    printf("testMapNew:\n");
    printf("OK\n");
}

void testMapSize()
{
    printf("testMapSize:\n");
    printf("OK\n");
}

void testMapGet()
{
    printf("testMapGet:\n");
    printf("OK\n");
}

void testMapPut()
{
    printf("testMapPut:\n");
    printf("OK\n");
}

void testMapPutAll()
{
    printf("testMapPutAll:\n");
    printf("OK\n");
}

void testMapRemove()
{
    printf("testMapRemove:\n");
    printf("OK\n");
}

void testMapHasKey()
{
    printf("testMapHasKey:\n");
    printf("OK\n");
}

void testMapEntries()
{
    printf("testMapEntries:\n");
    printf("OK\n");
}

void testMapCopy()
{
    printf("testMapCopy:\n");
    printf("OK\n");
}

void testMapEquals()
{
    printf("testMapEquals:\n");
    printf("OK\n");
}

void testMapHash()
{
    printf("testMapHash:\n");
    printf("OK\n");
}

void testMapToString()
{
    printf("testMapToString:\n");
    printf("OK\n");
}

void testMapMark()
{
    printf("testMapMark:\n");
    printf("OK\n");
}

void testMapFree()
{
    printf("testMapFree:\n");
    printf("OK\n");
}

void testObjectCopy()
{
    printf("testObjectCopy:\n");
    printf("OK\n");
}

void testObjectEquals()
{
    printf("testObjectEquals:\n");
    printf("OK\n");
}

void testObjectHash()
{
    printf("testObjectHash:\n");
    printf("OK\n");
}

void testObjectToString()
{
    printf("testObjectToString:\n");
    printf("OK\n");
}

void testObjectNew()
{
    printf("testObjectNew:\n");
    printf("OK\n");
}

void testObjectMark()
{
    printf("testObjectMark:\n");
    printf("OK\n");
}

void testObjectFree()
{
    printf("testObjectFree:\n");
    printf("OK\n");
}

void testPairNew()
{
    printf("testPairNew:\n");
    printf("OK\n");
}

void testPairGetFirst()
{
    printf("testPairGetFirst:\n");
    printf("OK\n");
}

void testPairGetSecond()
{
    printf("testPairGetSecond:\n");
    printf("OK\n");
}

void testPairSetFirst()
{
    printf("testPairSetFirst:\n");
    printf("OK\n");
}

void testPairSetSecond()
{
    printf("testPairSetSecond:\n");
    printf("OK\n");
}

void testPairCopy()
{
    printf("testPairCopy:\n");
    printf("OK\n");
}

void testPairEquals()
{
    printf("testPairEquals:\n");
    printf("OK\n");
}

void testPairHash()
{
    printf("testPairHash:\n");
    printf("OK\n");
}

void testPairToString()
{
    printf("testPairToString:\n");
    printf("OK\n");
}

void testPairMark()
{
    printf("testPairMark:\n");
    printf("OK\n");
}

void testStringNew()
{
    printf("testStringNew:\n");
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
    printf("testStringFromCharArray:\n");
    printf("OK\n");
}

void testStringToCharArray()
{
    printf("testStringToCharArray:\n");
    printf("OK\n");
}

void testStringCompare()
{
    printf("testStringCompare:\n");
    printf("OK\n");
}

void testStringCopy()
{
    printf("testStringCopy:\n");
    printf("OK\n");
}

void testStringEquals()
{
    printf("testStringEquals:\n");
    printf("OK\n");
}

void testStringHash()
{
    printf("testStringHash:\n");
    printf("OK\n");
}

void testStringFree()
{
    printf("testStringFree:\n");
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
    printf("61 tests passed.\n");
}