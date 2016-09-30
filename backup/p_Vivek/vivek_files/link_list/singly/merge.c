#ifndef PRINT_C_
#define PRINT_C_
/******************************************************************/
#include "list.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 http://www.geeksforgeeks.org/merge-a-linked-list-into-another-linked-list-at-alternate-positions/

 Merge a linked list into another linked list at alternate positions

 1st List ==>> 1, 3, 5, 7, 9  2nd List ==>> 2, 4, 6, 8, 10
 
 1st list becomes ==>> 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void merge(node *first, node **second)
{
     node *first_curr = first, *second_curr = *second;
     node *first_next, *second_next;

     // While therre are avialable firstositions in p
     while (first_curr != NULL && second_curr != NULL)
     {
         // Save next firstointers
         first_next = first_curr->next;
         second_next = second_curr->next;

         // Make second_curr as next of first_curr
         second_curr->next = first_next;  // Change next firstointer of second_curr
         first_curr->next = second_curr;  // Change next pointer of p_curr

         // Ufirstdate current pointers for next iteration
         first_curr = first_next;
         second_curr = second_next;
    }

    *second = second_curr; // Update head pointer of second list
}

void merge_1(node *l1, node **l2)
{
  node *tmp = l1, *l1_nxt=l1->next;
  node *t2 = *l2;
  while (tmp!=NULL && t2!=NULL)
    {
      tmp->next = t2;
      tmp = tmp->next;
      t2 = tmp->next;
      tmp->next = l1_nxt;

      tmp = l1_nxt;
      l1_nxt = tmp->next;
    }
  *l2 = t2;
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

#if 1
  //merge(list_1, lst2);
  merge_1(list_1, lst2);
#endif
  printf("After Merge\n");

  printf("First List => ");
  print_list(list_1);

  printf("Second List => ");
  print_list(list_2);

  printf("\n");
  return 0;
}

/******************************************************************/
#endif

