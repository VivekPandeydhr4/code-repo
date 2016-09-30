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
/******************************************/


int height(NODE *root)
{
  int h1,h2,Max;
  if(root)
    {
      h1=height(root->left);
      h2=height(root->right);
      Max=(h1>=h2)?h1:h2;
      return Max+1;
    }
  else return -1;
}
int height1(NODE *root)
{
  int h,h2;
  if(root)
    {
      h=0;
      if(root->left) h=height1(root->left)+1;
      if(root->right)
	{
	  h2=height1(root->right);
	  if(h2+1>h) h=h2+1;
	}
      return h;
    }
  else return -1;
}

int identical(NODE *root1, NODE *root2)
{
  if(!root1 && !root2) return 1;
  if(root1 && root2)
    {
      if((root1->data==root2->data) && identical(root1->left, root2->left) && identical(root1->left,root2->left)) return 1;
    }
  return 0;
}


void mirror(NODE *root)
{
  NODE *temp;
  if(root)
    {
      mirror(root->left);
      mirror(root->right);
      temp=root->left;
      root->left=root->right;
      root->right=temp;
    }
}


typedef struct node1
{
  int data;
  struct node1 *next;
}LIST;
void print_list_reversely(LIST *head)
{
  if(head)
    {
      print_list_reversely(head->next);
      printf("%d ",head->data);
    }
}
void f1(NODE *root, LIST *head)
{
      LIST *newnode;
      newnode=(LIST*)malloc(sizeof(LIST));
      newnode->data=root->data;newnode->next=head;
      if(!root->left && !root->right) {print_list_reversely(newnode);printf("\n");}
      else
	{
	  if(root->left) f1(root->left,newnode);
	  if(root->right) f1(root->right,newnode);
	}
      free(newnode);
}
void print_all_root_to_leaf_paths(NODE *root)
{
  if(root)  f1(root,NULL);
}

int LCA_BST(NODE *root, int a, int b)
{
  int t;
  if(a>b) {t=a;a=b;b=t;}
  if(a<=root->data && b>=root->data) return  root->data;
  else if(b<root->data) return LCA_BST(root->left,a,b);
  else return LCA_BST(root->right,a,b);
}

int LCA_BT(NODE *root, int a , int b)
{
  int x,y;
  if(root)
    {
      x=y=0;
      if(root->data==a || root->data ==b) return root->data;
      if(root->left) x=LCA_BT(root->left,a,b);
      if(root->right) y=LCA_BT(root->right,a,b);
      if(x && y) return root->data;
      else return (x^y);
    }
  else return 0;
}

NODE* BT_to_inorder_cirular_DLL(NODE *root)
{
  NODE *left,*right,*l,*r,*temp,*head;
  if(root)
    {
      left=root->left;right=root->right;
      root->left=root->right=root;
      head=root;
      if(left)
	{
	  l=BT_to_inorder_cirular_DLL(left);
	  head->right=l;head->left=l->left;
	  head->left->right=head->right->left=head;
	  head=l;	  
	}
      if(right)
	{
	  r=BT_to_inorder_cirular_DLL(right);
	  r->left->right=head;
	  head->left->right=r;
	  temp=head->left;
	  head->left=r->left;
	  r->left=temp;	  
	}
      return head;
    }
  else return NULL;
}
NODE* f2(NODE *root, NODE **T)
{
  NODE *H,*H1,*H2,*T1,*T2,*left,*right;
  if(root)
    {
      left=root->left;right=root->right;
      root->left=root->right=NULL;
      H=*T=root;
      if(left)
	{
	  H1=f2(left,&T1);
	  T1->right=H;H->left=T1;
	  H=H1;
	}
      if(right)
	{
	  H2=f2(right,&T2);
	  H2->left=*T;
	  (*T)->right=H2;
	  (*T)=T2;
	}
      return H;
    }
  else{*T=NULL; return NULL;}  
}
NODE* BT_to_DLL_inoreder(NODE *root)
{
  NODE *H,*T;
  H=f2(root,&T);
  return H;
}

