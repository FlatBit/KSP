
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "asmdef.h"
#include "progload.h"
#include "njvm.h"
#include "debug.h"

char command [100];
int bp = -1;
int halt = 0;
int IR;
int running = 0;

void showStack(void){
    for(int i = sp; i >= 0; i--){
        if(i == sp && i == fp){
            printf("sp, fp \t --->");
        }else{
            if(i == sp ){
                printf("sp");
            }
            if(i == fp){
                printf("fp");
            }
            printf("\t --->");
        }
        printf("\t%04d:\t %d \n", i, stack[i]);
    }
    printf("\t --- bottom of stack --- \n");
}

void showData(void){
    for(int i = 0; i < numberOfVariables; i++){
        printf("data[%04d]: \t %d \n", i, globalStack[i]);
    }
    printf("\t --- end of data --- \n");
}

DebugState checkDebugState (const char *str)
{
    for (int i = 0;  i < 6);  ++i){
        if (!strcmp (str, conversion[i].str)){
            return conversion[i].state;
        }
    }
    return -1;
}

void switchStates(DebugState ds){
    switch(ds){
        case inspect: {
            printf("DEBUG [inspect]: stack, data? \n");
            scanf( "%s", command);
            
            if (!strcmp("stack", command)) {
                showStack();
            }
            if (!strcmp("data", command)){
                showData();
            }
        } break;
        case list: {
            listProgramm();
        } break;
        case breakpoint: {
            if(bp < 0){
                printf("DEBUG [breakpoint]: cleared \n");
            }else{
                printf("DEBUG [breakpoint]: set to %d \n", bp);
            }
            printf("DEBUG [breakpoint]: address to set, -1 to clear, <ret> for no change? \n");
            int number;
            scanf("%d", &number);
            
            if (number == -1){
                bp = -1;
            }else{
                if(number >= 0 && number < numberOfInstructions){
                    bp = number;
                    printf("DEBUG [breakpoint]: now set at %d \n", number);
                }else{
                    printf("DEBUG [breakpoint]: breakpoint outside of instruction register");
                }
            }
            
        } break;
        case step: {
            halt = execute(IR);
            if(!jump){
                pc = pc + 1;
            }else{
                jump = 0;
            }
        } break;
        case run: {
           running = 1;
        } break;
        case quit: {
            exit(0);
        } break;
        default: {}
    }
}


void debugInterpreter(void){
        DebugState state;
        pc = 0;
        char input[100];
        while(!halt) {
            IR = prog[pc];
            if(running && pc != bp){
                halt = execute(IR);
                if(!jump){
                    pc = pc + 1;
                }else{
                    jump = 0;
                }
            }else{
                running = 0;
                printInstruction(IR);
                printf("DEBUG: inspect, list, breakpoint, step, run, quit \n");
                scanf("%s", input);
                state = checkDebugState(input);
                switchStates(state);
            }
            
        }
}
