
#include "stack.h"
#include "asmdef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "progload.h"
#include "debug.h"
#include "bigint.h"
#include "sup.h"

 //Instruction Regist & Global Stack
 unsigned int *prog;
 ObjRef *globalStack;
 ObjRef rRegister;
 int jump = 0;

 //Counter & Pointer
 int pc = 0;


 //Zwei Interpreter Listen und Ausfuehrung
int execute(int IR){
    int opCode;
    
    opCode = (IR & 0xFF000000) >> 24;
    switch(opCode){
        case HALT:
            return 1;
            break;
        case PUSHC: { pushC(SIGN_EXTEND(IMMEDIATE(IR)));  } break;
        case ADD:   { add();    } break;
        case SUB:   { sub();    } break;
        case MUL:   { mul();    } break;
        case DIV:   { divS();   } break;
        case MOD:   { mod();    } break;
        case RDINT: { rdInt();  } break;
        case WRINT: { wrInt();  } break;
        case RDCHR: { rdChr();  } break;
        case WRCHR: { wrChr();  } break;
        case PUSHG: { pushG(IMMEDIATE(IR)); }   break;
        case POPG:  { popG(IMMEDIATE(IR));  }   break;
        case ASF:   { assignSF(IMMEDIATE(IR));} break;
        case RSF:   { releaseSF();  }           break;
        case PUSHL: { pushL(SIGN_EXTEND(IMMEDIATE(IR))); }   break;
        case POPL:  { popL(SIGN_EXTEND(IMMEDIATE(IR)));  }   break;
        case EQ:    { eq();    } break;
        case NE:    { ne();    } break;
        case LT:    { lt();    } break;
        case LE:    { le();    } break;
        case GT:    { gt();    } break;
        case GE:    { ge();    } break;
        case JMP:   { jmp(IMMEDIATE(IR)); }     break;
        case BRF:   { brf(IMMEDIATE(IR)); }     break;
        case BRT:   { brt(IMMEDIATE(IR)); }     break;
        case CALL:  { call(IMMEDIATE(IR)); }    break;
        case RET:   { ret(); }  break;
        case DROP:  { drop(IMMEDIATE(IR)); }    break;
        case PUSHR: { pushr();} break;
        case POPR:  { popr(); } break;
        case DUP:   { dup(); }  break;
        case NEW:   { new(IMMEDIATE(IR));}  break;
        case GETF:  { getf(IMMEDIATE(IR));} break;
        case PUTF:  { putf(IMMEDIATE(IR));} break;
        case NEWA:  { newa(); }  break;
        case GETFA: { getfa(); } break;
        case PUTFA: { putfa(); } break;
        case GETSZ: { getsz(); } break;
        case PUSHN: { pushn(); } break;
        case REFEQ: { refeq(); } break;
        case REFNE: { refne(); } break;

        default: break;
    }
    return 0;
}


