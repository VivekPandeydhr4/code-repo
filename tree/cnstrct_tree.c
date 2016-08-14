#include "header.h"
#include "inorder.c"

/************************************************************
  Construct a tree when inorder and preorder in given.
 ***********************************************************/
int search(int arr[], int start, int end, int value)
{
  int i;

  for(i=start; i<=end; i++)
    {
      if(arr[i] == value)
        return i;
    }
  return -1;
}  

node* buildTree_inodr_preodr(int inorder[], int preorder[], int inStart, int inEnd)	
{
  static int preIndx = 0;
    
  if (inStart > inEnd) return NULL;
  
  node* trNode = create_node(preorder[preIndx++]);
  
  if(inStart == inEnd) return trNode;

  int inIndx = search(inorder, inStart, inEnd, trNode->data);

  trNode->left = buildTree_inodr_preodr(inorder, preorder, inStart, inIndx-1);
  trNode->right = buildTree_inodr_preodr(inorder, preorder, inIndx+1, inEnd);

  return trNode;
}

node* buildTree_inodr_preodr_1(int inorder[], int preorder[], int inStart, int inEnd)
{
  static int preIndx = 0;
  int i, inIndx=-1;

  if(inStart > inEnd) return NULL;

  node* trNode = create_node(preorder[preIndx++]);

  if(inStart == inEnd) return trNode;

  for(i=inStart; i<=inEnd; i++)
    {
      if(inorder[i] == trNode->data)
	{
	  inIndx = i;
	  break;
	}
    }

  trNode->left = buildTree_inodr_preodr_1(inorder, preorder, inStart, inIndx-1);
  trNode->right = buildTree_inodr_preodr_1(inorder, preorder, inIndx+1, inEnd);
  return trNode;
}

/************************************************************                                                                       
  Construct a tree when inorder and postorder in given.                                                                             
***********************************************************/

node* buildTree_inodr_postodr(int inorder[], int postorder[], int inStart, int inEnd)
{
  static int postIndx = 11;//sizeof(inorder)/sizeof(inorder[0]);
  //  printf("value of postIndx : %d\n", postIndx);
  if (inStart > inEnd) return NULL;

  node* trNode = create_node(postorder[postIndx-- -1]);

  if(inStart == inEnd) return trNode;

  int inIndx = search(inorder, inStart, inEnd, trNode->data);

  trNode->right = buildTree_inodr_postodr(inorder, postorder, inIndx+1, inEnd);
  trNode->left = buildTree_inodr_postodr(inorder, postorder, inStart, inIndx-1);

  return trNode;
}

int main()
{
  int inodr[]   = {2, 5, 6, 8, 9, 10, 12, 13, 15, 16, 20};
  int preodr[]  = {10, 5, 2, 6, 8, 9, 15, 13, 12, 16, 20};
  int postodr[] = {2, 9, 8, 6, 5, 12, 13, 20, 16, 15, 10};

  int size = sizeof(inodr)/sizeof(inodr[0]);
  node* tree = NULL;
  //printf("value of Array : %d\n", size);
  // tree = buildTree_inodr_preodr(inodr, preodr, 0, size-1);
  
  // tree = buildTree_inodr_preodr_1(inodr, preodr, 0, size-1);

  tree = buildTree_inodr_postodr(inodr, postodr, 0, size-1);
  inorder(tree);
  printf("\n");
  return 0;
}
