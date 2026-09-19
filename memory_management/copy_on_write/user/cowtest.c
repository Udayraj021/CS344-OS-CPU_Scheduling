#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  int *x = malloc(sizeof(int));

  if(x == 0) {
    printf("malloc failed\n");
    exit(1);
  }

  *x = 10;

  int pid = fork();

  if(pid < 0) {
    printf("fork failed\n");
    exit(1);
  }

  if(pid == 0) {
    printf("child before write: %d\n", *x);

    *x = 20;

    printf("child after write: %d\n", *x);

    exit(0);
  }

  wait(0);

  printf("parent after child write: %d\n", *x);

  if(*x == 10)
    printf("COW test passed\n");
  else
    printf("COW test failed\n");

  exit(0);
}