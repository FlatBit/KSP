#include <stdio.h>
#include "stack.h"
#include "njvm.h"
#include "progload.h"

int stack[STACK_SIZE];
int sp = 0;
int fp = 0;

int v1, v2, value;

int getValue(){
    sp--;
    return stack[sp];
}

void setValue(int value){
    stack[sp] = value;
    sp++;
}

/****** Stack Operation *******/

void pushC(int value){
    setValue(value);    
}

void rdInt(){
    fscanf(stdin, "%d", &value);
    setValue(value);
}

void wrInt(){
    value = getValue();
    printf("%d", value);
}

void rdChr(){
    fscanf(stdin, "%d", &value);
    setValue(value);
}

void wrChr(){
    value = getValue();
    printf("%c", value);
}

/***** Math Operations******/


void add(){
    v1 = getValue();
    v2 = getValue();
    value = v1 + v2;
    setValue(value);
}

void sub(){
    v1 = getValue();
    v2 = getValue();
    value = v2 - v1;
    setValue(value);
}

void mul(){
    v1 = getValue();
    v2 = getValue();
    value = v1 * v2;
    setValue(value);
}

void div(){
    v1 = getValue();
    v2 = getValue();
    value = v2 / v1;
    setValue(value);
}

void mod(){
    v1 = getValue();
    v2 = getValue();
    value = v2 % v1;
    setValue(value);
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

/****StaticDataArea*****/

void pushG(int index){
    if(globalStack && (index >= 0 || index < numberOfInstructions)){
        setValue(globalStack[index]);
    }
}

void popG(int index){
    if(globalStack && (index >= 0 || index < numberOfInstructions)){
        globalStack[index] = getValue();
    }
}
