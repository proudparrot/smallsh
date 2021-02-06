#include "constants.h"


/* replaces $$ with pid */
// commented printf statements there for testing.
void padDollar(void){
  // get pid
  char pid[10];
  sprintf(pid, "%d", getpid());
  //printf("%s\n", pid);
  int pidL = strlen(pid);
  //printf("%d\n", pidL);
  char* pidA[10];
  pidA[0] = strdup(pid);
  //printf("%s\n", pidA[0]);
  // to iterate over argument array
  int i;
  int j;
  int k;
  for (i=1; arg[i]; i++){
    //printf("%s\n", arg[i]);
    for (j=0; arg[i][j]; j++){
      //printf("%c\n", arg[i][j]);
      if (arg[i][j] == '$' && arg[i][j+1] == '$'){
        //printf("found $$\n");
        //printf("%c\n", arg[i][j-1]);
        //printf("%c\n", arg[i][j]);
        //printf("%c\n", arg[i][j+1]);
        //printf("%c\n", arg[i][j+2]);
        char* tempA[10];
        // empty space to add pid
        for (k = 0; k < pidL; k++){
          if (k < 2) {
            arg[i][j+k] = '\0';
            arg[i][j+k] = pidA[0][k];
          } else {
            tempA[0] = strdup(&arg[i][j+k]);
            arg[i][j+k] = '\0';
            arg[i][j+k] = pidA[0][k];
            //printf("%s\n", arg[i]);
            strcat(arg[i],tempA[0]);
            //snprintf(arg[i], 100, "%s%s", arg[i], tempA[0]);
          }
        }
        
      }
    }
    //printf("%s\n", arg[i]);    
  }
  return;
}