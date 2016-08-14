#include "list.h"

node* alt_merge(node *hd1, node* hd2)
{
  node *t1=NULL, *t2=NULL, *t3=NULL;

  t1 = hd1;
  t2 = hd2;

  while(t1 && t2)
    {
      t3 = t1->next;
      t1->next = t2;
      t1 = t2;
      t2 = t3;
    }
  return hd1;
}

node* rec_alt_merge (node *hd1, node *hd2)
{
  node *tmp=NULL;

  if (hd1 && hd2)
    {
      tmp = rec_alt_merge (hd1->next, hd2->next);
      hd1->next = hd2;
      hd2->next = tmp;
    }
  return hd1;
}

int main()
{
  
  
  int list_data_1[] = {1, 3, 5, 7, 9, 11, 13};
  int size_1 = sizeof(list_data_1)/sizeof(int);

  int list_data_2[] = {2, 4, 6, 8, 10, 14};
  int size_2 = sizeof(list_data_2)/sizeof(int);

  node *list_1 = NULL, *list_2 = NULL;

  list_1 = create_list(list_data_1, size_1);
  list_2 = create_list(list_data_2, size_2);

  printf("\n");

  printf("Before Merge\n");

  printf("First List => ");
  print_list(list_1);

  printf("Second List => ");
  print_list(list_2);
  
  //  node* head = alt_merge(list_1, list_2);
  node* head = rec_alt_merge(list_1, list_2);
  printf("After Merge => ");
  print_list(head);
  
  printf("\n");
  return 0;
}
