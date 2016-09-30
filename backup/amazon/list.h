#ifndef HEADER_H_
#define HEADER_H_
/*************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
  int data;
  struct NODE *next;
}node;

node* alloc_node(int num)
{
  node* newnode = (node*)malloc(sizeof(node));
  newnode->data = num;
  newnode->next = NULL;
  return newnode;
}

//int list_data[] = {1, 4, 5, 7, 9, 3, 19, 15, 24, 30, 11, 18, 20};


node* add_node(node* head, int num)
{
  node* temp;
  node* newnd = NULL;

  newnd = alloc_node(num);

  if (head == NULL) return newnd;

  for(temp=head; temp->next!=NULL; temp=temp->next);

  temp->next = newnd;

  return head;
}

node* create_list(int arr[], int size)
{
  node* head = NULL;
  int i=0;

  for(i=0; i<size; i++)
    head = add_node(head, arr[i]);
  return head;
}

void print_list (node* head)
{
  node* tmp = NULL;

  for(tmp=head; tmp!=NULL && tmp->next!=NULL; tmp=tmp->next)
    {
      printf("[%d]--> ", tmp->data);
    }
  if(tmp)
  printf("[%d]\n",tmp->data);
}

node* get_at_pos(node* head, int pos)
{
  node* temp = NULL;
  int i = 0;

  for (temp = head; temp != NULL; temp = temp->next)
    {
      i++;
      if (i >= pos)
	{
	  break;
	}
    }
  
  if (temp == NULL)
    {
      printf("Element does not exist at %d position\n",pos);
    }
  return temp;
}

void swap_node_data(node *a, node* b)
{
  int tmp = a->data;
  a->data = b->data;
  b->data = tmp;
}
/************************************************************/
#endif
