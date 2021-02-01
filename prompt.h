/*
* display prompt
* get command from user
*/

#include "constants.h"
#include "basic.h"

void commandPrompt(){
  
  // prompt runs until status is 1
  do {
    // Program Requirements
    // command line begins with :
    printf(": ");
    // Citation: Module4-Processes and I/O:
    // ensure standard output is displayed
    fflush(stdout);
    // get command from user 
    getCommand();
    // check for comments
    // check for blank commands
    // prompt repeats if either one is true
    status = checkComment() || checkBlank();
    // replace $$ with pid
    padDollar();
    printf("%s %d\n", command, getpid());
  } while (status == 1);
  return;
}

/*
* gets command from user
* removes newline
* Citation:
* https://stackoverflow.com
/questions/2693776/removing-trailing-newline-character-from-fgets-input
*/
void getCommand(void){
  // store input in command
  fgets(command, MAXLEN, stdin);
  // remove \n
  int i;
  for (i=0; i<strlen(command);i++){
    if (command[i] =='\n'){
      command[i] = '\0';
    }
  }
  return;
}