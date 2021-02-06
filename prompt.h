/*
* display prompt
* get command from user
*/

#include "blank.h"
#include "expansion.h"
#include "parse.h"
#include "execute.h"
#include "handler.h"

void prompt(){
  
  // prompt runs until status is 1
  do {
    // initialize SIGNALS
    // 0 means ignore
    // sigint is ignored by parent Processes
    // yet the signal is sent to all parent and children
    invokeSIGINT(0);
    // sigstop is sent to all parent and children
    // parent has to acknowledge sigstop
    invokeSIGSTP(1);
    // Program Requirements
    // command line begins with :
    printf(": ");
    // Citation: Module4-Processes and I/O:
    // ensure standard output is displayed
    fflush(stdout);
    // get inputString from user 
    getinputString();
    //printf("bf: %s\n", inputString);
    //printf("af: %s\n", inputString);
    // tempInt stores if blank or comment is passed into prompt
    tempInt = checkComment() || checkBlank();

    // process input when non blank and non comment
    if (tempInt == 0){
      // replace $$ with pid
      padDollar();  
      // get pertinent information from inputString
      parseInput();
    }
    
    // status = 1 repeats prompt
    status = execute() ||  tempInt;

    // reset pertinent constant when shell repeats and input is not a blank or a comment
    if (tempInt == 1){
      continue;
    } else {
      resetShell();
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

void resetShell(void){
  // reset variables in the order they occur in constants.h
  memset(inputString, 0, strlen(inputString));
  memset(savePtr, 0, strlen(savePtr));
  memset(tempString, 0, strlen(tempString));
  background = 0;
  memset(command, 0, strlen(command));
  argFound = 0;
  memset(&arg, 0, 512);
  memset(inFile, 0, strlen(inFile));
  memset(outFile, 0, strlen(outFile));
  //statusExit = 0;
  tempInt = 0; 
  return;
}