#ifndef DEBUG_H
#define DEBUG_H

void debugInterpreter(void);
int *breakpoints;

typedef enum DebugState{
    inspect,
    list,
    breakpoint,
    step,
    run,
    quit,
} DebugState;

const static struct {
    DebugState state;
    const char *str;
} conversion [] = {
    {inspect, "inspect"},
    {list, "list"},
    {breakpoint, "breakpoint"},
    {step, "step"},
    {run, "run"},
    {quit, "quit"},
};
#endif
