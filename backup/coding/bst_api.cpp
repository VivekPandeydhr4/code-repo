#include <stdio.h>
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
void insert_recly(NODE **proot, int x)
{
  NODE *newnode;
  
  if(*proot==NULL) {*proot=(NODE*)malloc(sizeof(NODE)); (*proot)->data=x;(*proot)->left=(*proot)->right=NULL;}
  else if(x<(*proot)->data) insert_recly(&(*proot)->left,x);
  else insert_recly(&(*proot)->right,x);
}

int search(NODE *root, int x)
{
  if(!root) return 0;
  if(root->data==x) return 1;
  if(root->left && search(root->left,x))  return 1;
  if(root->right && search(root->right,x)) return 1;
  return 0;
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
