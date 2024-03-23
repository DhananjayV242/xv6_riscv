#include "types.h"
#include "param.h"

/* 
Function prototypes for functions in timer.c
*/

uint64 clock(int id);
void updateInterval(int id, uint64 interval);

/* Extern variable declarations 
These are global variables declared in other files. */

extern uint64 timer_scratch[NCPU][6];
