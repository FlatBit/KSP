#ifndef NJVM_H
#define NJVM_H
#include "support.h"

/*
typedef struct{
    unsigned int size;
    unsigned char data[1];
} *ObjRef;
*/

typedef struct{
	int isObjRef;
	union{
		ObjRef objRef;
		int number;
	} u;
} StackSlot;

extern int pc;
extern unsigned int *prog;
extern ObjRef *globalStack;
extern ObjRef rRegister;
extern int jump;

int execute(int IR);
int printInstruction(int IR);
void listProgramm(void);

#endif
