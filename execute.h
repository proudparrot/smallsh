/*
* redirects command to their pertinent function
*/

#include "built.h"
#include "childF.h"
#include "childB.h"

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
    // when command is not built in and running in background
  } else if (background == 1) {
    return runBack();
    // not built in
    // running in foreground
  } else {
    return runChild();
  }
  return 1;
}