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
void print_all_root_to_leaf(node *root, lnode *head)
{
  if (root) 
    {
      head = add_node(head, root->data);
      if ((root->left == NULL) && (root->right == NULL))
	{
	  print_list(head);
	}
      print_all_root_to_leaf(root->left, head);
      print_all_root_to_leaf(root->right, head);
      delete_last_node(head);
    }
}
int main()
{
  /******************/
  node* root=NULL;
  root = init();
  /******************/
  lnode* head=NULL;
  
  printf("All root to leaf path \n");
  print_all_root_to_leaf(root, head);
    
  printf("\n");
  return 0;
}
