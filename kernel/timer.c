#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"

#include "timer.h"

/* Function declarations */

/*
FUNCTION: clock() 
PURPOSE: Returns the RTC value in MTIME register

This function is designed to be a system call that goes into machine mode 
to access the mtime register and return the value

The assembly code in getclock in kernelvec stores the value of mtime 
timer_scratch[id][6], which is 40 bytes from the start of the struct

Locking is avoided since the timer_scratch values are core specific, 
therefore, if a core is running the kernel and others are running processes,
there is no scenario where the timer_scratch[id] is modified by another hart
*/
uint64
clock(int id)
{
    asm volatile ("ecall");   // Designed to go to machinetrap in kernelvec.S
    uint64 clockval = timer_scratch[id][5];

    return clockval;
}

/*
FUNCTION: updateInterval
PURPOSE: Update the interval for machine timer interrupt

This function updates the interval for the machine timer interrupt 
by updating the timer_scratch variable. 

Locking is avoided since the timer_scratch values are core specific, 
therefore, if a core is running the kernel and others are running processes,
there is no scenario where the timer_scratch[id] is modified by another hart.

To ensure performance with locking, we will need to create a lock for each 
timer_scratch[id], which will only be used in the functions in this file, hence 
choice has been made to not use locking. 
*/
void 
updateInterval(int id, uint64 interval)
{
    timer_scratch[id][4] = interval;
}