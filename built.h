/*
* Three Built-in commands
* 1) exit: exit shell
* 2) cd
* 3) status
*/


#include "constants.h"

/*
* when command is "exit"
* changes the status to 0
*/
int exitShell(void){
  return 0;
}

/*
* Handles cd command
* shell continues post execution
*/
int cdShell(void){
  // handle cases with no path argument
  if (arg[1] == NULL){
    // Citation: (getcwd) https://www.ibm.com/support/knowledgecenter/SSLTBW_2.2.0/com.ibm.zos.v2r2.bpxbd00/rtgtc.htm#rtgtc
    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    if (chdir(cwd) == -1){
      printf("System Error try again\n");
      // Citation: Module4-Processes and I/O:
      // ensure standard output is displayed
      fflush(stdout);
      return 1;
      }
    // prompt repeats
    return 1;
  } else{
    // two things at once
    // changes directory to path in arg[1]
    // if directory not found prints message to user
    if (chdir(arg[1]) == -1){
      printf("Not found\n");
      // Citation: Module4-Processes and I/O:
      // ensure standard output is displayed
      fflush(stdout);
      return 1;
    }
    // prompt repeats
    return 1;
  }
  return 1;
}

/*
* Handles status command
* shell continues post execution
*/
int statShell(void){
  printf("exit value %d\n", statusExit);
  fflush(stdout);
  return 1;
}