#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  struct proc_info info;

  char *p = sbrklazy(5 * 4096);

  if(p == (char *)-1) {
    printf("sbrklazy failed\n");
    exit(1);
  }

  getprocinfo(getpid(), &info);

  printf("before access: page faults %d\n",
         info.page_faults);

  p[0] = 'A';
  p[2 * 4096] = 'B';
  p[4 * 4096] = 'C';

  getprocinfo(getpid(), &info);

  printf("after access: page faults %d\n",
         info.page_faults);

  printf("values: %c %c %c\n",
         p[0],
         p[2 * 4096],
         p[4 * 4096]);

  exit(0);
}