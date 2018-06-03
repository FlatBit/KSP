#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "njvm.h"
#include "progload.h"

int stack[STACK_SIZE];
int sp = 0;
int fp = 0;

int v1, v2, value;

int pop(void){
    sp--;
    if(sp < 0){
        printf("Error: Stack underflow\n");
        exit(99);
    }
    return stack[sp];
}

void push(int value){
    if(sp >= STACK_SIZE){
        printf("Error: Stack overflow\n");
        exit(99);
    }
    stack[sp] = value;
    sp++;
}

/****** Stack Operation *******/

void pushC(int value){
    push(value);    
}

void rdInt(void){
    printf("Enter Int: \t");
    fscanf(stdin, "%d", &value);
    push(value);
}

void wrInt(void){
    value = pop();
    printf("%d", value);
}

void rdChr(void){
    printf("Enter Char: \t");
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
        printf("Error: Division by zero");
        exit(99);
    }
    value = v2 / v1;
    push(value);
}

void mod(void){
    v1 = pop();
    v2 = pop();
    if(v1 == 0){
        printf("Error: Dibision by zero");
        exit(99);
    }
    value = v2 % v1;
    push(value);
}


/*****STACK_FRAME*****/

// Stack Fram Operations
void pushL(int index){
    int value = stack[fp + index ];
    push(value);
}

void popL(int index){
   stack[fp + index] = pop();
}

//Stack Frame Instructions
void assignSF(int n){
    push(fp);
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
        push(globalStack[index]);
    }
}

void popG(int index){
    if(globalStack && (index >= 0 && index < numberOfInstructions)){
        globalStack[index] = pop();
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
    push(pc + 1);
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
    int value = rRegister;
    push(value);
} 

void popr(void){
    int value = pop();
    rRegister = value;
} 

void dup(void){
    int value = pop();
    push(value);
    push(value);
} 


