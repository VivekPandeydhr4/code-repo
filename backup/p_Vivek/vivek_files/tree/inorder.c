#include "header.h"
#include "stack.c"
#include "queue.c"

void inorder(node* root)
{
  if(root)
    {
      inorder(root->left);
      printf("%d ",root->data);
      inorder(root->right);
    }
}

void inorder_iterative_1(node* root)
{
  stack* stk = (stack*)malloc(sizeof(stack));
  stk -> top = NULL;

  node* temp = root;
  push(stk, temp);

  while(!(is_empty(stk)))
    {
      while(temp->left)
        {
          temp = temp -> left;
          push(stk, temp);
        }
      while(1)
	{
          temp = pop(stk);
          if(temp) printf("%d ",temp->data);
          else break;
          if(temp->right)
	    {
	    temp=temp->right;
	    push(stk, temp);	    
	    break;
	    }
	}
    }
}
/*
void inorder_iterative_2(node* root)
{
  stack* stk = (stack*)malloc(sizeof(stack));
  stk -> top = NULL;

  node* temp = root;
  push(stk, temp);

  while(!(is_empty(stk)))
    {
      while(temp->left)
        {
          temp = temp -> left;
          push(stk, temp);
        }
      while(1)
	{
          temp = pop(stk);
          if(temp) printf("%d ",temp->data);
          else break;
          if(temp->right)
	    {
	      temp=temp->right;
	      break;
	    }
	}
    }
}
*/


void kth_smallest(node* root, int k)
{
  static int cnt=0;
  
  if(root)
    {
      kth_smallest(root->left, k);

	if(++cnt == k)
	  {
	    printf(" \n\n%d smallest element of tree: %d\n", k, root->data);
	  }

	kth_smallest(root->right, k);
    }

}
 //#if 0
int main()
{

  node* root = create_tree();
  int k=9;
  printf("PRINT TREE INORDER RECURSIVE:\n");
  inorder(root);

  kth_smallest(root, k);

  //  printf("\n");
  //printf("PRINT TREE INORDER ITERATIVE\n");
  //inorder_iterative_1(root);
  printf("\n\n");

  return 0;
}
//#endif
