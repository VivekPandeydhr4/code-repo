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

/*************************(( 2 ))*******************************
 Given a linked list, reverse alternate nodes and append them 
 to end of list. Extra allowed space is O(1)
 
 Examples:-

 Input List:  1->2->3->4->5->6
 Output List: 1->3->5->6->4->2

 Input List:  12->14->16->18->20
 Output List: 12->16->20->18->14
***************************************************************/
node* alt_reverse_iterate(node* head)
{
  node *hd2=NULL, *t1=NULL, *t2=NULL;

  if (head)
    {
      hd2 = head->next;
    }
  t1 = head;
  t2 = hd2;

  while (t2 && t2->next)
    {
      t1->next = t2->next;
      t1 = t1->next;
      t2 = t1->next;
    }
}

node* two_rev(node* head)
{
  node *t1=NULL, *t2=NULL;

  t1 = head;
  if (head->next)
    {
      t2 = head->next;
      head = t2;
    }

  while(t1 && t2)
    {
      t1->next = t2->next;
      t2->next = t1;
      t1 = t1->next;
      t2 = t2->next;
      if (t1) 
	{
	  if (t1->next)
	    t2->next = t1->next;
	  t2 = t1->next;
	}
    }
  return head;
}

node* rev(node* head)
{
  node *t1=NULL, *t2=NULL;

  t1 = head;
  if (head)
    {
      t2 = head->next;
    }
  while(t1 && t2)
    {
      t1->next = t2->next;
      t2->next = head;
      head = t2;
      t2 = t1->next;
    }
  return head;
}
node* rec_rev(node* head)
{
  node *t1=head;
  if (head->next)
    {
      t1 = rec_rev(head->next);
      head->next->next = head;
      head->next = NULL;
    }
  return t1;
}

node* rec_two_rev (node* head)
{
  node* t1=NULL, *t2=NULL, *list=NULL;

  t1 = head;
  
  if (t1 && t1->next)
    {
      t2 = t1->next;
      head = t2;
      if (t2->next)
	list = rec_two_rev(t2->next);
    }
  if (t2)
    t2->next = t1;
  if (t1)
    t1->next = list;
  return head;
}

int main()
{
  int list_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int size = sizeof(list_data)/sizeof(int);
  node* head = create_list(list_data, size);

  print_list(head);                                                                                                                
  //head = reverse_iterate(head);
  //head = alt_reverse_iterate(head);
  //head = two_rev(head);
  //head = rev(head);
  //head = rec_rev(head);
  head = rec_two_rev(head);
  printf("After Reverse\n");
  print_list(head);
  printf("\n");
  return 0;
}

/******************************************************************/
#endif
