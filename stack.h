#define STACK_SIZE 1000

//Variablen
int sp;
int fp;

//Methoden
int getValue();
void setValue(int value);

//StackFrame
void assignSF(int n);
void releaseSF();
void popL(int index);
void pushL(int index);
