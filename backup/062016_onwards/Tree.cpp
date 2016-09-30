#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "BST_wrapper.cpp"
using namespace std;

/******************************************************/
NODE* LCA_bst(NODE* root, int a, int b)
{
  int t;
  NODE *temp;
  if(!root) return NULL;
  if(a>b) {t=a;a=b;b=t;}
  temp=root;
  while(temp)
    {
      if(a==temp->data || b==temp->data) return temp;
      else if(a<temp->data && temp->data<b) return temp;
      else if(temp->data<a) temp=temp->right;
      else temp=temp->left;
    }
  return temp;
}
/****************************************************/

int search_in_array(int *A, int n, int data)
{
  for(int i=0;i<n;i++)
    if(A[i]==data) return i;
}
NODE* Tree_from_inorder_n_postorder(int* IN,int* POST, int n)
{
  int mid;
  NODE *newnode;
  if(n>0)
    {
      mid = search_in_array(IN,n,POST[n-1]);
      newnode=(NODE*)malloc(sizeof(NODE));
      newnode->data=POST[n-1];
      newnode->left=Tree_from_inorder_n_postorder(IN,POST,mid);
      newnode->right=Tree_from_inorder_n_postorder(IN+mid+1,POST+mid,n-mid-1);
      return newnode;
    }
  else return NULL;
}


/****************************************************/
void increment_down(NODE *root)
{
  int l,r,diff;
  if(root)
    {
      if(root->left || root->right)
	{
	  l=root->left?root->left->data:0;
	  r=root->right?root->right->data:0;
	  diff=root->data-(l+r);
	  if(root->left)
	    {
	      root->left->data+=diff;
	      increment_down(root->left);
	    }
	  else{
	    root->right->data+=diff;
	    increment_down(root->right);
	  }
	}
    }
}

void convert_a_tree_to_childSum_tree(NODE *root)
{//A node value can only be incremented, neither it can be decremented not overwritten
  int l,r,diff;
  if(root)
    {
      if(root->left) convert_a_tree_to_childSum_tree(root->left);
      if(root->right) convert_a_tree_to_childSum_tree(root->right);
      l=root->left?root->left->data:0;
      r=root->right?root->right->data:0;
      diff=l+r-root->data;
      if(diff>0) root->data+=diff;
      else if(diff<0) increment_down(root);      
    }
}
/****************************************************/
NODE* BT_node(int x)
{
  NODE *newnode;
  newnode=new NODE;
  newnode->data = x;
  newnode->left=newnode->right=NULL;
  return newnode;
}
int count_nodes(NODE *root)
{
  if(!root) return 0;
  return (1+count_nodes(root->left)+count_nodes(root->right));
}
int isIdentical(NODE *r1, NODE *r2)
{
  if(!r1 && !r2) return 1;
  if(!r1 || !r2) return 0;
  return (r1->data==r2->data && isIdentical(r1->left,r2->left) && isIdentical(r1->right, r2->right));
}

NODE* Largest_subtree_with_identical_left_n_right_subtrees(NODE* root, int *size)
{
  NODE *lnode=NULL, *rnode=NULL;
  int lsize=0, rsize=0;
  if(!root){*size=0;return root;}
  if(isIdentical(root->left,root->right))
    {
      *size=count_nodes(root);
      return root;
    }
  if(root->left)
    lnode = Largest_subtree_with_identical_left_n_right_subtrees(root->left,&lsize);
  if(root->right)
    rnode = Largest_subtree_with_identical_left_n_right_subtrees(root->right, &rsize);
  if(lsize>=rsize){*size=lsize;return lnode;}
  else {*size=rsize;return rnode;}
}
void distant_nodes(node *root, int d)
{
  if(root && d>=0)
    {
      if(d==0) printf("%d, ", root->data);
      else{
        distant_nodes(root->left, d-1);
        distant_nodes(root->right, d-1);
      }
    }
}
int k_dist_value(node* root, int v, int k, int level, int *vlevel)
{
  int toRet=0;

  if (root)
    {
      int l=0; int r=0;
      if(root->data == v) {*vlevel=level; toRet=1;}
      if(*vlevel == -1)
        {
          l=r=0;
          l = k_dist_value(root->left, v, k, level+1, vlevel);
          if(!l) r = k_dist_value(root->right, v, k, level+1, vlevel);
          toRet = (l+r);
        }
    
      if(*vlevel != -1)
	{
	  int d = (*vlevel)-level;
	  if(d==k) printf("%d, ", root->data);
	  else
	    {
	      if(d==0 || r==1) distant_nodes(root->left, k-d-1);
	      if(d==0 || l==1) distant_nodes(root->right, k-d-1);
	    }
	}
    }
  return toRet;
}
void print_k_distant_values(node *root, int v, int k)
{
  int vl=-1;
  if(root && k>=0)
    k_dist_value(root, v, k, 1, &vl);
}
//********************************************************************/

int find_level_of_a_value(NODE *root, int x, int l)
{
  int a=0,b=0;
  if(!root) return 0;
  if(root->data==x) return l;
  if(root->left) a=find_level_of_a_value(root->left,x,l+1);
  if(root->right) b=find_level_of_a_value(root->right,x,l+1);
  return a+b;
}
void print_cousin(NODE *root, int x, int level,int flag)
{
  if(root){
    level--;
    if(!level) {if(!flag) cout<<root->data<<' ';}
    else
      {
	if(root->left && root->left->data==x) flag=1;
	if(root->right && root->right->data==x) flag=1;
	if(root->left) print_cousin(root->left,x,level,flag);
	if(root->right) print_cousin(root->right,x,level,flag);
      }
  }
}
void print_all_cousin_noSibling(NODE *root, int x)
{
  int level = find_level_of_a_value(root,x,1);
  print_cousin(root,x,level,0);
}

//#####################################################################    


/****************************************************/
int main()
{
  NODE *root;
  int n,A[]={5,3,7,2,4,6,8,1,9}, POST[]={1,2,4,3,6,9,8,7,5},IN[]={1,2,3,4,5,6,7,8,9};
  n=sizeof(A)/sizeof(A[0]);
  root = create_bst(A,n);
  //cout<<find_level_of_a_value(root,2,1)<<endl;
  //print_all_cousin_noSibling(root,7);

  /*root=BT_node(50);
  root->left = BT_node(10);
  root->right = BT_node(60);
  root->left->left = BT_node(5);
  root->left->right = BT_node(20);
  root->right->left = BT_node(70);
  root->right->left->left = BT_node(65);
  root->right->left->right = BT_node(80);
  root->right->right = BT_node(70);
  root->right->right->left = BT_node(65);
  root->right->right->right = BT_node(80);
  inorder(root);cout<<endl;
  root = Largest_subtree_with_identical_left_n_right_subtrees(root,&n);
  */

  //root = Tree_from_inorder_n_postorder(IN, POST,9)  ;

  //convert_a_tree_to_childSum_tree(root);  
  //cout<<LCA_bst(root,9,4)->data;
  //postorder(root); 
  cout<<endl;
  inorder(root);
  cout<<endl;
  return 0;
}
