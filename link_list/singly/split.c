#ifndef PRINT_C_
#define PRINT_C_
/******************************************************************/
#include "list.h"


/* ~~~~~~~~~~~~~~~~~~~~~~~~~ *** 111 *** ~~~~~~~~~~~~~~~~~~~~~~~~~~
   Front back split of singly link list
   {1, 2, 3, 4, 5, 6} ==> {1, 2, 3} & {4, 5, 6}
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void front_back_split(node *list, node **front, node **back)
{
  node *p_slow = NULL, *p_fast = NULL;

  if (list == NULL)
    {
      printf("Empty List\n");
      return;
    }
  else if (list->next == NULL)
    {
      printf ("List contain only one node\n");
      return;
    }
  else
    {
      p_slow = list;
      p_fast = list->next;
      
      while (p_fast !=NULL && p_fast->next !=NULL)
	{
	  //p_slow = (p_fast->next) ? p_slow->next : NULL;
	  p_slow = p_slow->next;
	  //p_fast = (p_fast->next) ? p_fast->next->next : NULL;
	  p_fast = p_fast->next->next;
	}
      *front = list;
      *back  = p_slow->next; 
      p_slow->next = NULL;
    }

  return;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~ *** 222 *** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Alternate split of singly link list                           
   {1, 2, 3, 4, 5, 6, 7, 8, 9, 10} ==> {1, 3, 5, 7, 9} & {2, 4, 6, 8, 10}                    
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void alternate_split(node *list, node **odd, node **even)
{
  node *tmp = list;
  node *tmp2 = (tmp)? tmp->next: NULL ;
  *odd = tmp;
  *even = tmp2;
  while ((tmp!=NULL && tmp->next!=NULL) && (tmp2!=NULL && tmp2->next!=NULL))
    {
      tmp->next = tmp2->next;
      tmp = tmp->next;

      tmp2->next = tmp->next;
      tmp2 = tmp2->next;
    }
   if (tmp->next) tmp->next = NULL;
   if (tmp2->next) tmp2->next = NULL;

  return;
}

int main()
{
  int list_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
  int size = sizeof(list_data)/sizeof(int);
  node* head = create_list(list_data, size);
  node *front = NULL, *back = NULL;
  
  printf("\nInitial List => ");
  print_list(head);

#if 0 // Front Back Split
  
  front_back_split(head, &front, &back);

  printf("\n\t\t *** After Split *** \n");

  printf("\nFront List => ");
  print_list(front);

  printf("\nBack List => ");
  print_list(back);

#endif

#if 1  // Alternate Split

  alternate_split(head, &front, &back);

  printf("\n\t\t *** After Split *** \n");

  printf("\nOdd List => ");
  print_list(front);

  printf("\nEven List => ");
  print_list(back);

#endif

  printf("\n");
  return 0;
}

/******************************************************************/
#endif
