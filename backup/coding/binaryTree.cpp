#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stack>
#include <queue>
#include "bst_api.cpp"
#define max(a,b) ((a>=b)?(a):(b))

typedef struct dll
{
  struct dll* prev;
  int data;
  struct dll* next;
}DLL;
void bfs(NODE *root);
DLL* vertical_sum_DLL(NODE *root);
int isLeaf(NODE *root);
NODE* Extract_leaves(NODE **root);
int Diameter(NODE *root);
int distance(NODE *root,int a,int b);
using namespace std;
int main()
{
  int i,A[]={8,3,12,1,4,2,10,9,14,13,-1};//{5,3,7,2,4,6,8,1,9,-1};
  NODE *root=NULL,*ret;
  DLL *temp;  
  root=make_bst();
  for(i=0;A[i]!=-1;i++)
    { insert_recly(&root,A[i]);}
  bfs(root);
  printf("\n");
  //cout<<distance(root,3,14)<<endl;
  // for(temp=vertical_sum_DLL(root);temp;temp=temp->next) cout <<temp->data<<",";
  // cout<<endl;
  // inorder(root);
  // printf("\n");

  //cout <<(max(-1,-1)+1);
  //cout <<  Diameter(root)<<endl;

  // ret = Extract_leaves(&root);
  // for(temp=ret;temp;temp=temp->right) cout << temp->data <<",";
  // cout << "\n";

}


void bfs(NODE *root)
{
  NODE *t;
  queue<NODE*> Q;
  if(root)
    {
      Q.push(root);
      while(!Q.empty())
	{
	  t=Q.front();
	  Q.pop();
	  if(t->left) Q.push(t->left);
	  if(t->right) Q.push(t->right);
	  cout<<t->data<<',';
	}
    }
}

int isLeaf(NODE *root)
{
  return (!root->left && !root->right);
}

NODE* fun1(NODE* root, NODE **head)
{
  if(isLeaf(root)){root->right=*head;if(*head) (*head)->left=root;*head=root;return NULL;}
  if(root->right) root->right = fun1(root->right,head);
  if(root->left) root->left = fun1(root->left, head);
  return root;
}
NODE* Extract_leaves(NODE **root)
{
  NODE *toRet,*head;
  if(isLeaf(*root))
    {
      toRet= *root;
      *root= NULL;
      return toRet;
    }
  else
    {
      head=NULL;
      fun1(*root, &head);
      return head;
    }
}
int fun2(NODE *root, int *height)
{
  int lh=-1,ld=-1,rh=-1,rd=-1,t;
  if(root->left) ld=fun2(root->left,&lh);
  if(root->right) rd=fun2(root->right, &rh);
 
  (*height)=max(lh,rh)+1;
  t=(max(ld,rd));
  return max((lh+rh+2),t);
}

int Diameter(NODE *root)
{
  int height;
  if(!root) return -1;
  return fun2(root, &height);
}

void fun3(NODE *root, DLL *listNode)
{
  DLL *newnode;
  listNode->data = listNode->data +root->data;
  if(root->left)
    {
      if(!(listNode->prev)){newnode=(DLL*)malloc(sizeof(DLL));newnode->data=0;newnode->prev=NULL;newnode->next=listNode;listNode->prev=newnode;}
      else newnode=listNode->prev;
      fun3(root->left,newnode);
    }
  if(root->right)
    {
      if(!(listNode->next)) {newnode=(DLL*)malloc(sizeof(DLL));newnode->data=0;newnode->prev=listNode;listNode->next=newnode;newnode->next=NULL;}
      else newnode=listNode->next;
      fun3(root->right,newnode);
    }
}
DLL* vertical_sum_DLL(NODE *root)
{
  DLL *listNode;
  if(root)
    {
      listNode=(DLL*)malloc(sizeof(DLL)); listNode->data=0;listNode->prev=listNode->next=NULL;
      fun3(root,listNode);
      while(listNode->prev) listNode=listNode->prev;
      return listNode;
    }
  else return NULL;
}

int dist(NODE *root, int a, int b, int l)
{
  int d1=0,d2=0;
  if(root->left) d1=dist(root->left, a, b, l+1);
  if(root->right) d2=dist(root->right, a, b, l+1);
  if(root->data==a || root->data==b)
    {
      if(d1>0) return -(d1-l);
      if(d2>0) return -(d2-l);
      return l;
    }
  if(d1>0 &&d2>0) return -(d1+d2);
  else return d1+d2;
}

int distance(NODE *root,int a,int b)
{
  if(root)
    {
      return (-1)*dist(root,a,b,0);
    }
  else return -1;

}
