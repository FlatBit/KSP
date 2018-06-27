#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 1000
#include "njvm.h"
#include "support.h"

//Variablen
extern int sp;
extern int fp;
extern StackSlot stack[STACK_SIZE];

//Methoden
int getValue();
void setValue(int value);

//StackFrame
void pushC(int value);
void rdInt(void);
void wrInt(void);
void rdChr(void);
void wrChr(void);
void add(void);
void sub(void);
void mul(void);
void divS(void);
void mod(void);
void pushL(int index);
void popL(int index);
void pushG(int index);
void popG(int index);
void assignSF(int n);
void releaseSF(void);
void eq (void);    
void ne (void);               
void lt (void);                  
void le (void);                  
void gt (void);                  
void ge (void);                  
void jmp (int target);      
void brf (int target);      
void brt (int target); 
void call(int target); 
void ret(void); 
void drop(int n); 
void pushr(void); 
void popr(void); 
void dup(void); 

#endif
