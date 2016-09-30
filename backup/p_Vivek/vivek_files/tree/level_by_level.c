#include "header.h"
#include "stack.c"
#include "queue.c"

void print_level_by_level(node* root)
{
  queue* q1 = (queue*)malloc(sizeof(queue));
  queue* q2 = (queue*)malloc(sizeof(queue));

  q1->head=q1->tail=NULL;
  q2->head=q2->tail=NULL;

  node* temp=root;
  enq(q1,temp);

  while(q1->head || q2->head)
    {
      while(q1->head)
        {
          temp = deq(q1);
          printf("%d ",temp->data);
          if(temp->left)
	    enq(q2,temp->left);
          if(temp->right)
	    enq(q2,temp->right);
        }
      printf("\n");
      while(q2->head)
        {
          temp = deq(q2);
          printf("%d ",temp->data);
          if(temp->left)
	    enq(q1,temp->left);
          if(temp->right)
	    enq(q1,temp->right);
        }
      printf("\n");
    }
}

int main()
{

  node* root = create_tree();

  printf("\n");                                                                                                                   
  printf("PRINT TREE LEVEL BY LEVEL:\n");                                                                                           
  print_level_by_level(root);

  printf("\n\n");

  return 0;
}
