
#include "stack.h"
#include "asmdef.h"
#include <stdio.h>
#include <string.h>
#include "progload.h"
#include "njvm.h"
#include "debug.h"


DebugState state = -1;
char command [100];



void switchStates(DebugState ds){
    switch(ds){
        case inspect: {
            printf("DEBUG [inspect]: stack, data? \n");
            scanf( "%s", command);
            
            if (strcmp("stack", command)) {
                /* code */
            }
            else if (strcmp("data", command)){
                /* code */
            }
            
        } break;
        case list: {
            listProgramm();
        } break;
        case breakpoint: {
            printf("DEBUG [breakpoint]: cleared \n");
            printf("DEBUG [breakpoint]: address to set, -1 to clear, <ret> for no change? \n");
            scanf( "%s", command);
        } break;
        case step: {
            pc = pc + 1;
        } break;
        case run: {
            printf("DEBUG []: ");
            scanf( "%s", command);
        } break;
        case quit: {
            printf("DEBUG []: ");
            scanf( "%s", command);
        } break;
        default: {}
    }
}

void debugInterpreter(){
        int IR;
        int halt;
         
        pc = 0;
        do {
            IR = prog[pc];
            switchStates(state);
            halt = execute(IR);
        } while(!halt);
}