void f3(queue<NODE*>& q1, queue<NODE*>& q2)
{
  NODE *temp;
  if(!q1.empty())
    {
      while(!q1.empty())
	{
	  temp=q1.front();q1.pop();
	  if(temp->left) q2.push(temp->left);
	  if(temp->right) q2.push(temp->right);
	  cout << temp->data<<" ";
	}
      cout <<endl;
      f3(q2,q1);
    } 
}
void level_order_recly(NODE *root)
{
  queue<NODE*> q1,q2;
  if(root)
    {
      q1.push(root);
      f3(q1,q2);
    }
}

int leaf_count(NODE *root)
{
  if(root)
    {
      if(!root->left && !root->right) return 1;
      return (leaf_count(root->left)+leaf_count(root->right));
    }
  else return 0;
}

int path_Array(NODE *root, int key)
{
  int r;
  if(root)
    {
      if(root->data==key) return 1;
      else if(root->data<key)
	{
	  r=path_Array(root->right,key);
	  if(r) printf("1");
	}
      else 
	{
	  r=path_Array(root->left,key);
	  if(r) printf("0");
	}
      return r;
    }
  else {printf("-1\n"); return 0;}
}

int fun_leaves(NODE *root, int flag)
{
  int x=0,y=0;
  if(!root->left && !root->right)
    {
      if(!flag) return root->data; else return 0;
    }
  if(root->left) x=fun_leaves(root->left, 0);
  if(root->right) y=fun_leaves(root->right, 1);
  return x+y;
}

int sum_of_left_leaves(NODE *root)
{
  if(root) return fun_leaves(root,0);
  else return 0;
}

void No_of_diagonals(NODE *root, int *d, int k)
{
  if(k>*d) *d=k;
  if(root->right) No_of_diagonals(root->right, d, k);
  if(root->left) No_of_diagonals(root->left,d,k+1);
}
void fun_diag(NODE *root, int *A, int k)
{
  A[k]+=root->data;
  if(root->right) fun_diag(root->right, A, k);
  if(root->left) fun_diag(root->left, A, k+1);
}
void Diagonal_sum(NODE *root)
{
  int d=0,i,*A=NULL;
  if(root)
    {
      No_of_diagonals(root,&d,1);
      A=(int*)malloc((d+1)*sizeof(int));
      memset(A,0,(d+1)*sizeof(int));
      fun_diag(root,A,1);
      for(i=1;i<=d;i++) cout<<A[i]<<" ";
      printf("\n");
    }
}

