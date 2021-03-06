#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;
typedef struct node
{
  struct node *left;
  int data;
  struct node *right;
}NODE;
void BFS(NODE *root);
void BFS_Recly(queue<NODE*> *Q1);
void inorder(NODE *root);
NODE* make_bst(void);
void insert(NODE** proot, int x);
void insert_recly(NODE **proot, int x);
int LCA_binaryTree(NODE *root, int a, int b, NODE **lca);
void level_order(NODE *root);
int main()
{
  printf("Hi\n");
  int m,n,i,A[]={5,3,7,2,4,6,8,1,9,-1};
  NODE *root,*lca=NULL;
  root=make_bst();
  for(i=0;A[i]!=-1;i++)
    insert_recly(&root,A[i]);
  inorder(root);
  printf("\n");
  BFS(root);
  printf("\n");
  // while(1)
  //   {
  //     printf("Enter two values: ");
  //     scanf("%d%d",&m,&n);
  //     LCA_binaryTree(root,m,n,&lca);
  //     printf("LCA of %d and %d is: %d\n", m,n,lca->data);
  //   }
  return 0;

}
void level_order(NODE *root)
{
  NODE *temp,*prev;
  queue<NODE*> Q;
  Q.push(root);Q.push(NULL);temp=NULL;
  while(!Q.empty())
    {
      prev=temp;
      temp=Q.front();
      Q.pop();
      if(!temp){if(prev==NULL) break;printf("\n");Q.push(NULL);continue;}
      if(temp->left) Q.push(temp->left);
      if(temp->right) Q.push(temp->right);
      cout<<temp->data<<" ";
    }
}




void BFS(NODE *root)
{
  queue<NODE*> Q1;
  if(root)
    {
      Q1.push(root);
      BFS_Recly(&Q1);
    }
}
void BFS_Recly(queue<NODE*> *Q1)
{
  NODE *temp;
  queue<NODE*> Q2;
  while(!((*Q1).empty()))
    {
      temp=(*Q1).front();
      (*Q1).pop();
      if(temp->left) Q2.push(temp->left);
      if(temp->right) Q2.push(temp->right);
      printf("%d ", temp->data);
    }
  printf("\n");
  if(!Q2.empty())
    BFS_Recly(&Q2);
}
int LCA_binaryTree(NODE *root, int a, int b, NODE **lca)
{
  int x=0,y=0,p=0;
  if(root)
    {   	
      x=LCA_binaryTree(root->left,a,b,lca);
      if(x==2) return 2;
      if(root->data==a || root->data==b) p=1;
      if(p+x==2){*lca=root; return 2;}
      y=LCA_binaryTree(root->right,a,b,lca);
      if(y==2) return 2;
      if(p+x+y==2) {*lca=root; return 2;}
      return (p+x+y);
    }
  else return 0;
}

NODE* make_bst(void)
{
  return (NODE*)NULL;
}
void insert(NODE** proot, int x)
{
  NODE *temp,*parent,*newnode=(NODE*)malloc(sizeof(NODE));
  newnode->data=x;
  newnode->left=newnode->right=NULL;

  if(*proot==NULL) *proot=newnode;
  else{
  for(temp=*proot;temp;)
    {
      parent=temp;
      if(x<temp->data) temp=temp->left;
      else temp=temp->right;
    }
  if(x<parent->data) parent->left=newnode;
  else parent->right=newnode;
  }
}

void insert_recly(NODE **proot, int x)
{
  NODE *newnode;
  
  if(*proot==NULL) {*proot=(NODE*)malloc(sizeof(NODE)); (*proot)->data=x;(*proot)->left=(*proot)->right=NULL;}
  else if(x<(*proot)->data) insert_recly(&(*proot)->left,x);
  else insert_recly(&(*proot)->right,x);
}

void inorder(NODE *root)
{
  if(root)
    {
      inorder(root->left);
      printf("%d ",root->data);
      inorder(root->right);
    }
}
