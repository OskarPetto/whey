#include "../Constant.h"
#include "../Method.h"
#include "../Class.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void testEmptyFile()
{
    printf("testEmptyFile: ");
 
    struct Class *file = classNew("./empty.wc", 1);

    assert(file->constantTable->constantCount == 0);
    assert(file->methodTable->methodCount == 0);
 
    classFree(file);
    printf("OK\n");
}

void testIntegerConstantFile()
{
    printf("testIntegerConstantFile: ");
    struct Class *file = classNew("./integer.wc", 1);

    struct ConstantTable *table = file->constantTable; 

    assert(table->constantCount == 2);
    assert(table->constants[0].type == CONSTANT_TYPE_INTEGER);
    assert(table->constants[0].value.integerConstant == 4);
    assert(table->constants[1].type == CONSTANT_TYPE_INTEGER);
    assert(table->constants[1].value.integerConstant == 1073741828);
    
    assert(file->methodTable->methodCount == 0);
 
    classFree(file);
    printf("OK\n");
}

void testDoubleConstantFile()
{
    printf("testDoubleConstantFile: ");
    struct Class *file = classNew("./double.wc", 1);

    struct ConstantTable *table = file->constantTable; 

    assert(table->constantCount == 3);
    assert(table->constants[0].type == CONSTANT_TYPE_DOUBLE);
    assert(abs(table->constants[0].value.doubleConstant - 1.116451670505549e-307) < 0.0000000000000001 );
    assert(table->constants[1].type == CONSTANT_TYPE_DOUBLE);
    assert(table->constants[1].value.doubleConstant == 1.1);
    assert(table->constants[2].type == CONSTANT_TYPE_DOUBLE);
    assert(table->constants[2].value.doubleConstant == 4.940656458412465e-324);
    
    assert(file->methodTable->methodCount == 0);
 
    classFree(file);
    printf("OK\n");
}

void testStringConstantFile()
{
    printf("testStringConstantFile: ");
    struct Class *file = classNew("./string.wc", 1);

    struct ConstantTable *table = file->constantTable; 

    assert(table->constantCount == 3);
    assert(table->constants[0].type == CONSTANT_TYPE_STRING);
    assert(table->constants[0].value.stringConstant->characterCount == 10);

    assert(table->constants[0].value.stringConstant->characters[0] == 'E');
    assert(table->constants[0].value.stringConstant->characters[1] == 'n');
    assert(table->constants[0].value.stringConstant->characters[2] == 'd');
    assert(table->constants[0].value.stringConstant->characters[3] == 'i');
    assert(table->constants[0].value.stringConstant->characters[4] == 'a');
    assert(table->constants[0].value.stringConstant->characters[5] == 'n');
    assert(table->constants[0].value.stringConstant->characters[6] == 'n');
    assert(table->constants[0].value.stringConstant->characters[7] == 'e');
    assert(table->constants[0].value.stringConstant->characters[8] == 's');
    assert(table->constants[0].value.stringConstant->characters[9] == 's');

    assert(table->constants[1].type == CONSTANT_TYPE_STRING);
    assert(table->constants[1].value.stringConstant->characterCount == 1);
    assert(table->constants[1].value.stringConstant->characters[0] == '<');
    assert(table->constants[2].type == CONSTANT_TYPE_STRING);
    assert(table->constants[2].value.stringConstant->characterCount == 0);
    
    assert(file->methodTable->methodCount == 0);
 
    classFree(file);
    printf("OK\n");
}

void testAllConstantFile()
{
    printf("testAllConstantFile: ");
    struct Class *file = classNew("./allconstants.wc", 1);

    struct ConstantTable *table = file->constantTable; 

    assert(table->constantCount == 5);
    assert(table->constants[0].type == CONSTANT_TYPE_DOUBLE);
    assert(table->constants[1].type == CONSTANT_TYPE_STRING);
    assert(table->constants[2].type == CONSTANT_TYPE_STRING);
    assert(table->constants[3].type == CONSTANT_TYPE_INTEGER);
    assert(table->constants[4].type == CONSTANT_TYPE_DOUBLE);
    
    assert(table->constants[0].value.doubleConstant == 1.1);
    assert(table->constants[1].value.stringConstant->characterCount == 8);
    assert(table->constants[1].value.stringConstant->characters[0] == 'B');
    assert(table->constants[1].value.stringConstant->characters[1] == 'A');
    assert(table->constants[1].value.stringConstant->characters[2] == 'D');
    assert(table->constants[1].value.stringConstant->characters[3] == 'E');
    assert(table->constants[1].value.stringConstant->characters[4] == 'A');
    assert(table->constants[1].value.stringConstant->characters[5] == 'F');
    assert(table->constants[1].value.stringConstant->characters[6] == 'F');
    assert(table->constants[1].value.stringConstant->characters[7] == 'E');

    assert(table->constants[2].value.stringConstant->characterCount == 16);
    assert(table->constants[2].value.stringConstant->characters[0] == 'w');
    assert(table->constants[2].value.stringConstant->characters[1] == 'w');
    assert(table->constants[2].value.stringConstant->characters[2] == 'w');
    assert(table->constants[2].value.stringConstant->characters[3] == 'w');
    assert(table->constants[2].value.stringConstant->characters[4] == 'w');
    assert(table->constants[2].value.stringConstant->characters[5] == 'w');
    assert(table->constants[2].value.stringConstant->characters[6] == 'w');
    assert(table->constants[2].value.stringConstant->characters[7] == 'w');
    assert(table->constants[2].value.stringConstant->characters[8] == 'w');
    assert(table->constants[2].value.stringConstant->characters[9] == 'w');
    assert(table->constants[2].value.stringConstant->characters[10] == 'w');
    assert(table->constants[2].value.stringConstant->characters[11] == 'w');
    assert(table->constants[2].value.stringConstant->characters[12] == 'w');
    assert(table->constants[2].value.stringConstant->characters[13] == 'w');
    assert(table->constants[2].value.stringConstant->characters[14] == 'w');
    assert(table->constants[2].value.stringConstant->characters[15] == 'w');

    assert(table->constants[3].type == CONSTANT_TYPE_INTEGER);
    assert(table->constants[3].value.integerConstant == 1073741828);
 
    assert(table->constants[4].type == CONSTANT_TYPE_DOUBLE);
    assert(table->constants[4].value.doubleConstant == 1.0);

    classFree(file);
    printf("OK\n");
}