void programmInterpreter(void){
    int IR;
    int halt;
    pc = 0;
    do {
            IR = prog[pc];
            halt = execute(IR);
            if(!jump){
                pc = pc + 1;
            }else{
                jump = 0;
            }
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
        case PUSHL: { printf("%04d: \t PUSHL \t %d \n", pc, SIGN_EXTEND(IMMEDIATE(IR))); }  break;
        case POPL:  { printf("%04d: \t POPL \t %d \n", pc, SIGN_EXTEND(IMMEDIATE(IR))); }   break;
        case EQ:    { printf("%04d: \t EQ \n", pc); } break;
        case NE:    { printf("%04d: \t NE \n", pc); } break;
        case LT:    { printf("%04d: \t LT \n", pc); } break;
        case LE:    { printf("%04d: \t LE \n", pc); } break;
        case GT:    { printf("%04d: \t GT \n", pc); } break;
        case GE:    { printf("%04d: \t GE \n", pc); } break;
        case JMP:   { printf("%04d: \t JMP \t %d \n", pc,  IMMEDIATE(IR)); } break;
        case BRF:   { printf("%04d: \t BRF \t %d \n", pc,  IMMEDIATE(IR)); } break;
        case BRT:   { printf("%04d: \t BRT \t %d \n", pc,  IMMEDIATE(IR)); } break;
        case CALL:  { printf("%04d: \t CALL \t %d \n", pc, IMMEDIATE(IR)); } break;
        case RET:   { printf("%04d: \t RET \t \n", pc); } break;   
        case DROP:  { printf("%04d: \t DROP \t %d \n", pc, IMMEDIATE(IR)); } break;  
        case PUSHR: { printf("%04d: \t PUSHR \t \n", pc); } break; 
        case POPR:  { printf("%04d: \t POPR \t \n", pc); } break;  
        case DUP:   { printf("%04d: \t DUP \t \n", pc); } break;
        case NEW:   { printf("%04d: \t NEW \t %d \n", pc, IMMEDIATE(IR)); } break;
        case GETF:  { printf("%04d: \t GETF \t %d \n", pc, IMMEDIATE(IR)); } break;
        case PUTF:  { printf("%04d: \t PUTF \t %d \n", pc, IMMEDIATE(IR)); } break;
        case NEWA:  { printf("%04d: \t NEWA \t \n", pc); } break;
        case GETFA: { printf("%04d: \t GETFA \t \n", pc); } break;
        case PUTFA: { printf("%04d: \t PUTFA \t \n", pc); } break;
        case GETSZ: { printf("%04d: \t GETSZ \t \n", pc); } break;
        case PUSHN: { printf("%04d: \t PUSHN \t \n", pc); } break;
        case REFEQ: { printf("%04d: \t REFEQ \t \n", pc); } break;
        case REFNE: { printf("%04d: \t REFNE \t \n", pc); } break;
        default:    break;
    }

    return 0;
}

void listProgramm(void){
    int IR;
    int apc = pc;
    pc = 0;
    while(pc < numberOfInstructions - 1){
        IR = prog[pc];
        printInstruction(IR);
        pc = pc + 1;
    }
    pc = apc;
}

void initalizeToNULL(){
    bip.op1 = NULL; 
    bip.op2 = NULL;
    bip.rem = NULL;
    bip.res = NULL;
    rRegister = NULL;

}


// Liest die Kommandozeilen Argumente und benutzt int debug als Flag für den Debug
// Modus und int fileSet als Flag für eine geladene Datei
int main(int argc, char* argv[]){
    
    //Flags
    int debug = 0;
    int fileSet = 0;

    // Kommandozeilen Argumente Verarbeiten
    for(int i = 1; i < argc; i++){
        if(!strcmp(argv[i], "--version")){
            printf("Ninja Virtual Machine version %d (compiled %s %s)\n", version, __DATE__, __TIME__);
            return 0;
        }else if(!strcmp(argv[i], "--help")){
            printf("--version \t show version and exit\n");
            printf("--help \t \t show this help and exit\n");
            return 0;
        }else if(!strcmp(argv[i], "--debug")){
            debug = 1;
        }else{ 
            // Uebergebenen Dateipfad einlesen
            if(!fileSet){
                char *path = argv[i];
                StackMemory stackStruct = loadFile(path);
                if(stackStruct.pInstruction && stackStruct.pVariables){
                    prog = (unsigned int*)stackStruct.pInstruction;
                    globalStack = stackStruct.pVariables;
                    // Set GlobalStack to NULL
                    for(int i = 0; i < numberOfVariables; i++){
                        globalStack[i] = NULL;
                    }
                    fileSet = 1;
                }else{
                    printf("Error: Failed to initlize Instructions\n");
                    exit(99);
                }
            }else{
                printf("Error: more than one code file specified\n");
                exit(99);
            }
            initalizeToNULL();
        }
    }
    printf("Ninja Virtual Machine started\n");
    if(debug && fileSet){
        debugInterpreter();
    }else if(fileSet){
        programmInterpreter();
    }
    
    printf("Ninja Virtual Machine stopped\n");
    return 0;
}
