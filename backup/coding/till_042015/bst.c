#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
  struct node *left;
  int data;
  struct node *right;
}NODE;
void levels(NODE *root, int k,int *l);
int Kth_largest(NODE *root, int k, int *d);
void inorder(NODE *root);
NODE* make_bst(void);
void insert(NODE** proot, int x);
void insert_recly(NODE **proot, int x);
int LCA_binaryTree(NODE *root, int a, int b, NODE **lca);
NODE* BST_from_Sorted_array(int A[], int S, int E);
NODE* Largest_BST(NODE *root, int *size, int *min, int *max);
void LeftView(NODE *root, int l, int *current);
void Child_sum_tree(NODE *root);
void Sum_greaterEqual_tree(NODE *root, int *sum);
void bottom_view(NODE *root);
int check_mirror(NODE *root1, NODE *root2);
void All_root_to_leaf_paths(NODE*root);
int distance(NODE *root, int a, int b, int l);
int k_distance_nodes(NODE *root, int a, int k, int l);
void alternate_mirroring(NODE *root);
NODE* Pre_In_to_BT(int *P1, int *P2, int *I1, int *I2);
NODE * Extract_leaves_as_DLL(NODE **root);
void print_k_sum_path(NODE *root, int k);
int closest_leaf(NODE *root, int k, int l,int *cl_leaf, int *cl_l_distance);

int MY_LCA(NODE *root, int a, int b);
NODE* lca(NODE *root, int a, int b);


int main()
{
  int size, min, max,c=-1,cl_d,cl_leaf;
  int m,k,i,A[]={5,3,7,2,4,6,8,1,9,-1},C[]={-5,-7,-3,-8,-6,-4,-2,-9,0,-1};
  int P[]={5,3,2,1,4,7,6,8,9},I[]={1,2,3,4,5,6,7,8,9};
  NODE *root,*l=NULL,*root2;

  //l=Pre_In_to_BT(P,P+8,I,I+8);
  root=make_bst();
  for(i=0;A[i]!=-1;i++)
     insert_recly(&root,A[i]);
  inorder(root);
  printf("\n");

  int a=4,b=6;
  c=MY_LCA(root,a,b);
  printf("LCA of %d & %d: %d\n",a,b,c);


  /* closest_leaf(root,5,1,&cl_leaf,&cl_d); */
  /* printf("%d:%d\n",cl_d,cl_leaf); */
  /* root->left->right->data=5; */
  /* root->right->left->data=1; */
  /* print_k_sum_path(root,13); */

  /* alternate_mirroring(root); */
  /* l=Extract_leaves_as_DLL(&root); */
  /* for(root2=l;root2;root2=root2->right) */
  /*   printf("%d ",root2->data); */
  /* printf("\n Rest of BST: ");  */
  /* inorder(root);  */
  printf("\n"); 
  
  //  levels(root,1,&k);
  //printf("%d\n",distance(root,4,9,1));
  //All_root_to_leaf_paths(root);

  /* printf("Enter the value of K(0 to stop): "); */
  /* do */
  /*   {       */
  /*     scanf("%d",&k); */
  /*     if(k<=0) {printf("Thank You to stop\n");break;} */
  /*     if(Kth_largest(root,k,&m)) printf("%dth Largest data:%d\n",k,m); */
  /*     else printf("Tree has less than %d elements\n",k); */
  /*   }while(1); */

  /* root2=make_bst(); */
  /* for(i=0;C[i]!=-1;i++) */
  /*    insert_recly(&root2,C[i]); */
  /* inorder(root2); */
  /* printf("\n"); */
  // bottom_view(root);
  /* m=0; */
  /* Sum_greaterEqual_tree(root,&m); */
  /* inorder(root); */
  //printf("%d\n",check_mirror(root,root2)); 
  /* root2=make_bst();  */
  /* for(i=0;C[i]!=-1;i++)  */
  /*    insert_recly(&root2,C[i]);  */
  //   inorder(l); 
  //printf("\n"); 

  /* printf("%d\n",isIdentical(root,root2)); */
  /* c=-1; */
  /* LeftView(root,0,&c); */
  /* Child_sum_tree(root); */
  /* inorder(root); */
  /* printf("\n"); */
  /* while(1) */
  /*   { */
  /* printf("Enter two values: "); */
  /* scanf("%d%d",&m,&n); */
  /* LCA_binaryTree(root,m,n,&lca); */
  /* printf("LCA of %d and %d is: %d\n", m,n,lca->data); */
  /*   } */
  return 0;
}
int search(NODE *root, int x)
{
  if(!root) return 0;
  if(root->data==x) return 1;
  if(root->left && search(root->left,x))  return 1;
  if(root->right && search(root->right,x)) return 1;
  return 0;
}

