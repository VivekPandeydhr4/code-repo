#include "header.h"

void inorder(node* root)
{
  if(root)
    {
      inorder(root->left);
      printf("%d ",root->data);
      inorder(root->right);
    }
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

void postorder(node* root)
{
  if(root)
    {
      postorder(root->left);
      postorder(root->right);
      printf("%d ",root->data);
    }
}

node* remove_all_half_nodes(node* root)
{
  node* temp=NULL;
  if(root)
    {
      if (root->left)
	root->left=remove_all_half_nodes(root->left);
      if (root->right)
	root->right=remove_all_half_nodes(root->right);
      
      if(root->left && !root->right)
	{
	  temp = root->left;
	  free(root);
	  return temp;
	}
      if(!root->left && root->right)
	{
	  temp = root->right;
	  free(root);
	  return temp;
	}
      return root;
    }
  else return NULL;
}

node* fun(int arr[], int size, int *indx)
{
  node* nwroot=NULL;
  node *left, *right;
  if(size==0) return NULL;

  if (size%2 == 0)
    left = fun(arr, size/2-1, indx);
  else
    left = fun(arr, size/2, indx);

  nwroot = (node*) malloc (sizeof(node));
  nwroot->data = arr[*indx];(*indx)++;
  right = fun(arr, size/2, indx);
  nwroot->left = left;
  nwroot->right = right;

  return nwroot;
}

node* balanced_BST(int arr[], int size)
{
  int indx;
  if (size > 0)
    {
      indx = 0;
      return fun(arr, size, &indx);
    }
  else return NULL;
}

int fun1 (node* root, int *k)
{
  int l, r;
  if (root)
    {
      if (root->right)
	{
	  r = fun1(root->right, k);
	  if (*k==0) return r;
	}
      (*k)--;
      if(*k==0) return root->data;
      if(root->left)
	{
	  l = fun1(root->left, k);
	  if (*k==0) return l;
	}
      return -1;
    }
  return -1;
}

int kth_largest_In_BST(node* root, int k)
{
  if (k<=0 || !root) return -1;
  
  int x = fun1(root, &k);
  return x;
}

void floor_ceiling_Key(node *root, int k)
{
  node *tmp;
  int floor, ceil;
  tmp = root;
  floor = ceil = -1;
  while(tmp && tmp->data != k)
    {
      if (k < tmp->data)
	{
	  ceil = tmp->data;
	  tmp = tmp->left;
	}
      else
	{
	  floor = tmp->data;
	  tmp = tmp->right;
	}
    }
  if (tmp == NULL)
    printf("%d, %d", floor, ceil);
  else
    {
      if (tmp->left == NULL)
	printf("%d, ", floor);
      else
	{
	  tmp = tmp->left;
	  while(tmp->right)
	    tmp = tmp->right;
	  printf("%d, ", tmp->data);
	}
      if (tmp->right == NULL)
	printf("%d, ", ceil);
      else
	{
	  tmp = tmp->right;
	  while(tmp->left)
	    tmp = tmp->left;
	  printf("%d, ", tmp->data);
	}
    }
}
/*
int isCousin(node *root, int a, int b)
{
  if (!root) return 0;

  int x = funCousin(root, a, b);

  if (x == -1)
    return 1;
  else
    return 0;
}

int funCousin (node *root, int a, int b, int level)
{
  int l=0, r=0;

  if (root->left)
    l = funCousin(root->left, a, b, level+1);
  if (root->right)
    r = funCousin(root->right, a, b, level+1);

  if (root->data == a || root->data == b)
    {
      if (l || r) return 0;
      else return level;
    }
  if (l && r)
    {
      if ( l==r && l != level+1) return -1;
      else return 0;
    }
  if (l) return l;
  else return r;
  }*/

int isSumTree (node *root)
{
  if (!root) return 1;
  if (!root->left && !root->right) return 1;

  if (root->left && root->right)
    {
      return isSumTree(root->left) && isSumTree(root->right) &&
	(root->data == (root->left->data + root->right->data)*2);
    }
  if (root->left) return isSumTree(root->left) &&
		    (root->data == root->left->data*2);
  if (root->left) return isSumTree(root->left) &&
		    (root->data == root->left->data*2);
}

int funMPS (node *root, int *leftSum)
{
  int l=0, r=0;

  if (!root->left && !root->right)
    {
      *leftSum = root->data;
      return root->data;
    }
  if (root->left && root->right)
    {
      
    }
}

int maxPathSum(node *root)
{
  int leftSum=0;
  
  if (!root) return 0;

  return funMPS(root, &leftSum);
}

int size_BT(node* root)
{
  if(root)
    return 1+size_BT(root->left)+size_BT(root->right);
  else
    return 0;
}

int fun_sum_root_to_leaf(node* root, int sofar)
{
  int l=0, r=0;
  sofar = sofar+root->data;

  if(root->left)
    l = fun_sum_root_to_leaf(root->left, sofar*10);

  if(root->right)
    r = fun_sum_root_to_leaf(root->right, sofar*10);

  return l+r;
}

int total_sum_root_to_leaf(node* root)
{
  if(root)
    return fun_sum_root_to_leaf(root, 0);
  else
    return 0;
}

int main()
{
  /*****************************************/
  node* root = make_tree1();
  printf("\n TREE INORDER:\n");
  inorder(root);
  printf("\n");
  /*****************************************/

  node* testRt = create_node(9);
  testRt->left = create_node(3);
  testRt->right = create_node(1);
  testRt->left->left = create_node(5);
  testRt->left->right = create_node(3);
  testRt->right->left = create_node(2);
  printf("\n Print Test TREE INORDER:\n");
  inorder(testRt);
  int TotalSum = total_sum_root_to_leaf(testRt);
  printf("\nTotal Sum root to leaf = %d", TotalSum);









  
  //int sizeBT = size_BT(root);
  //printf("\n\tSize of BT = %d", sizeBT);

  
  //  printf(" Is Cousin = %s \n", (isCousin(root, 3, 5)?"Yes":"No"));
  //  floor_ceiling_Key(root, 4);
  /*
  int k = 12;
  int n = kth_largest_In_BST(root, k);
  printf("%d th largest element = %d", k, n);

  /*int In[] = {4, 5, 6, 8, 10, 11, 13, 15, 16, 17, 18, 19, 20, 21, 22};
  int size = sizeof(In)/sizeof(In[0]);

  node* nwroot = balanced_BST(In, size);
  inorder(nwroot);
  
  node* nwroot = remove_all_half_nodes(root);
  inorder(nwroot);
  */
  /*  
  printf("\n TREE PREORDER:\n");
  preorder(root);

  printf("\n TREE POSTORDER:\n");
  postorder(root);
  */

  printf("\n\n");
  return 0;
}


