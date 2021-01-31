#include <stdio.h>  // printf, fgets
#include <sys/types.h> // pid_t
#include <unistd.h> // getpid, getppid
#include <string.h> // strncmp

/*
* Constants
*/
//shell supports command lines with max length of 2048 characters
# define MAXLEN 2048
// process command when status = 0
int status = 1;
// to store user's command
char command[MAXLEN];
//pid_t shid = getpid();

/*
* Support Functions
*/
// get command from user
void getCommand(void);
// returns 1 when command is empty
int checkBlank(void);
// returns 1 when command begins with #
int checkComment(void);


/*
* display prompt
* get command
*/
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


/*
* returns 1 when command line is empty
*/
int checkBlank(void){
  if (strncmp(command, "", 1) == 0 || strncmp(command, " ", 1) == 0 ){
    return 1;
  }else
  {
    return 0;
  }
}

/*
* returns 1 when command begins with #
*/
int checkComment(void){
  if (strncmp(command, "#", 1) == 0){
    return 1;
  }else
  {
    return 0;
  }
}