#include "header.h"
#include "queue.c"
#include "stack.c"

void preorder(node* root)
{
  if(root)
    {
      printf("%d ",root->data);
      preorder(root->left);
      preorder(root->right);
    }
}

void preorder_iterative_1(node* root)
{
  stack* stk = (stack*)malloc(sizeof(stack));
  stk -> top = NULL;

  node* temp = root;

  while(temp)
    {
      if(temp->right)
	push(stk, temp->right);
      if(temp->left)
        push(stk, temp->left);
      push(stk, temp);

      temp=pop(stk);
      printf("%d ",temp->data);
      temp=pop(stk);
    }
}

/*********************************************************************
  2 is similar of 1 but more optimised than 1.
 *********************************************************************/
void preorder_iterative_2(node* root)
{
  stack* stk = (stack*)malloc(sizeof(stack));
  stk -> top = NULL;

  node* temp = root;

  while(temp)
    {
      if(temp->right)
        push(stk, temp->right);
      if(temp->left)
        push(stk, temp->left);

      printf("%d ",temp->data);
      temp=pop(stk);
    }
}

int main()
{

  node* root = create_tree();

  printf("PRINT TREE INORDER RECURSIVE:\n");
  preorder(root);

  printf("\n");
  printf("PRINT TREE INORDER ITERATIVE\n");
  preorder_iterative_2(root);
                                                                                                       
  printf("\n\n");

  return 0;
}
