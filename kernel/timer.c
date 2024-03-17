#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"

#include "timer.h"

/* Function declarations */

uint64
clock(int id)
{
    asm volatile ("ecall");
    uint64 clockval = timer_scratch[id][5];

    return clockval;
}