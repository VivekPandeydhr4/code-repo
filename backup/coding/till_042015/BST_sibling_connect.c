#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int data;
  struct node *left;
  struct node *right;
  struct node *next;
}NODE;
void sibling_connect(NODE *root);
NODE* insert(NODE *root, int x);
void inorder(NODE *root);
void preorder(NODE *root);
void postorder(NODE *root);
void level_connect(NODE *root);
int main()
{
  int x;
  NODE *root=NULL,*temp=NULL;  
  printf("Enter BST data: ");
  while(1)
    {
      scanf("%d",&x);
      if(x<0) break;
      root=insert(root,x);
    }
  printf("\nTREE DATA: ");
  inorder(root);
  printf("\n");
  level_connect(root);
  printf("\n Level order: ");
  for(temp=root;temp;temp=temp->next) printf("%d ",temp->data);
  printf("\n");
  return 0;
}
void sibling_connect(NODE *root)
{
  NODE *temp=root,*start=NULL, *back=NULL, *prev=NULL;
  if(root)
    {
      while(temp)
	{
	  if(temp->left)
	    {
	      if(back==NULL) start=back=temp->left;
	      else {back->next=temp->left; back=back->next;}
	    }
	  if(temp->right)
	    {
	      if(back==NULL) start=back=temp->right;
	      else {back->next=temp->right; back=back->next;}
	    }
	  prev=temp;
	  temp=temp->next;
	}
      prev->next=start;
      sibling_connect(start);
    }
}




void level_connect(NODE *root)
{
  NODE *temp,*first, *current, *prev;
  temp=root;
  while(temp)
    {
      first=current=NULL;
      while(temp)
	{
	  if(temp->left){if(first==NULL) first=current=temp->left; else current=current->next=temp->left;}
	  if(temp->right){if(first==NULL) first=current=temp->right; else current=current->next=temp->right;}
	  prev=temp;
	  temp=temp->next;
	}
      temp=prev->next=first;
    }
}






















/************ CREATING and DISPLAYING the BST ******************************/

NODE* insert(NODE *root, int x)
{
  NODE *newnode,*temp=root,*parent=NULL;
  newnode=(NODE*)malloc(sizeof(NODE));
  newnode->data=x;
  newnode->left=newnode->right=newnode->next=NULL;
  while(temp)
    {
      parent=temp;
      if(x<temp->data) {temp=temp->left;}
      else temp=temp->right;
    }
  if(!parent) return newnode;
  else if(x<parent->data) parent->left=newnode;
  else parent->right=newnode;
  return root;
}
void inorder(NODE *root)
{
  if(root)
    {
      inorder(root->left);
      printf("%d ", root->data);
      inorder(root->right);
    }
}
void preorder(NODE *root)
{
  if(root)
    {
      printf("%d ", root->data);
      preorder(root->left);      
      preorder(root->right);
    }
}
void postorder(NODE *root)
{
  if(root)
    {
      postorder(root->left);
      postorder(root->right);
      printf("%d ", root->data);
    }
}

