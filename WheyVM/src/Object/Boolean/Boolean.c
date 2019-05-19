#include "Boolean.h"

struct Object *booleanConst(struct Constant *constant)
{
    struct Object *boolean = integerNew(constant->value.integer_value);
    return boolean;
}

struct Object *booleanAnd(struct Object *boolean1, struct Object *boolean2)
{
    struct Object *result = integerNew(boolean1->value.integer_value && boolean2->value.integer_value);
    return result;
}

struct Object *booleanOr(struct Object *boolean1, struct Object *boolean2)
{
    struct Object *result = integerNew(boolean1->value.integer_value || boolean2->value.integer_value);
    return result;    
}

struct Object *booleanNot(struct Object *boolean)
{
    struct Object *result = integerNew(!boolean->value.integer_value);
    return result;
}

struct Object *booleanXor(struct Object *boolean1, struct Object *boolean2)
{
    struct Object *result = integerNew(boolean1->value.integer_value != boolean2->value.integer_value);
    return result;    
}

struct Object *booleanNew(Integer value)
{
    struct Object *boolean = objectNew(OBJECT_TYPE_BOOLEAN);
    boolean->value.integer_value = value;
    return boolean;
}

struct Object *booleanLoad(struct Object *boolean)
{
    return booleanCopy(boolean);
}

struct Object *booleanStore(struct Object *boolean)
{
    return booleanCopy(boolean);
}

struct Object *booleanCopy(struct Object *boolean)
{
    return booleanNew(boolean->value.integer_value);
}

Integer booleanEquals(struct Object *boolean1, struct Object *boolean2)
{
    if (boolean1 == boolean2) 
    {
        return 1;
    }

    return boolean1->value.integer_value == boolean2->value.integer_value;
}

Integer booleanHash(struct Object *boolean)
{
    return boolean->value.integer_value + 1;
}

struct Object *booleanToString(struct Object *boolean)
{
    struct Object *string = arrayNew(5);
    struct Array *charArray = string->value.array;

    if (boolean->value.integer_value)
    {
        stringAppendCharacter(charArray, 'T')
        stringAppendCharacter(charArray, 'r')
        stringAppendCharacter(charArray, 'u')
        stringAppendCharacter(charArray, 'e')
    }


}

void booleanMark(struct Object *boolean);
void booleanFree(struct Object *boolean);