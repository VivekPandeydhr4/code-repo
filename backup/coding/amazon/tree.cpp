#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <queue>
using namespace std;
typedef struct node
{
  struct node *left;
  int data;
  struct node *right;
}NODE;
NODE* make_bst(void)
{
  return (NODE*)NULL;
}
void insert(NODE** proot, int x)
{
  NODE *temp,*parent,*newnode=(NODE*)malloc(sizeof(NODE));
  newnode->data=x;
  newnode->left=newnode->right=NULL;

  if(*proot==NULL) *proot=newnode;
  else{
  for(temp=*proot;temp;)
    {
      parent=temp;
      if(x<temp->data) temp=temp->left;
      else temp=temp->right;
    }
  if(x<parent->data) parent->left=newnode;
  else parent->right=newnode;
  }
}
void insert_recly(NODE **proot, int x)
{
  NODE *newnode;
  
  if(*proot==NULL) {*proot=(NODE*)malloc(sizeof(NODE)); (*proot)->data=x;(*proot)->left=(*proot)->right=NULL;}
  else if(x<(*proot)->data) insert_recly(&(*proot)->left,x);
  else insert_recly(&(*proot)->right,x);
}
NODE * create_BST(int *A, int n)
{
  int i;
  NODE *root;
  root=make_bst();
  for(i=0;i<n;i++)
    insert_recly(&root,A[i]);
  return root;
}
void inorder(NODE *root)
{
  if(root)
    {
      inorder(root->left);
      printf("%d ",root->data);
      inorder(root->right);
    }
}
/******************************************/

NODE* remove_half_nodes(NODE *root)
{
  NODE *temp=NULL;
  if(!root) return NULL;
  if(root->left) root->left=remove_half_nodes(root->left);
  if(root->right) root->right=remove_half_nodes(root->right);
  temp=NULL;
  if(root->left && !root->right)       temp=root->left;
  if(!root->left && root->right)       temp=root->right;
  if(temp)
    {
      free(root);
      return temp;   
    }   
  else return root;
}
/******************************************/
int main()
{
  NODE *root;
  int size,A[]={5,4,6,2,8,1,3,7};
  size=sizeof(A)/sizeof(*A);
  root=create_BST(A,size); 
  inorder(root);cout<<endl;
  remove_half_nodes(root);
  inorder(root);cout<<endl;
  return 0;
}
