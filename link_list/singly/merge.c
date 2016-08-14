#include "list.h"

node* sorted_merge(node *hd1, node *hd2)
{
  node *t1 = hd1, *t2=hd2, *t3=NULL;
  node *head = NULL;

  if (hd2->data < hd1->data)
    {
      t1 = hd2;
      t2 = hd1;
    }
  head = t1;
  t3 = t2;
  while (t1->next && t3 && (t3->data < t1->next->data))
    {
      t3 = t3->next;
    }

}


int main()
{
  int list_data_1[] = {1, 3, 5, 7, 9, 11, 13};
  int size_1 = sizeof(list_data_1)/sizeof(int);

  int list_data_2[] = {2, 4, 6, 8, 10};
  int size_2 = sizeof(list_data_2)/sizeof(int);

  node *list_1 = NULL, *list_2 = NULL;
  node **lst2 = &list_2;
  list_1 = create_list(list_data_1, size_1);
  list_2 = create_list(list_data_2, size_2);

  printf("\n");

  printf("Before Merge\n");

  printf("First List => ");
  print_list(list_1);
  
  printf("Second List => ");
  print_list(list_2);

  printf("After Merge\n");

  printf("\n");
  return 0;
}


