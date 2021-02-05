/*
* Handles Input & Output redirection
*/
// make sure header files are not compiled twice


#ifndef redirection
#define redirection

#include "constants.h"

void inOutRed(void){
  // Citation: From Example: Output Redirection
  // Citation: From Example: Redirecting both Stdin and Stdout
  char *newFilePath = inFile;
  // open or create inputfile
  int sourceFD = open(newFilePath, O_RDONLY);
  // when file not found
  if (sourceFD == -1) {
    printf("cannot open %s for input\n", newFilePath);
    fflush(stdout);
    exit(1);
  }
  // Use dup2 to point FD 0, i.e., standard input to sourceFD
  int result = dup2(sourceFD, 0);
  // when error in dup2
  if (result == -1) {
    perror("source dup2()"); 
    exit(1);
  }
  // Citation: From Example: Output Redirection
  char *newFilePath2 = outFile;
  // open or create output file
  int targetFD= open(newFilePath2, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  // when file not found
  if (targetFD == -1) {
    printf("cannot open %s for output\n", newFilePath2);
    fflush(stdout);
    exit(1);
  }
  // Use dup2 to point FD 1, i.e., standard output to targetFD
  int result2 = dup2(targetFD, 1);
  // when error in dup2
  if (result2 == -1) {
    perror("dup2"); 
    exit(1);
  }
  return;
}

void inRed(void){
  // Citation: From Example: Output Redirection
  // Citation: From Example: Redirecting both Stdin and Stdout
  char *newFilePath = inFile;
  // open or create inputfile
  int sourceFD = open(newFilePath, O_RDONLY);
  // when file not found
  if (sourceFD == -1) {
    printf("cannot open %s for input\n", newFilePath);
    fflush(stdout);
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

void outRed(void){
  // Citation: From Example: Output Redirection
  char *newFilePath = outFile;
  // open or create output file
  int targetFD= open(newFilePath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  // when file not found
  if (targetFD == -1) {
    printf("cannot open %s for output\n", newFilePath);
    fflush(stdout);
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

// end the condition for compilation of this header file
#endif