int leaf_path(NODE *root, int *max_leaf)
{//helping function
  int l,r,x,y;
  if(!root->left && !root->right) {*max_leaf=root->data;return 0;}
  x=y=l=r=0;

  if(root->left) x=leaf_path(root->left,&l);
  if(root->right) y=leaf_path(root->right,&r);

  if(!root->left) {*max_leaf=r+root->data; return y;}
  if(!root->right) {*max_leaf=l+root->data; return x;}

  *max_leaf=(l>r?l:r)+root->data;

  return (x>y?x:y)>(l+r+root->data)?(x>y?x:y):(l+r+root->data);

}  
int Max_leaf_path_sum(NODE *root)
{
  int max_leaf=0;
  if(!root) return 0;
  return leaf_path(root,&max_leaf);  
}
void fill_top_for_each_HD(NODE *root, int *A, int *L, int min, int hd, int level)
{
  if(root)
    {
      if(!L[hd-min] || L[hd-min]>level) {L[hd-min]=level;A[hd-min]=root->data;}
      if(root->left) fill_top_for_each_HD(root->left,A,L,min,hd-1,level+1);
      if(root->right) fill_top_for_each_HD(root->right,A,L,min,hd+1,level+1);
    }
}
void min_max_HD(NODE *root, int *min, int *max,int hd)
{
  if(root)
    {
      if(hd<*min) *min=hd;
      if(hd>*max) *max=hd;
      if(root->left) min_max_HD(root->left,min,max,hd-1);
      if(root->right) min_max_HD(root->right,min,max,hd+1);
    }
}
void top_view(NODE* root)
{// print data with smallest level from the group of each HD(horizontal distance).
  int *A,*L,size,i,min,max;
  if(root)
    {
      min=max=0;
      min_max_HD(root,&min,&max,0);
      size=max-min+1;
      A=(int*)malloc(size*sizeof(int));
      L=(int*)malloc(size*sizeof(int));
      memset(A,0,size*sizeof(int));
      memset(L,0,size*sizeof(int));
      fill_top_for_each_HD(root,A,L,min,0,1);
      for(i=0;i<size;i++) cout<<A[i]<<" ";
      cout <<endl;
    }
}
void print_left_view(NODE *root, int *L, int level)
{
  if(level>*L) {printf("%d,", root->data);*L=level;}
  if(root->left) print_left_view(root->left,L,level+1);
  if(root->right) print_left_view(root->right,L,level+1); 
}
void left_view(NODE *root)
{// print the data of each level which comes first in Preoder
  int L;
  if(root)
    {
      L=0;
      print_left_view(root,&L,1);
      printf("\n");
    }
}
void fill_bottom_data_for_each_HD(NODE *root,int *A,int *L,int min,int hd,int level)
{
  if(root)
    {
      if(!L[hd-min] ||L[hd-min]<=level ) {L[hd-min]=level;A[hd-min]=root->data;}
      if(root->left) fill_bottom_data_for_each_HD(root->left,A,L,min,hd-1,level+1);
      if(root->right) fill_bottom_data_for_each_HD(root->right,A,L,min,hd+1,level+1);
    }
}
void bottom_view(NODE *root)
{// Lowest data at each virtical level. if two contradicts choose later one in level order traversal
  int min,max,i,size,*A,*L;
  if(root)
    {
      min=max=0;
      min_max_HD(root,&min,&max,0);
      size=max-min+1;
      A=(int*)malloc(size*sizeof(int));
      L=(int*)malloc(size*sizeof(int));
      memset(L,0,size*sizeof(int));
      fill_bottom_data_for_each_HD(root,A,L,min,0,1);
      for(i=0;i<size;i++) cout<<A[i]<<" ";
      cout<<endl;
    }
}
void singleton(NODE *root, NODE *parent)
{
  if(!parent) cout<<root->data<<" ";
  else if(root==parent->left && !parent->right) cout<<root->data<<" ";
  else if(root==parent->right && !parent->left) cout<<root->data<<" ";      
  if(root->left) singleton(root->left,root);
  if(root->right) singleton(root->right,root);  
}
void  singleton_child(NODE *root)
{
  if(root)
    {
      singleton(root,NULL);
      cout<<endl;
    }
}

void k_Dist(NODE *root, int *A, int d, int k)
{
  A[d]=root->data;
  if(!root->left && !root->right) /*cout << "hi\n";*/
    { if(k<=d && A[d-k]!=-1) 
	{	  
	  cout << A[d-k]<<"\n";
	  A[d-k]=-1;
	}
    }
  else
    {
      if(root->left) k_Dist(root->left, A,d+1,k);
      
      if(root->right) k_Dist(root->right, A,d+1,k);
    }
}

void All_k_distant_nodes_from_aLeaf(NODE *root,int k)
{
  int *A,depth;
  if(root)
    {
      depth=height(root);
      A=(int*)malloc((depth+1)*sizeof(int));
      k_Dist(root,A,0,k);
    }
}
void reverse(int *A, int i, int j)
{
  int t;
  while(i<j)
    {
      t=A[i];A[i]=A[j];A[j]=t;
      i++,j--;
    }
}
int size_of_tree(NODE *root)
{
  if(root)
    {
      return (size_of_tree(root->left)+size_of_tree(root->right)+1);
    }
  else return 0;
}
int print_path(NODE *root, int a, int b, int *A, int *index)
{//helping function
  int l, r, k;
  l=r=0;
  if(root->left) l=print_path(root->left,a,b,A,index);
  k=*index;
  if(root->right) r=print_path(root->right,a,b,A,index);

  //if(l<0)return l;
  //if(r<0) return r;
  if(!l && !r)
    {
      if(root->data==a || root->data==b) 
	{      
	  A[(*index)++]=root->data;return 1;
	}
      else return 0;
    }
  if(!r && l)
    {
      A[(*index)++]=root->data;
      if(root->data==a || root->data==b) return 0;
      else return 1;
    }
  if(!l && r)
    {
      A[(*index)++]=root->data;
      if(root->data==a || root->data==b){reverse(A,0,*index-1);return 0;}
      else return 1;
    }
  if(l && r)
     {
      A[(*index)++]=root->data;
      reverse(A,k,*index-1);
      return 0;
    }
}
void print_path_between_two_nodes(NODE *root, int a, int b)
{
  int n=0, index=0, i=0, *A;
  if(root)
    {
      n=size_of_tree(root);
      A=(int*)malloc(n*sizeof(int));
      memset(A,-1,n*sizeof(int));
      index=0;
      print_path(root,a,b,A,&index);
      for(i=0;A[i]!=-1;i++)	
	cout<< A[i]<< endl;; 	
    }
}

