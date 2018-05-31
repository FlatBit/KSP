
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
    /*
    int v1;
    int v2;
    int value;
    */

    opCode = (IR & 0xFF000000) >> 24;
    switch(opCode){
        case HALT:
            return 1;
            break;
        case PUSHC: { pushC(SIGN_EXTEND(IMMEDIATE(IR)));  } break;
        case ADD:   { add();    } break;
        case SUB:   { sub();    } break;
        case MUL:   { mul();    } break;
        case DIV:   { div();    } break;
        case MOD:   { mod();    } break;
        case RDINT: { rdInt();  } break;
        case WRINT: { wrInt();  } break;
        case RDCHR: { rdChr();  } break;
        case WRCHR: { wrChr();  } break;
        case PUSHG: { pushG(IMMEDIATE(IR));} break;
        case POPG:  { popG(IMMEDIATE(IR));} break;
        case ASF:   { assignSF(IMMEDIATE(IR)); break; }
        case RSF:   { releaseSF(); break; }
        case PUSHL: { pushL(IMMEDIATE(IR)); break; }
        case POPL:  { popL(IMMEDIATE(IR)); break; }
        default: break;
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

    // int value;
    opCode = IR >> 24;

    switch(opCode){
        case HALT:  { printf("HALT \n"); return 1; } break;
        case PUSHC: { printf("PUSHC \t %d \n", SIGN_EXTEND(IMMEDIATE(IR))); } break;
        case ADD:   { printf("ADD \n"); } break;
        case SUB:   { printf("SUB \n"); } break;
        case MUL:   { printf("MUL \n"); } break;
        case DIV:   { printf("DIV \n"); } break;
        case MOD:   { printf("MOD \n"); } break;
        case RDINT: { printf("RDINT \n"); } break;
        case WRINT: { printf("WRINT \n"); } break;
        case RDCHR: { printf("RDCHR \n"); } break;
        case WRCHR: { printf("WRCHR \n"); } break;
        case PUSHG: { printf("PUSHG \t %d \n", IMMEDIATE(IR)); } break;
        case POPG:  { printf("POPG \t %d \n", IMMEDIATE(IR)); } break;
        case ASF:   { printf("ASF \t %d \n", IMMEDIATE(IR)); } break;
        case RSF:   { printf("RSF \n"); } break;
        case PUSHL: { printf("PUSHL \t %d \n", IMMEDIATE(IR)); } break;
        case POPL:  { printf("POPL \t %d \n", IMMEDIATE(IR)); } break;
        default:    break;
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
        
        if(!strcmp(argv[i], "--asm")){
            char *path = "prog1.bin";
            stackMemory stackStruct = loadFile(path);
            if(stackStruct.pInstruction){
                prog = (unsigned int*)stackStruct.pInstruction;
            }
            if(stackStruct.pVariables){
                globalStack = stackStruct.pVariables;
            }
            listProgramm();
            programmInterpreter();
            // TODO free prog
        }
    }
    
    
    printf("Ninja Virtual stopped \n");
    return 0;
}
