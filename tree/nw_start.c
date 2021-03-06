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

node* delete_tree(node* root)
{
  if(root)
    {
      root->left = delete_tree(root->left);
      root->right = delete_tree(root->right);
      free(root);
    }
  return (node*)NULL;
}
/*
node* tier_2_circular_inorder_DLL(node* root)
{
  node *left=NULL, *right=NULL;

  left = root;
  if(root->left)
    {
      left = tier_2_circular_inorder_DLL(root->left);
      left->left->right = root;
      root->left = left->left;
      root->right = left;
      left->left = root;
    }
  if(root->right)
    {
      right = tier_2_circular_inorder_DLL(root->right);
      left->left->right = right;
      left->left = right->left;
      right->left->right = left;
      right->left->right = 
    }
}
*/

int size(node* root)
{
  int size1=1;
  if(!root) return 0;

  if(root->left) size1 += size(root->left);
  if(root->right) size1 += size(root->right);
  return size1;
}

int is_identical (node *root1, node* root2)
{
  if(!root1 && !root2) return 1;
  if(!root1 || !root2) return 0;

  return (root1->data == root2->data && is_identical(root1->left, root2->left) && is_identical(root1->right, root2->right));
}

int height(node* root)
{
  if(!root) return -1;
  return 1 + max(height(root->left), height(root->right));
}

void mirror(node* root)
{
  if(root)
    {
      mirror(root->left);
      mirror(root->right);
      node* tmp = root->left;
      root->left = root->right;
      root->right = tmp;
    }
}

int no_of_level(node* root)
{
  if(!root) return 0;
  return 1+max(no_of_level(root->left), no_of_level(root->right));
}

void print_paths(node* root, int* a, int i)
{
  int k;
  if(!root) {
    for(k=0; k<i; k++)
      printf("%d, ", a[k]);
    //printf("\n");
  }
  else{
  a[i] = root->data;
  print_paths(root->left, a, i+1);
  print_paths(root->right, a, i++);
  }
}
void print_all_root_to_leaf_path(node *root)
{
  int *a;
  if(root)
    {
      int level = no_of_level(root);
      a = (int*)malloc(sizeof(int)*level);
      print_paths(root, a, 0);
    }
}

void print_node_at_given_level(node* root, int level)
{
  if(root)
    {
      level--;
      if(level==0) printf("%d ", root->data);
      else{
	if(root->left) print_node_at_given_level(root->left, level);
	if(root->right) print_node_at_given_level(root->right, level);
      }
    }
}

void BFS2(node* root)
{
  if(root)
    {
      int level = no_of_level(root);
      int i;
      for(i=1; i<=level; i++)
	{
	  print_node_at_given_level(root, level);
	  printf("\n");
	}
    }
}

int one_is_mirror_of_other(node* r1, node* r2)
{
  if(!r1 && !r2) return 1;
  if(!r1 || !r2) return 0;
  if(r1->data != r2->data) return 0;

  return (one_is_mirror_of_other(r1->left, r2->right) ||
	  one_is_mirror_of_other(r1->right, r2->left));
}

void p2d(node* root, int level)
{
  if(root)
    {
      p2d(root->right, level+1);
      int i;
      for(i=0; i<level; i++)
	printf("    ");
      printf("%d\n", root->data);
      p2d(root->left, level+1);
    }
}

void p2d_print(node* root)
{
  int level = 0;
  if(root)
    {
      p2d(root, level);
    }
}

void sink_node(node* root)
{
  int t;
  if(root && root->data%2)
    {
      if(root->left && (root->left->data%2))
	{
	  t = root->data; 
	  root->data = root->left->data;
	  root->left->data = t; 
	  sink_node(root->left);
	}
      else if(root->right && (root->right->data%2))
	{
	  t = root->data;
	  root->data = root->right->data;
	  root->right->data = t;
	  sink_node(root->right);
	}
    }
}

void sink_BT(node* root)
{
  int t;
  if(root)
    {
      if(root->left)
	{
	  sink_BT(root->left);
	  if(root->data%2 && (root->left->data%2 == 0))
	    {
	      t = root->data;
	      root->data = root->left->data;
	      root->left->data = t;
	      sink_node(root->left);
	    }
	}
      if(root->right)
	{
	  sink_BT(root->right);
	  if(root->data%2 && (root->right->data%2==0))
	    {
	      t = root->data;
	      root->data = root->right->data;
	      root->right->data = t;
	      sink_node(root->right);
	    }
	}
    }
} 

void size_n_height(node* root, int* size, int* height)
{
  int lsize=0; int rsize=0; int rheight=0; int lheight=0;
  if(root)
    {
      if(root->left)
	size_n_height(root->left, &lsize, &lheight);
      if(root->right)
	size_n_height(root->right, &rsize, &rheight);
      (*size) = (lsize+rsize+1);
      (*height) = 1+(max(lheight, rheight));
    }
  else
    {
      *size = *height = 0;
    }
}

int density(node* root)
{
  int size=0, height=0;
  if(root)
    {
      size_n_height(root, &size, &height);
      if(height) return(size/height);
    }
  return 0;
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
	  toRet= (l+r);
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
//#####################################################################
int main()
{
  /*****************************************/
  node* root = make_tree1(); node* rt = make_tree1();
  printf("\n TREE INORDER:\n\n");  inorder(root); printf("\n\n");
  /*****************************************/

  p2d_print(root);

  printf("\n\n");
  print_k_distant_values(root, 5, 2);

  //  printf(" Tree Density = %d\n", density(root));

  /*
  node *p=NULL, *l=NULL, *r=NULL;
  p = create_node(1);
  l = create_node(2);
  r = create_node(3);
  p->left = l; p->right = r;
  printf("\n TREE INORDER:\n\n");  inorder(p); printf("\n\n");
  sink_BT(p);
  //sink_node(p);
  printf("\n TREE INORDER:\n\n");  inorder(p); printf("\n\n");
  */

  //  p2d_print(root);
  /*
  mirror(root);
  printf("\n Miror INORDER:\n");  inorder(root);

  printf("\n Is mirror  = %d", one_is_mirror_of_other(NULL, rt));
  */
  //  BFS2(root);

  //  print_all_root_to_leaf_path(root);
  /*
  printf("\n TREE INORDER:\n");  inorder(root);
  mirror(root);
  printf("\n Miror INORDER:\n");  inorder(root);
  */
  //  printf("\n Tree Height = %d", height(NULL));
  //printf("\n Is identical = %d", is_identical(root, rt));
  //printf("\n Tree Size = %d", size(root));

  /*
  node* n1 = create_node(6);
  node* n2 = create_node(5);
  node* n3 = create_node(8);
 
  printf("\n Node 1 = %p, data = %c", (void*)n1, n1->data);
  printf("\n Node 2 = %p, data = %c", (void*)n2, n2->data);
  printf("\n Node 3 = %p, data = %c", (void*)n3, n3->data);

  n1->left = n2;
  n1->right = n3;

  printf("\n TREE INORDER:\n");  inorder(n1);
  root = delete_tree(n1);
  printf("\n TREE INORDER:\n");  inorder(root);
  */

  //printf("\n TREE PREORDER:\n"); preorder(root);
  //printf("\n TREE POSTORDER:\n");  postorder(root);
  printf("\n\n");
  return 0;
}
