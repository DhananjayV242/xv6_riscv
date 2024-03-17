#include "kernel/types.h"
#include "user/user.h"

void
panic(char *s)
{
  fprintf(2, "%s\n", s);
  exit(1);
}


int
fork1(void)
{
  int pid;

  pid = fork();
  if(pid == -1)
    panic("fork");
  return pid;
}


int main(int argc, char *argv[])
{
   /* TODO Add condition to fail if 
   no program given to measure*/
   
   //uint64 start_time = clock();
    printf("Measuring time:\n");
    if(fork1() == 0)
        exec(argv[1], &(argv[1]));
    wait(0);

    printf("End of interval measurement!\n");
    //uint64 end_time = clock();
    //printf("The time taken for the clock tick: %d\n", end_time - start_time);

}