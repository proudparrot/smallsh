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