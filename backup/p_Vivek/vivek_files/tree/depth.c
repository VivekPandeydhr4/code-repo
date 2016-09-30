#include "header.h"
#include "stack.c"
#include "queue.c"

int find_depth(node *root)
{
  static int max=0;
  static int count=0;
  if(root->left!=NULL)
    {
      count++;
      if(count>max)
        max=count;
      find_depth(root->left);
    }
  if(root->right!=NULL)
    {
      count++;
      if(count>max)
        max=count;
      find_depth(root->right);
    }
  count--;
  return max;
}

int depth(node*root)
{
  if(root==NULL)
    {
      return -1;
    }
  return max(depth(root->left),depth(root->right))+1;
}

int depth_iterative(node* root)
{
  int n=0, dep=0;
  stack* stk = (stack*)malloc(sizeof(stack));
  stk -> top = NULL;

  node* temp = root;
  push(stk, temp);
  n++;
  while(!(is_empty(stk)))
    {
      while(temp->left)
        {
          temp = temp -> left;
          push(stk, temp);
          n++;
        }
      while(1)
        {
          temp = pop(stk);
          if(n>dep) dep=n;
          if(!temp) break;
          n--;
          if(temp->right)
            {
              temp=temp->right;
              push(stk, temp);
              n++;
              break;
            }
        }
    }
  return dep;

}

int main()
{

  node* root = create_tree();

  printf("PRINT TREE INORDER RECURSIVE:\n");
  inorder(root);

  printf("\n");
  printf("PRINT TREE INORDER ITERATIVE\n");
  //  inorder_iterative(root);                                                                                                       
  printf("\n\n");

  return 0;
}

