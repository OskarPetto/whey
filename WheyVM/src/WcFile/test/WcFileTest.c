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
    struct WcFile *file = wcFileNew("./string.wc");

    assert(file->constantCount == 3);
    assert(file->constants[0]->type == CONSTANT_TYPE_STRING);
    assert(file->constants[0]->value.stringConstant->characterCount == 10);
    assert(file->constants[0]->value.stringConstant->characters[0] == 'E');
    assert(file->constants[0]->value.stringConstant->characters[1] == 'n');
    assert(file->constants[0]->value.stringConstant->characters[2] == 'd');
    assert(file->constants[0]->value.stringConstant->characters[3] == 'i');
    assert(file->constants[0]->value.stringConstant->characters[4] == 'a');
    assert(file->constants[0]->value.stringConstant->characters[5] == 'n');
    assert(file->constants[0]->value.stringConstant->characters[6] == 'n');
    assert(file->constants[0]->value.stringConstant->characters[7] == 'e');
    assert(file->constants[0]->value.stringConstant->characters[8] == 's');
    assert(file->constants[0]->value.stringConstant->characters[9] == 's');

    assert(file->constants[1]->type == CONSTANT_TYPE_STRING);
    assert(file->constants[1]->value.stringConstant->characterCount == 1);
    assert(file->constants[1]->value.stringConstant->characters[0] == '<');
    assert(file->constants[2]->type == CONSTANT_TYPE_STRING);
    assert(file->constants[2]->value.stringConstant->characterCount == 0);
    assert(file->functionCount == 0);
 
    wcFileFree(file);
    printf("OK\n");
}

void testAllConstantFile()
{
    printf("testAllConstantFile: ");
    struct WcFile *file = wcFileNew("./allconstants.wc");

    assert(file->constantCount == 5);
    assert(file->constants[0]->type == CONSTANT_TYPE_DOUBLE);
    assert(file->constants[1]->type == CONSTANT_TYPE_STRING);
    assert(file->constants[2]->type == CONSTANT_TYPE_STRING);
    assert(file->constants[3]->type == CONSTANT_TYPE_INTEGER);
    assert(file->constants[4]->type == CONSTANT_TYPE_DOUBLE);
    
    assert(file->constants[0]->value.doubleConstant == 1.1);
    assert(file->constants[1]->value.stringConstant->characterCount == 8);
    assert(file->constants[1]->value.stringConstant->characters[0] == 'B');
    assert(file->constants[1]->value.stringConstant->characters[1] == 'A');
    assert(file->constants[1]->value.stringConstant->characters[2] == 'D');
    assert(file->constants[1]->value.stringConstant->characters[3] == 'E');
    assert(file->constants[1]->value.stringConstant->characters[4] == 'A');
    assert(file->constants[1]->value.stringConstant->characters[5] == 'F');
    assert(file->constants[1]->value.stringConstant->characters[6] == 'F');
    assert(file->constants[1]->value.stringConstant->characters[7] == 'E');

    assert(file->constants[2]->value.stringConstant->characterCount == 16);
    assert(file->constants[2]->value.stringConstant->characters[0] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[1] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[2] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[3] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[4] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[5] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[6] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[7] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[8] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[9] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[10] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[11] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[12] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[13] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[14] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[15] == 'w');

    assert(file->constants[3]->type == CONSTANT_TYPE_INTEGER);
    assert(file->constants[3]->value.integerConstant == 1073741828);
 
    assert(file->constants[4]->type == CONSTANT_TYPE_DOUBLE);
    assert(file->constants[4]->value.doubleConstant == 1.0);

    wcFileFree(file);
    printf("OK\n");
}

void testOneFunctionFile()
{
    printf("testOneFunctionFile: ");
    struct WcFile *file = wcFileNew("./onefunction.wc");

    assert(file->constantCount == 0);
    assert(file->functionCount == 1);

    assert(file->functions[0]->argumentCount == 1);
    assert(file->functions[0]->byteCount == 10);
    assert(file->functions[0]->bytes[0] == 1);
    assert(file->functions[0]->bytes[1] == 2);
    assert(file->functions[0]->bytes[2] == 3);
    assert(file->functions[0]->bytes[3] == 4);
    assert(file->functions[0]->bytes[4] == 5);
    assert(file->functions[0]->bytes[5] == 6);
    assert(file->functions[0]->bytes[6] == 7);
    assert(file->functions[0]->bytes[7] == 8);
    assert(file->functions[0]->bytes[8] == 9);
    assert(file->functions[0]->bytes[9] == 10);
    
    wcFileFree(file);
    printf("OK\n");
}