NODE* Next_right(NODE *root, int x, int *L, int level)
{
  NODE *l,*r;
  if(root->data==x){*L=level; return NULL;}
  if(*L && *L==level){*L=0; return root;}
  l=r=NULL;
  if(root->left) l=Next_right(root->left,x,L,level+1);
  if(l) return l;
  if(root->right) r=Next_right(root->right,x,L,level+1);
  return r;  
}
void Next_right_at_same_level(NODE *root, int x)
{
  int L;
  NODE* right;
  if(root)
    {
      L=0;
      if(right=Next_right(root,x,&L,1))
	cout << right->data<<endl;
      else cout <<-1<<endl;
    }
}


NODE* low_left_leaf(NODE *root, int level, int isLeaf, int *L, NODE **leaf)
{
  if(!root->left && !root->right && isLeaf) {if(*L<level) {*L=level,*leaf=root;}}
  if(root->left) low_left_leaf(root->left,level+1,1,L,leaf);
  if(root->right) low_left_leaf(root->right,level+1,0,L,leaf);
}
NODE* lowest_left_leaf(NODE *root)
{
  int L;
  NODE *leaf;
  if(root)
    {
      L=0;
      low_left_leaf(root,1,1,&L,&leaf);
      return leaf;
    }
  else return NULL;
}
void Extract(NODE** root, NODE **head, NODE **tail)
{//helping
  if(!(*root)->left && !(*root)->right)
    {
      if(*head){(*tail)->right=(*root);(*root)->left=*tail;*tail=(*root);}
      else *head=*tail=(*root);
      *root=NULL;
    }
  if((*root)->left) Extract(&((*root)->left),head,tail);
  if((*root)->right) Extract(&((*root)->right),head,tail);
}
NODE* Extract_leaves(NODE **root)
{//Erroneuos
  NODE *head=NULL,*tail=NULL;
  if(*root)
    {
      //if(!(*root)->left && !(*root)->right){head=*root;*root=NULL;return head;}
      Extract(root,&head,&tail);
      return head;
    }
  else return NULL;
}

NODE* Retain_sumPath_exceeding_K(NODE *root, int k)
{
  if(root)
    {
      k=k-root->data;
      if(k<=0) return root;
      if(!root->left && !root->right){free(root);return NULL;}
      if(root->left) root->left=Retain_sumPath_exceeding_K(root->left,k);
      if(root->right) root->right=Retain_sumPath_exceeding_K(root->right, k);
      if(!root->left && !root->right) {free(root);return NULL;}
      else return root;
    }
  else return NULL;
}
int Kth_largest(NODE *root, int k, int *count)
{
  int l,r;
  l=r=-1;
  if(root->right) r=Kth_largest(root->right,k,count);
  if(r!=-1) return r;
  (*count)++;
  if((*count)==k) return root->data;
  if(root->left) l=Kth_largest(root->left,k,count);
  if(l!=-1) return l;
  return -1;
}
int Kth_largest_in_BST(NODE *root, int k)
{
  int count=0;
  if(root && k>0)
    {
      return Kth_largest(root,k,& count);
    }
  else return -1;
}
NODE* Remove_all_half_nodes(NODE *root)
{
  NODE *temp=NULL;
  if(root)
    {
      if(!root->left && !root->right) return root;
      if(root->left && root->right)
	{
	  root->left=Remove_all_half_nodes(root->left);
	  root->right=Remove_all_half_nodes(root->right);
	  return root;
	}
      if(root->left) temp=Remove_all_half_nodes(root->left);
      else  temp=Remove_all_half_nodes(root->right);
      free(root);
      return temp;      
    }
  else return NULL;
}

