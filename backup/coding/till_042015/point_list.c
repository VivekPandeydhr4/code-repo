#include<stdio.h>
#include<stdlib.h>

/*******************************************************/
typedef struct node
{
  int x,y;
  struct node * next;
}NODE;

/*******************************************************/
NODE* append(NODE *head,int x,int y);
NODE* prepend(NODE *head, int x);
NODE* build_list();
void print_circular_list(NODE *head);
void reverse_circular_list(NODE *head);
void reverse_circular_list_recly(NODE *head);
void make_circular_list(NODE *head);
void print_list(NODE *head);
NODE* reverse_list(NODE *head);
NODE* reverse_k_elem(NODE *head, int k);
NODE* reverse_k_elem_recly(NODE *head, int k);
NODE* split_at_mid(NODE *head);
NODE* swap_pairs_itly(NODE *head);
NODE* swap_pairs_recly(NODE *head) ;
NODE* sorted_merge_itly(NODE *h1, NODE *h2);
NODE* sorted_merge_recly(NODE *h1, NODE *h2);
NODE* suffle_merge_itly(NODE *h1,NODE *h2);
NODE* merge_sort(NODE *head);
void Merge(NODE *first, NODE **second);
int palindrome(NODE *h);
int pal(NODE **h1, NODE *h2);
void Merge_itly(NODE *f, NODE **s);
void Remove_duplicate(NODE *root);
NODE* Kth_lastNode(NODE *head, int k);
NODE* Reverse_k_Elem(NODE *head, int k);
NODE* Reverse_K_elem(NODE *head, int k);
NODE* sortList_0_1(NODE *head);
int check_palindrome(NODE *head);
int check_pal(NODE *head, NODE **toMatch);
NODE* Alternate_Merge(NODE *h1, NODE *h2);
NODE* reverse(NODE *head);
NODE* rev_k_nodes(NODE *head,int k);
NODE *Rev_k_nodes(NODE *head, int k);
NODE* sorted_merging(NODE *h1, NODE *h2);
void remove_midPoints(NODE *head);
/*******************************************************/
int main()
{
  int a,b;
  NODE *second,*head=build_list(),*head2=build_list();

  printf("Enter list data:");
  while(1)
    {
      scanf("%d %d",&a,&b);
      if(a==-1) break;
      head=append(head,a,b);
    }
  /* while(1) */
  /*   { */
  /*     scanf("%d",&a); */
  /*     if(a==-1) break; */
  /*     head2=append(head2,a); */
  /*   } */
  //printf("%d\n",check_palindrome(head));
  //head=Reverse_K_elem(head,3);
   print_list(head);
   printf("\n");
   remove_midPoints(head);
   print_list(head);
   printf("\n");

   /* print_list(head2); */
   /* /\* head=Alternate_Merge(head,head2); *\/ */
   /* printf("\n"); */
   /* head=sorted_merging(head,head2); */
   /* print_list(head); */
   /* printf("\n"); */
   //head=sortList_0_1(head);
  //second=Kth_lastNode(head,1); 
  //Remove_duplicate(head);
  //printf("%d\n",second->data);
  //print_list(head);
  /* printf("  Enter data list2: "); */
  /* while(1) */
  /*   { */
  /*     scanf("%d",&a); */
  /*     if(a==-1) break; */
  /*     head1=append(head1,a); */
  /*   } */
  /* print_list(head); */
  /* print_list(head1); */
  /* Merge_itly(head,&head1); */
  /* print_list(head); */
  /* print_list(head1); */

  return 0;
}

void remove_midPoints(NODE *head)
{
  int z;
  NODE *start,*temp;
  start=head;

  while(start && start->next)
    {      
      if(start->x==start->next->x) z=0;
      else if(start->y==start->next->y) z=1;
      else {start=temp->next; continue;}
      
      temp=start->next;
      while(temp->next && *(((int*)(temp->next))+z)==*(((int*)(start))+z))
	{
	  start->next=temp->next;
	  free(temp);
	  temp=start->next;
	}
      start=temp->next;
    }
  /* while(start && start->next) */
  /*   {       */
      /* if(start->x==start->next->x) */
      /* 	{ */
      /* 	  temp=start->next; */
      /* 	  while(temp->next && temp->next->x==start->x) */
      /* 	    { */
      /* 	      start->next=temp->next; */
      /* 	      free(temp); */
      /* 	      temp=start->next; */
      /* 	    } */
      /* 	  start=temp->next; */
      /* 	} */
      /* else if(start->y==start->next->y) */
      /* 	{ */
      /* 	  temp=start->next; */
      /* 	  while(temp->next && temp->next->y==start->y) */
      /* 	    { */
      /* 	      start->next=temp->next; */
      /* 	      free(temp); */
      /* 	      temp=start->next; */
      /* 	    } */
      /* 	  start=temp->next; */
      /* 	} */
      /* else start=start->next; */
 /* } */
}
void print_list(NODE *head)
{
  NODE *temp=NULL;
  printf("\n\tList: ");
  for(temp=head;temp;temp=temp->next)
    printf("(%d,%d) ",temp->x,temp->y);
  printf("\n");

}
NODE* build_list()
{
  return (NODE*)NULL;

}

NODE* append(NODE *head,int a, int b)
{
  NODE *temp=NULL;
  NODE* newnode=(NODE*)malloc(sizeof(NODE));
  newnode->x=a;
  newnode->y=b;
  newnode->next=NULL;
  if(!head) return newnode;
  for(temp=head;temp->next;temp=temp->next);
  temp->next=newnode;
  return head;
}
 
