/*
Carries out basic processes on inputString
1) checks for blank lines
2) checks for comments
  2a) lines that begin with #
3) pads $$ with pid
*/

#include "constants.h"

/*
* returns 1 when inputString line is empty
*/
int checkBlank(void){
  if (strncmp(inputString, "", 1) == 0 || strncmp(inputString, " ", 1) == 0 ){
    return 1;
  }else
  {
    return 0;
  }
}

/*
* returns 1 when inputString begins with #
*/
int checkComment(void){
  if (strncmp(inputString, "#", 1) == 0){
    return 1;
  }else
  {
    return 0;
  }
}

/* replaces $$ with pid */
void padDollar(void){
  // to iterate over ever char in inputString
  int cmdLen = strlen(inputString);
  // to store temporary string
  char padCmd[cmdLen+50];
  // to store pid
  char id[5];
  // continues prompt is status is 1
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
        strcat(padCmd, id);
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