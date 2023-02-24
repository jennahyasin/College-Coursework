/*
# Name: Jennah Yasin
# Date: March 15, 2022
# Title: Lab 2 - Step 5
# Description: This program represents the child and parent processes.
*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]){
   pid_t pid;
   int i, n = atoi(argv[1]); //n microseconds to input from keyboard for delay
   printf("\n Before forking. \n");
   pid = fork();
   if(pid == -1) {
      fprintf(stderr, "can't fork, error %d\n", errno);
    }
   //Once the child is checked as processed, the parent is then processed
   else if(pid == 0) {
       execlp("/bin/ls", "ls", NULL);
       }

   else{
   //Child process
         wait(NULL);
         printf("Child Complete");
         exit(0);
          }
        return 0;
 }