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

void print_spiral(node* root)
{
  stack* s1 = (stack*)malloc(sizeof(stack));
  stack* s2 = (stack*)malloc(sizeof(stack));

  s1->top=NULL;
  s2->top=NULL;

  node* temp=root;
  push(s1,temp);

  while(s1->top || s2->top)
    {
      while(s1->top)
        {
          temp = pop(s1);
          printf("%d ",temp->data);
          if(temp->left)
	    push(s2,temp->left);
          if(temp->right)
	    push(s2,temp->right);
        }
      printf("\n");
      while(s2->top)
        {
          temp = pop(s2);
          printf("%d ",temp->data);
          if(temp->right)
	    push(s1,temp->right);
          if(temp->left)
	    push(s1,temp->left);
        }
      printf("\n");
    }
}

int main()
{
  /*************************************************/
  node* root = make_tree();
  printf(" INORDER TREE :\n");
  inorder(root);
  printf("\n");
  /*************************************************/

  printf("\nPRINT TREE LEVEL BY LEVEL:\n");
  print_level_by_level(root);

  printf("\nPRINT TREE SPIRAL:\n");
  print_spiral(root);

  printf("\n\n");

  return 0;
}