void testOneMethodFile()
{
    printf("testOneMethodFile: ");
    struct Class *file = classNew("./onemethod.wc", 1);

    assert(file->constantTable->constantCount == 2);

    struct MethodTable *table = file->methodTable;

    assert(table->methodCount == 1);

    assert(table->methods[0].nameIndex == 257);
    assert(table->methods[0].argumentCount == 1);
    assert(table->methods[0].returnsSomething == 1);
    assert(table->methods[0].localsCount == 2);
    assert(table->methods[0].maxOperandCount == 3);

    assert(table->methods[0].codeSize == 10);

    assert(table->methods[0].byteCode[0] == 1);
    assert(table->methods[0].byteCode[1] == 2);
    assert(table->methods[0].byteCode[2] == 3);
    assert(table->methods[0].byteCode[3] == 4);
    assert(table->methods[0].byteCode[4] == 5);
    assert(table->methods[0].byteCode[5] == 6);
    assert(table->methods[0].byteCode[6] == 7);
    assert(table->methods[0].byteCode[7] == 8);

    assert(table->methods[0].byteCode[8] == 9);

    assert(table->methods[0].byteCode[9] == 10);
    
    classFree(file);
    printf("OK\n");
}

void testMultipleMethodsFile()
{
    printf("testMultipleMethodsFile: ");
    struct Class *file = classNew("./multiplemethods.wc", 1);

    struct MethodTable *table = file->methodTable;

    assert(file->constantTable->constantCount == 0);

    assert(table->methodCount == 3);

    assert(table->methods[0].nameIndex == 0);
    assert(table->methods[0].argumentCount == 2);
    assert(table->methods[0].returnsSomething == 0);
    assert(table->methods[0].localsCount == 4);
    assert(table->methods[0].maxOperandCount == 5);

    assert(table->methods[0].codeSize == 10);
    assert(table->methods[0].byteCode[0] == 1);
    assert(table->methods[0].byteCode[1] == 2);
    assert(table->methods[0].byteCode[2] == 3);
    assert(table->methods[0].byteCode[3] == 4);
    assert(table->methods[0].byteCode[4] == 5);
    assert(table->methods[0].byteCode[5] == 6);
    assert(table->methods[0].byteCode[6] == 7);
    assert(table->methods[0].byteCode[7] == 8);
    assert(table->methods[0].byteCode[8] == 9);
    assert(table->methods[0].byteCode[9] == 10);

    assert(table->methods[1].nameIndex == 2);
    assert(table->methods[1].argumentCount == 0);
    assert(table->methods[1].returnsSomething == 0);
    assert(table->methods[1].localsCount == 10);
    assert(table->methods[1].maxOperandCount == 1);

    assert(table->methods[1].codeSize == 0);

    assert(table->methods[2].nameIndex == 3);
    assert(table->methods[2].argumentCount == 0);
    assert(table->methods[2].returnsSomething == 1);
    assert(table->methods[2].localsCount == 0);
    assert(table->methods[2].maxOperandCount == 1);

    assert(table->methods[2].codeSize == 1);
    assert(table->methods[2].byteCode[0] == 1);
    
    classFree(file);
    printf("OK\n");
}

