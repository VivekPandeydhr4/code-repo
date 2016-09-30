#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <climits>
#include <stack>
#include <queue>
using namespace std;
typedef struct node
{
  struct node *left;
  int data;
  struct node *right;
}NODE;

void inorder(NODE *root);
NODE* make_bst(void);
void insert(NODE** proot, int x);
void insert_recly(NODE **proot, int x);
void inorder_using_stack(NODE *root);
void pairSum_in_BST(NODE* root, int k);
NODE* delete_nodes_in_path_less_than_min(NODE *root, int k);
void preorder_using_stack(NODE *root);
void Moris_inorder(NODE *root);
void Moris_preorder(NODE*);
void inorder_using_stack1(NODE *root);
void level_tree(NODE *root);
int isIdentical(NODE *root1, NODE *root2);
int check_BST(NODE *root, int *min, int *max);
void Zig_Zag_traversal(NODE *root);

void level_order(NODE *root)
{
  NODE *t=NULL;
  queue<NODE*> s;
  if(root)
    {
      s.push(root);
      while(!s.empty())
	{
	  t=s.front();s.pop();
	  if(t->left) s.push(t->left);
	  if(t->right) s.push(t->right);
	  printf("%d, ",t->data);
	}
      printf("\n");
    }
}
int diameter_fun(NODE *root, int *h)
{
  int h1,h2,d1,d2,d;

  //if(!root->left && !root->right) {*h=1; return 1;}
  h1=h2=0;d1=d2=0;
  if(root->left) d1=diameter_fun(root->left,&h1);
  if(root->right) d2=diameter_fun(root->right,&h2);

  d=(d1>=d2) ? d1 :d2;
  if(h1+h2+1 > d)  d=h1+h2+1;
  (*h)=(h1>=h2)?h1+1:h2+1;
  return d;  
}
int diameter(NODE *root)
{
  int h;
  if(!root) return 0;
  
  return diameter_fun(root,&h);
}
void in_itratively(NODE *root)
{
  NODE *temp=NULL,*t=NULL;
  stack<NODE* > s;
  temp=root;
  while(1)
    {
      while(temp)
	{
	  s.push(temp);
	  temp=temp->left;
	}
      if(s.empty()) break;
      t=s.top();s.pop();
      cout <<t->data<<", ";
      temp=t->right;
    }
  cout <<endl;

}
void preorder_itly(NODE *root)
{
  stack<NODE*> s;
  NODE *t=NULL;
  if(root) s.push(root);
  while(!s.empty())
    {
      t=s.top();s.pop();
      cout << t->data<<", ";
      if(t->right) s.push(t->right);
      if(t->left) s.push(t->left);
    }
  cout <<endl;
}

void postorder_itly(NODE *root)
{
  stack<NODE*> s,q;
  NODE *t=NULL;
  if(root) s.push(root);
  while(!s.empty())
    {
      t=s.top();s.pop();
      q.push(t);
      if(t->left) s.push(t->left);
      if(t->right) s.push(t->right);
    }
  while(!q.empty())   {t=q.top();q.pop();cout << t->data<<", ";}
  cout <<endl;
}

void PostOrder_with_one_stack(NODE *root)
{
  NODE *t=NULL,*t2=NULL,*temp=NULL;
  stack<NODE *> s;
  temp=root;
  while(1)
    {
      while(temp)
	{
	  if(temp->right) {s.push(temp->right);}
	  s.push(temp);
	  temp=temp->left;
	}
      if(s.empty()) break;
      t=s.top();s.pop();
      if(!s.empty()&&t->right==s.top()){t2=s.top();s.pop();s.push(t);temp=t2;}
      else {cout <<t->data<<", "; temp=NULL;}
    }
  cout <<endl;
}


void fill_sum(NODE *root, int hd, int *A, int min)
{
  A[hd-min]+=root->data;
  if(root->left) fill_sum(root->left,hd-1,A,min);
  if(root->right) fill_sum(root->right,hd+1,A,min);
}
void find_min_max_HD(NODE *root,int hd, int *Pmin, int *Pmax)
{
  if(hd<*Pmin) *Pmin=hd;
  if(hd>*Pmax) *Pmax=hd;

  if(root->left) find_min_max_HD(root->left,hd-1,Pmin,Pmax);
  if(root->right) find_min_max_HD(root->right,hd+1,Pmin, Pmax);
}
void vertical_sum(NODE *root)
{

  int min=INT_MAX,max=INT_MIN,size,*A,i;
  if(root)
    {
      find_min_max_HD(root,0,&min,&max);
      size=max-min+1;
      A=(int*)malloc(size*sizeof(int));
      memset(A,0,size*sizeof(int));
      fill_sum(root,0,A,min);
      for(i=0;i<size;i++) cout << A[i]<<", ";
      cout <<endl;
    }
}



