#ifndef HEADER_H_
#define HEADER_H_
/*************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
  int data;
  struct NODE *next;
  struct NODE *prev;
}node;

node* alloc_node(int num)
{
  node* newnode = (node*)malloc(sizeof(node));
  newnode->data = num;
  newnode->next = NULL;
  newnode->prev = NULL;
  return newnode;
}
/************************************************************/

#endif
