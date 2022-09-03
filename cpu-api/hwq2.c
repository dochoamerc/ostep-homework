#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static int x = 100;

int main(int argc, char *argv[]) {
  printf("hello world! X is %d (pid: %d) \n", x, (int) getpid());
  int rc = fork();
  if(rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
     printf("hello, I am child. X = %d, I will change it to 30. (pid:%d)\n", x, (int) getpid());
    x=30;
  } else {
    int rc_wait = wait(NULL);
    printf("hello, I am parent of %d. X = %d, I will change x to 2. (rc_wait:%d) (pid:%d)\n", rc, x, rc_wait, (int) getpid());
    x = 2;
  }

  printf("X is: %d\n",x);

  return 0;
}
