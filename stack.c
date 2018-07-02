#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "progload.h"

StackSlot stack[STACK_SIZE];
int sp = 0;
int fp = 0;
int input, output;

ObjRef v1, v2, value;


// Pop Funktionen für StackSlot, ObjRef und Number
StackSlot pop(void){
    sp--;
    if(sp < 0){
        printf("Error: Stack underflow\n");
        exit(99);
    }
    StackSlot ss = stack[sp];
    return ss;
}

ObjRef popo(void){
    StackSlot ss = pop();
        return ss.u.objRef;
    }

int popn(void){
    StackSlot ss = pop();
        return ss.u.number;
    }

// Push Funktionen für StackSlot, ObjRef und Number

void push(StackSlot ss){
    if(sp >= STACK_SIZE){
        printf("Error: Stack overflow\n");
        exit(99);
    }
    stack[sp] = ss;
    sp++;   
}

void pusho(ObjRef obj){
    StackSlot ss;
    ss.isObjRef = 1;
    ss.u.objRef = obj;
    push(ss);
}

ObjRef createObj(int dataI){
    ObjRef obj = malloc(sizeof(ObjRef));
    obj->data[0] = dataI;
    obj->size = sizeof(dataI); 
    return obj;
}

void pushnr(int value){
    StackSlot ss;
    ss.isObjRef = 0;
    ss.u.number = value; 
    push(ss);
}

/****** Stack Operation *******/



void pushC(int value){
    bigFromInt(value);
    pusho(bip.res);    
}

void rdInt(void){

    fflush(stdout);
    bigRead(stdin);
    pusho(bip.res);
    
    /*
    fscanf(stdin, "%d", &input);
    pusho(createObj(input));
    */
}

void wrInt(void){
    /*
    bip.op1 = bip.res;
    bigPrint(stdout);
    bigDump(stdout, bip.res);
    */
    
    ObjRef obj = popo();
    bip.op1 = obj;
    output = bigToInt();
    printf("%d", output);
    
}

void rdChr(void){
    
    fflush(stdout);
    bigRead(stdin);
    pusho(bip.res);
    /*
    fscanf(stdin, "%d", &input);
    pusho(createObj(input)); 
    */
}

void wrChr(void){
    /*
    bip.op1 = bip.res;
    bigPrint(stdout);
    bigDump(stdout, bip.res);
    */
    
    bip.op1 = popo();
    output = bigToInt();
    printf("%c", output);
}

/***** Math Operations******/


void add(void){
    bip.op2 = popo();
    bip.op1 = popo();
    bigAdd();
    value = bip.res;
    pusho(value);
}

void sub(void){
    bip.op2 = popo();
    bip.op1 = popo();
    bigSub();
    value = bip.res;
    pusho(value);
}

void mul(void){
    bip.op2 = popo();
    bip.op1 = popo();
    bigMul();
    value = bip.res;
    pusho(value);
}

void divS(void){
    bip.op2 = popo();
    bip.op1 = popo();
    bigDiv();
    value = bip.res;
    pusho(value);
}

void mod(void){
    bip.op2 = popo();
    bip.op1 = popo();
    bigDiv();
    value = bip.rem;
    pusho(value);
}


/*****STACK_FRAME*****/

// Stack Fram Operations
void pushL(int index){
    StackSlot ss = stack[fp + index ];
    push(ss);
}

// TODO pop() benötigt ObjRef
void popL(int index){
   stack[fp + index] = pop();
}

//Stack Frame Instructions
void assignSF(int n){
    pushnr(fp);
    fp = sp;
    StackSlot inn;
    // Initalisiere Local Variables NULL
        inn.isObjRef = 1;
        inn.u.objRef = NULL;
        for(int i = 0; i < n; i++){    
            stack[fp + i] = inn;
        }
    sp = sp + n;
    
}

void releaseSF(void){
    sp = fp;
    fp = popn();
}

/****StaticDataArea*****/

void pushG(int index){
    if(globalStack && (index >= 0 && index < numberOfVariables)){
        value = globalStack[index];
        pusho(value);
    }
}

void popG(int index){
    if(globalStack && (index >= 0 && index < numberOfVariables)){
        globalStack[index] = popo();
    }
}


/*****Boolean Operations ****/
void eq (void){
    bip.op2 = popo();
    bip.op1 = popo();
    int res = bigCmp();
    if(res == 0){
        bigFromInt(1);
        pusho(bip.res);
    }else{
        bigFromInt(0);
        pusho(bip.res);
    }
}   

void ne (void){
    bip.op2 = popo();
    bip.op1 = popo();
    int res = bigCmp();
    
    if(res != 0){
        bigFromInt(1);
        pusho(bip.res);
    }else{
        bigFromInt(0);
        pusho(bip.res);
    }
}   

