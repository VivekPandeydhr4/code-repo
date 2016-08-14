#include "header.h"
#include "stack.c"
#include "queue.c"

void print_zig_zag(node* root)
{
  stack* stk1 = (stack*)malloc(sizeof(stack));
  stack* stk2 = (stack*)malloc(sizeof(stack));
  stk1->top=NULL;
  stk2->top=NULL;

  node* temp=root;
  push(stk1, temp);

  while((!is_empty(stk1)) || (!is_empty(stk2)))
    {
      while(!is_empty(stk1))
        {
          temp=pop(stk1);
          printf("%d ",temp->data);
          if(temp->left)
            push(stk2,temp->left);
          if(temp->right)
            push(stk2,temp->right);
        }
      while(!is_empty(stk2))
        {
          temp=pop(stk2);
          printf("%d ",temp->data);
          if(temp->right)
	    push(stk1,temp->right);
          if(temp->left)
	    push(stk1,temp->left);
	}
    }
}


int main()
{

  node* root = create_tree();

  printf("\n");                                                                                                                  
  printf("PRINT TREE IN ZIG-ZAG PATH\n");                                                                                            
  print_zig_zag(root);



  printf("\n\n");

  return 0;
}

