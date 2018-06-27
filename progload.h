#ifndef PROGLOAD_H
#define PROGLOAD_H
#include "njvm.h"
#include "support.h"


extern int numberOfInstructions;
extern int numberOfVariables;
extern int version;

typedef struct {
    void *pInstruction;
    ObjRef *pVariables;
} StackMemory;

StackMemory loadFile(char *path);

#endif
