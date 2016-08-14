#include "header.h"
#include "level_by_level.c"

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

void general(node *root)
{
  printf("\n TREE INORDER:\n");                                                                                        
  inorder(root);
  printf("\n");                                                                                                                   
  printf("\nPRINT TREE LEVEL BY LEVEL:\n");                                                                                           
  print_level_by_level(root);
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

      return max(wr, wl, wrt);
    }
}

int is_symmetric(node *r1, node *r2)
{
  int x=1;

  if ((r1 && (!r2)) || (r2 && (!r1)))
  {
     return 0;
  }
  if ((!r1) && (!r2))
  {
    return 1;
  }
  x = is_symmetric(r1->left, r2->left);

  if (x) x = is_symmetric(r1->right, r2->right);

  return x;
}

int is_BST(node *root)
{
  int x = 1;

  if(root)
  {
     if (root->left)
     {
         if (root->left->data < root->data)
         {
             x = is_BST(root->left);
         }
         else
         {
             x = 0;
         } 
     }
     if (x && root->right)
     {
         if (root->right->data > root->data)
         {
             x = is_BST(root->right);
         }
         else
         {
            x = 0;
         }
     }  
  }
  return x;
}

int nth_min(node* root, int *n)
{
    	int x=0; 
	if (!root && n<0)
  	{
     	return -1;
  	}
 
	if (root->left) 
    	  x = nth_min(root->left, n);
						 		 
  	if (--(*n)==0)
  	{
     	  x = root->data;
  	}
  
	if ((!x) && (root->right))
  		x = nth_min(root->right, n);
     return x;
}

int nth_max(node* root, int *n)
{
    	int x=0; 
	if (!root && n<0)
  	{
     	return -1;
  	}
 
	if (root->right) 
    	  x = nth_max(root->right, n);
						 		 
  	if (--(*n)==0)
  	{
     	  x = root->data;
  	}
  
	if ((!x) && (root->left))
  		x = nth_max(root->left, n);
     return x;
}

void print_left_view(node *root)
{
   if (root)
   {
      printf("%d ", root->data);
      if (root->left)
         print_left_view(root->left);
      else
         print_left_view(root->right);
   }
}

void print_right_view(node *root)
{
   if (root)
   {
      printf("%d ", root->data);
      if (root->right)
         print_right_view(root->right);
      else
         print_right_view(root->left);
   }
}

void print_BottomUp_right_view(node *root)
{
   if (root)
   {
      if (root->right)
         print_BottomUp_right_view(root->right);
      else
         print_BottomUp_right_view(root->left);
      if (root->left || root->right)
         printf("%d ", root->data);
   }
}

void printf_leaf(node *root)
{
  if (root)
  {
     printf_leaf(root->left);
     if (!root->left && !root->right)
        printf("%d ", root->data);
     printf_leaf(root->right);
  }
}

void print_TopDown_left_view(node *root)
{
   if (root)
   {
      if (root->left || root->right)
         printf("%d ", root->data);
      if (root->left)
         print_TopDown_left_view(root->left);
      else
         print_TopDown_left_view(root->right);
   }
}

void print_boundary(node *root)
{
  if (root)
  {
      print_TopDown_left_view(root);
      printf_leaf(root);
      print_BottomUp_right_view(root->right);
  }
}

void print_boundary_single_traverse(node *root, int left, int right)
{
   if (root)
   {
      if (right == 0)
         printf("%d ", root->data);
      print_boundary_single_traverse(root->left, left+1, right);
	
      if ((!root->left) && (!root->right) && right>0)
         printf("%d ", root->data);
	
      print_boundary_single_traverse(root->right, left, right+1);
      if (left==0)
      {
          if (right != 0)
              printf("%d ", root->data);
      }
   }
}

int main()
{
  /***************************/
  node* root = make_tree();
  general(root); 
  /***************************/

  
        /** 19 **/
  /*
  printf("Boundary Node of Tree:\n");
  print_boundary(root);
  */ 
        /** 18 **/ //Programme incomplete
  /*
  printf("\nBoundary Node of Tree in single traverse:\n");
  print_boundary_single_traverse(root, 1, 0);
  */
        /** 17 **/
  /*
  printf("Leaf Node of Tree:\n");
  printf_leaf(root);
  */
        /** 16 **/
  /*
  printf("Bottom Up Right view if Tree:\n");
  print_BottomUp_right_view(root);
  */
        /** 15 **/
  /*
  printf("Right view of Tree:\n");
  print_right_view(root);
  */
        /** 14 **/
  /*
  printf("Left view of Tree:\n");
  print_left_view(root);
  */
        /** 13 **/
  /*
  int n=1;
  printf("%d is %dth Maximum Element \n", nth_max(root, &n), n); 
  */
        /** 12 **/
  /*
  int n=15;
  printf("%d is %dth Minimum Element \n", nth_min(root, &n), n); 
  */
        /** 11 **/
 /* 
   root->left->left->data = 100;
   printf("\n Now TREE INORDER:\n");                                                                                        
   inorder(root);
   printf("\n");                                                                                                                   
   printf("\nPRINT TREE LEVEL BY LEVEL:\n");                                                                                           
   print_level_by_level(root);
   printf("\nIs BST = %d\n", is_BST(root));
  */
        /** 10 **/
/*
   printf("\nPRINT TREE LEVEL BY LEVEL:\n");                                                                                           
   print_level_by_level(root);
   
   printf("\nIs Symmetric = %d", is_symmetric(root->left, root->right));
*/

        /** 9 **/
  printf("\n Node of max wt = %d\n", max_wt_node(root)); //incomplete programme

        /** 8 **/
  /* Programme incomplete
  printf("\n TREE POSTORDER:\n");                                                                                        
  postorder(root);
  printf("\n");                                                                                                                   

  printf("\n\t *** Postorder doubly linked list of tree ***\n");
  node *head =  to_postorder_doubly_list(root);
  doubly_list_forward_print(head);
  */

        /** 7 **/
  /*
  printf("\n TREE PREORDER:\n");                                                                                        
  preorder(root);
  printf("\n");                                                                                                                   

  printf("\n\t *** Preorder doubly linked list of tree ***\n");
  node *head =  to_preorder_doubly_list(root);
  doubly_list_forward_print(head);
  */
        /** 6 **/
  /*
  printf("\n\t\t *** Inorder doubly linked list of tree ***\n");
  node *head =  to_inorder_doubly_list(root);
  doubly_list_forward_print(head);
  */

        /** 5 **/
  /*
  int n1=4, n2=11;
  node *tmp = lowest_comm_ancestor(root, n1, n2);
  printf("\nLCA of %d & %d = %d", n1, n2, (tmp) ? tmp->data : -1);
  */

        /** 4 **/
  /*
  printf(" Mirror TREE INORDER:\n");                                                                                        
  mirror_image(root);
  inorder(root);
  printf("\n");                                                                                                                   
  */
        /** 3 **/
  //  printf("\n No of Even nodes: %d\n", count_even_nodes(root));                                                                    
        /** 1 **/
  //printf("\n Sibling = %s\n", is_sibling(root, 5, 15) ? "Yes" : "No");                                                            

        /** 2 **/
  /*            
  printf("\n Print Left of his father\n");
  inorder_left(root, 1);
  */
  
        /** 1 **/
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
