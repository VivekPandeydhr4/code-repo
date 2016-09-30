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

void doubly_list_forward_print(node *head)
{
  node *tmp = NULL;
  
  for (tmp = head; tmp ; tmp = tmp->right)
    printf("%d ", tmp->data);
  printf("\n");
}

void doubly_list_backward_print(node *head)
{
  node *tmp = NULL;
  
  for (tmp = head; tmp ; tmp = tmp->left)
    printf("%d ", tmp->data);
  printf("\n");
}

int count_even_nodes(node* root)
{
  if (root)
    {
      int n1 = count_even_nodes(root->left);
      int n2 = count_even_nodes(root->right);
      
      if (root->data%2)
	return n1+n2;
      else
	{
	  printf("\n%d", root->data);
	  return n1+n2+1;
	}
    }
  else return 0;
}

int is_sibling(node *root, int n1, int n2)
{
  int x=-1;

  if (root)
    {
      if (root->left && root->right)
	{
	  if (((root->left->data == n1) && (root->right->data == n2)) || 
              ((root->left->data == n2) && (root->right->data == n1)))
	    {
	      return 1;
	    }
	  else
	    {
	      x = is_sibling(root->left, n1, n2);
	      if (x!=1)
		x = is_sibling(root->right, n1, n2);
	      return x;
	    }
	}
    }
  return 0;
}

void inorder_left(node* root, int flag)
{
  if (root)
    {
      inorder_left(root->left, 1);
      if(flag)
	printf("%d ",root->data);
      inorder_left(root->right, 0);
    }
}

int level(node* root, int n, int lvl)
{
  int x=-1;

  if(root)
    {
      if (root->data == n) return lvl;
      if (root->left)
	  x = level(root->left, n, lvl+1);
      if ((x==-1) && root->right)
	{
	  x = level(root->right, n, lvl+1);
	}
    }
  return x;
}

int is_same_level(node* root, int n1, int n2)
{
  /* Compare the level of both input data*/
}

void mirror_image(node* root)
{
  node* tmp=NULL;
  if (root)
    {
      tmp = root->left;
      root->left = root->right;
      root->right = tmp;
      
      mirror_image(root->left);
      mirror_image(root->right);
    }
}

node *lowest_comm_ancestor(node *root, int n1, int n2)
{
  if (root)
    {
      if((root->data > n1) && (root->data < n2) || 
	 (root->data > n2) && (root->data < n1))
	{
	  return root;
	}
      else if ((root->data > n1) && (root->data > n2))
	{
	  return lowest_comm_ancestor(root->left, n1, n2);
	}
      else if ((root->data < n1) && (root->data < n2))
	{
	  return lowest_comm_ancestor(root->right, n1, n2);
	}
    }
  return NULL;
}

node *to_inorder_doubly_list(node *root)
{
  node *hd1=root, *hd2=NULL;
  if (root)
    {
      if (root->left)
	hd1 = to_inorder_doubly_list(root->left);
      if (root->right)
	hd2 = to_inorder_doubly_list(root->right);
      
      node *tmp=NULL;
      for(tmp = hd1; (tmp != root) && (tmp->right); tmp = tmp->right);
      if (tmp && tmp !=root)
	{
	  tmp->right = root;
	  root->left = tmp;
	}
      if (hd2)
	{
	  hd2->left = root;
	  root->right = hd2;
	}
    }
  return hd1;
}

node *to_preorder_doubly_list(node *root)
{
  node *hd1=NULL, *hd2=NULL;
  if (root)
    {
      if (root->left)
	hd1 = to_preorder_doubly_list(root->left);
      if (root->right)
	hd2 = to_preorder_doubly_list(root->right);
      
      if (hd1 != NULL)
	{
	  node *tmp=NULL;
	  for(tmp = hd1; (tmp != root) && (tmp->right); tmp = tmp->right);
	  if (tmp && tmp !=root)
	    {
	      tmp->right = hd2;
	      if (hd2)
		hd2->left = tmp;
	    }
	  root->right = hd1;
	  hd1->left = root;
	}
      else
	{
	  if (hd2)
	    hd2->left = root;
	  root->right = hd2;
	}
      root->left = NULL;
    }
  return root;
}

