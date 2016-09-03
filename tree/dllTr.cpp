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
      if(tmp == head)
	{
	  printf("\nThis is Circular DLL\n");
	  break;
	}
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

/****************  T6  *******************
 **** BST to Inorder Doubly Circular LL****/
node* BST_2_Inorder_Circular_DLL(node* root)
{
  node *left, *right;
  node *toReturn, *temp;
  if(root)
    {
      left = root->left;
      right = root->right;
      root->left = root->right = root;
      toReturn = root;
      if(left)
	{
	  left = BST_2_Inorder_Circular_DLL(left);
	  root->right = left;
	  root->left = left->left;
	  left->left->right = root;
	  left->left = root;
	  toReturn = left;
	}
      if(right)
	{
	  right = BST_2_Inorder_Circular_DLL(right);
	  toReturn->left->right = right;
	  right->left->right = toReturn;
	  temp = toReturn->left;
	  toReturn->left = right->left;
	  right->left = temp;
	  return toReturn;
	}
    }
  else return NULL;
}

/************  T6  ****************
 **** BST to Inorder Doubly LL*******/
node* fun_BST_2_InDLL(node* root, node** tail)
{
  node* head = root;
  if(root->left)
    {
      head = fun_BST_2_InDLL(root->left, tail);
    }
  if(*tail) {(*tail)->right = root;}

  root->left = *tail;
  *tail = root;

  if(root->right)
    {
      fun_BST_2_InDLL(root->right, tail);
    }
  return head;
}
node* BST_2_InorderDLL(node* root)
{
  // return pointer will be the head of DLL

  if(root)
    {
      node* tail=NULL;
      return fun_BST_2_InDLL(root, &tail);
    }
  else return NULL;
}
/************  T7  ****************
 **** BST to Preorder Doubly *******/
node* fun_BST_2_PreorderDLL(node* root, node** tail)
{
  node *head, *lh, *rh, *lt, *rt, *tmp;
  head = *tail = root;
  tmp = root->right;

  if(root->left)
    {
      lh = fun_BST_2_PreorderDLL(root->left, &lt);
      root->right = lh;
      lh->left = root;
      root->left = NULL; head = root;
      *tail = lt;
    }
  if(tmp)
    {
      rh = fun_BST_2_PreorderDLL(tmp, &rt);
      (*tail)->right = rh;
      rh->left = *tail;
      (*tail) = rt;
    }
  return head;
}
node* BST_2_PreorderDLL(node* root)
{
  node* tail=NULL;
  if(root)
    {
      fun_BST_2_PreorderDLL(root, &tail);
    }
  else return NULL;
}

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


  node* head =BST_2_Inorder_Circular_DLL(root);
  printf("\n");
  print_Dll_fwd(head);

  /*
  printf("\n TREE PREORDER:\n");
  preorder(root);
  node* head = BST_2_PreorderDLL(root);
  printf("\n");
  print_Dll_fwd(head);

  node* head = BST_2_InorderDLL(root);
  printf("\n");
  print_Dll_fwd(head);
  */

  printf("\n");
  return 0;
}
