void debugInterpreter();

typedef enum DebugState{
    inspect,
    list,
    breakpoint,
    step,
    run,
    quit,
} DebugState;
