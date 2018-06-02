#define STACK_SIZE 1000

//Variablen
int sp;
int fp;
int stack[STACK_SIZE];

//Methoden
int getValue();
void setValue(int value);

//StackFrame
void pushC(int value);
void rdInt();
void wrInt();
void rdChr();
void wrChr();
void add();
void sub();
void mul();
void divS();
void mod();
void pushL(int index);
void popL(int index);
void pushG(int index);
void popG(int index);
void assignSF(int n);
void releaseSF();
void eq ();    
void ne ();               
void lt ();                  
void le ();                  
void gt ();                  
void ge ();                  
void jmp (int index);      
void brf (int index);      
void brt (int index); 