int fun3(NODE *root, int *current)
{
  int l=0,r=0;
  if(root->right)
    {
      r=fun3(root->right,current);
      if(*current==0) return r;
    }

  (*current)--;
  if(*current==0) return root->data;

  if(root->left)
    {
      l=fun3(root->left,current);
      if(*current==0) return l;
    }

  return INT_MIN;
}
int kth_largest_element(NODE *root, int k)
{
  if(k<=0) return INT_MAX;
  if(!root) return INT_MIN;

  return fun3(root,&k);
}
int fun4(NODE *root, int flag)
{
  int total=0;
  if(!root->left && !root->right)
    {
      if(flag) return root->data;
      else return 0;
    }
  if(root->left) total+=fun4(root->left, 1);
  if(root->right) total+=fun4(root->right,0);
  return total;
}
int Sum_of_left_leaves(NODE *root)
{
  if(root)
    {
      return fun4(root,1);
    }
  else return 0;
}

NODE* remove_paths_of_less_then_k_length(NODE *root, int k)
{
  if(k<=1) return root;
  if(!root) return NULL;

  root->left=remove_paths_of_less_then_k_length(root->left,k-1);
  root->right=remove_paths_of_less_then_k_length(root->right, k-1);

  if(root->left || root->right) return root;
  else return NULL;
}

#include <map>

void fill_map(NODE *root, map<int,int> &m, int hd)
{
  map<int, int>::iterator it;
  it=m.find(hd);
  //cout << "("<<hd << "," << root->data <<"),";
  if(it!=m.end()) m.erase(it);
  m[hd]=root->data;

  if(root->left) fill_map(root->left, m, hd-1);
  if(root->right) fill_map(root->right, m, hd+1);
}
void bottom_view_using_map(NODE *root)
{
  int min_hd,max_hd,i;
  if(root)
    {
      min_hd=max_hd=0;
      min_max_HD(root,&min_hd,&max_hd,0);
      map<int,int> m;
      
      fill_map(root,m,0);
      
      for(int i=min_hd;i<=max_hd;i++)	
	cout <<m[i] <<", ";
      cout<<endl;
    }
}

int fun5(NODE *root, int level, int *leaf_level)
{
  int a,b,l1,l2;

  if(!root->left && !root->right){*leaf_level=level;return root->data;}
  if(root->left) a=fun5(root->left,level+1,&l1);
  if(root->right) b=fun5(root->right,level+1,&l2);

  if(root->left && root->right)
    {
      if(l1<=l2) {*leaf_level=l1; return a;}
      else       {*leaf_level=l2; return b;}
    }
  if(root->left) {*leaf_level=l1; return a;}
  if(root->right) {*leaf_level=l2; return b;}
}
int closest_leaf(NODE *root)
{
  int leaf_level;
  if(root)
    {
      return fun5(root,1,&leaf_level);
    }
  else return INT_MIN;
}
int h(int *A, int n , int i)
{
  if(A[i]==INT_MIN) {return 0;}
  else if(A[i]<0) return -A[i];
  else {A[i]=-(i+h(A,n,A[i]));return -A[i];}
}
int height_of_ParentArray_tree(int *A, int n)
{
  int i,max;
  for(i=0;i<n;i++) if(A[i]==-1) {A[i]=INT_MIN;break;}
  for(i=0;i<n;i++)
    {
      if(A[i]>=0)
	{
	  h(A,n,i);
	}
    }
  for(i=0,max=0;i<n;i++)
    {
      if(A[i]>max) max=A[i];
    }
  return A[i];
}
void SpecialLevelOrder_in_complete_binary_tree(NODE *root)
{//1,2,3,4,7,5,6,8,15,9,14. lowermost level is also completely full
  queue<NODE*> q;
  NODE *first,*second;
  if(root)
    {
      cout <<root->data<<", ";
      if(root->left) {q.push(root->left);q.push(root->right);}
      while(!q.empty())
	{
	  first=q.front();q.pop();
	  second=q.front();q.pop();
	  if(first->left)	    
	    {
	      q.push(first->left);
	      q.push(second->right);
	      q.push(first->right);
	      q.push(second->left);
	    }
	  cout << first->data <<", "<<second->data<<", ";
	}
      cout<<endl;
    }
}
int search(NODE *root, int x, int level)
{
  int l=-1,r=-1;
  if(!root) return -1;  
  if(root->data==x) return level;
  if(root->left) l=search(root->left,x,level+1);
  if(l>0) return l;
  if(root->right) r=search(root->right,x,level+1);
  return r;
}
int Lca_level(NODE *root, int a, int b, int level)
{
  int l=0,r=0;
  if(!root) return -1;
  
  if(root->data==a ||root->data==b) return level;

  l=r=-1;
  if(root->left) l=Lca_level(root->left,a,b,level+1);
  if(root->right) r=Lca_level(root->right,a,b,level+1);
  if(l>0 && r>0) return level;
  else if(l>0) return l;
  else if(r>0) return r;
  else return -1;
}
int Dist_between_two_nodes(NODE *root, int a , int b)
{
  int l=0,l1=0,l2=0;
  if(root)
    {
      if(a==b) return 0;

      l1=search(root,a,1);
      l2=search(root,b,1);
      if(l1==-1 ||l2==-1) return -1;
      l=Lca_level(root,a,b,1);
      return (l1-l)+(l2-l);
    }
  else return -1;
}

