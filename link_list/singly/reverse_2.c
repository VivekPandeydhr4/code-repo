#ifndef REVERSE_C_
#define REVERSE_C_
/******************************************************************/
#include "list.h"

node* reverse_iterate(node* head)
{
  node *t1=NULL, *t2=NULL;
  t1 = head;

  while(t1->next)
    {
      t2 = t1->next->next;
      t1->next->next = head;
      head = t1->next;
      t1->next = t2;
    }
  return head;
}

node* rev_first_k(node* head, int k)
{
  node *t1=NULL, *t2=NULL;
  int n=1;
  t1 = head;
  if (head) t2 = head->next;

  while (t2 && (n!=k))
    {
      t1->next = t2->next;
      t2->next = head;
      head = t2;
      t2 = t1->next;
      n++;
    }
  return head;
}

node* rev_k(node* head, int k)
{
  node *t1=NULL, *t2=NULL, *hd=NULL;
  int n=1, flag=1;
  t1 = head;
  if (head) t2 = head->next;

  hd = t1;
  while (t2 && (n!=k))
    {
      t1->next = t2->next;
      if (flag)
	t2->next = hd;
      else
	t2->next = hd->next;
      if (flag)
	hd = t2;
      else
	hd->next = t2;
      t2 = t1->next;
      n++;
      if (n==k)
	{
	  n=1;
	  hd = t1;
	  t1 = t1->next;
	  t2 = t1->next;
	  if (flag)
	    {
	      head = hd;
	      flag = 0;
	    }
	}
    }
  return head;
}

int main()
{
  int list_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int size = sizeof(list_data)/sizeof(int);
  node* head = create_list(list_data, size);
  printf("*** Original List ***\n");
  print_list(head);                                                                                                                
 
  head = rev_k(head, 3);
  printf("After Reverse\n");
  print_list(head);
  printf("\n");
  return 0;
}

/******************************************************************/
#endif
