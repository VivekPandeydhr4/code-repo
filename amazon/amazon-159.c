#include "array.h"
#include "list.h"

int find_sum(int arr[], int size, int sum)
{
  int i, j;

  for (i=0; i<size; i++)
    {
      for (j=0; j<size; j++)
	{
	  if ((i!=j) && (arr[i]+arr[j] == sum))
	    {
	      printf("[%d] + [%d] = [%d]\n", arr[i], arr[j], sum);
	      return 1;
	    }
	}
    }
  return 0;
}

node *sort_0_1_list (node *head)
{
  node *tmp1=NULL, *tmp0=NULL; 

  tmp1 = head;
  if (head)
    tmp0 = head->next;
  while (tmp1 && tmp0)
    {
      while (tmp1 && (tmp1->data != 1))
	{
	  tmp1 = tmp1->next;
	}
      
      tmp0 = tmp1->next;
      while (tmp0 && (tmp0->data != 0))
	{
	  tmp0 = tmp0->next;
	}

      if (tmp0 && tmp1 && !tmp0->data && tmp1->data)
	{
	  swap_node_data(tmp1, tmp0);
	  tmp1 = tmp1->next;
	  tmp0 = tmp0->next;
	}
    }
  return head;
}

int main()
{
  /* 2nd Round Q:2 */

  int arr[] = {0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0};

  node* head = create_list(arr, ARR_SIZE(arr));

  printf("\t\t *** Original list *** \n");
  print_list(head);
  head = sort_0_1_list(head);

  printf("\n\t\t *** Sorted list *** \n");
  print_list(head);

  /*** Telephonic Round Q:2 ***/
  /*
  int arr[] = {3, 2, 4, 6, 7, 11, 5, 10, 13, 8};

  print(arr, ARR_SIZE(arr));

  if (!find_sum(arr, ARR_SIZE(arr), 26))
    printf("No pair found\n");
  */
  return 0;
}

