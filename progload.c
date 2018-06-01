#include <stdio.h>
#include <stdlib.h>
#include "progload.h"

stackMemory stackPointers;
int numberOfInstructions;
int numberOfVariables;
int version = 3;

void *readInProg(FILE *file){
    char format[4];
    int versionNumber;
   
    
    if(fread(format, 1, 4, file) != 4){
        printf("Format konnte nicht einglesen werden \n");
        exit(99);
    }
    if(!(format[0] == 'N' && format[1] == 'J' && format[2] == 'B' && format[3] == 'F')){
        printf("Format Angabe fehlerhaft \n");
    }
    printf("Format: %c %c %c %c \n", format[0], format[1], format[2], format[3]);
    
    
    if(fread(&versionNumber, 4, 1, file) != 1){
        printf("Konnte Versions Nummer nicht einlesen \n");
        exit(99);
    }
    if(versionNumber != version){
        printf("Versions Nummer stimmt nicht überein");
        exit(99);
    }
    printf("Version Number: %d \n", versionNumber);

    if(fread(&numberOfInstructions, 4, 1, file) != 1){
        printf("Konnte Zahl der Instructionen nicht einlesen \n");
        exit(99);
    }
    
    void *ptr = malloc(numberOfInstructions * sizeof(int));
    if(ptr == NULL){
        printf("Failed to allocate memory for Instructions \n");
    }
    
    printf("Number of Instruction: %d \n", numberOfInstructions);
    
    if(fread(&numberOfVariables, 4, 1, file) != 1){
        printf("Konnte Zahl der Variablen nicht einlesen. \n");
        exit(1);
    }
    printf("Number of Variables: %d \n",numberOfVariables);
    stackPointers.pVariables = malloc(numberOfVariables * sizeof(int));

    if(fread(ptr, 4, numberOfInstructions, file) != numberOfInstructions){
        printf("Konnte Instruktionen nicht einlesen. \n");
    }
    return ptr;
}

stackMemory loadFile(char *path){
    FILE *file = fopen(path, "r");
    if(file == NULL){
        printf("Failed to load file");
        exit(1);
    }
    stackPointers.pInstruction = readInProg(file);
    fclose(file);
    return stackPointers;
}

void ags(){
    
}
