#ifndef SIBLING_H_
#define SIBLING_H_

#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
  int data;
  struct node *left;
  struct node *right;
  struct node *sibling;
}node;

node* create_node(int num)
{
  node *newnode = (node*)malloc(sizeof(node));

  newnode -> data = num;
  newnode -> left = NULL;
  newnode -> right= NULL;
  newnode -> sibling= NULL;

  return newnode;
}

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

node* insert_node(node* root, int num)
{
  if(!root) root = create_node(num);
  else if(num<root->data) root->left=insert_node(root->left,num);
  else root->right=insert_node(root->right,num);
  return root;
}

node* make_tree()
{
  int arr[] = {15, 10, 18, 5, 13, 16, 19, 4, 6, 11, 17, 22, 8, 20, 21};

  int size = sizeof (arr) / sizeof (int);
  int i=0; node* root=NULL;

  for (i=0; i<size; i++)
    root = insert_node(root, arr[i]);
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

queue *connect_sibling(node* root)
{
  node *last_node = create_node(-1);
  queue* q1 = (queue*)malloc(sizeof(queue));
  queue* q2 = (queue*)malloc(sizeof(queue));
  queue* q3 = (queue*)malloc(sizeof(queue));

  q1->head=q1->tail=NULL;
  q2->head=q2->tail=NULL;
  q3->head=q3->tail=NULL;

  node* temp=root, *temp1=NULL;
  enq(q1,temp);

  while(q1->head || q2->head)
    {
      while(q1->head)
        {
          temp = deq(q1);
	  if (temp1)
	    temp1->sibling = temp;
	  else
	    enq(q3, temp);
          if(temp->left)
            enq(q2,temp->left);
          if(temp->right)
            enq(q2,temp->right);
	  temp1 = temp;
        }
      if (temp1)
	{
	  temp1->sibling = last_node;
	  temp1 = NULL;
	}
      while(q2->head)
        {
          temp = deq(q2);
	  if (temp1)
	    temp1->sibling = temp;
	  else
	    enq(q3, temp);
          if(temp->left)
            enq(q1,temp->left);
          if(temp->right)
            enq(q1,temp->right);
	  temp1 = temp;
	}
      if (temp1)
	{
	  temp1->sibling = last_node;
	  temp1 = NULL;
	}
    }
  return q3;
}

void print_sibling_pointer(node* root)
{
  node *tmp=NULL, *tmp1=NULL;

  tmp = root;
  while (tmp)
    {
      tmp1 = tmp;
      while (tmp1)
	{
	  printf("%d ",tmp1->data);
	  tmp1 = tmp1->sibling;
	}
      printf("\n");
      if (tmp->left)
	tmp = tmp->left;
      else if (tmp->right)
	tmp = tmp->right;
      else 
	tmp = NULL;
    }
}

void print_sibling_pointer_2(queue* q)
{
  node *tmp=NULL, *tmp1=NULL;

  tmp = deq(q);
  while (tmp)
    {
      tmp1 = tmp;
      while (tmp1)
	{
	  printf("%d ",tmp1->data);
	  tmp1 = tmp1->sibling;
	}
      printf("\n");
      tmp = deq(q);
    }
}

int main()
{

  node* root = make_tree();

  printf("\nPRINT TREE INORDER:\n");
  inorder(root);

  printf("\n\nPRINT TREE LEVEL BY LEVEL:\n");
  print_level_by_level(root);

  printf("\n\nPRINT TREE Connected Sibling:\n");
  queue *que = connect_sibling(root);
  print_sibling_pointer_2(que);

  printf("\n\n");

  return 0;
}

#endif
