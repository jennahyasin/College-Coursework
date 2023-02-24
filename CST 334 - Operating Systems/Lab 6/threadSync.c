/*
Name:Jennah Yasin
Date: April 12, 2022
Title: Lab 6 - Step 1
Description: This program handles two threads at a time where one 
enters thread is entered and the other is returned, right after one another. 
*/

/**********************************************************************************
 * *  334 Su 21 Lab6 Step 1                                                          *
*  Description: threadSync.c - simple multi-threaded program with sychronization. *
*  **********************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define NTHREADS 10
pthread_t threads[NTHREADS];
sem_t mutex;
   int sem_unlink(const char *name);
void *go(void *arg)
{   
   sem_wait(&mutex);
   printf("Thread %lu Entered Critical Section..\n", (size_t)arg);
   sleep(1);
   sem_post(&mutex);
   return (NULL);
}
int main()
{
   sem_open(&mutex, 0, 1);
   static int i;
   for (i = 0; i < NTHREADS; i++)
      pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
   for (i = 0; i < NTHREADS; i++)
   {
      pthread_join(threads[i], NULL);
      printf("Thread %d returned \n", i);
   }
   printf("Main thread done.\n");
   sem_unlink(&mutex);
   return 0;
}
