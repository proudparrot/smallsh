#include "constants.h"


/* replaces $$ with pid */
// commented printf statements there for testing.
void padDollar(void){
  // to iterate over ever char in inputString
  int cmdLen = strlen(inputString);
  //printf("in-cmdlen: %d\n", cmdLen);
  // to store temporary string
  char *padCmd;
  padCmd = malloc(50);
  //printf("in-bf-pcmd: %s\n", padCmd);
  // to store pid
  char id[50];
  // continues prompt if status is 1
  // meaning no blank lines and no comments (lines starting in #)
  // place pid in variable id
  sprintf(id, "%d", getpid());
  //printf("in-id: %s\n", id);
  // to iterate over inputString
  int i;
  // to track when $$ replaced
  int padTally = 0;
  //int idLen = strlen(id);
  //printf("in-tally1: %d - \n", padTally);
  // go through each char in inputString
  for (i=0; i<cmdLen;i++){
    //printf("in-i-test: %d - \n", i);
    // find $$
    if (inputString[i]=='$' && inputString[i+1]=='$'){
      //printf("here i1: %d\n", i);
      // concat id to temp string
      strncat(padCmd, id, strlen(id));
      //printf("in-af1-pcmd: %s\n", padCmd);
      // skip over $$ in inputString
      i++;
      //printf("here i2: %d\n", i);
      // track tally times
      padTally++;
      //printf("in-tally2: %d - \n", padTally);
    } else{
      // when no $$ replaced
      if (padTally == 0){
        // copy inputString as is
        padCmd[i] = inputString[i];
        //printf("in-af2-pcmd: %s\n", padCmd);
      } else{
        // add rest of the inputString after id replacement
        int padLen = strlen(padCmd);
        //printf("padLen: %d - \n", padLen);
        padCmd[padLen] = inputString[i];
        //printf("in-af3-pcmd: %s\n", padCmd);
      }
    }
  }
  // copy the padded string to inputString constant
  // place \0 at the end to signify end of string
  int j = strlen(padCmd);
  padCmd[j] = '\0';
  // clear inputString
  memset(inputString, 0, strlen(inputString));
  // move padCmd to inputString
  strcpy(inputString, padCmd);
  // reset padCmd memory
  free(padCmd);
  return;
}