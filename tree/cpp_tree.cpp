#include <iostream>
#include <stack>
#include <queue>
#include "header.h"

using namespace std;

void inorder(node* root)
{
  if(root)
    {
      inorder(root->left);
      printf("%d ",root->data);
      inorder(root->right);
    }
}

int tree_height_iterarively(node *root)
{
  stack <node*> s;

  if (!root) return -1;
  node *temp=root; int height=-1, max=-1;

  while(1)
    {
      while(temp)
	{
	  s.push(temp);
	  height++;
	  if (height>max) max = height;
	  temp = temp->left;
	}
      if (s.empty()) return max;
      temp = s.top();
      s.pop();
      height--;
      temp = temp->right;
    }
}

void fun_1(queue <node*> q1)
{
  node *tmp, *t;
  queue <node*> q2;

  if(!q1.empty())
    {
      tmp = q1.front();
      
      do
	{
	  t = q1.front();
	  q1.pop();
	  if(t->left) q2.push(t->left);
	  if(t->right) q2.push(t->right);
	  q1.push(t);
	}while(q1.front() != tmp);
    }
  fun_1(q2);

  while(!q1.empty())
    {
      t = q1.front();
      q1.pop();
      cout << t->data << " " << endl;
    }
}

void reverse_level_order_traversal(node *root)
{
  queue <node*> q1;
  
  if (root)
    {
      q1.push(root);
      fun_1(q1);
    }
}
int main()
{
  /*****************************************/
  node* root = make_tree();
  printf("\n TREE INORDER:\n");
  inorder(root);
  printf("\n");
  /*****************************************/

  reverse_level_order_traversal(root);
  //  printf("Height = %d", tree_height_iterarively(root));
  printf("\n\n");
  return 0;
}
