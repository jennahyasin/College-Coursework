//# 334 Su 20 Lab 4 data struct node definition

#include <stdio.h>
#include <stdlib.h>
#include "node.h"

struct node* createNode(int data){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

int getNodeData(struct node* n){
    return n->data;
}

struct node* getNodeNext(struct node* n){
    return n->next;
}

void destroyNode(struct node* n){
    free(n);
}