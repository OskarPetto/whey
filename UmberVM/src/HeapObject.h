#ifndef HEAPOBJECT_H
#define HEAPOBJECT_H

struct HeapObject;

struct HeapObject
{
    uint8_t type;
    struct HeapObject *next;
    uint8_t marked;
    union HeapObjectValue value;
};

union HeapObjectValue
{
    
};


#endif