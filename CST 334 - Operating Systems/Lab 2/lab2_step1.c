/*
# Name: Jennah Yasin
# Date: March 15, 2022
# Title: Lab 2 - Step 1
# Description: This program represents the child and parent processes for Step 1
# of the lab 2 requirement before any changes.
*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pid_t  pid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay 
    printf("\n Before forking.\n");
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }
    if (pid){
        // Parent process 
        for (i=0;i<100;i++) {
           printf("\t \t \t Parent Process %d \n",i);
           usleep(n);
        }
   }
   else{
        // Child process 
        for (i=0;i<100;i++) {
           printf("Child process %d\n",i);
           usleep(n);
          }
   }
    return 0;
 }
