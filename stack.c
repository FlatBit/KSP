#include <stdio.h>
#include "stack.h"

int stack[STACK_SIZE];
int sp = 0;
int fp = 0;

int getValue(){
    sp--;
    return stack[sp];
}

void setValue(int value){
    stack[sp] = value;
    sp++;
}

/*****STACK_FRAME*****/

// Stack Fram Operations
void pushL(int index){
    int value = stack[fp + index - 1];
    setValue(value);
}

void popL(int index){
   stack[fp + index - 1] = getValue();
}

//Stack Frame Instructions
void assignSF(int n){
    setValue(fp);
    fp = sp;
    sp = sp + n;
}

void releaseSF(){
    sp = fp;
    fp = getValue();
}