NODE *fun_lca(NODE *root, int a, int b)
{
   NODE *l,*r;
   if(root->data==a || root->data== b) return root;
   l=r=NULL;
   if(root->left) l=fun_lca(root->left,a,b);
   if(root->right) r=fun_lca(root->right,a,b);

   if(l && r) return root;
   if(!l && !r) return NULL;
   if(l) return l;
   else return r;
}

NODE* lca(NODE *root, int a, int b)
{
  
   if(!root) return NULL;
   if(!search(root,a)|| !search(root,b)) return NULL;
   return fun_lca(root,a,b);
}

int fun2(NODE *root, int a, int b, int *flag)
{
  int l=0,r=0,c=0,f1=0,f2=0;

  if(root->data==a || root->data==b) c=1;
  if(root->left) l=fun2(root->left,a,b,&f1);
  if(root->right) r=fun2(root->right,a,b,&f2);

  /* if(f1==2 || f2 == 2) {*flag==2; return l|r;} */
  /* if((f1 && f2) || (c && (f1 || f2))) {*flag=2; return root->data;} */

  /* if(!c && (f1||f2)) {*flag=1;return l|r;} */
  /* if(c && !(f1||f2))  {*flag=1;return root->data;} */
  /* if(!c && !f1 && !f2) {*flag=0;return 0;} */


  if(c) 
    {
      if(f1||f2) {*flag=2; return root->data;}
      else {*flag=1; return root->data;}
    }
  else
    {
      if(f1==2 || f2==2) {*flag=2;return l|r;}
      if(f1==1 && f2 == 1) {*flag=2;return root->data;}
      if(f1||f2) {*flag=1;return l|r;}
      *flag=0; return 0;      
    }
}
int MY_LCA(NODE *root, int a, int b)
{
  int flag,r;
  if(!root) return 0;

  r=fun2(root,a,b,&flag);
  if(flag==2) return r;
  else return 0;
}

int depth(NODE *root, int *leaf)
{
  int l1,l2,d1,d2;
  if(root)
    {
      if(!root->left && !root->right) {*leaf=root->data; return 1;}
      d1=depth(root->left,&l1);
      d2=depth(root->right,&l2);
      if(!d1 ) {*leaf=l2;return d2+1;}
      if(!d2 ) {*leaf=l1;return d1+1;}
      if(d1<=d2) {*leaf=l1;return d1+1;}
      else {*leaf=l2;return d2+1;}
    }
  else {return 0;}
}

