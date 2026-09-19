#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  int tickets[3] = {5, 10, 20};
  int pids[3];

  for(int i = 0; i < 3; i++) {
    int pid = fork();

    if(pid < 0) {
      printf("fork failed\n");
      exit(1);
    }

    if(pid == 0) {
      settickets(tickets[i]);

      volatile int x = 0;

      while(1) {
        x++;
      }
    }

    pids[i] = pid;
  }

  pause(200);

  for(int i = 0; i < 3; i++) {
    struct proc_info info;

    if(getprocinfo(pids[i], &info) < 0) {
      printf("getprocinfo failed for pid %d\n", pids[i]);
    } else {
      printf("pid %d tickets %d rtime %d\n",
             info.pid,
             info.tickets,
             info.rtime);
    }
  }

  for(int i = 0; i < 3; i++) {
    kill(pids[i]);
  }

  for(int i = 0; i < 3; i++) {
    wait(0);
  }

  exit(0);
}