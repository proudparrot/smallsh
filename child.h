/*
* Handles non-built in commands
*/

#include "redirection.h"

int runChild(void){
  // Citation: Code from lecture example
  // Topic: using exec() with fork()
  int childStatus;
  // Fork a new process
  pid_t spawnPid = fork();

  switch(spawnPid){
    // fork return -1 when error during fork
    case -1:
      perror("fork()\n");
      exit(1);
      break;
    // successful fork returns 0
    // this means child process was created
    case 0:
      // In the child process
      // when both input and output files are given
      if (strcmp(inFile, "") != 0 && strcmp(outFile, "") != 0 ){
        inOutRed();
        // when only input is provided
      } else if (strcmp(inFile, "") != 0){
        inRed();
        // when only output is provided
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
        printf("back guy\n");
        // Citation: Example from lecture: Non-blocking Wait using WNOHANG
        // waitpid will wait for the child process with pid = spawnPid
        // termination status is placed in memory location pointed by childStatus
        // WNOHANG controls the behavior of waitpid. It makes waitpid non-blocking. The parent process is not blocked until child finishes. Hence we use it for background processes.
        pid_t backPid = waitpid(spawnPid, &childStatus, WNOHANG);
        // until no child process has waitpid with WNOHANG will return 0, so we use spawnPid to print background process's pid
        printf("background pid is %d\n", spawnPid);
        fflush(stdout);
      } else{
        printf("front guy\n");
        // Wait for child's termination
        // here 0 in control part of waitpid (where WNOHANG was in background wait pid) makes this a foreground process
        spawnPid = waitpid(spawnPid, &childStatus, 0);
        //printf("foreground pid is %d\n", spawnPid);
      }
      // Citation: Lecture on waitpid
      // with -1 waitpid waits for any child process
      // but with WNOHANG and no child termination waitpid immediately returns 0
      spawnPid = waitpid(-1, &childStatus, WNOHANG);
      // when a background process is terminated spawnPid > 0
      if (spawnPid > 0){
        printf("background pid %d is done: \n", spawnPid);
        // handle child termination
        // Citation: from example "Interpreting the Termination Status"
        endProcess(WIFEXITED(childStatus), WEXITSTATUS(childStatus), WTERMSIG(childStatus));
      } else {
        // handle child termination
        // Citation: from example "Interpreting the Termination Status"
        endProcess(WIFEXITED(childStatus), WEXITSTATUS(childStatus), WTERMSIG(childStatus));
      }  
      //printf("The process with pid %d is returning from main\n", getpid());
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
