#include "list.h"

node *reverse(node *head)
{
  node *t1, *t2;

  t1 = head;
  
  while (t1->next)
    {
      t2 = t1->next;
      t1->next = t2->next;
      t2->next = head;
      head = t2;      
    }
  return head;
}

node* rev(node* head)
{
  node *list = head;

  if (head->next)
    {
      list = rev(head->next);    
      head->next->next = head;
      head->next = NULL;
    }
  return list;
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

node *mergepoint(node *hd1, node *hd2)
{
  node *t1=hd1, *t2=hd2;
  int cnt1=0, cnt2=0;

  while(t1->next && t2->next)
    {
      t1 = t1->next;
      t2 = t2->next;
    }

  if (t1->next == NULL)
    {
      while(t2->next)
	{
	  t2 = t2->next;
	  cnt2++;
	}
    }
  if (t2->next == NULL)
    {
      while (t1->next)
	{
	  t1 = t1->next;
	  cnt1++;
	}
    }
  if (t1 != t2) return NULL;

  t1 = hd1; t2 = hd2;

  if (cnt1 > 0)
    {
      while (cnt1 != 0)
	{
	  t1 = t1->next;
	  cnt1--;
	}
    }

  if (cnt2 > 0)
    {
      while (cnt2 != 0)
	{
	  t2 = t2->next;
	  cnt2--;
	}
    }

  while (t1 != t2)
    {
      t1 = t1->next;
      t2 = t2->next;
    }

  return t1;
}

int main()
{
  /**************************************************************/
  int list_data[] = {1, 4, 5, 7, 9, 3, 19, 15, 24, 30, 11, 18, 20};
  int size = sizeof(list_data)/sizeof(int);
  node* head = create_list(list_data, size);
  node* tmp = NULL;
  printf("\t\t *** Original List ***\n");
  print_list(head);
  printf("\n");
  /**************************************************************/

  /* Merge Point of two list 
  int l_data[] = {31, 35, 23, 55, 76};
  int l_size = sizeof(l_data)/sizeof(int), i=0, n=6;
  node* head2 = create_list(l_data, l_size);

  printf("\t\t *** First List ***\n");
  print_list(head);
  printf("\n");

  printf("\t\t *** Second List ***\n");
  print_list(head2);
  printf("\n");

  node *t1=head;
  i = 1;
  while(i != n)
    {
      i++;
      t1 = t1->next;
    }
  node *t2=head2;
  while(t2->next)
    {
      t2 = t2->next;
    }
  t2->next = t1;

  printf("\t\t *** After merge at %d position ***\n",n);
  printf("\t\t *** First List ***\n");
  print_list(head);
  printf("\n");

  printf("\t\t *** Second List ***\n");
  print_list(head2);
  printf("\n");

  printf("\n Merge point = %d", mergepoint(head, head2)->data);

  */
  /*
  node* clone = clone_list(head);
  printf("\n\t\t *** Clone List ***\n");
  print_list(clone);
  */
  printf("\n");
  return 0;
}
