/*
Name:Jennah Yasin
Date: April 12, 2022
Title: Lab 6 - Step 2
Description: This program takes two separate threads to implement
the producer-consumer problem that ultimately outputs the alphabet.
One thread uses produce to fill the buffer and the other uses consume
to empty out the buffer for the next letter of the alphabet. 
*/

//Shared data: semaphore full, empty, mutex;
//pool of n buffers, each can hold one item
//mutex provides mutual exclusion to the buffer pool //empty and full count the number of empty and full buffers 
//Initially: full = 0, empty = n, mutex = 1
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 26
#define BufferSize 1
pthread_t threads[2];

char letters[NTHREADS];
char buffer[26];
int fill = 0;
int use = 0;

sem_t empty;
sem_t full;
sem_t mutex;

void put(int value)
{
   buffer[fill] = value;
   fill = (fill+1) % 26;
}
int get()
{
   int tmp = buffer[use];
   use = (use + 1) % 26;
   return tmp;
}

//Producer thread
void * producer(void *arg)
{
    int i;
    for(char alpha = 'A'; alpha <= 'Z'; alpha++)
    {
      sem_wait(&empty); //waits for buffer to be empty first
      sem_wait(&mutex);

      put(alpha); //adds the letter tot the buffer

      printf("Producer Thread %lu :: %c >> buffer \n" , pthread_self(), alpha);

      sem_post(&mutex); 
      sem_post(&full); //signal that buffer is now full
   } 
   return NULL;
}


void *consumer(void *arg)
{
   //Consumer thread
   int tmp = 0;
   while(tmp != 90) //until it isn't Z (90 ASCII # for Z)
   {
      sem_wait(&full); //checks if buffer is full
      sem_wait(&mutex);

      tmp = get(); // remove next item from buffer ...

      printf("Consumer thread %lu :: buffer >> %c\n", pthread_self(), tmp);

      sem_post(&mutex);
      sem_post(&empty); //empties the bfufer
} 
  return NULL;
}

int main()
{
   sem_init(&mutex, 0, 1);
   sem_init(&empty, 0, BufferSize);
   sem_init(&full, 0, 0);

   int i = 0;
   //prints out all letters of the alphabet
   printf("Contents of letter array: ");
   for(char alphabet = 'A'; alphabet <= 'Z'; ++alphabet){
      letters[i] = alphabet;
      printf("%c ", letters[i]);
      i++;
   }
   //creates the two threads 
   pthread_create(&threads[0], NULL, producer, NULL);
   pthread_create(&threads[1], NULL, consumer, NULL);
   
   //joins the two threads
   pthread_join(threads[0], NULL);
   printf("Producer Thread %lu :: Ended. \n");

   pthread_join(threads[1], NULL);
   printf("Consumer Threads %lu :: Ended. \n");

   printf("Program Completed");
   //destroys all semaphore positions
   sem_destroy(&mutex);
   sem_destroy(&full);
   sem_destroy(&empty);
   
 return 0;
}