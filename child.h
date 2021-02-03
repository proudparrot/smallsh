/*
* Handles non-built in commands
*/


#include "constants.h"

int runChild(void){
  // Citation: Code from lecture example
  // Topic: using exec() with fork()
  char *newargv[] = {command, arg[1], NULL};
  int childStatus;

  // Fork a new process
  pid_t spawnPid = fork();

  switch(spawnPid){
    case -1:
      perror("fork()\n");
      exit(1);
      break;
    case 0:
      // In the child process
      // Replace the current program with "command"
      execvp(newargv[0], newargv);
      // exec only returns if there is an error
      perror("execvp");
      exit(1);
      break;
    default:
      // In the parent process
      // Wait for child's termination
      spawnPid = waitpid(spawnPid, &childStatus, 0);
      // handle child termination
      // Citation: from example "Interpreting the Termination Status"
      endProcess(WIFEXITED(childStatus), WEXITSTATUS(childStatus), WTERMSIG(childStatus));
      break;
  } 
  return 1;
}


/*
* exits process
* Citation: from example "Interpreting the Termination Status"
*/
void endProcess(int exited, int exitStat, int termSig){
  if (exited){
    statusExit = exitStat;
  } else{
    statusExit = termSig;
  }
  return;
}