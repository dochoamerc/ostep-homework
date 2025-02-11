#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  printf("hello world (pid:%d)\n",(int) getpid());
  int rc = fork();
  if(rc<0){
    fprintf(stderr,"fork failed\n");
    exit(1);
  } else if( rc==0) {
    printf("hello, I am child (pid:%d)\n", (int) getpid());
    char *myargs[] = {"ls","-l",NULL};
    execv("/bin/ls",myargs);
    printf("this shouldn't print out");
  } else {
    int rc_wait = wait(NULL);
    printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int)getpid());
  }
  return 0;
}