int closest_leaf(NODE *root, int k, int l,int *cl_leaf, int *cl_l_distance)
{
  int d,k_level,cl_d1,leaf,cl_leaf1;
  if(root)
    {
      if(root->data==k)
	{	  
	  if(!root->left && !root->right)
	    {
	      *cl_leaf=root->data;*cl_l_distance=0; return l;
	    }
	  
	  *cl_l_distance=depth(root->left,&leaf);	  
	  (*cl_l_distance)-=1;
	  *cl_leaf=leaf;
	  return l;
	}
      else 
	{
	  if(root->left)
	    {
	      k_level=closest_leaf(root->left,k,l+1,&cl_leaf1,&cl_d1);
	      if(k_level)
		{
		  d=depth(root->right,&leaf);
		  if(d && k_level-l+d < cl_d1)
		    {
		      *cl_leaf=leaf;
		      *cl_l_distance=d+k_level-l;
		    }
		  else
		    {
		      *cl_leaf=cl_leaf1;
		      *cl_l_distance=cl_d1;
		    }
		  return k_level;
		}
	    }

	  if(root->right)
	    {
	      k_level=closest_leaf(root->right,k,l+1,&cl_leaf1,&cl_d1);
	      if(k_level)
		{
		  d=depth(root->left,&leaf);
		  if(d && k_level-l+d < cl_d1)
		    {
		      *cl_leaf=leaf;
		      *cl_l_distance=d+k_level-l;
		    }
		  else
		    {
		      *cl_leaf=cl_leaf1;
		      *cl_l_distance=cl_d1;
		    }
		  return k_level;
		}
	    }	  
	}
    }  
}
int height(NODE *root)
{
  int x=-1,y=-1;
  if(root)
    {
      x=height(root->left);
      y=height(root->right);
      x=x>=y?x:y;
      return x+1;
    }
  else return -1;
}
void f(NODE *root, int l,int k, int *A)
{
  int i;
  A[l]=root->data;
  k=k-root->data;
  if(!root->left && !root->right)
    {
      if(!k) {i=0; while(i<=l&&A[i]) printf("%d ",A[i++]);printf("\n"); }
    }
  else {if(root->left) f(root->left,l+1,k,A);
    if(root->right) f(root->right,l+1,k,A);}
  A[l]=0;
}
void print_k_sum_path(NODE *root, int k)
{
  int h,*A;
  if(root)
  {
    h=height(root);
    A=(int*)malloc((h+1)*sizeof(int));
    memset(A,0,sizeof(A));
    f(root,0,k,A);
  }
}
NODE* fun1(NODE *root, NODE **head, NODE **tail)
{
  if(!root->left &&!root->right)
    {
      if(*tail==NULL) *head=*tail=root;
      else{ (*tail)->right=root;root->left=*tail;*tail=root;}
      return NULL;
    }
  if(root->left) root->left=fun1(root->left,head,tail);
  if(root->right) root->right=fun1(root->right,head,tail);
  return root;
}

NODE * Extract_leaves_as_DLL(NODE **root)
{
  NODE *head,*tail;
  head=tail=NULL;
  if(!(*root)) return head;
  *root=fun1(*root,&head,&tail);
  return head;
}

NODE* Pre_In_to_BT(int *P1, int *P2, int *I1, int *I2)
{
  int *J;
  NODE *newnode;
  if(P1<=P2)
    {
      newnode=(NODE*)malloc(sizeof(NODE));
      newnode->data=*P1;
      for(J=I1;J<=I2;J++) if(*J==*P1) break;
      newnode->left=Pre_In_to_BT(P1+1,P1+(J-I1),I1,J-1);    
      newnode->right=Pre_In_to_BT(P1+(J-I1)+1,P2,J+1,I2);
      return newnode;
    }
  else return NULL;
}
void alt_mirror(NODE *root, int flag)
{
  NODE *temp;
  if(root)
    {
      if(flag){temp=root->left;root->left=root->right;root->right=temp;}
      alt_mirror(root->left,!flag);
      alt_mirror(root->right,!flag);
    }
}

void alternate_mirroring(NODE *root)
{
  alt_mirror(root,1);
}
void print_kth_level(NODE *root, int k)
{  
  if(root && k>=0)
    {
      print_kth_level(root->left, k-1);
      if(k==0) printf("%d ",root->data);
      print_kth_level(root->right, k-1);
    }
}


