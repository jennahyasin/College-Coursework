/*
# Name: Jennah Yasin
# Date: April 5, 2022
# Title: Lab5 - Step 3
# Description : This program is an implementation of using threading
# in order to multiply two matrices with one another.
*/

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define N 1024 //# rows of matrix A
#define M 1024//# columns  matrix A & # rows matrix B
#define L 1024 //# colummns matrix B
#define NTHREADS N //# threads
pthread_t threads[NTHREADS];

double matrixA[N][M]; //initialize matrix A
double matrixB[M][L]; //initialize matrix B
double matrixC[N][L]; //initialize result matrix C

//this function references int i and calculates 
//the product of matrixA*matrixB which is matrixC.
void* matrixCalculation(void* arg)
{
   int i = *((int*)arg);
   //calculates row * column for each
   for (int j = 0; j < L; j++)
   {
      double temp = 0;
      for (int k = 0; k < M; k++)
      {
         temp += matrixA[i][k] * matrixB[k][j];
      } 
      matrixC[i][j] = temp;
   }
   pthread_exit(NULL);
}

//main function that prints out matrixA, matrixB, then calculates
// and displays matrixC.
int main() {
   srand(time(NULL));
   int pass[NTHREADS];
   //randomly generates two matrices with numbers between 0-9
   for(int i = 0; i < N; i++)
      for(int j = 0; j < M; j++)
      {
         matrixA[i][j] = rand() % 10;
         matrixB[i][j] = rand() % 10;
      }
   //prints out matrixA
   printf("\n");
   for(int i = 0; i < N; i++)
   {
      for(int j=0; j<M; ++j) 
      {
         if(j ==(M-1))
         {
             printf(" %g  ", matrixA[i][j]);
             printf("\n");
         } else {
           printf(" %g ", matrixA[i][j]);
           }
      }
   }

   //prints out matrixB
   printf("\n");
   for(int i = 0; i < M; i++)
   {
      for(int j = 0; j < L; ++j) 
      {
         if(j==(L-1))
         {
            printf(" %g  ", matrixB[i][j]);
            printf("\n");
         }
         else{
            printf(" %g ", matrixB[i][j]);
         }
      } 
   }

   //Make threads
   for(int i = 0; i<NTHREADS; i++)
   {
      pass[i]=i;
      pthread_create(&threads[i], NULL, matrixCalculation, &pass[i]);
   }

   //join threads
   for(int i = 0; i<NTHREADS; i++)
   {
      pthread_join(threads[i], NULL);
   } 

   //print out matrix C
   printf("\n");
   for(int i = 0; i < N; i++)
   {
      for(int j = 0; j < L; j++)
      {
         if(j==(L-1)){
            printf(" %g ", matrixC[i][j]);
            printf("\n");
         }
         else{
            printf(" %g ", matrixC[i][j]);
         }
      }
   }
}  
