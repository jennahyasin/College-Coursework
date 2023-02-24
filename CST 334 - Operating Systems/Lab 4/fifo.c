/*
# Name: Jennah Yasin
# Date: March 28, 2022
# Title: Lab 4 - Source File 
# Description: This program works with the functions offered in the 
# queue.c program to calculate the number of faults and the hit rate
# of a run of a txt file with 10,000 entries with any size cache.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "queue.h"
#include "node.h"

struct queue* q; //in order to use queue.c file functions
typedef struct {//to 
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
        int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file
    q = queue_create(); //makes q object from queue.c
    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int requests=0; //keeps track of the total requests
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
    }
    while (fgets(pageCache, 100, stdin))
    {
        int page_num = atoi(pageCache); //Stores number read from file as int
        requests++;
        if(!queue_find(q, page_num))//if page is not found in cache, enqueue and increment totalFaults
        {
            if(queue_length(q) == C_SIZE)
            {
                dequeue(q);
            }
            enqueue(q, page_num);
            totalFaults++;
        }
    }
    //functions to make calculations easier
    int totalHits = requests-totalFaults; //calculates totalHits
    float hitRate =(float)totalHits/requests; //calculates hitRate decimal before percentage
    //Print statements for output  
    printf(" %d Total Accesses, ", requests);
    printf(" %d Total Hits , ",totalHits);
    printf(" %d Total Page Faults, ", totalFaults);
    printf(" %g %% Hit Rate.\n", hitRate*100);  //prints out hitRate percentage 
    queue_destroy(q);
    return 0;

}
