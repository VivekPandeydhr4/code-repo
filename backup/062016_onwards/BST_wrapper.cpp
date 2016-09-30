#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef struct node
{
  int data;
  struct node *left;
  struct node *right;
}NODE;
/****************************************/
NODE* init_bst()
{
  return (NODE*)NULL;
}

NODE* insert_into_bst(NODE *root, int x)
{
  NODE* newnode;
  newnode=(NODE*)malloc(sizeof(NODE));
  newnode->data=x;
  newnode->left=newnode->right=NULL;
  if(!root) return newnode;
  if(x<root->data)
    root->left = insert_into_bst(root->left,x);
  else root->right = insert_into_bst(root->right, x);
  return root;
}
NODE *insert_into_bst_itly(NODE *root, int x)
{
  NODE *newnode,*temp;
  newnode=(NODE*)malloc(sizeof(NODE));
  newnode->data=x;
  newnode->left=newnode->right=NULL;
  if(!root) return newnode;
  temp=root;
  while(1)
    {
      if(x<temp->data)
	{
	  if(temp->left) temp=temp->left;
	  else {temp->left=newnode;break;}
	}
      else
	{
	  if(temp->right) temp=temp->right;
	  else {temp->right=newnode;break;}
	}
    }
  return root;
}

NODE* create_bst(int *A, int n)
{
  NODE *root;
  int i;
  if(!A || n<=0) return NULL;
  root=init_bst();
  for(i=0;i<n;i++)
    root = insert_into_bst_itly(root,A[i]);
  return root; 
}

void inorder(NODE *root)
{
  if(root)
    {
      if(root->left) inorder(root->left);
      cout<<root->data<<" ";
      if(root->right) inorder(root->right);
    }
}

void preorder(NODE *root)
{

  if(root)
    {
      cout<<root->data<<' ';
      if(root->left) preorder(root->left);
      if(root->right) preorder(root->right);
    }

}
void postorder(NODE *root)
{

  if(root)
    {      
      if(root->left) postorder(root->left);
      if(root->right) postorder(root->right);
      cout<<root->data<<' ';
    }

}
