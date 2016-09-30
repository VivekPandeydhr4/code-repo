#include<stdio.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
/*******************************************************/
typedef struct node
{
  unsigned long long data;
  struct node * next;
}NODE;

/*******************************************************/
void print_list(NODE *head)
{
  NODE *temp=NULL;
  printf("\nList: ");
  for(temp=head;temp;temp=temp->next)
    printf("%lld ",temp->data);
  printf("\n");

}

NODE* append(NODE *head,int x)
{
  NODE *temp=NULL;
  NODE* newnode=(NODE*)malloc(sizeof(NODE));
  newnode->data=x;
  newnode->next=NULL;
  if(!head) return newnode;
  for(temp=head;temp->next;temp=temp->next);
  temp->next=newnode;
  return head;
}
 
NODE* prepend(NODE *head, int x)
{
  NODE *newnode=(NODE*)malloc(sizeof(NODE));
  newnode->data=x;
  newnode->next=head;
  return newnode;
}
NODE* create_list(int *A, int n)
{
  int i;
  NODE *head=NULL;
  for(i=0;i<n;i++)
    {
      head=append(head,A[i]);
    }
  return head;
}

/*****************************************************/

typedef struct bnode
{
  int data;
  struct bnode *left, *right;
}BNODE;

void inorder(BNODE *root)
{
  if(root)
    {
      inorder(root->left);
      cout<<root->data<<' ';
      inorder(root->right);
    }
}

BNODE* insert_bst(BNODE *root, int data)
{
  BNODE *newnode=NULL, *temp=NULL;
  newnode=(BNODE*)malloc(sizeof(BNODE));
  newnode->data= data;
  newnode->left=newnode->right=NULL;
  if(!root) return newnode;
  temp=root;
  while(temp)
    {
      if(data<temp->data)
	{
	  if(temp->left) temp=temp->left;
	  else {temp->left=newnode;break;}
	}
      else
	{
	  if(temp->right) temp=temp->right;
	  else {temp->right = newnode;break;}
	}
    }
  return root;
}

/*****************************************************/
/*****************************************************/

BNODE* sortedList_to_BST(NODE *head)
{
  NODE *slow=NULL,*fast=NULL,*prev=NULL;
  BNODE *root=NULL;
  if(head)
    {
      if(head->next)
	{
	  for(slow=head,fast=head->next;fast&&fast->next;)
	    {
	      prev=slow;
	      slow=slow->next;
	      fast=fast->next->next;	      
	    }
	  if(fast) {prev=slow;slow=slow->next;}
	  root=insert_bst(root,slow->data);
	  prev->next=NULL;
	  root->left = sortedList_to_BST(head);
	  root->right = sortedList_to_BST(slow->next);
	  prev->next=slow;
	  return root;
	}
      else return insert_bst(root,head->data);
    }
  else return NULL;
}
/*****************************************************/
NODE* mergeSort_list(NODE *head);
NODE* quick_sort(NODE *head)
{
  NODE *pivot=NULL,*left=NULL,*lTail=NULL,*right=NULL,*rTail=NULL,*temp=NULL;
  if(head)
    {
      if(head->next)
	{
	  pivot=head;
	  for(temp=head->next;temp;)
	    {
	      if(temp->data<pivot->data)
		{
		  if(!left) left=lTail=temp;
		  else lTail=lTail->next=temp;
		  temp=temp->next;
		  lTail->next=NULL;
		}
	      else 
		{
		  if(!right) right=rTail=temp;
		  else rTail=rTail->next=temp;
		  temp=temp->next;
		  rTail->next=NULL;
		}
	    }
	  	 
	  left= quick_sort(left);
	  right= quick_sort(right);	  
	  for(temp=left;temp->next;temp=temp->next);  
	  pivot->next=right;
	  if(left){temp->next=pivot;return left;}	    
	  else return pivot;	    
	}
    }
  return head;
}
/*****************************************************/

NODE* sorted_merge(NODE *h1, NODE *h2)
{
  NODE *temp;
  if(!h1) return h2;
  if(!h2) return h1;
  if(h1->data<=h2->data)
    {
      temp=h1->next;
      h1->next=sorted_merge(temp,h2);
      return h1;
    }
  else
    {
      temp=h2->next;
      h2->next=sorted_merge(h1,temp);
      return h2;
    }
}