node *to_postorder_doubly_list(node *root)
{
  node *hd1=root, *hd2=NULL;
  if (root)
    {
      if (root->left)
	hd1 = to_postorder_doubly_list(root->left);
      if (root->right)
	hd2 = to_postorder_doubly_list(root->right);
      
      node *tmp=NULL;
      if (hd1)
	{
	  for(tmp = hd1; (tmp != root) && (tmp->right); tmp = tmp->right);
	  if (tmp && tmp !=root)
	    {
	      tmp->right = hd2;
	      if (hd2)
		{
		  hd2->left = tmp;
		  for( ; (tmp != root) && (tmp->right); tmp = tmp->right);
		  if (tmp && tmp !=root)
		    {
		      tmp->right = root;
		      root->left = tmp;
		      root->right = NULL;
		    }
		}
	    }
	}
      else
	{
	   if (hd2)
	    {
	      hd1 = hd2;
	      for(tmp = hd1; (tmp != root) && (tmp->right); tmp = tmp->right);
	      if (tmp && tmp !=root)
		{
		  tmp->right = root;
		  root->left = tmp;
		  root->right = NULL;
		}
	    }
	   else
	     hd1 = root;
	}
    }
  return hd1;
}

int max(int a, int b, int c)
{
  int t;
  if (a > b)
    t = a;
  else 
    t = b;

  if (t > c)
    return t;
  else return c;
}

int max_wt_node(node *root)
{
  if (root)
    {
      int wr, wl, wrt;
      wr = root->data + ((root->left) ? root->left->data : 0) +
	((root->right) ? root->right->data : 0);

      if (root->left)
	wl = max_wt_node(root->left);

      if (root->right)
	wrt = max_wt_node(root->right);

      return (wr, wl, wrt);
    }
}

int is_BST(node *root)
{
  int x=1;

  if (root)
    {
      if (root->left)
	{
	  if (root->left->data < root->data)
	    x = 1;
	  else 
	    x = 0;
	}
      if (root->right)
	{
	  if (root->right->data > root->data)
	    x = 1;
	  else
	    x = 0;
	}
      
      x = is_BST(root->left);

      if (x) x = is_BST(root->right);
    }
  return x;
}
int main()
{
  /*****************************************/
  node* root = make_tree();
  printf("\n TREE INORDER:\n");                                                                                        
  inorder(root);
  printf("\n");                                                                                                                   
  /*****************************************/

  node *tmp=root;
  tmp->left->left->data = 25;
  printf("\n Now TREE INORDER:\n");                                                                                        
  inorder(root);
  printf("\n");                                                                                                                     
  printf("\n Tree is BST = %d\n", (is_BST(root)));

  // printf("\n Node of max wt = %d\n", max_wt_node(root)); // Programme Incomplete

  /* Programme incomplete
  printf("\n TREE POSTORDER:\n");                                                                                        
  postorder(root);
  printf("\n");                                                                                                                   

  printf("\n\t *** Postorder doubly linked list of tree ***\n");
  node *head =  to_postorder_doubly_list(root);
  doubly_list_forward_print(head);
  */

  /*
  printf("\n TREE PREORDER:\n");                                                                                        
  preorder(root);
  printf("\n");                                                                                                                   

  printf("\n\t *** Preorder doubly linked list of tree ***\n");
  node *head =  to_preorder_doubly_list(root);
  doubly_list_forward_print(head);
  */
  /*
  printf("\n\t\t *** Inorder doubly linked list of tree ***\n");
  node *head =  to_inorder_doubly_list(root);
  doubly_list_forward_print(head);
  */

  /*
  int n1=4, n2=11;
  node *tmp = lowest_comm_ancestor(root, n1, n2);
  printf("\nLCA of %d & %d = %d", n1, n2, (tmp) ? tmp->data : -1);
  */

  /*
  printf(" Mirror TREE INORDER:\n");                                                                                        
  mirror_image(root);
  inorder(root);
  printf("\n");                                                                                                                   
  */
  //  printf("\n No of Even nodes: %d\n", count_even_nodes(root));                                                                    
  //printf("\n Sibling = %s\n", is_sibling(root, 5, 15) ? "Yes" : "No");                                                            

  /*            
  printf("\n Print Left of his father\n");
  inorder_left(root, 1);
  */
  
  /*
  int lvl=0;
  int n=16;
  lvl = level(root, n, 0);
  if (lvl == -1)
    {
      printf("\n*** Node not found ***\n");
    }
  else
    {
      printf("\nLevel = %d\n", lvl);
    }
  */
  printf("\n\n");

  return 0;
}
