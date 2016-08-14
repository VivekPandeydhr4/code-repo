#ifndef PRINT_C_
#define PRINT_C_
/******************************************************************/
#include "list.h"

# if 0
void print_list (node* head)
{
  node* tmp = NULL;

  for(tmp=head; tmp->next!=NULL; tmp=tmp->next)
    {
      printf("[%d]--> ", tmp->data);
    }
  printf("[%d]\n",tmp->data);
}

#endif
int main()
{
  int list_data[] = {1, 4, 5, 7, 9, 3, 19, 15, 24, 30, 11, 18, 20};
  int size = sizeof(list_data)/sizeof(int);
  node* head = NULL;
  
  head = create_list(list_data, size);

  printf("\n");
  print_list(head);

  printf("\n");
  return 0;
}

/******************************************************************/
#endif
