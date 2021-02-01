/*
Constants and Functions for smallsh Program
*/

// make sure header files are not compiled twice
#ifndef constants
#define constants

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


/*
* Support Functions
*/
// get command from user
void getCommand(void);
// returns 1 when command is empty
int checkBlank(void);
// returns 1 when command begins with #
int checkComment(void);
// replaces $$ with pid
void padDollar(void);



// end the condition for compilation of this header file
#endif