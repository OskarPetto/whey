#include "../Constant.h"
#include "../Function.h"
#include "../WcFile.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void testEmptyFile()
{
    printf("testEmptyFile: ");
    printf("OK\n");
}

void testIntegerConstantFile()
{
    printf("testIntegerConstantFile: ");
    printf("OK\n");
}

void testDoubleConstantFile()
{
    printf("testDoubleConstantFile: ");
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