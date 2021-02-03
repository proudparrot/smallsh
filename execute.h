/*
* redirects command to their pertinent function
*/

#include "built.h"
#include "child.h"

int execute(void){
  // when command is to exit
  if (strcmp(command, "exit") == 0){
    return exitShell();
    // when command is cd
  } else if (strcmp(command, "cd") == 0){
    return cdShell();
    // when command is status
  } else if (strcmp(command, "status") == 0){
    return statShell();
    // when comman is not built in
  } else{
    return runChild();
  }
  return 1;
}