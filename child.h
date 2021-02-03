/*
* Handles non-built in commands
*/


#include "constants.h"

int runChild(void){
  printf("forking time\n");
  // Citation: Code from lecture
  // Topic: creating and terminating process
  pid_t spawnpid = -5;
	int intVal = 10;
  // If fork is successful, the value of spawnpid will be 0 in the child, the child's pid in the parent
	spawnpid = fork();
	switch (spawnpid){
		case -1:
      // Code in this branch will be executed by the parent when fork() fails and the creation of child process fails as well
			perror("fork() failed!");
			exit(1);
			break;
		case 0:
      // spawnpid is 0. This means the child will execute the code in this branch
			intVal = intVal + 10;
			printf("I am the child! intVal = %d\n", intVal);
			break;
		default:
      // spawnpid is the pid of the child. This means the parent will execute the code in this branch
			intVal = intVal - 10;
			printf("I am the parent! ten = %d\n", intVal);
			break;
	}
	printf("This will be executed by both of us!\n");
  return 1;
}