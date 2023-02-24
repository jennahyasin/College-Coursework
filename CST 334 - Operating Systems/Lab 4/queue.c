// FIFO queue to support FIFO page replacement policy simulation

#include <stdint.h>
#include <stdbool.h>
#include "queue.h"
#include "node.h"

/**
* Creates a new queue struct with head and tail equal to NULL
*/ 
struct queue* queue_create(){
    struct queue* temp = (struct queue*)malloc(sizeof(struct queue));
    temp->head = NULL;
    temp->tail = NULL;
    return temp;
}

/**
* Adds a node to the end of the queue
* q: the queue 
* data: the data to be added into the new node
* returns: a pointer to the node that was just added
*/
struct node* enqueue(struct queue* q, int data){
    struct node* tempNode = createNode(data); // Create a new node

    //Check if the head node has a value
    if (q->head == NULL){
        q->head = tempNode;
    } 
    //Check if the tail node has a value
    else if (q->tail == NULL){
        q->tail = tempNode;
        q->head->next = tempNode;
    } 
    //If the head and tail have values, add to the end
    else {
        q->tail->next = tempNode;
        q->tail = tempNode;
    }
    return tempNode;
}

/**
* Deletes the node at the beginning of the queue
* q: the queue 
*/
void dequeue(struct queue* q){
    struct node* headNode = q->head; // Get the head node
    
    if(headNode != NULL){
        q->head = getNodeNext(headNode);
        destroyNode(headNode);
    }
}

/**
* Gets the length of the queue by counting all the nodes
* q: the queue 
* returns: the length of the queue
*/
int queue_length(struct queue* q){
    struct node* currNode = q->head; // Start at the head
    int sum = 0;

    // Loop through the queue, counting each node
    while(currNode != NULL){
        sum++;
        currNode = getNodeNext(currNode);
    }
    return sum;
}

/**
* Traverses over the queue, printing the data from each node
* q: the queue 
*/
void queue_traverse(struct queue* q){
    struct node* currNode = q->head; // Start at the head
    int index = 0;

    // Loop through the queue, printing each node
    while(currNode != NULL){
        printf("%d %d\n", index, getNodeData(currNode));
        currNode = getNodeNext(currNode);
        index++;
    }
}

/**
* Deletes all nodes from the queue
* q: the queue 
*/
void queue_destroy(struct queue* q){
    struct node* currNode = q->head; // Start at the head
    struct node* nextNode; // Node to preserve the next value

    //Loop through the queue, destroying each node
    while(currNode != NULL){
        nextNode = getNodeNext(currNode);
        destroyNode(currNode);
        currNode = nextNode;
    }
    q->head = NULL;
}

/**
* Finds a particular node in the queue
* q: the queue 
* data: what node to search for based on its data
* returns: the node in the queue containing the given data or
* NULL if the data is not found
*/
struct node* queue_find(struct queue* q, int data){
    struct node* currNode = q->head; // Start at the head

    // Scan through queue to find data
    while(currNode != NULL){
        if(getNodeData(currNode) == data){
            return currNode;
        }
        // Move on to next node, if data is not found
        currNode = getNodeNext(currNode);;
    }
    // Data was not found, so return NULL
    return NULL;
}

