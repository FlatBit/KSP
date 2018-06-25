#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "progload.h"

StackSlot stack[STACK_SIZE];
int sp = 0;
int fp = 0;

int v1, v2, value;

// Hier StackSlot Unterscheidung
int pop(void){
    sp--;
    if(sp < 0){
        printf("Error: Stack underflow\n");
        exit(99);
    }
    int rValue;
    StackSlot ss = stack[sp];
    if(ss.isObjRef == 1){
        rValue = ss.u.objRef->data[0];
    }else{
        rValue = ss.u.number;
    }
    return rValue;
}

StackSlot popSS(){
    sp--;
    StackSlot ss = stack[sp];
    return ss;
}

void pushSS(StackSlot ss){
    if(sp >= STACK_SIZE){
        printf("Error: Stack overflow\n");
        exit(99);
    }
    stack[sp] = ss;
    sp++;   
}

void push(int value){
    char data = (char) value;
    ObjRef obj = malloc(sizeof(ObjRef));
    obj->data[0] = data;
    obj->size = sizeof(data);
    StackSlot ss;
    ss.isObjRef = 1;
    ss.u.objRef = obj; 
    pushSS(ss);
}

void pushN(int value){
    char data = (char) value;
    StackSlot ss;
    ss.isObjRef = 0;
    ss.u.number = data; 
    pushSS(ss);
}

/****** Stack Operation *******/

void pushC(int value){
    push(value);    
}

void rdInt(void){
    fscanf(stdin, "%d", &value);
    push(value);
}

void wrInt(void){
    value = pop();
    printf("%d", value);
}

void rdChr(void){
    fscanf(stdin, "%d", &value);
    push(value);
}

void wrChr(void){
    value = pop();
    printf("%c", value);
}

/***** Math Operations******/


void add(void){
    v1 = pop();
    v2 = pop();
    value = v1 + v2;
    push(value);
}

void sub(void){
    v1 = pop();
    v2 = pop();
    value = v2 - v1;
    push(value);
}

void mul(void){
    v1 = pop();
    v2 = pop();
    value = v1 * v2;
    push(value);
}

void divS(void){
    v1 = pop();
    v2 = pop();
    if(v1 == 0){
        printf("Error: division by zero\n");
        exit(99);
    }
    value = v2 / v1;
    push(value);
}

void mod(void){
    v1 = pop();
    v2 = pop();
    if(v1 == 0){
        printf("Error: division by zero\n");
        exit(99);
    }
    value = v2 % v1;
    push(value);
}


/*****STACK_FRAME*****/

// Stack Fram Operations
void pushL(int index){
    StackSlot ss = stack[fp + index ];
    pushSS(ss);
}

// TODO pop() benötigt ObjRef
void popL(int index){
   stack[fp + index] = popSS();
}

//Stack Frame Instructions
void assignSF(int n){
    pushN(fp);
    fp = sp;
    sp = sp + n;
}

void releaseSF(void){
    sp = fp;
    fp = pop();
}

/****StaticDataArea*****/

void pushG(int index){
    if(globalStack && (index >= 0 && index < numberOfInstructions)){
        ObjRef value = globalStack[index];
        StackSlot ss;
        ss.isObjRef = 1;
        ss.u.objRef = value;
        pushSS(ss);
    }
}

// TODO globalStack speichert auch StackSlots
void popG(int index){
    if(globalStack && (index >= 0 && index < numberOfInstructions)){
        globalStack[index] = popSS().u.objRef;
    }
}


/*****Boolean Operations ****/
void eq (void){
    v1 = pop();
    v2 = pop();
    push((v1 == v2));
}   

void ne (void){
    v1 = pop();
    v2 = pop();
    push((v1 != v2));
}   

void lt (void){
    v1 = pop();
    v2 = pop();
    push((v2 < v1));
}   

void le (void){
    v1 = pop();
    v2 = pop();
    push((v2 <= v1));
}   

void gt (void){
    v1 = pop();
    v2 = pop();
    push((v2 > v1));
}   

void ge (void){
    v1 = pop();
    v2 = pop();
    push((v2 >= v1));
}   

/******* JUMP Statements *****/

void jmp (int target){
    jump = 1;
    pc = target;
}   

void brf (int target){
    if(!pop()){
        jump = 1;
        pc = target;
    }
}   

void brt (int target){
    if(pop()){
        jump = 1;
        pc = target;
    }
} 

/****** Instructions Aufgabe 4 ****/

void call(int target){
    pushN(pc + 1);
    pc = target;
    jump = 1;
}

void ret(void){
    int target = pop();
    pc = target;
    jump = 1;
} 

void drop(int n){
    for(int i = 0; i < n; i++){
        pop();
    }
}

void pushr(void){
    ObjRef value = rRegister;
    StackSlot ss;
    ss.isObjRef = 1;
    ss.u.objRef = value;
    pushSS(ss);
} 

void popr(void){
    StackSlot value = popSS();
    rRegister = value.u.objRef;
} 

void dup(void){
    int value = pop();
    push(value);
    push(value);
} 