void lt (void){
    bip.op2 = popo();
    bip.op1 = popo();
    int res = bigCmp();
    if(res < 0){
        bigFromInt(1);
        pusho(bip.res);
    }else{
        bigFromInt(0);
        pusho(bip.res);
    }
}   

void le (void){
    bip.op2 = popo();
    bip.op1 = popo();
    int res = bigCmp();
    if(res <= 0){
        bigFromInt(1);
        pusho(bip.res);
    }else{
        bigFromInt(0);
        pusho(bip.res);
    }
}   

void gt (void){
    bip.op2 = popo();
    bip.op1 = popo();
    int res = bigCmp();
    if(res >= 0){
        bigFromInt(1);
        pusho(bip.res);
    }else{
        bigFromInt(0);
        pusho(bip.res);
    }
}   

void ge (void){
    bip.op2 = popo();
    bip.op1 = popo();
    int res = bigCmp();
    if(res >= 0 ){
        bigFromInt(1);
        pusho(bip.res);
    }else{
        bigFromInt(0);
        pusho(bip.res);
    }
}   

/******* JUMP Statements *****/

void jmp (int target){
    jump = 1;
    pc = target;
}   

void brf (int target){
    bigFromInt(0);
    bip.op1 = bip.res;
    bip.op2 = popo();
    if(bigCmp() == 0){
        jump = 1;
        pc = target;
    }
}   

void brt (int target){
    bigFromInt(1);
    bip.op1 = bip.res;
    bip.op2 = popo();
    if(bigCmp() == 0){
        jump = 1;
        pc = target;
    }
} 

/****** Instructions Aufgabe 4 ****/

void call(int target){
    pushnr(pc + 1);
    pc = target;
    jump = 1;
}

void ret(void){
    int target = popn();
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
    pusho(value);
} 

void popr(void){
    rRegister = popo();
} 

void dup(void){
    StackSlot ss = pop();
    push(ss);
    push(ss);
} 

/* Operations 7 */

//create new Object Referenz on the stack
void new(int numObjRef){
    ObjRef obj = newCompoundObject(numObjRef);
    pusho(obj);
}

//Object on TOS
void getf(int index){
    ObjRef obj = popo();
    if(obj == NULL){
        fatalError("Objekt nicht initalisiert");
    }
    ObjRef *elements = GET_REFS(obj);
    ObjRef field = elements[index];
    pusho(field);
}

//Value on TOS and Object below TOS
void putf(int index){
    ObjRef data = popo();
    ObjRef obj = popo();
    if(obj == NULL){
        fatalError("Objekt nicht initalisiert");
    }
    ObjRef *elements = GET_REFS(obj);
    elements[index] = data;
}

/**** Array Operations ****/
void newa(void){
    bip.op1 = popo();
    int arrSize = bigToInt();
    ObjRef arr = newCompoundObject(arrSize);
    pusho(arr);
}

// index is on Stack, not know during compile time
void getfa(void){
    bip.op1 = popo();
    int index = bigToInt();
    ObjRef obj = popo();
    if(obj == NULL){
        fatalError("Objekt nicht initalisiert");
    }
    ObjRef *arr = GET_REFS(obj);
    if(index >= GET_SIZE(obj) | index < 0){
        fatalError("Index out of Bounds!");
    }
    pusho(arr[index]);
}

void putfa(void){
    // data
    // index
    // array
    /*  m[0] = new(Fraction[2]);
        pushl 0 // m
        pushc 0 // index
        pushc 2 
        newa
        putfa
    */
    ObjRef data = popo();
    bip.op1 = popo();
    int index = bigToInt();
    ObjRef obj = popo();
    if(obj == NULL){
        fatalError("Objekt nicht initalisiert");
    }
    ObjRef *arr = GET_REFS(obj);
    if(index >= GET_SIZE(obj) | index < 0){
        fatalError("Index out of Bounds!");
    }
    arr[index] = data;
}


void getsz(void){
    ObjRef obj = popo();
    if(obj == NULL){
        fatalError("Objekt nicht initalisiert!");
    }
    int size = GET_SIZE(obj);
    bigFromInt(size);
    pusho(bip.res);
}

void pushn(void){
    pusho(NULL);
}

void refeq(void){
    ObjRef obj1 = popo();
    ObjRef obj2 = popo();
    if((obj1 == NULL) | (obj2 == NULL)){
        if(obj1 == obj2){
            bigFromInt(1);
            pusho(bip.res);
        }else{
            bigFromInt(0);
            pusho(bip.res);
        }
    }else{
        fatalError("Objekte nicht initalisiert!");
    }
}

void refne(void){
    ObjRef obj1 = popo();
    ObjRef obj2 = popo();
    if((obj1 == NULL) | (obj2 == NULL)){
        if(obj1 != obj2){
            bigFromInt(1);
            pusho(bip.res);
        }else{
            bigFromInt(0);
            pusho(bip.res);
        }
    }else{
        fatalError("Objekte nicht initalisiert!");
    }
}
