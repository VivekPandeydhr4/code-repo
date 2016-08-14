#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
  int x, y;
  struct NODE* next;
}node;

node* add_node(node* head, int a, int b)
{
  node* temp;

  node* newnode = (node*) malloc(sizeof(node));
  newnode->x = a;
  newnode->y = b;
  newnode->next = NULL;

  if (head == NULL) return newnode;

  for(temp=head; temp->next!=NULL; temp=temp->next);

  temp->next = newnode;

  return head;
}

node* create_list(int arr[][2], int size)
{
  node* head = NULL;
  int i=0;

  for(i=0; i<size; i++)
    head = add_node(head, arr[i][0], arr[i][1]);
  return head;
}

void print_list (node* head)
{
  node* tmp = NULL;

  for(tmp=head; tmp!=NULL && tmp->next!=NULL; tmp=tmp->next)
    {
      printf("(%d, %d)--> ", tmp->x, tmp->y);
    }
  if(tmp)
    printf("(%d, %d)\n",tmp->x, tmp->y);
}

/* http://www.geeksforgeeks.org/given-linked-list-line-segments-remove-middle-points/ */

node* rem_mid_of_strt_line (node* head)
{
  node *start=NULL, *tmp=NULL;
  int turn = 0;
  char ch_coord;
  start = head;
  if (start) tmp = start->next;
  
  if (start->x == tmp->x) ch_coord = 'y';
  else ch_coord = 'x';

  while(tmp && tmp->next)
    {
      if ((ch_coord == 'y') && (tmp->y == tmp->next->y))
	{
	  turn = 1;
	  ch_coord = 'x';
	}
      if ((ch_coord == 'x') && (tmp->x == tmp->next->x))
	{
	  turn = 1;
	  ch_coord = 'y';
	}

      if (turn)
	{
	  start = tmp;
	  turn = 0;
	}
      else
	{
	  start->next = tmp->next;
	  free(tmp);
	}
      tmp = start->next;
    }
  return head;
}

node* rem_mid_of_strt_line_1 (node* head)
{
  node *start=NULL, *tmp=NULL;

  start = head;
  if (start) tmp = start->next;

  while(tmp && tmp->next)
    {
      if (((start->x == tmp->x) && (tmp->x != tmp->next->x))
	  ||((start->y == tmp->y) && (tmp->y != tmp->next->y)))
	{
	  start = tmp;
	}
      else
	{
	  start->next = tmp->next;
	  free(tmp);
	}
      tmp = start->next;
    }
  return head;
}

void remove_midPoints(node *head)
{
  int z;
  node *start,*temp;
  start=head;

  while(start && start->next)
    {      
      if(start->x==start->next->x) z=0;
      else if(start->y==start->next->y) z=1;
      else {start=temp->next; continue;}
      
      temp=start->next;
      while(temp->next && *(((int*)(temp->next))+z)==*(((int*)(start))+z))
	{
	  start->next=temp->next;
	  free(temp);
	  temp=start->next;
	}
      start=temp->next;
    }
}
int main ()
{
  /*  int arr[][2] = {
                  {1, 2}, {1, 4}, {1, 5}, {1, 6}, 
                  {3, 6}, {5, 6}, {6, 6}, {9, 6},
                  {9, 7}, {9, 10}, {9, 12}, {9, 15},
                 };
  */
  int arr[][2] = {
    {0, 10}, {1, 10}, {5, 10}, {7, 10}, {7, 5}, {20, 5}, {40, 5}
                 };
  int size = sizeof(arr)/sizeof(arr[0]);

  node *head = create_list (arr, size);
  printf("\n\t\t **** Original List ****\n");
  print_list(head);

  //head = rem_mid_of_strt_line_1 (head);
  remove_midPoints(head);
  printf("\n\t\t **** New List ****\n");
  print_list(head);

  printf("\n");
  return 0;
}