void testMultipleFunctionsFile()
{
    printf("testMultipleFunctionsFile: ");
    struct WcFile *file = wcFileNew("./multiplefunctions.wc");

    assert(file->constantCount == 0);
    assert(file->functionCount == 3);

    assert(file->functions[0]->argumentCount == 1);
    assert(file->functions[0]->byteCount == 10);
    assert(file->functions[0]->bytes[0] == 1);
    assert(file->functions[0]->bytes[1] == 2);
    assert(file->functions[0]->bytes[2] == 3);
    assert(file->functions[0]->bytes[3] == 4);
    assert(file->functions[0]->bytes[4] == 5);
    assert(file->functions[0]->bytes[5] == 6);
    assert(file->functions[0]->bytes[6] == 7);
    assert(file->functions[0]->bytes[7] == 8);
    assert(file->functions[0]->bytes[8] == 9);
    assert(file->functions[0]->bytes[9] == 10);

    assert(file->functions[1]->argumentCount == 0);
    assert(file->functions[1]->byteCount == 0);

    assert(file->functions[2]->argumentCount == 5);
    assert(file->functions[2]->byteCount == 1);
    assert(file->functions[2]->bytes[0] == 1);
    
    wcFileFree(file);
    printf("OK\n");
}

void testCompleteFile()
{
    printf("testCompleteFile: ");
    struct WcFile *file = wcFileNew("./completefile.wc");

    assert(file->constantCount == 5);
    assert(file->constants[0]->type == CONSTANT_TYPE_DOUBLE);
    assert(file->constants[1]->type == CONSTANT_TYPE_STRING);
    assert(file->constants[2]->type == CONSTANT_TYPE_STRING);
    assert(file->constants[3]->type == CONSTANT_TYPE_INTEGER);
    assert(file->constants[4]->type == CONSTANT_TYPE_DOUBLE);
    
    assert(file->constants[0]->value.doubleConstant == 1.1);
    assert(file->constants[1]->value.stringConstant->characterCount == 8);
    assert(file->constants[1]->value.stringConstant->characters[0] == 'B');
    assert(file->constants[1]->value.stringConstant->characters[1] == 'A');
    assert(file->constants[1]->value.stringConstant->characters[2] == 'D');
    assert(file->constants[1]->value.stringConstant->characters[3] == 'E');
    assert(file->constants[1]->value.stringConstant->characters[4] == 'A');
    assert(file->constants[1]->value.stringConstant->characters[5] == 'F');
    assert(file->constants[1]->value.stringConstant->characters[6] == 'F');
    assert(file->constants[1]->value.stringConstant->characters[7] == 'E');

    assert(file->constants[2]->value.stringConstant->characterCount == 16);
    assert(file->constants[2]->value.stringConstant->characters[0] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[1] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[2] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[3] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[4] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[5] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[6] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[7] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[8] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[9] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[10] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[11] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[12] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[13] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[14] == 'w');
    assert(file->constants[2]->value.stringConstant->characters[15] == 'w');

    assert(file->constants[3]->type == CONSTANT_TYPE_INTEGER);
    assert(file->constants[3]->value.integerConstant == 1073741828);
 
    assert(file->constants[4]->type == CONSTANT_TYPE_DOUBLE);
    assert(file->constants[4]->value.doubleConstant == 1.0);

    assert(file->functionCount == 3);

    assert(file->functions[0]->argumentCount == 1);
    assert(file->functions[0]->byteCount == 10);
    assert(file->functions[0]->bytes[0] == 1);
    assert(file->functions[0]->bytes[1] == 2);
    assert(file->functions[0]->bytes[2] == 3);
    assert(file->functions[0]->bytes[3] == 4);
    assert(file->functions[0]->bytes[4] == 5);
    assert(file->functions[0]->bytes[5] == 6);
    assert(file->functions[0]->bytes[6] == 7);
    assert(file->functions[0]->bytes[7] == 8);
    assert(file->functions[0]->bytes[8] == 9);
    assert(file->functions[0]->bytes[9] == 10);

    assert(file->functions[1]->argumentCount == 0);
    assert(file->functions[1]->byteCount == 0);

    assert(file->functions[2]->argumentCount == 5);
    assert(file->functions[2]->byteCount == 1);
    assert(file->functions[2]->bytes[0] == 1);
    
    wcFileFree(file);
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
    testCompleteFile();
    printf("All tests passed.\n");

    return 0;
}