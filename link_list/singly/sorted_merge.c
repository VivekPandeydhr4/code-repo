#include "list.h"

node* rec_sorted_merge (node *hd1, node *hd2)
{
  node *tmp=NULL;

  if (hd1 && hd2)
    {
      if (hd1->data < hd2->data)
	{
	  if (hd1->next)
	    tmp = rec_sorted_merge (hd1->next, hd2);
	  else
	    tmp = hd2;
	  hd1->next = tmp;
	  return hd1;
	}
      else
	{
	  if (hd2->next)
	    tmp = rec_sorted_merge (hd1, hd2->next);
	  else
	    tmp = hd1;
	  hd2->next = tmp;
	  return hd2;
	}
    }
  //  return hd1;
}

node* sorted_merge (node* hd1, node* hd2)
{
  if (hd1 && hd2 && 
      (hd2->data < hd1->data))
    {
      //      tmp = hd1-
    }
}

node* sum_list(node* hd1, node* hd2)
{

  node *tmp1, *tmp2;
  int sum1, sum2;

  if(!hd1) return hd2;
  if(!hd2) return hd1;

  sum1 = sum2 = 0;

  for (tmp1=hd1, tmp2=hd2; tmp1 && tmp2;)
    {
      if (tmp1->data < tmp2->data)
	{
	  sum1 += tmp1->data;
	  tmp1 = tmp1->next;
	}
      else if (tmp2->data < tmp1->data)
	{
	  sum2 += tmp2->data;
	  tmp2 = tmp2->next;
	}
      else break;
    }
  if(tmp1 && tmp2)
    {
      if (sum1 >= sum2)
	{
	  tmp1->next = sum_list(tmp1->next, tmp2->next);
	  return hd1;
	}
      else
	{
	  tmp2->next = sum_list(tmp1->next, tmp2->next);
	  return hd2;
	}
    }

  while(tmp1) {sum1 += tmp1->data; tmp1 = tmp1->next;}
  while(tmp2) {sum2 += tmp2->data; tmp2 = tmp2->next;}

  if (sum1 >= sum2) return hd1;
  else return hd2;
}

int main()
{
  
  
  int list_data_1[] = {1, 3, 4, 5, 7, 9, 10, 11, 13};
  int size_1 = sizeof(list_data_1)/sizeof(int);

  int list_data_2[] = {2, 4, 6, 7, 8, 10, 13, 14};
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
  //node* head = rec_sorted_merge(list_1, list_2);

  node* head = sum_list(list_1, list_2);
  printf("After Merge => ");
  print_list(head);
  
  printf("\n");
  return 0;
}
