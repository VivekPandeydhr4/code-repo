#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODE
{
  int data;
  struct NODE *next;
  struct NODE *rand;
}node;

node* alloc_node(int num)
{
  node* newnode = (node*)malloc(sizeof(node));
  newnode->data = num;
  newnode->next = NULL;
  newnode->rand = NULL;
  return newnode;
}

void print_list(node *head)
{
  node *tmp=head;

  while(tmp)
    {
      printf("%2d ",tmp->data);
      tmp = tmp->next;
    }
}

void print_list_rand(node *head)
{
  node *tmp=head;

  while(tmp)
    {
      printf("%2d ",tmp->rand->data);
      tmp = tmp->next;
    }
}

node* create_list()
{
  int list_data[] = {1, 4, 5, 7, 9, 3, 19, 15, 24, 30, 11, 18, 20};
  int size = sizeof(list_data)/sizeof(int);
  int i=0;
  node *head = NULL;

  for (i=size-1; i>=0; i--)
    {
      node *alt = alloc_node(list_data[i]);
      if(head)
	  alt->next = head;
      head = alt;      
    }

  node *tmp = head;

  while(tmp)
    {
      int r = rand()%12;
      node *alt = NULL;
      for (i=1, alt=head; (i<=r+1) && (alt != NULL); i++, alt = alt->next);
      tmp->rand = alt;
      
      tmp = tmp->next;
    }
  return head;
}

node *clone_list(node* head)
{
  node *tmp = NULL;
  node *clone_head = NULL;
  node *clone_tail = NULL;

  tmp = head;
  while(tmp)
    {
      node *alt = alloc_node(tmp->data);
      if(tmp == head)
        {
          clone_head = alt;
          clone_tail = alt;
	}
      else
        {
          clone_tail->next = alt;
          clone_tail = alt;
        }

      tmp = tmp->next;
    }
  return clone_head;
}

void clone_rand(node* origin, node* clone)
{
  node *o_tmp=NULL, *c_tmp=NULL, *c2_tmp=NULL;

  for (o_tmp = origin, c2_tmp=clone; o_tmp; o_tmp = o_tmp->next, c2_tmp = c2_tmp->next)
    {
      for (c_tmp = clone; c_tmp->data != o_tmp->rand->data; c_tmp = c_tmp->next);
      c2_tmp->rand = c_tmp;
    }
}

void clone_rand_2(node* origin, node*clone)
{
  node *t=NULL, *t1=NULL, *t2=NULL;

  t = origin;
  if(origin) t1 = origin->next;
  t2  = clone;

  while(t2->next)
    {
      t->next = t2;
      t = t2->next;
      
      t2->next = t1;
      t2 = t;
      t = t1;
      t1 = t->next;
    }

  //  print_list(origin);

  printf("\n");

  t1 = origin;
  t2 = clone;

  while(t1->next)
    {
      //      if ()
      t2->rand = t1->rand->next;
      t1 = t2->next;
      t2 = t1->next;
    }

  t1 = origin;
  t2 = clone;

  while(t2->next)
    {
      t1->next = t2->next;
      t1 = t2;
      t2 = t1->next;
    }

}

int main()
{
  node *head = create_list();

  node * clone = clone_list(head);
  clone_rand_2(head, clone);

  printf("\n\t *** Original Random *** \n");
  print_list(head);
  //  printf("\n");

  printf("\n\n\t *** Original List Random *** \n");
  print_list_rand(head);

  printf("\n\n\t *** Clonned List *** \n");
  print_list(clone);

  printf("\n\n\t *** Clonned List Random *** \n");
  print_list_rand(clone);

  printf("\n");

  return 0;
}

