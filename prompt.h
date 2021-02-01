/*
* display prompt
* get command from user
*/

#include "blank.h"
#include "parse.h"
#include "execute.h"

void prompt(){
  
  // prompt runs until status is 1
  do {
    // Program Requirements
    // command line begins with :
    printf(": ");
    // Citation: Module4-Processes and I/O:
    // ensure standard output is displayed
    fflush(stdout);
    // get inputString from user 
    getinputString();
    // check for comments
    // check for blank inputStrings
    // prompt repeats if either one is true
    status = checkComment() || checkBlank();
    if (status == 0){
      // replace $$ with pid
      padDollar();
      // get pertinent information from inputString
      parseInput();
      // handle commands
      execute();
    }
    
  } while (status == 1);
  return;
}

/*
* gets inputString from user
* removes newline
* Citation:
* https://stackoverflow.com
/questions/2693776/removing-trailing-newline-character-from-fgets-input
*/
void getinputString(void){
  // store input in inputString
  fgets(inputString, MAXLEN, stdin);
  // remove \n
  int i;
  for (i=0; i<strlen(inputString);i++){
    if (inputString[i] =='\n'){
      inputString[i] = '\0';
    }
  }
  return;
}