int count_nodes(NODE *root)
{
  if(!root) return 0;
  else return (count_nodes(root->left)+count_nodes(root->right)+1);
}
void preorder_fill(NODE *root, int *A, int *index)
{
  if(!root) {A[*index]=-1;(*index)++;}
  else
    {
      A[*index]=root->data;(*index)++;
      preorder_fill(root->left,A,index);
      preorder_fill(root->right,A,index);
    }
}
int* Serialize_a_binary_tree(NODE *root, int *n)
{
  int size=0,index=0,*A=NULL;

  size=count_nodes(root);
  A=(int*)malloc(1+(2*size*sizeof(int)));
  index=0;
  preorder_fill(root,A,&index);
  *n=index;
  return A;
}

NODE* Deserialize(int *A, int *index, int n)
{
  NODE *newnode=NULL;
  if(*index<n)
    {
      if(A[*index]==-1) {(*index)++;return NULL;}
      newnode=(NODE*)malloc(sizeof(NODE));
      newnode->data=A[*index];(*index)++;
      newnode->left=Deserialize(A,index,n);
      newnode->right=Deserialize(A,index,n);
      return newnode;
    }
}
int main()
{
  NODE *root,*temp, *t,*newnode; 
  int m,n,i,A[]={5,3,7,2,4,6,8,1,9,-1},C[]={-5,-7,-3,-8,-6,-4,-2,-9,0,-1},*P=NULL;
  root=make_bst();
  for(i=0;A[i]!=-1;i++)
     insert_recly(&root,A[i]);
  //Moris_preorder(root);

  P=Serialize_a_binary_tree(root,&n);
  // for(i=0;i<n;i++)
  //   cout<< P[i]<<",";
  // cout <<endl;
  i=0;
  temp=Deserialize(P,&i,n);
  inorder(temp);
  cout<<endl;
  //cout << diameter(root)<<endl;


  // newnode=(NODE*)malloc(sizeof(NODE));
  // newnode->data=10;newnode->left=newnode->right=NULL;
  // root->left->left->right=newnode;

  // newnode=(NODE*)malloc(sizeof(NODE));
  // newnode->data=20;newnode->left=newnode->right=NULL;
  // root->right->left->left=newnode;

  // postorder_itly(root);
  // PostOrder_with_one_stack(root);

  // vertical_sum(root);
  //level_order(root);
  //in_itratively(root);
  //root->data=30;
  //inorder(root);
  // temp=make_bst();
  // for(i=0;A[i]!=-1;i++)
  //    insert_recly(&temp,A[i]);
  //inorder(temp);
  //Zig_Zag_traversal(root);
  //cout << check_BST(root,&m,&n);
  
  // printf("\n");    
  
  // level_tree(root);		

  // for(temp=root;temp;temp=temp->left)
  //   {
  //      for(t=temp;t;t=t->right) 
  // 	 printf("%d ",t->data);
  //      printf("\n");
  //   }
  printf("\n");    
  return 0;
}
void Zig_Zag_traversal(NODE *root)
{
  NODE *temp;
  stack<NODE*> s1,s2;
  if(root) s1.push(root);
  while(!s1.empty())
    {
      while(!s1.empty())
	{
	  temp=s1.top();s1.pop();
	  if(temp->left) s2.push(temp->left);
	  if(temp->right) s2.push(temp->right);
	  printf("%d ",temp->data);
	}

      while(!s2.empty())
	{
	  temp=s2.top();s2.pop();
	  if(temp->right) s1.push(temp->right);
	  if(temp->left) s1.push(temp->left);
	  printf("%d ",temp->data);
	}
    }
  printf("\n");;
}


int check_BST(NODE *root, int *min, int *max)
{
  int lmin,lmax,rmin,rmax,x,y;
  if(!root) return 1;
  
  *min=*max=root->data;
  if(root->left)
    {
      x=check_BST(root->left,&lmin, &lmax);
      if(x && lmax<*min){*min=lmin; return 1;}
      else return 0;
    }
  if(root->right)
    {
      y=check_BST(root->right,&rmin,&rmax);
      if(y && *max<=rmin) {*max=rmax; return 1;}
      else return 0;
    }
  return 1;

}

