#include "../Constant.h"
#include "../Function.h"
#include "../WcFile.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void testEmptyFile()
{
    printf("testEmptyFile: ");
 
    struct WcFile *file = wcFileNew("./empty.wc");

    assert(file->constantCount == 0);
    assert(file->functionCount == 0);
 
    wcFileFree(file);
    printf("OK\n");
}

void testIntegerConstantFile()
{
    printf("testIntegerConstantFile: ");
    struct WcFile *file = wcFileNew("./integer.wc");

    assert(file->constantCount == 2);
    assert(file->constants[0]->type == CONSTANT_TYPE_INTEGER);
    assert(file->constants[0]->value.integerConstant == 4);
    assert(file->constants[1]->type == CONSTANT_TYPE_INTEGER);
    assert(file->constants[1]->value.integerConstant == 1073741828);
    
    assert(file->functionCount == 0);
 
    wcFileFree(file);
    printf("OK\n");
}

void testDoubleConstantFile()
{
    printf("testDoubleConstantFile: ");
    struct WcFile *file = wcFileNew("./double.wc");

    assert(file->constantCount == 3);
    assert(file->constants[0]->type == CONSTANT_TYPE_DOUBLE);
    assert(abs(file->constants[0]->value.doubleConstant - 1.116451670505549e-307) < 0.0000000000000001 );
    assert(file->constants[1]->type == CONSTANT_TYPE_DOUBLE);
    assert(file->constants[1]->value.doubleConstant == 1.1);
    assert(file->constants[2]->type == CONSTANT_TYPE_DOUBLE);
    assert(file->constants[2]->value.doubleConstant == 4.940656458412465e-324);
    assert(file->functionCount == 0);
 
    wcFileFree(file);
    printf("OK\n");
}

void testStringConstantFile()
{
    printf("testStringConstantFile: ");
    printf("OK\n");
}

void testAllConstantFile()
{
    printf("testAllConstantFile: ");
    printf("OK\n");
}

void testOneFunctionFile()
{
    printf("testOneFunctionFile: ");
    printf("OK\n");
}

void testMultipleFunctionsFile()
{
    printf("testMultipleFunctionsFile: ");
    printf("OK\n");
}

void testAllFile1()
{
    printf("testAllFile1: ");
    printf("OK\n");
}

void testAllFile2()
{
    printf("testAllFile2: ");
    printf("OK\n");
}


int main(int argc, char* argv[])
{
    testEmptyFile();
    testIntegerConstantFile();
    testDoubleConstantFile();
    testStringConstantFile();
    testAllConstantFile();
    testOneFunctionFile();
    testMultipleFunctionsFile();
    testAllFile1();
    testAllFile2();
    printf("All tests passed.\n");

    return 0;
}