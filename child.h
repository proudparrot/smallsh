/*
* Handles non-built in commands
*/


#include "redirection.h"
#include "background.h"

int runChild(void){
  // Citation: Code from lecture example
  // Topic: using exec() with fork()
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
      // check input and output files
      if (strcmp(inFile, "") != 0 && strcmp(outFile, "") != 0 ){
        inOutRed();
      } else if (strcmp(inFile, "") != 0){
        inRed();
      } else if (strcmp(outFile, "") != 0){
        outRed();
      }
      // Replace the current program with "command"
      execvp(arg[0], arg);
      // exec only returns if there is an error
      perror("execvp");
      exit(1);
      break;
    default:
      // In the parent process
      // handle background process
      if (background == 1){
        runBack();

      } else{
        printf("front guy\n");
      }
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
* update statusExit (used by built.h statShell)
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
