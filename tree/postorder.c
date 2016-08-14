#include "header.h"
#include "queue.c"
#include "stack.c"

void postorder(node* root)
{
  if(root)
    {
      postorder(root->left);
      postorder(root->right);
      printf("%d ",root->data);
    }
}

void postorder_iterative_1(node* root)
{
  stack* stk = (stack*)malloc(sizeof(stack));
  stack* vstd= (stack*)malloc(sizeof(stack));
  stk -> top = NULL;
  vstd-> top = NULL;

  node* temp = root;
  node* alt =NULL;
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
          alt = pop(stk);
          if(vstd->top){
	    if(alt==vstd->top->element)
	      {
		printf("%d ",alt->data);
		pop(vstd);
		continue;
	      }
          }
          if(alt->right)
            {
              push(vstd, alt);
              push(stk, alt);
              temp=alt->right;
              push(stk, temp);
              break;
            }


          if(alt)
            {
              printf("%d ",alt->data);
            }
          else break;
        }
    }
}
/*
void postorder_iterative_2(node* root)
{
  stack* stk = (stack*)malloc(sizeof(stack));

}
*/
int main()
{
  node* root = create_tree();

  printf("PRINT TREE POSTORDER RECURSIVE:\n");
  postorder(root);

  printf("\n");                                                                                                                   
  printf("PRINT TREE POSTORDER ITERATIVE\n");                                                                                        
  //  postorder_iterative_1(root);                                                                                                         
  printf("\n");
  return 0;
}
