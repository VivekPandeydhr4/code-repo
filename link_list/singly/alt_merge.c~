#include "list.h"

node* sorted_merge (node *hd1, node *hd2)
{
  node *t1=hd1, *t2=hd2, *t3=NULL;
  node *t4=NULL, *head=NULL;
  if (hd1->data > hd2->data)
    {
      t1 = hd2;
      t2 = hd1;
    }

  head = t1;
  
  while (t1 && t2)
    {
      t3 = t1->next;

      while ((t3 && t2) && 
	     t3->data < t2->data)
	{
	  t1 = t3;
	  t3 = t3->next;
	}
      t1->next = t2;
      t1 = t2;
      t2 = t3;
    }
  return head;
}

node* front_back_split(node *head)
{
  node *t1=head, *t2=NULL;
  if (head) t2 = t1->next;

  while (t2 && t2->next)
    {
      t1 = t1->next;
      t2 = t2->next->next;
    }
  t2 = t1->next;
  t1->next = NULL;
  return t2;
}

node* merge_sort(node *head)
{
  node *t1=NULL, *t2=NULL, *t3=NULL;

  if (head->next == NULL) return head;
  t1 = front_back_split(head);
  
  t2 = merge_sort(head);
  t3 = merge_sort(t1);
  
  node *t = sorted_merge(t2, t3);
  return t;
}
int main()
{
  
  int data[] = {2, 1, 4, 3, 12, 5, 8, 7, 10, 9, 23, 11, 13};
  int size = sizeof(data)/sizeof(int);
  node *head1 = create_list(data, size);

  printf("Original List => ");
  print_list(head1);

  printf("\n");
  head1 = merge_sort(head1);

  printf("Sorted List => ");
  print_list(head1);
  
  /*
  int list_data_1[] = {1, 2};//, 5, 7, 9, 11, 13};
  int size_1 = sizeof(list_data_1)/sizeof(int);

  int list_data_2[] = {3, 4};//, 6, 8, 10};
  int size_2 = sizeof(list_data_2)/sizeof(int);

  node *list_1 = NULL, *list_2 = NULL;
  //node **lst2 = &list_2;
  list_1 = create_list(list_data_1, size_1);
  list_2 = create_list(list_data_2, size_2);

  printf("\n");

  printf("Before Merge\n");

  printf("First List => ");
  print_list(list_1);

  printf("Second List => ");
  print_list(list_2);

  node* head = sorted_merge(list_1, list_2);
  printf("After Merge => ");
  print_list(head);
  
  node* hd = front_back_split(head);

  printf("Front List => ");
  print_list(head);

  printf("Back List => ");
  if (hd)
    print_list(hd);
  else
    printf("NULL Not present\n");
  */
  printf("\n");
  return 0;
}
