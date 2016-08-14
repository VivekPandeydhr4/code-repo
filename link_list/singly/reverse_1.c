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

node* rev_k(node *head, int k)
{
  node *tmp=NULL, *t1=NULL;
  int i=0;
  
  if (head)
    {
      tmp = head;
      i=1;
      while(i!=k && tmp->next!=NULL)
	{
	  i++;
	  tmp=tmp->next;
	}
      t1 = tmp->next;
      tmp->next = NULL;
      tmp = head;
      head = rev(head);

      t1 = rev_k(t1, k);
      tmp->next = t1;
    }
  return head;
}

int main()
{
  int list_data[] = {1, 4, 5, 7, 9, 3, 19, 15, 24, 30, 11, 18, 20, 23};
  int size = sizeof(list_data)/sizeof(int);
  node* head = create_list(list_data, size);
  node* tmp = NULL;
  printf("\t\t *** Original List ***\n");
  print_list(head);

  //  head = reverse(head);
  //head = rev(head);
  printf("\n\t\t *** Reversed K element of List ***\n");
  head = rev_k(head, 4);
  print_list(head);
  printf("\n");
  return 0;
}


node* append(node *head, int n)
{
  //  node *tmp = alloc_node(n);
  
  if(head)
    {
      head = append(head->next, n);
    }
  else
    {
      head = alloc_node(n);
    }
  return head;
}

