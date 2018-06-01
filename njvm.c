
#include "stack.h"
#include "asmdef.h"
#include <stdio.h>
#include <string.h>
#include "progload.h"
#include "debug.h"

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
        case PUSHG: { pushG(IMMEDIATE(IR)); }   break;
        case POPG:  { popG(IMMEDIATE(IR));  }   break;
        case ASF:   { assignSF(IMMEDIATE(IR));} break;
        case RSF:   { releaseSF();  }           break;
        case PUSHL: { pushL(IMMEDIATE(IR)); }   break;
        case POPL:  { popL(IMMEDIATE(IR));  }   break;
        case EQ:    { eq();    } break;
        case NE:    { ne();    } break;
        case LT:    { lt();    } break;
        case LE:    { le();    } break;
        case GT:    { gt();    } break;
        case GE:    { ge();    } break;
        case JMP:   { jmp(IMMEDIATE(IR)); }     break;
        case BRF:   { brf(IMMEDIATE(IR)); }     break;
        case BRT:   { brt(IMMEDIATE(IR)); }     break;

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
        case HALT:  { printf("%04d: \t HALT \n", pc); return 1; } break;
        case PUSHC: { printf("%04d: \t PUSHC \t %d \n", pc, SIGN_EXTEND(IMMEDIATE(IR))); } break;
        case ADD:   { printf("%04d: \t ADD \n", pc); } break;
        case SUB:   { printf("%04d: \t SUB \n", pc); } break;
        case MUL:   { printf("%04d: \t MUL \n", pc); } break;
        case DIV:   { printf("%04d: \t DIV \n", pc); } break;
        case MOD:   { printf("%04d: \t MOD \n", pc); } break;
        case RDINT: { printf("%04d: \t RDINT \n", pc); } break;
        case WRINT: { printf("%04d: \t WRINT \n", pc); } break;
        case RDCHR: { printf("%04d: \t RDCHR \n", pc); } break;
        case WRCHR: { printf("%04d: \t WRCHR \n", pc); } break;
        case PUSHG: { printf("%04d: \t PUSHG \t %d \n", pc, IMMEDIATE(IR)); }    break;
        case POPG:  { printf("%04d: \t POPG \t %d \n", pc, IMMEDIATE(IR)); }     break;
        case ASF:   { printf("%04d: \t ASF \t %d \n", pc, IMMEDIATE(IR)); } break;
        case RSF:   { printf("%04d: \t RSF \n", pc); } break;
        case PUSHL: { printf("%04d: \t PUSHL \t %d \n", pc, IMMEDIATE(IR)); } break;
        case POPL:  { printf("%04d: \t POPL \t %d \n", pc, IMMEDIATE(IR)); } break;
        case EQ:    { printf("%04d: \t EQ \n", pc); } break;
        case NE:    { printf("%04d: \t NE \n", pc); } break;
        case LT:    { printf("%04d: \t LT \n", pc); } break;
        case LE:    { printf("%04d: \t LE \n", pc); } break;
        case GT:    { printf("%04d: \t GT \n", pc); } break;
        case GE:    { printf("%04d: \t GE \n", pc); } break;
        case JMP:   { printf("%04d: \t JMP \t %d \n", pc,  IMMEDIATE(IR)); } break;
        case BRF:   { printf("%04d: \t BRF \t %d \n", pc,  IMMEDIATE(IR)); } break;
        case BRT:   { printf("%04d: \t BRT \t %d \n", pc,  IMMEDIATE(IR)); } break;
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
            char *path = "progs/prog6.bin";
            stackMemory stackStruct = loadFile(path);
            if(stackStruct.pInstruction){
                prog = (unsigned int*)stackStruct.pInstruction;
            }
            if(stackStruct.pVariables){
                globalStack = stackStruct.pVariables;
            }
            programmInterpreter();
            // TODO free prog
        }
        if(!strcmp(argv[i], "--debug")){
            char *path = "progs/prog6.bin";
            stackMemory stackStruct = loadFile(path);
            if(stackStruct.pInstruction){
                prog = (unsigned int*)stackStruct.pInstruction;
            }
            if(stackStruct.pVariables){
                globalStack = stackStruct.pVariables;
            }
            debugInterpreter();
        }
    }
    
    
    printf("Ninja Virtual stopped \n");
    return 0;
}
