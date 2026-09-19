#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  int bursts[3] = {10, 5, 2};

  for(int i = 0; i < 3; i++) {
    int pid = fork();

    if(pid < 0) {
      printf("fork failed\n");
      exit(1);
    }

    if(pid == 0) {
      setburst(bursts[i]);

      printf("pid %d burst %d started\n", getpid(), bursts[i]);

      volatile int x = 0;
      for(int j = 0; j < 100000000; j++) {
        x++;
      }

      printf("pid %d burst %d finished\n", getpid(), bursts[i]);

      exit(0);
    }
  }

  for(int i = 0; i < 3; i++) {
    wait(0);
  }

  exit(0);
}