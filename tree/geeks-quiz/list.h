#ifndef LIST_H_
#define LIST_H_
/*************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct LNODE
{
  int data;
  struct LNODE *next;
}lnode;

lnode* alloc_node(int num)
{
  lnode* newnode = (lnode*)malloc(sizeof(lnode));
  newnode->data = num;
  newnode->next = NULL;
  return newnode;
}

//int list_data[] = {1, 4, 5, 7, 9, 3, 19, 15, 24, 30, 11, 18, 20};


lnode* add_node(lnode* head, int num)
{
  lnode* temp;
  lnode* newnd = NULL;

  newnd = alloc_node(num);

  if (head == NULL) return newnd;

  for(temp=head; temp->next!=NULL; temp=temp->next);

  temp->next = newnd;

  return head;
}

lnode* create_list(int arr[], int size)
{
  lnode* head = NULL;
  int i=0;

  for(i=0; i<size; i++)
    head = add_node(head, arr[i]);
  return head;
}

void print_list (lnode* head)
{
  lnode* tmp = NULL;

  for(tmp=head; tmp!=NULL && tmp->next!=NULL; tmp=tmp->next)
    {
      printf("[%d]--> ", tmp->data);
    }
  if(tmp)
  printf("[%d]\n",tmp->data);
}

void delete_last_node(lnode *head)
{
  lnode* temp;
  if (head == NULL) return;
  if (head->next == NULL) 
    {
      free(head);
      head->next = NULL;
    }
  for(temp=head; temp->next && temp->next->next; temp=temp->next);
   
      free(temp->next);  	
      temp->next = NULL;
}
lnode* get_at_pos(lnode* head, int pos)
{
  lnode* temp = NULL;
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
/************************************************************/
#endif
