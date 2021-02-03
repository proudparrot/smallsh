#include "constants.h"


/* replaces $$ with pid */
void padDollar(void){
  // to iterate over ever char in inputString
  int cmdLen = strlen(inputString);
  // to store temporary string
  char padCmd[cmdLen*50];
  // to store pid
  char id[50];
  // continues prompt if status is 1
  // meaning no blank lines and no comments (lines starting in #)
  if (status == 1){
    return;
  } else{
    // place pid in variable id
    sprintf(id, "%d", getpid());
    // to iterate over inputString
    int i;
    // to track when $$ replaced
    int padTally = 0;
    //int idLen = strlen(id);

    // go through each char in inputString
    for (i=0; i<cmdLen;i++){
      // find $$
      if (inputString[i]=='$' && inputString[i+1]=='$'){
        // concat id to temp string
        strncat(padCmd, id, strlen(id));
        // skip over $$ in inputString
        i++;
        // track tally times
        padTally++;
      } else{
        // when no $$ replaced
        if (padTally == 0){
          // copy inputString as is
          padCmd[i] = inputString[i];
        } else{
          // add rest of the inputString after id replacement
          int padLen = strlen(padCmd);
          padCmd[padLen] = inputString[i];
        }
        }
      }
    }
  // copy the padded string to inputString constant
  strcpy(inputString, padCmd);
  
  return;
}