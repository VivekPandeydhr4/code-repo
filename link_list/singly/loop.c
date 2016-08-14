#ifndef LOOP_C_
#define LOOP_C_
/******************************************************************/
#include "list.h"

void make_loop(node* head, int pos)
{
  node* tmp = NULL;

  for (tmp = head; tmp != NULL && tmp->next != NULL; tmp = tmp->next);

  if (tmp)
    tmp->next = get_at_pos(head, pos);
    
}

int is_loop(node* head, node** psame)
{
  node *pSlow = NULL, *pFast = NULL;

  pSlow = head;
  pFast = (head) ? head->next : NULL;

  while (pSlow && pFast)
    {
      pSlow = pSlow->next;
      pFast = (pFast->next) ? pFast->next->next : pFast->next;
      if (pSlow == pFast)
	{
	  *psame = pSlow;
	  return 1;
	}
    }
  return 0;
}

node* find_merge_point(node* head)
{
  node *tmp=NULL, *tmp1=NULL, *psame=NULL;
  int i = 1;

  if (is_loop(head, &psame))
    {
      if (psame->next == psame || psame->next->next == psame) return psame;

      for (tmp=head; i != 0; tmp = tmp->next)
	{
	  for (tmp1=psame->next; tmp1!=psame; tmp1=tmp1->next)
	    {
	      if (tmp1 == tmp)
		{
		  i = 0;
		  return tmp;
		}
	    }
	}
    }
  printf("\nloop not found\n");
  return NULL;
}

int list_length(node* head)
{
  node* merge_point = find_merge_point(head);

  node *tmp=NULL;

  int count = 0, i = 1;

  if (merge_point)
    {
      for (tmp=head; tmp!=merge_point; tmp=tmp->next)
	{
	  count++;
	}
      count++;
      for (tmp=merge_point->next; tmp!=merge_point; tmp=tmp->next)
	{
	  count++;
	}
    }
  return count;
}

int check_loop(node* head)
{
  node *c=NULL, *b=NULL, *n=NULL;

  if (!head) return 0;
  if (head && !head->next) return 0;

  for (b=NULL, c=head, n=head->next; c; )
    {
      c->next = b;
      b = c;
      c = n;
      if (n) n = n->next;
    }
  if (b==head) return 1;
  else return 0;
}

int main()
{
  int list_data[] = {1, 4, 5, 7, 9, 3, 19, 15, 24, 30, 11, 18, 20};
  int size = sizeof(list_data)/sizeof(int);
  node* head = create_list(list_data, size);

  node* tmp=NULL;
  int i=0;
  printf("\n");
  print_list(head);

  make_loop(head, 5);
  /*for (i=0; i<size; i++)
    {
      printf("\n vkp = %d, %d\n", i, size);
      //make_loop(head, 1+1);
      //      printf("\nMerged Point = %d", (find_merge_point(head)) ? find_merge_point(head)->data : -1);
      }*/
  printf("\n");
  //print_list(head);
  printf("\nLoop found = %s\n ", (check_loop(head)) ? "YES" : "NO");
  printf("\nMerged Point = %d", (find_merge_point(head)) ? find_merge_point(head)->data : -1);
  printf("\nLoop length = %d", list_length(head));
  printf("\n");
  return 0;
}

/******************************************************************/
#endif
