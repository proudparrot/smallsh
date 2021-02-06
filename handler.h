#ifndef handler
#define handler

#include "constants.h"

/*
* Citation: Exploration: Signal Handling API
*/
// Citation: Example: Custom Handler for SIGINT
// signal handler for SIGTSTP
void handle_SIGSTP(int signo){
  char* msg_0 = "Exiting foreground-only mode\n";
  char* msg_1 = "Entering foreground-only mode (& is now ignored)\n";
  // switch state of program
  // 0 = foreground and background allowed
  // 1 = only foreground process allowed
  if (abnormalState == 0){
    abnormalState = 1;
    write(STDOUT_FILENO, msg_1, 50);
  } else if (abnormalState == 1){
    abnormalState = 0;
    write(STDOUT_FILENO, msg_0, 30);
  }
  return;
}

void invokeSIGINT(int signo){
  // initialize SIGINT_action struct to be empty
  struct sigaction SIGINT_action = {0};
  // fill struct
  // register signal handler
  // ignore SIGINT when signo = 0
  if (signo == 0){
    SIGINT_action.sa_handler = SIG_IGN;
  } else{
    // continue with default SIGINT behavior
    SIGINT_action.sa_handler = SIG_DFL;
  }
  
  // block all other signal while handle_SIGINT is running
  sigfillset(&SIGINT_action.sa_mask);
  // No flags set
  SIGINT_action.sa_flags = 0;
  // Install signal handler
  sigaction(SIGINT, &SIGINT_action, NULL);
  return;
}

void invokeSIGSTP(int signo){
  // initialize SIGSTP_action struct to be empty
  struct sigaction SIGSTP_action = {0};
  // fill struct
  // register signal handler
  // ignore SIGSTP when signo = 0
  if (signo == 0){
    SIGSTP_action.sa_handler = SIG_IGN;
  } else{
    // SIGSTP behavior determined by its handler
    SIGSTP_action.sa_handler = handle_SIGSTP;
  }
  
  // block all other signal while handle_SIGSTP is running
  sigfillset(&SIGSTP_action.sa_mask);
  // No flags set
  SIGSTP_action.sa_flags = 0;
  // Install signal handler
  sigaction(SIGTSTP, &SIGSTP_action, NULL);
  return;
}


#endif