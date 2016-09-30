#include "header.h"
#include "inorder.c"
#include "preorder.c"
#include "postorder.c"

int main()
{
  node* root = create_tree();

  printf("PRINT TREE INORDER RECURSIVE:\n");
  inorder(root);

  printf("\n");
  return 0;
}
