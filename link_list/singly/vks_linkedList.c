#include "list.h"

node* swap_data(node *head, int a, int b)
{
  node *temp=NULL, *first=NULL, *second=NULL;
  node *prev=NULL, *prev2=NULL, *t1=NULL, *t2=NULL;

  for(temp=head; temp; prev=temp, temp=temp->next)
    if (temp->data == a || temp->data == b) break;

  if (!temp) return head;
  
  first = temp;
  for (prev2 = temp, temp = temp->next; temp;
       prev2 = temp, temp = temp->next)
    if (temp->data == a || temp->data == b)
      break;

  if (!temp) return head;

  second = temp;
  if (first->next == second)
    {
      temp = second->next;
      second->next = first;
      first->next = temp;
      if (prev) prev->next = second;
      else head = second;
    }
  else
    {
      t1 = first->next;
      t2 = second->next;
      second->next = t1;
      first->next = t2;
      prev2->next = first;
      if (prev) prev->next = first;
      else head = second;
    }
  return head;
}

node *add_carry(node *head, node **tail, node *mid, int *carry)
{
  node *newnode = (node*) malloc (sizeof(node));

  newnode->data = (head->data + *carry)%10;
  *carry = (head->data + *carry)/10;

  if (head->next == mid)
    {
      newnode->next = NULL;
      *tail = newnode;
      return newnode;
    }
  else
    {
      newnode->next = add_carry(head->next, tail, mid, carry);
      return newnode;
    }
}

node *sum_equal_list(node *h1, node *h2, int *carry)
{
  if (!h1) return NULL;
  node *temp=NULL;
  temp = sum_equal_list (h1->next, h2->next, carry);

  node *newnode = (node*) malloc(sizeof(node));
  newnode->data = (h1->data + h2->data + *carry)%10;
  *carry = (h1->data + h2->data + *carry)/10;
  newnode->next = temp;
  return newnode;
}

node *sum_list(node *h1, node *h2)
{
  node *tmp=NULL, *h=NULL;
  int l1, l2, l;
  if (!h1) return h2;
  if (!h2) return h1;
  
  for (tmp=h1, l1=0; tmp; tmp=tmp->next, l1++);
  for (tmp=h2, l2=0; tmp; tmp=tmp->next, l2++);

  if (l1<l2) {l=l1; l1=l2; l2=l; h=h1; h1=h2; h2=h;}
  
  for (tmp=h1, l=0; l<l1-l2; tmp=tmp->next, l++);
  node *m = tmp;
  node *first = NULL, *second=NULL;
  node *tail = NULL, *mid = NULL;

  if (m != h) first = h1;
  
  int carry = 0;
  second = sum_equal_list(m, h2, &carry);
  if (first)
    {
      first = add_carry(first, &tail, m, &carry);
      tail->next = second;
      second = first;
    }
  if (carry)
    {
      node *newnode = (node*) malloc (sizeof(node));
      newnode->data = carry;
      newnode->next = second;
      second = newnode;
    }
  return second;
}

node *split_at_mid(node *head)
{
  node *fast=NULL, *slow=NULL, *tmp=NULL;

  for (slow=head, fast=head->next; fast && fast->next;)
    {
      slow = slow->next;
      fast = fast->next->next;
    }
  tmp = slow->next;
  slow->next = NULL;
  return tmp;
}

node *sorted_merge(node *h1, node* h2)
{
  if (!h1) return h2;
  if (!h2) return h1;

  if (h1->data <= h2->data)
    {
      h1->next = sorted_merge(h1->next, h2);
      return h1;
    }
  else
    {
      h2->next = sorted_merge(h1, h2->next);
      return h2;
    }
}

node *merge_sort(node *head)
{
  node *first=NULL, *second=NULL;
  if (!head || !head->next) return head;

  second = split_at_mid(head);
  first = merge_sort(head);
  second = merge_sort(second);
  return sorted_merge(first, second);
}

void partition(node *head, node **first, node **second)
{
  node *tmp=NULL;
  *first = NULL; *second=NULL;

  node *tail1=NULL, *tail2=NULL;

  for (tmp = head->next; tmp;)
    {
      if (tmp->data < head->data)
	{
	  if (*first==NULL)
	    {
	      *first = tail1 = tmp;
	      tmp = tmp->next;
	      tail1->next = NULL;
	    }
	  else
	    {
	      tail1->next = tmp; tmp=tmp->next;
	      tail1 = tail1->next; tail1->next=NULL;
	    }
	}
      else
	{
	  if (*second == NULL)
	    {
	      *second = tail2 = tmp;
	      tmp = tmp->next;
	      tail2->next = NULL;
	    }
	  else
	    {
	      tail2->next = tmp;
	      tmp = tmp->next;
	      tail2 = tail2->next;
	      tail2->next = NULL;
	    }
	}
    }
}

node *quick_sort (node *head)
{
  node *first=NULL, *second=NULL, *tmp=NULL;
  if (!head || !head->next) return head;
  
  partition(head, &first, &second);
  if (first) first = quick_sort(first);
  if (second) second = quick_sort(second);

  head->next = second;
  if (!first) return head;

  for (tmp = first; tmp->next; tmp = tmp->next);
  tmp->next = head;
  return first;
}

int main()
{
  int data[] = {1, 3, 4, 5};//, 7, 19, 10, 1, 16};
  int size = sizeof(data)/sizeof(int);
  node *head = NULL; head = create_list(data, size);
  printf("\n\tFirst List\n"); print_list(head);

  //head = merge_sort(head);
//  head = quick_sort(head);
 // printf("\n\tSorted List\n"); print_list(head);

  
  int data1[] = {3, 4, 5};//, 7, 9, 10, 11, 13};
  int size1 = sizeof(data1)/sizeof(int);
  node *head1 = NULL; head1 = create_list(data1, size1);
  printf("\n\tSecond List\n"); print_list(head1);

  node *result = sum_list(head, head1);
  printf("\n\tResult List\n"); print_list(result);
  
  /*
  head = swap_data(head, 1, 3);
  printf("After Swap => ");
  print_list(head);
  */
  printf("\n");
  return 0;
}
