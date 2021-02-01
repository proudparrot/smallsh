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
  if (strcmp(command, "exit") == 0){
    return 0;
  }
  return 1;
}