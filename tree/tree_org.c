#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif


typedef struct node
{
  int data;
  struct node *left;
  struct node *right;
}node;
/**********************************
           TREE STACK
***********************************/
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
/*************************************/

/***************************************
         TREE QUEUE
***************************************/
typedef struct queue_node
{
  node *element;
  struct queue_node *next;
}quend;

typedef struct queue
{
  quend *head;
  quend *tail;
}queue;

void enq(queue *q, node *nd)
{
  quend *nwnd = (quend*)malloc(sizeof(quend));
  nwnd -> element = nd;
  nwnd -> next = NULL;

  if(!q->head) q->head = q->tail = nwnd;
  else{
    q->tail->next=nwnd;
    q->tail=nwnd;
  }
}

node* deq(queue *q)
{
  quend *temp;
  node *alt = NULL;
  if(q->head){
    
    temp = q->head;
    q->head = q->head->next;
    if(q->head==NULL) q->tail = NULL;
    alt = temp->element;
    free(temp);
  }
  return alt;
}
/****************************************/

node* create_node(int num);
node* insert_node(node* root, int num);
node* create_tree();
void inorder(node* root);
node* insert(node* root, int num);

void print_level_by_level(node* root);
void print_zig_zag(node* root);
void inorder_iterative(node* root);
int depth_iterative(node* root);
int find_depth(node *root);
int depth(node*root);

void preorder(node* root);
void preorder_iterative(node* root);
void postorder(node* root);
void postorder_iterative(node* root);

int main()
{
  node* root = create_tree();

  printf("PRINT TREE INORDER RECURSIVE:\n");
  inorder(root);
  
  printf("\n");
  printf("PRINT TREE INORDER ITERATIVE\n");
  inorder_iterative(root);
  printf("\n\n");


  printf("PRINT TREE PREORDER RECURSIVE:\n");
  preorder(root);
  
  printf("\n");
  printf("PRINT TREE PREORDER ITERATIVE\n");
  preorder_iterative(root);
  printf("\n\n");


  printf("PRINT TREE POSTORDER RECURSIVE:\n");
  postorder(root);
  
  /* printf("\n");
  printf("PRINT TREE POSTORDER ITERATIVE\n");
  postorder_iterative(root);

  /* printf("\n");
  printf("PRINT TREE LEVEL BY LEVEL:\n");
  print_level_by_level(root);*/

  /*  printf("\n");
  printf("PRINT TREE IN ZIG-ZAG PATH\n");
  print_zig_zag(root);*/

  printf("\n");
    printf("DEPTH OF TREE: %d",depth(root));
  printf("\n");
  return 0;
}

node* create_node(int num)
{
  node *newnode = (node*)malloc(sizeof(node));
 
  newnode -> data = num;
  newnode -> left = NULL;
  newnode -> right= NULL;

  return newnode;
}

node* insert_node(node* root, int num)
{
  if(!root) root = create_node(num);
  else if(num<root->data) root->left=insert_node(root->left,num);
  else root->right=insert_node(root->right,num);
  return root;
}

node* create_tree()
{
  node* root=NULL;
 
  root = insert_node(root,10);
  root = insert_node(root,5);
  root = insert_node(root,6);
  root = insert_node(root,2);
  root = insert_node(root,8);
  root = insert_node(root,9);
  root = insert_node(root,15);
  root = insert_node(root,13);
  root = insert_node(root,16);
  root = insert_node(root,12);
  root = insert_node(root,20);
  
  /*
  root = insert(root,10);
  root = insert(root,5);
  root = insert(root,6);
  root = insert(root,2);
  root = insert(root,8);
  root = insert(root,11);
  root = insert(root,13);
  root = insert(root,16);
  root = insert(root,18);
  root = insert(root,20);
  */
  return root;
}

void inorder(node* root)
{
  if(root)
    {
      inorder(root->left);
      printf("%d ",root->data);
      inorder(root->right);
    }
}

node* insert(node* root, int num)
{
  node* newnode = create_node(num);
  node* temp;
  if(!root) root= newnode;
  else{
    for(temp=root;;);
  }
  return root;
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

void inorder_iterative(node* root)
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

void preorder(node* root)
{
  if(root)
    {
      printf("%d ",root->data);
      preorder(root->left);
      preorder(root->right);
    }
}

int depth(node*root)
{
  if(root==NULL)
    {
      return -1;
    }
  return max(depth(root->left),depth(root->right))+1;
} 

void preorder_iterative(node* root)
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

void postorder(node* root)
{
  if(root)
    {
      postorder(root->left);
      postorder(root->right);
      printf("%d ",root->data);
    }
}

void postorder_iterative(node* root)
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
