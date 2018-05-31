struct stackMemory;
int numberOfInstructions;
int numberOfVariables;

typedef struct stackMemory stackMemory;
struct stackMemory{
    void *pInstruction;
    signed int *pVariables;
};

stackMemory loadFile(char *path);
