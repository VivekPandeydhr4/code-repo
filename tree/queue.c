#ifndef QUEUE_C_
#define QUEUE_C_

#include "header.h"

typedef struct queue_node
{
  node *element;
  struct queue_node *next;
}quend;

typedef struct queue
{
  quend *head;
  quend *tail;
}queue;

void enq(queue *q, node *nd)
{
  quend *nwnd = (quend*)malloc(sizeof(quend));
  nwnd -> element = nd;
  nwnd -> next = NULL;

  if(!q->head) q->head = q->tail = nwnd;
  else{
    q->tail->next=nwnd;
    q->tail=nwnd;
  }
}

node* deq(queue *q)
{
  quend *temp;
  node *alt = NULL;
  if(q->head){

    temp = q->head;
    q->head = q->head->next;
    if(q->head==NULL) q->tail = NULL;
    alt = temp->element;
    free(temp);
  }
  return alt;
}

#endif
