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

void print_Dll_fwd(node *head)
{
  node *tmp=NULL;

  tmp = head;
  while(tmp)
    {
      printf("%d ", tmp->data);
      tmp = tmp->right;
    }
  printf("\n");
}

void print_Dll_Bkwd(node *tail)
{
  node *tmp=NULL;

  tmp = tail;
  while(tmp)
    {
      printf("%d ", tmp->data);
      tmp = tmp->left;
    }
  printf("\n");
}

node *BST_to_DLL_inorder(node *root)
{
  node *left=NULL, *right=NULL;

  if (root)
    {
      left = BST_to_DLL_inorder(root->left);
      right = BST_to_DLL_inorder(root->right);
      if (left)
	{
	  node *tmp = left;
	  while(tmp->right)
	    tmp = tmp->right;
	  tmp->right = root;
	  root->left = tmp;
	}
      if (right)
	{
	  right->left = root;
	  root->right = right;
	}
    }
  if (left) return left;
  else return root;
}

node *BST_to_DLL_inorder_2(node *root, node **tail)
{
  node *hd1, *tl1, *hd2, *tl2, *head;
  
  if (root)
    {
      head = root; *tail = root;

      if (root->left)
	{
	  hd1 = BST_to_DLL_inorder_2(root->left, &tl1);
	  tl1->right = root;
	  root->left = tl1;
	  head = hd1;
	}
      if (root->right)
	{
	  hd2 = BST_to_DLL_inorder_2(root->right, &tl2);
	  hd2->left = root;
	  root->right = hd2;
	  *tail = tl2;
	}
      return head;
    }
  else return NULL;
}

node* fun(node *root)
{
  node *tail=NULL;

  return BST_to_DLL_inorder_2(root, &tail);
}

node *BST_to_DLL_preorder(node *root)
{
  node *left=NULL, *right=NULL;

  if (root)
    {
      left = BST_to_DLL_preorder(root->left);
      right = BST_to_DLL_preorder(root->right);
      if (left)
	{
	  node *tmp = left;
	  while(tmp->right)
	    tmp = tmp->right;
	  tmp->right = right;
	  if (right)
	    right->left = tmp;

	  left->left = root;
	  root->right = left;
	  root->left = NULL;
	}
      else 
	{
	  if (right)
	    right->left = root;
	}
    }
  return root;
}

node *BST_to_DLL_preorder_2(node *root, node **tail)
{
  node *hd1, *tl1, *hd2, *tl2, *head, *temp;
  
  if (root)
    {
      head = root; *tail = root;
      temp = root->right;
      if (root->left)
	{
	  hd1 = BST_to_DLL_preorder_2(root->left, &tl1);
	  root->right = hd1;
	  hd1->left = root;
	  *tail = tl1;
	}
      if (temp)
	{
	  hd2 = BST_to_DLL_preorder_2(temp, &tl2);
	  (*tail)->right = hd2;
	  hd2->left = *tail;
	  *tail = tl2;
	}
      return head;
    }
  else return NULL;
}

node* funpreorder(node *root)
{
  node *tail=NULL;

  return BST_to_DLL_preorder_2(root, &tail);
}

node *BST_to_DLL_postorder(node *root)
{
  node *left=NULL, *right=NULL, *head=NULL, *tmp=NULL;

  if (root)
    {
      left = BST_to_DLL_postorder(root->left);
      right = BST_to_DLL_postorder(root->right);

      if (left)
	{
	  tmp = left;
	  while (tmp->right) tmp = tmp->right;

	  tmp->right = right;
	  if (!right)
	    {
	      tmp->right = root;
	      root->left = left;
	    }
	  head = left;
	}
      if (right)
	{
	  tmp = right;
	  if (!left)
	    {
	      head = right;
	    }
	  else
	    {
	      right->left = tmp;
	    }

	  while(tmp->right)
	    tmp = tmp->right;

	  tmp->right = root;
	  root->left = tmp;
	  root->right = NULL;
	}
    }
  if (head) return head;
  else return root;
}

/*
node* fun3(node *root)
{
  node *tail=NULL;

}

node* 
*/
int main()
{
  /*****************************************/
  int arr[] = {15, 10, 18, 5, 13, 16, 19, 4, 3, 6, 11, 17, 22, 8, 20, 21};
  int arr1[] = {18, 16, 17};
  int size = sizeof (arr) / sizeof (int);
  node* root = make_tree(arr, size);
  printf("\n TREE INORDER:\n");
  inorder(root);
  printf("\n");
  /*****************************************/

  //node *head = BST_to_DLL_inorder(root);
  //node *head = fun(root);
  
  //preorder(root);
  //node *head = funpreorder(root);
  //node *head = BST_to_DLL_preorder(root);

  postorder(root);
  node *head = BST_to_DLL_postorder(root);
  printf("\n");
  print_Dll_fwd(head);  
  printf("\n");
  return 0;
}
