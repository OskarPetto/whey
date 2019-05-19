#include "GC.h"


struct GC{

    int stuff ;
    int anotherStuff;
};

static struct GC* getGC()
{
    static struct GC* instance = NULL;

    if (instance == NULL)
    {
        //INIT
    }

    return instance;
}

void gcAddObject(struct Object *object)
{
    
}

