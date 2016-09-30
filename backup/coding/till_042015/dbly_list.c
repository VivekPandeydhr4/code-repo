#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
}NODE;
/******************************/
NODE* build_list();
void print_list(NODE *head);
NODE* reverseList_Recly(NODE **h);
NODE* DLL_to_Balanced_BST(NODE *head);
void inorder(NODE *root);
/*******************************/
int size(NODE *head)
{
  int n;
  NODE *temp;
  for(n=0,temp=head;temp;temp=temp->next,n++);
  return  n;

}
NODE* DLL_to_BT(NODE **head, int n)
{//helping function
  NODE *l,*root;
  if(n==0) return NULL;
  if(n%2==0) l=DLL_to_BT(head, n/2-1);
  else  l=DLL_to_BT(head, n/2);
  (*head)->prev=l;
  root=(*head);
  *head=(*head)->next;
  root->next=DLL_to_BT(head,n/2);
  return root;
}
NODE* DLL_balanced_BT(NODE *head)
{//O(n) time: efficient than DLL_to_Balanced_BST() which was O(nlogn)
  int n;
  if(head)
    {
      n=size(head);
      return DLL_to_BT(&head,n);
    }
  else return NULL;
}

int main()
{
  NODE *root=NULL,*head=NULL;
    head=build_list();
    print_list(head);
    root=DLL_balanced_BT(head);
    inorder(root);
    printf("\n");
    /* reverseList_Recly(&root); */
    /* print_list(root); */
    return 0;
}


void inorder(NODE *root)
{
  if(root)
    {
      if(root->prev) inorder(root->prev);
      printf("%d ",root->data);
      if(root->next) inorder(root->next);
    }
}
NODE* find_median(NODE *head)
{
  NODE *fast,*slow;
  if(head)
    {
      slow=head;
      if(head->next)
	{
	  fast=head->next;
	  while(fast&&fast->next)
	    {
	      fast=fast->next->next;slow=slow->next;
	    }	  
	}
      return slow;
    }
  else return NULL;
}
NODE* DLL_to_Balanced_BST(NODE *head)
{
  NODE *mid;
  if(head)
    {
      mid=find_median(head);
      if(!mid) return NULL;
      if(mid->next) {mid->next->prev=NULL;mid->next=DLL_to_Balanced_BST(mid->next);}
      if(mid->prev) {mid->prev->next=NULL;mid->prev=DLL_to_Balanced_BST(head);}
      return mid;
    }
  else return NULL;
}



NODE* build_list()
{
    int n;
    NODE *newnode=NULL,*head=NULL,*tail=NULL;
    printf("Enters numbers: ");
    scanf("%d",&n);
    if(n==-1) return NULL;
    newnode=(NODE*)malloc(sizeof(NODE));
    newnode->data=n;
    newnode->prev=newnode->next=NULL;
    head=tail=newnode;
    while(1)
    {
	scanf("%d",&n);
	if(n==-1) break;
	newnode=(NODE*)malloc(sizeof(NODE));
	newnode->data=n;
	newnode->next=NULL;
	tail->next=newnode;
	newnode->prev=tail;
	tail=newnode;
    }
    return head;
}
void print_list(NODE *head)
{
  NODE *temp=NULL;
  if(!head) printf("Empty list\n");
  else
    {
      printf("List data:-\n\t");
      for(temp=head;temp;temp=temp->next)    
	printf("%d ",temp->data);
    }
  printf("\n");
}

NODE* reverseList_Recly(NODE **h)
{
    NODE *tail;
    if(*h)
    {
	if((*h)->next)
	{
	    tail=reverseList_Recly(&((*h)->next));
	    tail->next=*h;
	    tail=tail->next;
	    *h=tail->next;
	    tail->next=NULL;
	    return tail;
	}
	else return (*h);
    }
    else return NULL;
	
}    
