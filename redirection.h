/*
* Handles Input & Output redirection
*/

#include "constants.h"


void inOutRed(void){
  // Citation: From Example: Output Redirection
  // Citation: From Example: Redirecting both Stdin and Stdout
  char *newFilePath = inFile;
  // open or create inputfile
  int sourceFD = open(newFilePath, O_RDONLY);
  // when file not found
  if (sourceFD == -1) {
    perror("source open()");
    exit(1);
  }
  // Use dup2 to point FD 0, i.e., standard input to sourceFD
  int result = dup2(sourceFD, 0);
  // when error in dup2
  if (result == -1) {
    perror("source dup2()"); 
    exit(1);
  }
  return;
}

void inRed(void){
  return;
}

void outRed(void){
  // Citation: From Example: Output Redirection
  char *newFilePath = outFile;
  // open or create output file
  int targetFD= open(newFilePath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  // when file not found
  if (targetFD == -1) {
    printf("open() failed on \"%s\"\n", newFilePath);
    exit(1);
  }
  // Use dup2 to point FD 1, i.e., standard output to targetFD
  int result = dup2(targetFD, 1);
  // when error in dup2
  if (result == -1) {
    perror("dup2"); 
    exit(1);
  }
  return;
}