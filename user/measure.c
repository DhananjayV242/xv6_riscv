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

   if(argc < 2)
    panic("Usage: measure <program name>");
   
   printf("Measuring %s:\n", argv[1]);

   uint64 time = 0;
   uint64 start_time, end_time;

   for(int i=0; i<10; i++)
   {
    start_time = clock();
    
    if(fork1() == 0)
    {
      exec(argv[1], &(argv[1]));
      printf("exec %s failed\n", argv[1]);
      panic("exec failed");
    }
    wait(0);
    end_time = clock();
    time += (end_time - start_time);
   }   

    time /= 10;
    printf("\n\nFinished measuring %s!\n", argv[1]);
    printf("Total Execution count: 10\n");
    printf("Average time of execution: %p cycles\n\n", time);

    return 0;
}