int isIdentical(NODE *root1, NODE *root2)
{
  if(!root1 && !root2) return 1;
  if(root1 && root2)
    {
      if(root1->data==root2->data && isIdentical(root1->left,root2->left) && isIdentical(root1->right, root2->right)) return 1;
      else return 0;
    }
  else return 0;
}
void level_tree(NODE *root)
{
  NODE *t,*old,*first,*prev;
  queue<NODE*> q1,q2,q;
  if(root)
    {
      q1.push(root);
      old=NULL;
      while(!q1.empty())
	{
	  first=prev=NULL;
	  while(!q1.empty())
	    {
	      t=q1.front();q1.pop();
	      if(t->left) q2.push(t->left);
	      if(t->right) q2.push(t->right);
	      if(!prev) first=prev=t;
	      else prev=prev->right=t;
	      t->right=NULL;
	    }
	  if(old) old->left=first;
	  old=first;
	  q=q1;
	  q1=q2;
	  q2=q;
	}
    }
}
void inorder_using_stack1(NODE *root)
{
  stack<NODE *> s;
  NODE *temp=root,*node;
  s.top();
  while(temp || !s.empty())
    {
      while(temp)
	{
	  s.push(temp);
	  temp=temp->left;
	}
      if(!s.empty()){
      node=s.top();s.pop();
      cout << node->data <<" ";
      temp=node->right;}
    }
}
void Moris_inorder(NODE *root)
{
  NODE *p,*q;
  p=root;
  while(p)
    {
      if(!p->left){ cout << p->data <<" "; p=p->right;}
      else
	{
	  q=p->left;
	  while(q->right && q->right!=p) q=q->right;
	  if(!q->right){q->right=p;p=p->left;}
	  else
	    {
	      cout << p->data <<" ";
	      q->right=NULL;
	      p=p->right;
	    }
	}
    }
}

void Moris_preorder(NODE *root)
{
  int flag=0;
  NODE *p,*q;
  p=root;
  while(p)
    {      
      if(!p->left){ cout<<p->data<< ", ";p=p->right;}
      else
	{
	  q=p->left;
	  while(q->right && q->right!=p) q=q->right;
	  if(!q->right){cout << p->data <<" ";q->right=p;p=p->left;}
	  else
	    {
	      q->right=NULL;
	      p=p->right;
	    }
	}
    }
}


void preorder_using_stack(NODE *root)
{
  stack<NODE*> s;
  NODE *temp;
  temp=root;
  while(temp)
    {
      while(temp)
	{
	  cout << temp->data <<" ";
	  if(temp->right) s.push(temp->right);
	  temp=temp->left;
	}
      if(!s.empty()) {temp=s.top();s.pop();}
    }
}

NODE* delete_nodes_in_path_less_than_min(NODE *root, int k)
{
  if(root)
    {
      k=k-root->data;
      if(k<=0) return root;
      if(root->left) root->left=delete_nodes_in_path_less_than_min(root->left,k);
      if(root->right) root->right=delete_nodes_in_path_less_than_min(root->right,k);
      if(root->left==NULL && root->right==NULL)
	{
	  free(root);
	  return NULL;
	}
      else return root;
    }
  else return NULL;
}

void pairSum_in_BST(NODE* root, int k)
{
  NODE *l,*r,*temp,*x=NULL,*y=NULL;
  int f1=1,f2=1;
  stack<NODE*> s1,s2;
  if(root)
    {
      temp=root;
      while(temp) {s1.push(temp);temp=temp->left;}
      temp=root;
      while(temp) {s2.push(temp);temp=temp->right;}
      f1=f2=1;
      while(1)
	{
	  if(f1)
	    {
	      l=s1.top();
	      s1.pop();
	      temp=l->right;
	      while(temp) {s1.push(temp);temp=temp->left;}
	    }	 
	  if(f2)
	    {	     
	      r=s2.top();	    

	      s2.pop();

	      temp=r->right;
	      while(temp) {s2.push(temp);temp=temp->right;}
	    }
	  if(l==r) break;
	  if(l->data+r->data==k){printf("%d,%d\n",l->data,r->data); break;}
	  else if(l->data+r->data<k) {f1=1;f2=0;}
	  else {f1=0;f2=1;}
	  printf("Hi3\n");
	}
    }
}

void inorder_using_stack(NODE *root)
{
  NODE *temp;
  stack<NODE*> s;
  temp=root;
  while(temp)
    {
      s.push(temp);
      temp=temp->left;
    }
  while(!s.empty())
    {
      temp=s.top();
      s.pop();
      printf("%d ",temp->data);
      
      temp=temp->right;
    
      while(temp)
	{
	  s.push(temp);
	  temp=temp->left;
	}          
      
    }
  printf("\n");
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
