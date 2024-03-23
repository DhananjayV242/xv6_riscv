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
    panic("Usage: measure [optional: execution count] <program name>\n");
  
  int loopCount = 10;
  int execIndex = 1;

  if(argc == 3)
  {
    loopCount = atoi(argv[1]);
    execIndex = 2;
  }
   
   printf("Measuring %s:\n", argv[1]);

   uint64 time = 0;
   uint64 start_time, end_time;

   for(int i=0; i<loopCount; i++)
   {

    printf("\n\n");
    printf("*********************************\n");
    printf("*** Executing %s: Iteration %d ***\n", argv[execIndex], i);
    printf("*********************************\n");
    
    start_time = clock();
    
    if(fork1() == 0)
    {
      exec(argv[execIndex], &(argv[execIndex]));
      printf("exec %s failed\n", argv[execIndex]);
      panic("exec failed");
    }
    wait(0);
    end_time = clock();
    time += (end_time - start_time);
   }   

    time /= loopCount;
    printf("\n\nFinished measuring %s!\n", argv[execIndex]);
    printf("Total Execution count: %d\n", loopCount);
    printf("Average time of execution: %p cycles\n\n", time);

    return 0;
}