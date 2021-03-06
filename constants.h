/*
Constants and Functions for smallsh Program
*/

// make sure header files are not compiled twice
#ifndef constants
#define constants

#include <stdlib.h> //exit
#include <stdio.h>  // printf, perror, fgets
#include <sys/types.h> // pid_t
#include <unistd.h> // getpid, getppid, chdir, execvp, dup2
#include <string.h> // strncmp
#include <sys/wait.h> // for waitpid
#include <sys/stat.h> // redirection.h, open
#include <fcntl.h> // redirection.h
#include <signal.h> // for signals, handler.h

/*
* Constants
*/
//shell supports inputString lines with max length of 2048 characters
# define MAXLEN 2048
// process inputString when status = 0
int status = 1;
// for use in built in status / statShell
int statusExit = 0;
// to store user's initial input
char inputString[MAXLEN];
// for token generation
char* savePtr;
// to store temporary string
char tempString[256];
// to store temporary integer
int tempInt = 0; 
// backgroud tracker
// is set to 1 when last word is &
int background = 0;
// when abnormalState = 1 commands with & run in foreground
int abnormalState = 0;
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
void resetShell(void);

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
int execute(void);

/* For built.h*/
// exit command
int exitShell(void);
// cd command
int cdShell(void);
// status command
int statShell(void);

/* For child.h*/
// executes a non-built in command
int runChild(void);
// exits process
void endProcess(int exited, int exitStat, int termSig, int print);

/* For redirection.h */
// output redirection
void outRed(void);
// input redirection
void inRed(void);
// both input and output redirection
void inOutRed(void);

/* For background.h */
// executes a non-built in command
// in background
int runBack(void);
// exits process
// in backgroud
void endBack(int exited, int exitStat, int termSig, int print);


/* For handler.h */
// indicates what must be done whe SIGTSTP is recognized
void handle_SIGSTP(int signo);
// set up for SIGINT
void invokeSIGINT(int signo);
// set up for SIGTSTP
void invokeSIGSTP(int signo); 


// end the condition for compilation of this header file
#endif