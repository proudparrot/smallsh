/*
* parse inputString
* get pertinant information: 
* command
* arguments
* inputfile
* outputfile
* backgroud indicator
*/


#include "constants.h"

void parseInput(void){
  int i = 0;
  
  // command is made up of words separated by space
  char* token = strtok_r(inputString, " ", &savePtr);

  // if not comment or blank
  // first word is always a command
  strcpy(command, token);
  
  // separate parts of inputString and
  // place them in appropriate variables
  while (token != NULL) {
    // 0 means token can only be an argument
    argFound = 0;
    // look for input file
    setInFile(token);
    // look for output file
    setOutFile(token);
    // save current token in tempString
    strcpy(tempString, token);
    // go to next token
    token = strtok_r(NULL, " ", &savePtr);
    // look for backgroud indicator
    // only if at the end of inputString
    if (token == NULL){
      setBack(tempString, token);
    }
    // when none of the previous calls change argFound
    // token is part of argument
    if (argFound == 0){
      // copy tempString to argument array
      arg[i] = strdup(tempString);
      i++;
    }
  } 

  printf("%s\n", command);
  printf("%s\n", arg[4]);
  printf("%s\n", inFile);
  printf("%s\n", outFile);
  printf("%d\n", background);

  return;
}

/*
* changes background to 1 when & at the end
*/
void setBack(char* check, char* token){
  if (strcmp(check, "&") == 0){
    background = 1;
    // this token is not part of argument
    argFound = 1;
  }
  return;
}

/*
* saves the name of the input_file if present
*/
void setInFile(char* token){
  if (strcmp(token, "<") == 0){
    token = strtok_r(NULL, " ", &savePtr);
    strcpy(inFile, token);
    // this token is not part of argument
    argFound = 1; 
    return;
  }
  return;
}

/*
* saves the name of the output_file if present
*/
void setOutFile(char* token){
  if (strcmp(token, ">") == 0){
    token = strtok_r(NULL, " ", &savePtr);
    strcpy(outFile, token);
    // this token is not part of argument
    argFound = 1;
    return;
  }
  return;
}