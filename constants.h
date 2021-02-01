/*
Constants and Functions for smallsh Program
*/

// make sure header files are not compiled twice
#ifndef constants
#define constants

#include <stdlib.h> //exit
#include <stdio.h>  // printf, fgets
#include <sys/types.h> // pid_t
#include <unistd.h> // getpid, getppid
#include <string.h> // strncmp

/*
* Constants
*/
//shell supports inputString lines with max length of 2048 characters
# define MAXLEN 2048
// process inputString when status = 0
int status = 1;
// to store user's initial input
char inputString[MAXLEN];
// for token generation
char* savePtr;
// to store temporary string
char tempString[256];
// backgroud tracker
// is set to 1 when last word is &
int background = 0;
// to store command
char command[256];
// to track if an argument was found during parsing
int argFound;
// to store arguments
char* arg[512];
// to store inputfile
char inFile[256];
// to store output file
char outFile[256];


/*
* Support Functions
*/

/* For prompt.h*/
// get inputString from user
void getinputString(void);

/* For blank.h*/
// returns 1 when inputString is empty
int checkBlank(void);
// returns 1 when inputString begins with #
int checkComment(void);
// replaces $$ with pid
void padDollar(void);

/* For parse.h*/
// set backgroud
void setBack(char* check, char* token);
// set inFile
void setInFile(char* token);
// set outFile
void setOutFile(char* token);

/* For execute.h*/
// redirect command to appropritate function
void execute(void);

/* For built.h*/
// exit shell
int exitShell(void);




// end the condition for compilation of this header file
#endif