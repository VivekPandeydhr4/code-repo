#ifndef STACK_C_
#define STACK_C_
 
#include "header.h"

typedef struct stk_node
{
  node *element;
  struct stk_node *next;
}stknd;

typedef struct stack
{
  stknd *top;
}stack;

void push(stack *stk, node *nd)
{
  stknd* nwnd = (stknd*)malloc(sizeof(stknd));

  nwnd->element = nd;
  if(stk->top==NULL) nwnd->next =  NULL;
  else nwnd->next = stk->top;
  stk->top = nwnd;

}

node* pop(stack *stk)
{
  stknd* alt=NULL;
  node* temp=NULL;
  if(stk->top)
    {
      alt = stk->top;
      temp=alt->element;
      stk->top = stk->top->next;
      free(alt);
    }
  return temp;
}

int is_empty(stack* stk)
{
  int flag=0;
  if(!stk->top) flag=1;
  return flag;
}

#endif
