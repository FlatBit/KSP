
#include "stack.h"
#include "asmdef.h"
#include <stdio.h>
#include <string.h>
#include "progload.h"

 //Instruction Regist & Global Stack
 unsigned int *prog;
 signed int *globalStack;

 //Counter & Pointer
 int pc = 0;


 //Zwei Interpreter Listen und Ausfuehrung
int execute(int IR){
    int opCode;
    int v1;
    int v2;
    int value;

    opCode = (IR & 0xFF000000) >> 24;
    switch(opCode){
        case HALT:
            return 1;
            break;
        case PUSHC:
            value = SIGN_EXTEND(IMMEDIATE(IR));
            setValue(value);
            break;
        case ADD:
            v1 = getValue();
            v2 = getValue();
            value = v1 + v2;
            setValue(value);
            break;
        case SUB:
            v1 = getValue();
            v2 = getValue();
            value = v2 - v1;
            setValue(value);
            break;
        case MUL:
            v1 = getValue();
            v2 = getValue();
            value = v1 * v2;
            setValue(value);
            break;
        case DIV:
            v1 = getValue();
            v2 = getValue();
            value = v2 / v1;
            setValue(value);
            break;
        case MOD:
            v1 = getValue();
            v2 = getValue();
            value = v2 % v1;
            setValue(value);
            break;
        case RDINT:
            fscanf(stdin, "%d", &value);
            setValue(value);
            break;
        case WRINT:
            value = getValue();
            printf("%d", value);
            break;
        case RDCHR:
            fscanf(stdin, "%d", &value);
            setValue(value);
            break;
        case WRCHR:
            value = getValue();
            printf("%c", value);
            break;
        case PUSHG:

            break;
        case POPG:

            break;
        case ASF:
            assignSF(IMMEDIATE(IR));
            break;
        case RSF:
            releaseSF();
            break;
        case PUSHL:
            pushL(IMMEDIATE(IR));
            break;
        case POPL:
            popL(IMMEDIATE(IR));
            break;
        default:
            break;
    }

    return 0;
}

void programmInterpreter(){
        int IR;
        int halt;
        pc = 0;
        do {
            IR = prog[pc];
            pc = pc + 1;
            halt = execute(IR);
        } while(!halt);
}

int printInstruction(int IR){
    int opCode;
    int value;
    opCode = IR >> 24;

    switch(opCode){
        case HALT:
            printf("HALT \n");
            return 1;
            break;
        case PUSHC:
            printf("PUSHC \t %d \n", SIGN_EXTEND(IMMEDIATE(IR)));
            break;
        case ADD:
            printf("ADD \n");
            break;
        case SUB:
            printf("SUB \n");
            break;
        case MUL:
            printf("MUL \n");
            break;
        case DIV:
            printf("DIV \n");
            break;
        case MOD:
            printf("MOD \n");
            break;
        case RDINT:
            printf("RDINT \n");
            break;
        case WRINT:
            printf("WRINT \n");
            break;
        case RDCHR:
            printf("RDCHR \n");
            break;
        case WRCHR:
            printf("WRCHR \n");
            break;
        case PUSHG:
            printf("PUSHG \n");
            break;
        case POPG:
            printf("POPG \n");
            break;
        case ASF:
            printf("ASF \n");
            break;
        case RSF:
            printf("RSF \n");
            break;
        case PUSHL:
            printf("PUSHL \n");
            break;
        case POPL:
            printf("POPL \n");
            break;
        default:
            break;
    }

    return 0;
}

void listProgramm(){
    int IR;
    int halt;
    pc = 0;
    do {
        IR = prog[pc];
        pc = pc + 1;
        halt = printInstruction(IR);
    } while(!halt);
}



int main(int argc, char* argv[]){
    
    int i;
    printf("Ninja Virtual Machine started \n");

    for(i = 0; i < argc; i++){
        if(!strcmp(argv[i], "--version")){
            printf("Ninja Virtual Machine version 0 (compiled %s %s) \n", __DATE__, __TIME__);
            return 0;
        }
        if(!strcmp(argv[i], "--help")){
            printf("--version \t show version and exit \n");
            printf("--help \t \t show this help and exit \n");
            return 0;
        }
        if(!strcmp(argv[i], "--prog1")){
            //prog = {(PUSHC << 24 | 0x3), PUSHC << 24 | 0x4), (ADD << 24), (WRINT << 24), (HALT << 24)};
            prog[0] = (PUSHC << 24 | 0x3);
            prog[1] = (PUSHC << 24 | 0x4);
            prog[2] = (ADD << 24);
            prog[3] = (PUSHC << 24 | 0xA);
            prog[4] = (PUSHC << 24 | 0x6);
            prog[5] = (SUB << 24);
            prog[6] = (MUL << 24);
            prog[7] = (WRINT << 24);
            prog[8] = (PUSHC << 24 | 0xA);
            prog[9] = (WRCHR << 24);
            prog[10] = (HALT << 24);
            programmInterpreter();
            listProgramm();
            
        }
        if(!strcmp(argv[i], "--prog2")){
            prog[0] = (PUSHC << 24 | 0x2);
            prog[1] = (RDINT<< 24);
            prog[2] = (MUL << 24);
            prog[3] = (PUSHC << 24 | 0x3);
            prog[4] = (PUSHC << 24 | 0x6);
            prog[5] = (SUB << 24);
            prog[6] = (MUL << 24);
            prog[7] = (WRINT << 24);
            prog[8] = (PUSHC << 24 | 0xA);
            programmInterpreter();
            listProgramm();

        }
        if(!strcmp(argv[i], "--prog3")){
            prog[0] = (RDCHR << 24);
            prog[1] = (WRINT << 24);
            prog[2] = (PUSHC << 24 | 'n');
            prog[3] = (WRCHR << 24);
            prog[4] = (HALT);
        }

        if(!strcmp(argv[i], "--asm")){
            char *path = "prog1.bin";
            prog = loadFile(path);
            listProgramm();
            // TODO free prog
        }
    }
    
    
    printf("Ninja Virtual stopped \n");
    return 0;
}
