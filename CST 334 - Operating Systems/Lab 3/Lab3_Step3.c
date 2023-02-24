/*
# Name: Jennah Yasin
# Date: March 22, 2022
# Title: Lab3 - Step 3
# Description: C Program for Lab 3 assignment, Step 3: 
# implements the pipe command: cat/etc/passwd | grep root
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
//main
int main() {
   int fds[2];
   pipe(fds);
   //child duplicates downstream into stdn
   if(fork() == 0) {
      dup2(fds[0], 0);
      close(fds[1]);

      execlp("grep", "grep", "root", 0);

   }
   //child 2 duplicates upstream into stdout
   else if(fork() == 0) {
       dup2(fds[1], 1);

       close(fds[0]);
       execlp("cat", "cat", "/etc/passwd", 0);

     }
     else {
         close(fds[0]);
         close(fds[1]);
         wait(0);
         wait(0);
     }

     return 0;
}