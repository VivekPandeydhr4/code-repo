#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int data;
  struct node *left;
  struct node *right;
  struct node *random;
}NODE;
NODE* insert(NODE *root, int x);
void Random_inorder(NODE *root);
void inorder(NODE *root);
void preorder(NODE *root);
void postorder(NODE *root);
NODE* detach_Clone(NODE *root);
void set_random_ptr(NODE *root);
NODE* Clone_BT(NODE *root);
void build_BT(NODE *root);



NODE* separate_duplicate(NODE *root)
{
  NODE *clone;
  if(root)
    {
      clone=root->left;
      root->left=root->left->left;
      clone->left=separate_duplicate(root->left);
      clone->right=separate_duplicate(root->right);
      return clone;
    }
  else return NULL;
}
void fill_random_at_duplicate(NODE *root)
{
  if(root)
    {
  
      if(root->random) root->left->random=root->random->left;
      fill_random_at_duplicate(root->left->left);
      fill_random_at_duplicate(root->right);
    }
}
void insert_duplicate_at_left(NODE *root)
{
  NODE *newnode;
  if(root)
    {
      newnode=(NODE*)malloc(sizeof(NODE));
      newnode->data=root->data;
      newnode->right=newnode->random=NULL;
      newnode->left=root->left;
      root->left=newnode;
      insert_duplicate_at_left(root->left->left);
      insert_duplicate_at_left(root->right);
    }

}
NODE *clone_Random_BT(NODE *root)
{
  NODE *clone;
  if(root)
    {
      insert_duplicate_at_left(root);
      fill_random_at_duplicate(root);
      clone=separate_duplicate(root);
      return clone;
    }
  else return NULL;
}

int main()
{
  int i,A[]={5,3,7,2,4,6,8};
  NODE *root=NULL,*clone=NULL;
  for(i=0;i<7;i++)
    root=insert(root,A[i]);
  inorder(root);
  printf("\n");

  root->random=root->right->left;//5->6
  root->left->random=NULL;//3->5
  root->left->left->random=root->right->right;//2->8
  root->left->right->random=root;//4->5
  root->right->random=root->left->left;//7->2
  root->right->left->random=root->left;//6->3
  root->right->right->random=root->left->right;//8->4

  clone=clone_Random_BT(root);
  inorder(clone);
  printf("\n");

  Random_inorder(root);
  printf("\n");

  Random_inorder(clone);
  printf("\n");
  
  return 0;
}

NODE* Clone_BT(NODE *root)
{
  NODE *clone=NULL;
  build_BT(root);
  set_random_ptr(root);
  clone=detach_Clone(root);
  return clone;
}
void build_BT(NODE *root)
{
  NODE *newnode=NULL;
  if(root)
    {
      build_BT(root->left);
      build_BT(root->right);
      newnode=(NODE*)malloc(sizeof(NODE*));
      newnode->data=root->data;
      newnode->left=root->left;
      root->left=newnode;
      if(root->right) newnode->right=root->right->left;
      else newnode->right=NULL;
    }
}

void set_random_ptr(NODE *root)
{
  if(root)
    {
      set_random_ptr(root->left->left);
      set_random_ptr(root->right);
      if(root->random) root->left->random=root->random->left;
      else root->left->random=NULL;
    }
}
NODE* detach_Clone(NODE *root)
{
  NODE *temp,*l,*r;
  if(root)
    {
      l=detach_Clone(root->left->left);
      r=detach_Clone(root->right);
      temp=root->left;
      root->left=temp->left;
      temp->left=l;
      return temp;
    }
  return NULL;
}
/************ CREATING and DISPLAYING the BST ******************************/

NODE* insert(NODE *root, int x)
{
  NODE *newnode,*temp=root,*parent=NULL;
  newnode=(NODE*)malloc(sizeof(NODE));
  newnode->data=x;
  newnode->left=newnode->right=newnode->random=NULL;
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
void Random_inorder(NODE *root)
{
  if(root)
    {
      Random_inorder(root->left);
      if(root->random)printf("%d ", root->random->data);
      else printf("-1 ");
      Random_inorder(root->right);
    }
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