NODE* mergeSort_list(NODE *head)
{
  NODE *mid=NULL,*head2=NULL,*temp=NULL,*fast=NULL;
  if(head)
    {
      if(head->next)
	{
	  for(mid=head,fast=head->next;fast&& fast->next;mid=mid->next,fast=fast->next->next);
	  head2=mid->next;
	  mid->next=NULL;
	  head=mergeSort_list(head);
	  head2=mergeSort_list(head2);
	  head=sorted_merge(head,head2);	  
	}      
    }
  return head;
}

/*****************************************************/
BNODE* sortedDLL_to_balancedBST_inplace(NODE *head)
{

  return NULL;
}

/*****************************************************/


NODE* sortList_already_sorted_aleternatingAsc_desc(NODE *head)
{//Iteratively
  int i;
  NODE *a=NULL,*aTail=NULL,*d=NULL,*dTail=NULL,*temp=NULL,*t1,*t2,*t3,*tail;
  if(head)
    {
      //separatinng asc and desc sorted sublists
      for(temp=head,i=1;temp;)
	{
	  if(i%2)
	    {
	      if(!a) a=aTail=temp;
	      else aTail=aTail->next=temp;
	      temp=temp->next;
	      i++;
	      aTail->next=NULL;	      
	    }
	  else
	    {
	      if(!d) d=dTail=temp;
	      else dTail=dTail->next=temp;
	      temp=temp->next;
	      i++;
	      dTail->next=NULL;
	    }
	}
      print_list(a);
      print_list(d);
      //reverse desc list
      if(d)
	{
	  if(d->next)
	    {
	      t1=NULL;
	      t2=d;
	      t3=d->next;
	      while(t3)
		{
		  t2->next=t1;
		  t1=t2;
		  t2=t3;
		  t3=t3->next;
		}
	      t2->next=t1;
	      d=t2;
	    }	  
	}
      print_list(d);
      //sorted merge asc and reversed Desc lists
      head=tail=NULL;
      while(a && d)
	{
	  if(a->data<=d->data)
	    {
	      if(!head) head=tail=a;
	      else tail=tail->next=a;
	      a=a->next;
	      tail->next=NULL;
	    }
	  else
	    {
	      if(!head) head=tail=d;
	      else tail=tail->next=d;
	      d=d->next;
	      tail->next=NULL;
	    }
	}
      if(!a) tail->next=d;
      else tail->next=a;
    }
  return head;
}

NODE* fun(NODE *h1, NODE *h2, NODE *h3, int l1, int l2, int l3, int *carry)
{
  if(!l1) return NULL;

  if(l1>l2)
    {
      ret = fun(h1->next,h2,h3,l1-1,l2,l3,carry);
    }
  else if(l2 && l2>l3)
    {
      ret = fun(h1->next,h2->next,h3,l1-1,l2-1,l3,carry);
    }
  else if
  newnode=(NODE*)malloc(sizeof(NODE));
  newnode->data = (head->data+(*carry))%10;
  (*carry)= (head->data+(*carry))/10;
  newnode->next = ret;
  return newnode;
      


}

NODE* sum_3Numbers_as_List(NODE *h1, NODE *h2, NODE *h3)
{
  int l1, l2,l3,carry;
  for(l1=0,temp=h1;temp;l1++,temp=temp->next);
  for(l2=0,temp=h2;temp;l2++,temp=temp->next);
  for(l3=0,temp=h3;temp;l3++,temp=temp->next);
  
  if(l1<l2){swapNode(&h1,&h2);swap(&l1,&l2);}
  if(l3>l1){swapNode(&h1,&h3);swap(&l1,&l3);}
  if(l3>l2){swapNode(&h2,&h3);swap(&l2,&l3);}
  carry=0;
  return fun(h1,h2,h3,l1,l2,l3,&carry)
  
}








































/*****************************************************/
int main()
{  
  int i,n,A[]={2,7,4,5,6,3,8,1,9};
  NODE *head=NULL;
  BNODE *root=NULL;
  n=sizeof(A)/sizeof(A[0]);
  head = create_list(A,n); print_list(head);
  head = sortList_already_sorted_aleternatingAsc_desc(head);print_list(head);
  //head = quick_sort(head);print_list(head);
  //root = sortedList_to_BST(head); 
  //inorder(root);
  cout<<endl;return 0;
}