/******************************************/
int main()
{
  static int x=x++;
  NODE *root, *root2, *temp,*prev;
  int m,n,i,size,A[]={8,4,12,2,6,10,14,1,3,5,7,9,11,13,15,-1};//{5,1,6,3,4,2,8,7,-1};//{5,1,6,2,3,4,-1};
  int TREE[]={};
  size=sizeof(A)/sizeof(A[0])-1;
  root=create_BST(A,size);
  // for(i=0;i<size;i++) cout << A[i]<<", ";
  // cout <<endl;
  // temp=(NODE*)malloc(sizeof(NODE));temp->data=11;temp->left=temp->right=NULL;
  // root->left->right->right=temp;
  inorder(root);cout<<endl;  

  cout<<Dist_between_two_nodes(root,1,12)<<endl;


  //SpecialLevelOrder_in_complete_binary_tree(root);
  //bottom_view_using_map(root);

  // cout <<closest_leaf(root)<<endl;

  //OBinorder(remove_paths_of_less_then_k_length(root,5));
  //inorder(Remove_all_half_nodes(root));cout<<endl;
  // cout<<Sum_of_left_leaves(root);
  // cout<<endl;
  // root->right->right->left=(NODE*)malloc(sizeof(NODE));
  // root->right->right->left->data=11;
  // root->right->right->left->left=root->right->right->left->right=NULL;  
  // for(i=1;i<=size;i++)
  //   {
  //     cout <<Kth_largest_in_BST(root,i) <<",";
  //   }
  // cout <<endl;

  //root=Retain_sumPath_exceeding_K(root,29);
  // temp=Extract_leaves(&root);
  // for(prev=temp;prev->right;prev=prev->right); //cout << prev->data << ",";
  // for(;prev;prev=prev->left) cout << prev->data << " ";
  // cout <<endl;
  //inorder(root);cout<<endl;  
  // temp=lowest_left_leaf(root);
  // if(temp) cout << temp->data<<endl;
  // else cout << -1<<endl;
	 
  // for(i=0;i<size;i++)
  //   Next_right_at_same_level(root,A[i]);
  //print_path_between_two_nodes(root,6,9);
  //All_k_distant_nodes_from_aLeaf(root,2);
  //singleton_child(root);
  //cout << Max_leaf_path_sum(root)<<endl;
  //Diagonal_sum(root);
  //cout << sum_of_left_leaves(root)<<endl;
  // for(i=0;i<size;i++)
  //   {
  //     path_Array(root,A[i]);
  //     cout <<endl;
  //   }
  //cout << leaf_count(root)<<endl;
  //level_order_recly(root);
  //root=BT_to_DLL_inoreder(root);
  /*for(temp=root;temp;prev=temp,temp=temp->right)
    printf("%d ",temp->data);
  printf("\n");
  for(temp=prev;temp;temp=temp->left)
    printf("%d ",temp->data);
    printf("\n");*/
  //printf("%d\n",LCA_BT(root,1,9));
  //print_all_root_to_leaf_paths(root);
  // mirror(root);
  // inorder(root);cout<<endl;  
  //cout << height(root) <<height1(root)<<endl;
  // root2=make_bst();
  // for(i=0;A[i]!=-1;i++)
  //    insert_recly(&root2,A[i]);
  // inorder(root2);
  // root2->left->left->left->data=1;
  // cout<<endl;
  // cout<<identical(root,root2)<<endl;
}
