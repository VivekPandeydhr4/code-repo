#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <queue>
using namespace std;
typedef struct node
{
  struct node *left;
  int data;
  struct node *right;
  struct node *random;
}NODE;
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
NODE * create_BST(int *A, int n)
{
  int i;
  NODE *root;
  root=make_bst();
  for(i=0;A[i]!=-1;i++)
    insert_recly(&root,A[i]);
  return root;
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
void inorder_random(NODE *root)
{
  if(root)
    {
      inorder_random(root->left);
      if(root->random)  printf("%d ",root->data);
      else printf("-1 ");
      inorder_random(root->right);
    }
}

/******************************************/
int levels(NODE *root, int level)
{
  int l=0,r=0;
  if(!root->left && !root->right) return level;  
  if(root->left) l=levels(root->left, level+1);
  if(root->right) r=levels(root->right,level+1);
  if(l>=r) return l;
  else return r;
}
void print_paths(NODE *root, int *A, int index)
{
  int i=0;
  A[index]=root->data;
  if(!root->left && !root->right)
    {
      for(i=0;i<=index;i++) cout<<A[i]<<", ";
      cout << endl;
    }
  if(root->left) print_paths(root->left,A,index+1);
  if(root->right) print_paths(root->right,A,index+1);
}
void print_all_root_to_leaf_path(NODE *root)
{
  int h=0, *A=NULL;
  if(root)
    {
      h=levels(root,1);
      A=(int*)malloc(h*sizeof(int));
      print_paths(root,A,0);      
    }
}

NODE* detach_clone_from_main_BT(NODE *root)
{
  NODE *clone=NULL;
  if(root)
    {
      clone=root->left;
      root->left=root->left->left;
      clone->left=detach_clone_from_main_BT(root->left);
      clone->right=detach_clone_from_main_BT(root->right);
      return clone;
    }
  else return NULL;
}
void fill_randoms_in_clone_nodes(NODE *root)
{
  if(root)
    {
      if(root->random==NULL) root->left->random=NULL;
      else root->left->random=root->random->left;
      
      if(root->left->left) fill_randoms_in_clone_nodes(root->left->left);
      if(root->right) fill_randoms_in_clone_nodes(root->right);
    }
}
void clone_nodes_at_left_link(NODE *root)
{
  NODE *newnode=NULL;
  if(root)
    {
      if(root->left) clone_nodes_at_left_link(root->left);
      if(root->right) clone_nodes_at_left_link(root->right);

      newnode=(NODE*)malloc(sizeof(NODE));
      newnode->data=root->data;newnode->left=newnode->right=NULL;
      newnode->left=root->left;
      root->left=newnode;
    }
}
NODE* Clone_BT_with_random_ptr(NODE *root)
{
  if(!root) return NULL;

  clone_nodes_at_left_link(root);
  fill_randoms_in_clone_nodes(root);
  return detach_clone_from_main_BT(root);  
}

void Greater_sum(NODE *root, int *sum)
{
  int temp=0;
  if(root)
    {
      if(root->right) Greater_sum(root->right,sum);      
      temp=root->data;
      root->data=*sum;
      *sum=(*sum)+temp;
      if(root->left) Greater_sum(root->left,sum);
    }
}
void transform_greater_sum_BST(NODE *root)
{
  int sum=0;
  if(root)
    {
      Greater_sum(root, &sum);      
    }
}

void populate_values_in_A(NODE *root, int hd, vector<int> *A, int min)
{
  A[hd-min].push_back(root->data);
  if(root->left) populate_values_in_A(root->left,hd-1,A,min);
  if(root->right) populate_values_in_A(root->right,hd+1,A,min);

}
void min_max_HD(NODE *root, int hd,int *min, int *max)
{
  if(hd<*min) *min=hd;
  if(hd>*max) *max=hd;
  if(root->left) min_max_HD(root->left,hd-1,min,max);
  if(root->right) min_max_HD(root->right,hd+1,min,max);
}
void print_vertical_order(NODE *root)
{
  int i=0,min=INT_MAX,max=INT_MIN;
  vector<int> *A=NULL;
  if(root){
  min_max_HD(root,0,&min,&max);
  A=(vector<int>*)malloc((max-min+1)*sizeof(vector<int>));
  populate_values_in_A(root,0,A,min);
  for(i=0;i<=max-min;i++)
    {
      for(vector<int>::iterator it=A[i].begin();it!=A[i].end();it++)
	{
	  cout<< *it<<" ";	  
	}
      cout <<endl;
    }
  }
}
void k_dist_nodes(NODE *root, int k)
{
  if(k==0) cout << root->data<<" ";
  else if(k>0)
    {
      if(root->left) k_dist_nodes(root->left,k-1);
      if(root->right) k_dist_nodes(root->right,k-1);
    }
}
int func(NODE *root, int data, int k, int level)
{
  int l=0,r=0,d=0;
  if(root->data==data)
    {
      if(k==0) cout << root->data<<" ";
      if(root->left) k_dist_nodes(root->left,k-1);
      if(root->right) k_dist_nodes(root->right,k-1);
      return level;
    }
  
  if(root->left)
    {
      l=func(root->left,data,k,level+1);
      if(l)
	{
	  d=l-level;
	  if(d==k) cout <<root->data<<" ";
	  else if(d<k && root->right) k_dist_nodes(root->right,k-d-1);
	  return l;
	}
    }
  if(root->right)
    {
      r=func(root->right,data,k,level+1);
      if(r)
	{
	  d=r-level;
	  if(d==k) cout <<root->data<<" ";
	  else if(d<k && root->left) k_dist_nodes(root->left,k-d-1);
	  return r;
	}
    }
  return 0;
}
void print_nodes_at_distance_k_from_a_target_node(NODE *root, int data, int k)
{
  if(root && k>=0)
    {
      func(root,data,k,1);
      cout <<endl;
    }
}

int LCA(NODE *root, int a, int b, int *lca)
{
      int l,r;
      l=r=0;
      if(root->left) l=LCA(root->left,a,b,lca);
      if(root->right) r=LCA(root->right,a,b,lca);
      if(l+r==2)
	{
	  if(l==1 && r==1) *lca=root->data;
	  return 2;
	}
      if(l+r==1)
	{
	  if(root->data==a || root->data==b) {*lca=root->data; return 2;}
	  else return 1;
	}
      if(root->data==a ||root->data==b) return 1;
      else return 0;

}
int LCA_BT(NODE *root, int a, int b)
{
  int lca=0,x=0;
  if(root)
    {
      x=LCA(root,a,b,&lca);
      if(x==2) return lca;
      else return INT_MIN;
    }
  else return INT_MIN;
}
/******************************************/
int main()
{
  NODE *root, *root2, *temp,*prev,*clone;
  int data,k,m,n,i,a,b,size,A[]={8,4,12,2,6,10,14,1,3,5,7,9,11,13,15,-1};

  size=sizeof(A)/sizeof(A[0])-1;
  root=create_BST(A,size);
  inorder(root);cout<<endl;  



  for(i=0;i<10;i++)
    {
      cout<<"Enter a,b: ";
      cin >>a>>b;
      cout <<LCA_BT(root,a,b)<<endl;      
   }
  // print_nodes_at_distance_k_from_a_target_node(root,data,k);
  //print_vertical_order(root);
  // transform_greater_sum_BST(root);
  // inorder(root);cout<<endl;
  
  //clone=Clone_BT_with_random_ptr(root);
  //print_all_root_to_leaf_path(root);
  return 0;
}
