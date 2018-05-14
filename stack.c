#include <stdio.h>
#include "stack.h"

int stack[STACK_SIZE];
int sp = 0;

int getValue(){
    sp--;
    return stack[sp];
}

void setValue(int value){
    stack[sp] = value;
    sp++;
}
