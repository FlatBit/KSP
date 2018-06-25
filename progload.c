#include <stdio.h>
#include <stdlib.h>
#include "progload.h"
#include "debug.h"

StackMemory stackPointers;
int numberOfInstructions;
int numberOfVariables;
int version = 5;

void *readInProg(FILE *file){
    char format[4];
    int versionNumber;
   
    
    if(fread(format, 1, 4, file) != 4){
        printf("Format konnte nicht einglesen werden\n");
        exit(99);
    }

    if(!(format[0] == 'N' && format[1] == 'J' && format[2] == 'B' && format[3] == 'F')){
        printf("Format Angabe fehlerhaft\n");
        exit(99);
    }
    
    if(fread(&versionNumber, 4, 1, file) != 1){
        printf("Konnte Versions Nummer nicht einlesen\n");
        exit(99);
    }
    if(versionNumber != version){
        printf("Versions Nummer stimmt nicht überein\n");
        exit(99);
    }

    if(fread(&numberOfInstructions, 4, 1, file) != 1){
        printf("Konnte Zahl der Instructionen nicht einlesen\n");
        exit(99);
    }
    
    void *ptr = malloc(numberOfInstructions * sizeof(int));
    //breakpoints = calloc(numberOfInstructions, sizeof(int));
    if(ptr == NULL){
        printf("Failed to allocate memory for Instructions\n");
        exit(99);
    }
    
    
    if(fread(&numberOfVariables, 4, 1, file) != 1){
        printf("Konnte Zahl der Variablen nicht einlesen.\n");
        exit(99);
    }
    stackPointers.pVariables = malloc(numberOfVariables * sizeof(ObjRef));

    if(fread(ptr, 4, numberOfInstructions, file) != numberOfInstructions){
        printf("Konnte Instruktionen nicht einlesen.\n");
        exit(99);
    }
    return ptr;
}

StackMemory loadFile(char *path){
    FILE *file = fopen(path, "r");
    if(file == NULL){
        printf("Error: cannot open code file %s\n", path);
        exit(1);
    }
    stackPointers.pInstruction = readInProg(file);
    fclose(file);
    return stackPointers;
}