void testCompleteFile()
{
    printf("testCompleteFile: ");
    struct Class *file = classNew("./completefile.wc", 1);

    struct ConstantTable *constantTable = file->constantTable;
    struct MethodTable *methodTable = file->methodTable;


    assert(constantTable->constantCount == 5);
    assert(constantTable->constants[0].type == CONSTANT_TYPE_DOUBLE);
    assert(constantTable->constants[1].type == CONSTANT_TYPE_STRING);
    assert(constantTable->constants[2].type == CONSTANT_TYPE_STRING);
    assert(constantTable->constants[3].type == CONSTANT_TYPE_INTEGER);
    assert(constantTable->constants[4].type == CONSTANT_TYPE_DOUBLE);
    
    assert(constantTable->constants[0].value.doubleConstant == 1.1);
    assert(constantTable->constants[1].value.stringConstant->characterCount == 8);
    assert(constantTable->constants[1].value.stringConstant->characters[0] == 'B');
    assert(constantTable->constants[1].value.stringConstant->characters[1] == 'A');
    assert(constantTable->constants[1].value.stringConstant->characters[2] == 'D');
    assert(constantTable->constants[1].value.stringConstant->characters[3] == 'E');
    assert(constantTable->constants[1].value.stringConstant->characters[4] == 'A');
    assert(constantTable->constants[1].value.stringConstant->characters[5] == 'F');
    assert(constantTable->constants[1].value.stringConstant->characters[6] == 'F');
    assert(constantTable->constants[1].value.stringConstant->characters[7] == 'E');

    assert(constantTable->constants[2].value.stringConstant->characterCount == 16);
    assert(constantTable->constants[2].value.stringConstant->characters[0] == 'w');
    assert(constantTable->constants[2].value.stringConstant->characters[1] == 'w');
    assert(constantTable->constants[2].value.stringConstant->characters[2] == 'w');
    assert(constantTable->constants[2].value.stringConstant->characters[3] == 'w');
    assert(constantTable->constants[2].value.stringConstant->characters[4] == 'w');
    assert(constantTable->constants[2].value.stringConstant->characters[5] == 'w');
    assert(constantTable->constants[2].value.stringConstant->characters[6] == 'w');
    assert(constantTable->constants[2].value.stringConstant->characters[7] == 'w');
    assert(constantTable->constants[2].value.stringConstant->characters[8] == 'w');
    assert(constantTable->constants[2].value.stringConstant->characters[9] == 'w');
    assert(constantTable->constants[2].value.stringConstant->characters[10] == 'w');
    assert(constantTable->constants[2].value.stringConstant->characters[11] == 'w');
    assert(constantTable->constants[2].value.stringConstant->characters[12] == 'w');
    assert(constantTable->constants[2].value.stringConstant->characters[13] == 'w');
    assert(constantTable->constants[2].value.stringConstant->characters[14] == 'w');
    assert(constantTable->constants[2].value.stringConstant->characters[15] == 'w');

    assert(constantTable->constants[3].type == CONSTANT_TYPE_INTEGER);
    assert(constantTable->constants[3].value.integerConstant == 1073741828);
 
    assert(constantTable->constants[4].type == CONSTANT_TYPE_DOUBLE);
    assert(constantTable->constants[4].value.doubleConstant == 1.0);

    assert(methodTable->methodCount == 3);

    assert(methodTable->methods[0].nameIndex == 0);
    assert(methodTable->methods[0].argumentCount == 1);
    assert(methodTable->methods[0].returnsSomething == 1);
    assert(methodTable->methods[0].localsCount == 2);
    assert(methodTable->methods[0].maxOperandCount == 3);

    assert(methodTable->methods[0].codeSize == 10);
    assert(methodTable->methods[0].byteCode[0] == 1);
    assert(methodTable->methods[0].byteCode[1] == 2);
    assert(methodTable->methods[0].byteCode[2] == 3);
    assert(methodTable->methods[0].byteCode[3] == 4);
    assert(methodTable->methods[0].byteCode[4] == 5);
    assert(methodTable->methods[0].byteCode[5] == 6);
    assert(methodTable->methods[0].byteCode[6] == 7);
    assert(methodTable->methods[0].byteCode[7] == 8);
    assert(methodTable->methods[0].byteCode[8] == 9);
    assert(methodTable->methods[0].byteCode[9] == 10);

    assert(methodTable->methods[1].nameIndex == 0);
    assert(methodTable->methods[1].argumentCount == 1);
    assert(methodTable->methods[1].returnsSomething == 1);
    assert(methodTable->methods[1].localsCount == 2);
    assert(methodTable->methods[1].maxOperandCount == 3);

    assert(methodTable->methods[1].codeSize == 0);

    assert(methodTable->methods[2].nameIndex == 0);
    assert(methodTable->methods[2].argumentCount == 2);
    assert(methodTable->methods[2].returnsSomething == 1);
    assert(methodTable->methods[2].localsCount == 5);
    assert(methodTable->methods[2].maxOperandCount == 3);

    assert(methodTable->methods[2].codeSize == 1);
    assert(methodTable->methods[2].byteCode[0] == 1);
    
    classFree(file);
    printf("OK\n");
}


int main(int argc, char* argv[])
{
    testEmptyFile();
    testIntegerConstantFile();
    testDoubleConstantFile();
    testStringConstantFile();
    testAllConstantFile();
    testOneMethodFile();
    testMultipleMethodsFile();
    testCompleteFile();
    printf("All tests passed.\n");

    return 0;
}