int k_distance_nodes(NODE *root, int a, int k, int l)
{
  int x=0,y=0;
  if(root)
    {
      if(root->data==a)
	{
	  print_kth_level(root,k);
	  return l;
	}
      if(root->left)
	{
	  x=k_distance_nodes(root->left,a,k,l+1);
	  if(x){
	    if(x-l==k) printf("%d ",root->data);
	  else if(x-l<k) print_kth_level(root->right,k-(x-l+1));
	  return x;}
	}
      if(root->right)
	{
	  y=k_distance_nodes(root->right,a,k,l+1);
	  if(y){
	  if(y-l==k) printf("root->data ");
	  else print_kth_level(root->left,k-(y-l+1));
	  return y;}
	}
      return 0;
    }
  return 0;
}

int distance(NODE *root, int a, int b, int l)
{
  int x=0,y=0;
  if(root)
    {
      if(root->left) x=distance(root->left,a,b,l+1);
      if(root->right) y=distance(root->right,a,b,l+1);
      if(!x && !y)
	{
	  if(root->data==a || root->data == b) return l;
	  else return 0;
	}
      else if(x && y) return (x+y-2*l);
      else
	{
	  if(root->data==a || root->data == b) return (x+y-l);
	  else return x+y;
	}
    }
  else return 0;
}

void levels(NODE *root, int k,int *l)
{
  if(root)
    {
      if(k>*l) *l=k;
      if(root->left) levels(root->left,k+1,l);
      if(root->right) levels(root->right,k+1,l);
    }
}
void fun(NODE *root, int *A, int k )
{
  int i;
  A[k]=root->data;
  if(root->left==NULL && root->right==NULL)
    {
      for(i=0;i<=k;i++)
	printf("%d ",A[i]);
      printf("\n");
    }
  if(root->left) fun(root->left,A,k+1);
  if(root->right) fun(root->right,A,k+1);
}

void All_root_to_leaf_paths(NODE*root)
{
  int l=0,*A;
  if(root)
    {
      levels(root,1,&l);
      A=(int*)malloc(l*sizeof(int));
      fun(root,A,0);
    }
}


