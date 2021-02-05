/*
* Handles non-built in commands
* running in background
* Citation: adapted from child.h
*/

#include "redirection.h"
#include "handler.h"

int runBack(void){
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
      // background child ignores sigint
      invokeSIGINT(0);
      // background child must ignore sigtstp
      invokeSIGSTP(0);
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
      perror(arg[0]);
      exit(1);
      break;
    default:
      // In the parent process
      // handle background process
      // Citation: Example from lecture: Non-blocking Wait using WNOHANG
      // waitpid will wait for the child process with pid = spawnPid
      // termination status is placed in memory location pointed by childStatus
      // WNOHANG controls the behavior of waitpid. It makes waitpid non-blocking. The parent process is not blocked until child finishes. Hence we use it for background processes.
      // until no child process has waitpid with WNOHANG will return 0, so we use spawnPid to print background process's pid before calling waitpid
      printf("background pid is %d\n", spawnPid);
      fflush(stdout);
      // place spawnPid in an array of processes running in background
      spawnPid = waitpid(spawnPid, &childStatus, WNOHANG);
      // Citation: Lecture on waitpid
      // with -1 waitpid waits for any child process
      // but with WNOHANG and no child termination waitpid immediately returns 0
      spawnPid = waitpid(-1, &childStatus, WNOHANG);
      // when a background process is terminated spawnPid > 0
      if (spawnPid > 0){
        // handle child termination
        printf("background pid %d is done: ", spawnPid);
        // Citation: from example "Interpreting the Termination Status"
        endBack(WIFEXITED(childStatus), WEXITSTATUS(childStatus), WTERMSIG(childStatus));
        // print exit value
        printf("exit value %d\n", statusExit);
        fflush(stdout);
        break;
      }
      // handle child termination
      // Citation: from example "Interpreting the Termination Status"
      endBack(WIFEXITED(childStatus), WEXITSTATUS(childStatus), WTERMSIG(childStatus));
      break;
  } 
  return 1;
}

/*
* exits process
* update statusExit (used by built.h statShell)
* Citation: from example "Interpreting the Termination Status"
*/
void endBack(int exited, int exitStat, int termSig){
  if (exited){
    statusExit = exitStat;
  } else{
    statusExit = termSig;
  }
  return;
}