#ifndef HEADER_H_
#define HEADER_H_

#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
  int data;
  struct node *left;
  struct node *right;
}node;

node* create_node(int num)
{
  node *newnode = (node*)malloc(sizeof(node));

  newnode -> data = num;
  newnode -> left = NULL;
  newnode -> right= NULL;

  return newnode;
}

node* insert_node(node* root, int num)
{
  if(!root) root = create_node(num);
  else if(num<root->data) root->left=insert_node(root->left,num);
  else root->right=insert_node(root->right,num);
  return root;
}

node* create_tree()
{
  node* root=NULL;

  root = insert_node(root,10);
  root = insert_node(root,5);
  root = insert_node(root,6);
  root = insert_node(root,2);
  root = insert_node(root,8);
  root = insert_node(root,9);
  root = insert_node(root,15);
  root = insert_node(root,13);
  root = insert_node(root,16);
  root = insert_node(root,12);
  root = insert_node(root,20);

  /*                                                                                                                                
  root = insert(root,10);                                                                                                           
  root = insert(root,5);                                                                                                            
  root = insert(root,6);                                                                                                            
  root = insert(root,2);                                                                                                            
  root = insert(root,8);                                                                                                            
  root = insert(root,11);                                                                                                           
  root = insert(root,13);                                                                                                           
  root = insert(root,16);                                                                                                           
  root = insert(root,18);                                                                                                           
  root = insert(root,20);                                                                                                          
  */
  return root;
}

node* make_tree()
{
  int arr[] = {15, 10, 18, 5, 13, 16, 19, 4, 6, 11, 17, 22, 8, 20, 21};
  //int arr[] = {3, 2};//, 4};
  int size = sizeof (arr) / sizeof (int);
  int i=0; node* root=NULL;

  for (i=0; i<size; i++)
    root = insert_node(root, arr[i]);
  return root;
}
void inorder(node* root)
{
  if(root)
    {
      inorder(root->left);
      printf("%d ",root->data);
      inorder(root->right);
    }
}

void preorder(node* root)
{
  if(root)
    {
      printf("%d ",root->data);
      preorder(root->left);
      preorder(root->right);
    }
}

void postorder(node* root)
{
  if(root)
    {
      postorder(root->left);
      postorder(root->right);
      printf("%d ",root->data);
    }
}

#endif
