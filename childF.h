/*
* Handles non-built in commands
*/

#include "redirection.h"
#include "handler.h"

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
      // any children running as foreground process
      //must terminate itself when it receives sig int
      invokeSIGINT(1);
      // foregound child must ignore sigtstp
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
      // Wait for child's termination
      // here 0 in control part of waitpid (where WNOHANG was in background wait pid) makes this a foreground process
      spawnPid = waitpid(spawnPid, &childStatus, 0);

      // Citation: Lecture on waitpid
      // with -1 waitpid waits for any child process
      // but with WNOHANG and no child termination waitpid immediately returns 0
      spawnPid = waitpid(-1, &childStatus, WNOHANG);
      // when a background process is terminated spawnPid > 0
      if (spawnPid > 0){
        // handle child termination
        printf("background pid %d is done: ", spawnPid);
        // Citation: from example "Interpreting the Termination Status"
        endProcess(WIFEXITED(childStatus), WEXITSTATUS(childStatus), WTERMSIG(childStatus));
        // print exit value
        if (statusExit != 0 && statusExit != 1){
          printf("terminated by signal %d\n", statusExit);
          fflush(stdout);
        } else{
          printf("exit value %d\n", statusExit);
          fflush(stdout);
        }
        break;
      }
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
