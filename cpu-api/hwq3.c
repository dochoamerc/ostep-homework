#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static int status = 0;
  
int main(int argc, char *argv[]) {
  printf("forking:\n\n");

  int pipeW[2];
  int pipeR[2];
  if(pipe(pipeW) == -1 || pipe(pipeR) == -1) {
    fprintf(stderr,"Pipe failed");
    return 1;
  }
  
  int rc = fork();
  
  if(rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {//child
    close(pipeW[0]);//close reading 
    write(pipeW[1], "hello",6); //child writes hello
    close(pipeW[1]);
    exit(0);
  } else {
    char fullString[100];
    close(pipeW[1]); //close writing
    read(pipeW[0], fullString, 100);
    close(pipeW[0]);

    printf("%s",fullString);
    fprintf(stderr,"goodbye");
  }
  return 0;
}
