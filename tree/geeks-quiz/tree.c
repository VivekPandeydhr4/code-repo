#include "tree.h"
#include "list.h"

node* init()
{
  /***********************************************************************/
  int arr[] = {15, 10, 18, 5, 13, 14, 16, 19, 4, 6, 11, 17, 22, 8, 20, 21};
  int size = sizeof (arr) / sizeof (int);
  int i=0; node* root=NULL;

  for (i=0; i<size; i++)
    root = insert_node(root, arr[i]);

  printf("Inorder Traversal ==> \n");
  inorder(root);
  /***********************************************************************/
  printf("\n");
  return root;
}

int leaf_count(node* root)
{
  if(root==NULL) return;
  if(root->left==NULL && root->right==NULL)
    return 1;
  return leaf_count(root->left) + leaf_count(root->right);

}

int is_BST(node* root)
{
  int isbst=1;
  if(root){//==NULL) return;
    if(((root->left) && (root->data < root->left->data))
     ||(root->right) && (root->data > root->right->data))
    {
      //isbst = 0;
      return 0;//isbst;
    }

  isbst = is_BST(root->left);
  if(isbst) isbst = is_BST(root->right);
  }
  return isbst;
}

void kth_distant_node(node *root, int k, int n)
{
  if(root)
    {
      if (n == k)
	printf("%d ", root->data);
      n++;
      kth_distant_node(root->left, k, n);
      kth_distant_node(root->right, k, n);
      n--;
    }
}
void kth_distant_node_2(node *root, int k)
{
  if(root)
    {
      if (k == 0)
	printf("%d ", root->data);
      kth_distant_node_2(root->left, k-1);
      kth_distant_node_2(root->right, k-1);
    }
}
void root_to_leaf_sum(node* root, int sum, int arr[], int size)
{
  if(root && (sum>=0))
    {
      arr[size++] = root->data;
      if (sum-root->data == 0)
	{
	  int i=0;
	  for(i=0; i<size; i++)
	    printf("%d ", arr[i]);
	}
      root_to_leaf_sum(root->left, sum-root->data, arr, size);
      root_to_leaf_sum(root->right, sum-root->data, arr, size);
      //      size--;
    }
}

void all_root_leaf_path(node* root, int arr[], int size)
{
  if(root)
    {
      arr[size++] = root->data;
      if(root->left==NULL && root->right==NULL)
	{
	  int i=0;
	  for(i=0; i<size; i++)
	    printf("%d ", arr[i]);
	  printf("\n");
	}
      all_root_leaf_path(root->left, arr, size);
      all_root_leaf_path(root->right, arr, size);
    }
  
}

node* kth_smallest(node* root, int k)
{
  node* tmp=NULL;
  if(root==NULL) return NULL;
  
  if(k == 0) return root;

  if (root->left)
    tmp = kth_smallest(root->left, k);
  //k--;
  if (root->right)
    if(!tmp) tmp = kth_smallest(root->right, k);
  k--;
  return tmp;
}

int tree_identical(node *r1, node *r2)
{
  int bool=1;
  
  if (r1 || r2)
    {
      if((r1 && !r2) || (!r1 && r2)
	 || ((r1 && r2) && (r1->data != r2->data)))
	{
	  return 0;
	}
      bool = tree_identical(r1->left, r2->left);
      if(bool) bool = tree_identical(r1->right, r2->right);
    }
  return bool;
}

void make_mirror (node* root)
{
  if(root)
    {
      node* tmp=root->left;
      root->left = root->right;
      root->right = tmp;
      make_mirror(root->left);
      make_mirror(root->right);
    }
}

int main()
{
  /******************/
  node* root=NULL;
  root = init();
  /******************/
  int num=0, flag=0;
  /******************/

  make_mirror(root);
  printf("\n Mirror Image=>\n");
  inorder(root);
  /*
  int arr1[] = {15, 10, 18, 5, 13, 14, 16, 19, 4, 6, 11, 17, 22, 8, 20, 21};
  int size = sizeof (arr1) / sizeof (int);
  int i=0; node* root2=NULL;

  for (i=0; i<size; i++)
    root2 = insert_node(root2, arr1[i]);

  printf("\nInorder Traversal of 2nd Tree ==> \n");
  inorder(root);
  printf("\nIs Indetical = %s \n", (tree_identical(root, root2))?"Yes":"No");
  */
  /*
  node* tmp=NULL;
  num=3;
  tmp = kth_smallest(root, num);
  if(tmp)
    printf("%d th node = %d",num,tmp->data);
  else
    printf("Not Found");
  */
  /*
  int arr[10] = {0};
  all_root_leaf_path(root, arr, 0);
  */
  /*
  int arr[10] = {0};
  int sum = 115;
  root_to_leaf_sum(root, sum, arr, 0);
  */
  /*
  int k=2;
  kth_distant_node_2(root, k);
  kth_distant_node(root, k, 0);
  */
  /*
  root->right->left->data = 6;
  flag = is_BST(root);
  printf("Is BST = %s \n", (flag)?"Yes":"No");
  */

  /*
  num = leaf_count(root);
  printf("Total leaf = %d \n", num);
  */
  printf("\n");
  return 0;
}
