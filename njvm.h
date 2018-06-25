#ifndef NJVM_H
#define NJVM_H

typedef struct{
    unsigned int size;
    unsigned char data[1];
} *ObjRef;

typedef struct{
	int isObjRef;
	union{
		ObjRef objRef;
		int number;
	} u;
} StackSlot;

int pc;
unsigned int *prog;
ObjRef *globalStack;
ObjRef rRegister;

 int jump;
 int execute(int IR);
 int printInstruction(int IR);
 void listProgramm(void);

#endif



