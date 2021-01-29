/*
* Displays the shell prompt.
* Gets Input from user
*/

void getCommand(void){
  //to store user's command
  //supports max 2048 characters 
  char command[2048];
  //user input is in command
  fgets(command, 2048, stdin);
  printf("%s\n", command);
  return;

}

void displayCommandPrompt(void){
  // Program Requirements
  // command line begins with :
  printf(": ");
  // Citation: Module4-Processes and I/O:
  // ensure standard output is displayed
  fflush(stdout);
  getCommand();
  return;
}