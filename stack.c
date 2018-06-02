#include <stdio.h>
#include "stack.h"
#include "njvm.h"
#include "progload.h"

int stack[STACK_SIZE];
int sp = 0;
int fp = 0;

int v1, v2, value;

int pop(){
    sp--;
    return stack[sp];
}

void push(int value){
    stack[sp] = value;
    sp++;
}

/****** Stack Operation *******/

void pushC(int value){
    push(value);    
}

void rdInt(){
    printf("Enter Int: \t");
    fscanf(stdin, "%d", &value);
    push(value);
}

void wrInt(){
    value = pop();
    printf("%d", value);
}

void rdChr(){
    printf("Enter Char: \t");
    fscanf(stdin, "%d", &value);
    push(value);
}

void wrChr(){
    value = pop();
    printf("%c", value);
}

/***** Math Operations******/


void add(){
    v1 = pop();
    v2 = pop();
    value = v1 + v2;
    push(value);
}

void sub(){
    v1 = pop();
    v2 = pop();
    value = v2 - v1;
    push(value);
}

void mul(){
    v1 = pop();
    v2 = pop();
    value = v1 * v2;
    push(value);
}

void divS(){
    v1 = pop();
    v2 = pop();
    value = v2 / v1;
    push(value);
}

void mod(){
    v1 = pop();
    v2 = pop();
    value = v2 % v1;
    push(value);
}


/*****STACK_FRAME*****/

// Stack Fram Operations
void pushL(int index){
    int value = stack[fp + index - 1];
    push(value);
}

void popL(int index){
   stack[fp + index - 1] = pop();
}

//Stack Frame Instructions
void assignSF(int n){
    push(fp);
    fp = sp;
    sp = sp + n;
}

void releaseSF(){
    sp = fp;
    fp = pop();
}

/****StaticDataArea*****/

void pushG(int index){
    if(globalStack && (index >= 0 || index < numberOfInstructions)){
        push(globalStack[index]);
    }
}

void popG(int index){
    if(globalStack && (index >= 0 || index < numberOfInstructions)){
        globalStack[index] = pop();
    }
}


/*****Boolean Operations ****/
void eq (){
    v1 = pop();
    v2 = pop();
    push((v1 == v2));
}   

void ne (){
    v1 = pop();
    v2 = pop();
    push((v1 != v2));
}   

void lt (){
    v1 = pop();
    v2 = pop();
    push((v2 < v1));
}   

void le (){
    v1 = pop();
    v2 = pop();
    push((v2 <= v1));
}   

void gt (){
    v1 = pop();
    v2 = pop();
    push((v2 > v1));
}   

void ge (){
    v1 = pop();
    v2 = pop();
    push((v2 >= v1));
}   

void jmp (int index){
    pc = index;
}   

void brf (int index){
    if(!pop()){
        pc = index;
    }
}   

void brt (int index){
    if(pop()){
        pc = index;
    }
} 