int Kth_largest(NODE *root, int k, int *d)
{
  int x,y;
  if(root)
    {
      if(Kth_largest(root->right, k, &y)) {*d=y;return 1;}
      y--;
      if(!y) {*d=root->data;return 1;}
      if(Kth_largest(root->left,y,&x)){*d=x;return 1;}
      *d=x;
      return 0;
    }
  else {*d=k;return 0;}
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

int check_mirror(NODE *root1, NODE *root2)
{
  if(!root1 && !root2) return 1;
  if(root1 && root2)
    return (root1->data==(root2->data)*(-1) && check_mirror(root1->left, root2->right) && check_mirror(root1->right, root2->left)) ;
  
  
  else  return 0;
}


void Find_bottoms(NODE *root, int *L, int *D, int l , int hd, int min)
{
  if(root)
    {
      if(L[hd-min]<=l) {L[hd-min]=l;D[hd-min]=root->data;}
      if(root->left) Find_bottoms(root->left,L,D,l+1,hd-1,min);
      if(root->right) Find_bottoms(root->right,L,D,l+1,hd+1,min);
    }
}
void Min_Max_HD(NODE* root, int *min, int *max, int hd)
{
  int lmin,lmax,rmin,rmax;
  if(root)
    {
      *min=*max=hd;
      if(root->left)
	{
	  Min_Max_HD(root->left,&lmin,&lmax,hd-1);
	  *min=lmin;
	  if(lmax>hd)*max=lmax;
	}
      if(root->right)
	{
	  Min_Max_HD(root->right,&rmin,&rmax,hd+1); 
	  if(*min>rmin) *min=rmin;
	  if(*max<rmax) *max=rmax;
	}
    }
}
void bottom_view(NODE *root)
{
  int min,max,*L,*D,i;
  if(root)
    {
      Min_Max_HD(root,&min,&max,0);
      L=(int*)malloc((max-min+1)*sizeof(int));
      D=(int*)malloc((max-min+1)*sizeof(int));
      memset(L,-1,(max-min+1)*sizeof(int));
      Find_bottoms(root, L, D, 0, 0, min);
      for(i=0;i<max-min+1;i++) printf("%d ",D[i]);
      printf("\n");
    }
}
void Sum_greaterEqual_tree(NODE *root, int *sum)
{
  if(root)
    {
      Sum_greaterEqual_tree(root->right,sum);
      root->data+=(*sum);
      (*sum)=root->data;
      Sum_greaterEqual_tree(root->left,sum);
    }
}

int isSubset(NODE *r1,NODE *r2)
{
  if(!r2) return 1;
  if(!r1) return 0;
  if(isIdentical(r1,r2)) return 1;
  return (isSubset(r1->left,r2)||isSubset(r1->right,r2));
}
int isIdentical(NODE *r1, NODE *r2)
{
  if(!r1 && !r2) return 1;
  if(r1 && r2) return ((r1->data==r2->data)&&(isIdentical(r1->left,r2->left))&&(isIdentical(r1->right,r2->right)));
  return 0;
}
void Child_sum_tree(NODE *root)
{
  int l=0,r=0;
  if(root)
    {
      if(root->left)
	{l=root->left->data;Child_sum_tree(root->left);l+=root->left->data;}
      if(root->right)
	{r=root->right->data;Child_sum_tree(root->right);r+=root->right->data;}
      root->data=l+r;
    }
}


void LeftView(NODE *root, int l, int *current)
{
  if(root)
    {
      if(l>*current)
	{
	  printf("%d ",root->data);
	  (*current)++;
	}
      LeftView(root->left,l+1,current);
      LeftView(root->right,l+1,current);
    }
}



NODE* Largest_BST(NODE *root, int *size, int *min, int *max)
{
  int lsize,lmin,lmax,rsize,rmin,rmax;
  NODE *L=NULL,*R=NULL;
  lsize=rsize=0;
  if(root)
    {
      if(root->left) L=Largest_BST(root->left,&lsize,&lmin,&lmax);
      if(root->right) R=Largest_BST(root->right,&rsize,&rmin,&rmax);
      if(lsize==0 && rsize==0) { *size=1;*min=*max=root->data;return root;}
      if(lsize && rsize==0)	
	{
	  if(L==root->left && root->data >lmax){*size=lsize+1;*min=lmin;*max=root->data;return root;}
	  else {*size=lsize;*min=lmin;*max=lmax;return L;}
	}
      if(lsize==0 && rsize)
	{
	  if(R==root->right && root->data < rmin) {*size=rsize+1;*max=rmax;*min=root->data;return root;}
	  else {*size=rsize;*min=rmin;*max=rmax;return R;}
	}
      else
	{
	  if(L==root->left && R==root->right && root->data > lmax && root->data <=rmin)
	    { *size=lsize+rsize+1;*min=lmin;*max=rmax;return root;}
	  if(lsize >=rsize) {*size=lsize;*min=lmin;*max=lmax;return L;}
	  else {*size=rsize;*min=rmin;*max=rmax;return R;}
	}     
    }
  else {*size=0;*min=-1;*max=-1;return R;}
}
NODE* BST_from_Sorted_array(int A[], int S, int E)
{
  int mid;
  NODE *root;
  if(S<=E)
    {
      mid=S+(E-S)/2;
      root=(NODE*)malloc(sizeof(NODE));
      root->data=A[mid];
      root->left=BST_from_Sorted_array(A,S,mid-1);
      root->right=BST_from_Sorted_array(A,mid+1,E);
      return root;
    }
  return NULL;
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
  NODE *temp,*parent,*newnode=malloc(sizeof(NODE));
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
