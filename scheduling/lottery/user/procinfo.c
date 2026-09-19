#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  struct proc_info info;

  if(settickets(5) < 0) {
    printf("procinfo: settickets failed\n");
    exit(1);
  }
  if(setburst(7) < 0) {
    printf("procinfo: setburst failed\n");
    exit(1);
  }
  // volatile int x = 0;
  // for(int i = 0; i < 100000000; i++)
  //   x++;

  if(getprocinfo(getpid(), &info) < 0) {
    printf("procinfo: getprocinfo failed\n");
    exit(1);
  }

  printf("pid %d tickets %d burst %d rtime %d ctime %d pages %lu\n",
         info.pid, info.tickets, info.burst_time,
         info.rtime, info.ctime, info.num_pages);
  exit(0);
}
//rtime will be printing almost 0 , as process gets finished very fast, so to see rtime, i have commented the loop, whichwhen uncommented, can seee rtime>0.
