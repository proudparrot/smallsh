#include <stdio.h>  // printf
#include <sys/types.h> // pid_t
#include <unistd.h> // getpid, getppid
#include "commandprompt.h"


int main(void) {
  commandPrompt();
  return 0;
}